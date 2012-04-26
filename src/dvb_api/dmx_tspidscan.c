/*
$Id: dmx_tspidscan.c,v 1.23 2006/01/02 18:23:59 rasc Exp $


 DVBSNOOP
 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Brute force scan all pids on a transponder
 -- scanpids principle is based on the sourcefile getpids.c from 'obi'



$Log: dmx_tspidscan.c,v $
Revision 1.23  2006/01/02 18:23:59  rasc
just update copyright and prepare for a new public tar ball

Revision 1.22  2005/11/08 23:15:25  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.21  2005/09/06 23:13:51  rasc
catch OS signals (kill ...) for smooth program termination

Revision 1.20  2005/08/22 22:37:59  rasc
ATSC frontend info

Revision 1.19  2005/08/17 21:18:18  rasc
improvements on pidscan

Revision 1.18  2004/10/12 20:37:47  rasc
 - Changed: TS pid filtering from file, behavior changed
 - New: new cmdline option -maxdmx <n>  (replaces -f using pidscan)
 - misc. changes

Revision 1.17  2004/09/01 20:20:34  rasc
new cmdline option: -buffersize KB  (set demux buffersize in KBytes)

Revision 1.16  2004/04/05 17:32:13  rasc
mass typo fix adaption --> adaptation

Revision 1.15  2004/01/31 01:24:26  rasc
PIDSCAN  redesign,
try to show pid content  (PES streamID, SECTION tableID)

Revision 1.14  2004/01/13 21:04:20  rasc
BUGFIX: getbits overflow fixed...

Revision 1.13  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured

Revision 1.12  2004/01/02 00:00:37  rasc
error output for buffer overflow

Revision 1.11  2004/01/01 20:09:23  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.10  2003/12/28 14:00:26  rasc
bugfix: section read from input file
some changes on packet header output

Revision 1.9  2003/12/15 22:41:28  rasc
pidscan improved, problems with max filters on demux

Revision 1.8  2003/12/15 22:29:27  rasc
pidscan improved, problems with max filters on demux

Revision 1.7  2003/12/15 20:09:48  rasc
no message

Revision 1.6  2003/12/14 18:29:56  rasc
no message

Revision 1.5  2003/12/10 23:18:10  rasc
improve pidscan

Revision 1.4  2003/12/10 20:07:15  rasc
minor stuff

Revision 1.3  2003/12/09 20:34:23  rasc
transponder pid-scan improved (should be sufficient now)

Revision 1.2  2003/12/09 18:27:48  rasc
pidscan on transponder

Revision 1.1  2003/12/07 23:36:13  rasc
pidscan on transponder
- experimental(!)


*/






#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <unistd.h>



#include "dvbsnoop.h"
#include "strings/dvb_str.h"
#include "misc/cmdline.h"
#include "misc/helper.h"
#include "misc/output.h"
#include "misc/sig_abort.h"

#include "dvb_api.h"
#include "dmx_error.h"
#include "dmx_tspidscan.h"




/*
 * some definition
 */

// min. buffer collect time before read/poll
// has to be below timeouts!!!
#define PID_TIME_WAIT		100

// timeout in ms
// TimoutHIGH will be used on PIDs < 0x20
#define PID_TIMEOUT_LOW		(250 - PID_TIME_WAIT)
#define PID_TIMEOUT_HIGH	(30100 - PID_TIME_WAIT)

// max filters (will be checked dynamically)
#define MAX_PID_FILTER		256

// highest pid
#define MAX_PID                 0x1FFF

#define TS_LEN			188
#define TS_SYNC_BYTE		0x47
#define TS_BUF_SIZE		(TS_LEN * 2048)		/* fix buffer size */



enum TS_TYPE {		// TS Content
		TS_NOPID, TS_SECTION, TS_PES, TS_ERROR,
		TS_SCRAMBLED, TS_STUFFING, TS_UNKNOWN
};

typedef struct _TS_PID {
	int	count;
	int     type;
	int     id;
} TS_PID;


static TS_PID *pidArray;


static int    analyze_ts_pid (u_char *buf, int len);
static TS_PID *ts_payload_check (u_char *b, int pid, TS_PID *tspid);





int ts_pidscan (OPTION *opt)
{
  // $$$ TODO   buffersize-option?
  u_char 	buf[TS_BUF_SIZE];
  struct pollfd pfd;
  struct dmx_pes_filter_params flt;
  int 		*dmxfd;
  int 		timeout;
  int 		timeout_corr;
  int		pid,pid_low;
  int    	i;
  int		filters;
  int		max_pid_filter;
  int		pid_found;
  int		rescan;




   indent (0);

   out_nl (2,"");
   out_nl (2,"---------------------------------------------------------");
   out_nl (2,"Transponder PID-Scan...");
   out_nl (2,"---------------------------------------------------------");



   //  -- max demux filters to use...
   max_pid_filter = MAX_PID_FILTER;
   if (opt->max_dmx_filter > 0) max_pid_filter = opt->max_dmx_filter;	// -maxdmx opt


   // alloc pids
   pidArray = (TS_PID *) malloc ( (MAX_PID+1) * sizeof(TS_PID) );
  	if (!pidArray) {
		IO_error("malloc");
		return -1;
	}

  	for (i=0; i <= MAX_PID ; i++)  {
		(pidArray+i)->count = 0;
		(pidArray+i)->type  = TS_NOPID;
	}


   dmxfd = (int *) malloc(sizeof(int) * MAX_PID_FILTER);
	if (!dmxfd) {
		free (pidArray);
		IO_error("malloc");
		return -1;
	}

	for (i = 0; i < max_pid_filter; i++)
		dmxfd[i] = -1;



   pid = 0;
   while ( (pid <= MAX_PID) && !isSigAbort() )  {

	pid_low = pid;
	timeout_corr = 0;
	rescan = 0;

	do {
		pid = pid_low;
	   
		// -- open DVR device for reading
	   	pfd.events = POLLIN | POLLPRI;
   		if((pfd.fd = open(opt->devDvr,O_RDONLY|O_NONBLOCK)) < 0){
			IO_error(opt->devDvr);
			free (pidArray);
			free (dmxfd);
			return -1;
   		}


		// -- set multi PID filter
		// -- try to get as many dmx filters as possible
		// -- error messages only if filter 0 fails

		filters = 0;
		for (i = 0; (i < max_pid_filter) && (pid <= MAX_PID); i++) {
			if (dmxfd[i] < 0) {
				if ((dmxfd[i]=open(opt->devDemux,O_RDWR)) < 0)  {
					// -- no filters???
					if (i == 0) IO_error(opt->devDemux);
					break;
				}
			}

			// -- default buffer should be sufficient
			// ioctl (dmxfd[i],DMX_SET_BUFFER_SIZE, sizeof(buf));

			// -- skip already scanned pids (rescan-mode)
			while ( ((pidArray+pid)->type != TS_NOPID) && (pid < MAX_PID) ) pid++;
	
			flt.pid = pid;
			flt.input = DMX_IN_FRONTEND;
			flt.output = DMX_OUT_TS_TAP;
			flt.pes_type = DMX_PES_OTHER;
			flt.flags = DMX_IMMEDIATE_START;
			if (ioctl(dmxfd[i], DMX_SET_PES_FILTER, &flt) < 0) {
				if (i == 0) IO_error("DMX_SET_PES_FILTER");
				break;
			}
			pid ++;
			filters ++;
		}




		// -- ieek, no dmx filters available???
		// -- there is something terribly wrong here... - abort
		if (filters == 0) {

			pid = MAX_PID+1;	// abort criteria for loop

		} else {


			// -- calc timeout;
			// -- on lower pids: higher timeout
			// -- (e.g. TOT/TDT will be sent within 30 secs)

			timeout =  (opt->timeout_ms) ? opt->timeout_ms : PID_TIMEOUT_LOW;
			if ( (pid_low) < 0x20) timeout = PID_TIMEOUT_HIGH;


			if (rescan) out (8,"re-");
			out (8,"scanning pid   0x%04x to 0x%04x",pid_low, pid-1);
			out (9,"  (got %d dmx filters) ",filters);
			out_NL (8);


			// give read a chance to collect _some_ pids
			usleep ((unsigned long) PID_TIME_WAIT * 1000);

			pid_found = 0;
			if (poll(&pfd, 1, timeout) > 0) {
				if (pfd.revents & POLLIN) {
					int len; 
					len = read(pfd.fd, buf, sizeof(buf));
					if (len >= TS_LEN) {
						pid_found = analyze_ts_pid (buf, len);
					}
				}
			}
	

			// rescan should to be done?
			if (pid_found) {
			  rescan++;
			  if (rescan > filters ) rescan = 0;	// abort rescans (if no TS-PUSI)
			} else {
			  rescan = 0;	
			}

		} // if (filters==0)


		// -- close dmx, filters
		for (i = 0; i < max_pid_filter; i++) {
			if (dmxfd[i] >= 0) {
				ioctl(dmxfd[i], DMX_STOP);  // ignore any errors
				close(dmxfd[i]);
				dmxfd[i] = -1;
			}
		}


		close(pfd.fd);

	} while (rescan);


	// -- output
	for (i = pid_low; i < pid; i++) {
		TS_PID *p = pidArray+i;

		if ( p->count > 0) {
			out (1,"PID found: %4d (0x%04x)  ",i,i);

			switch  (p->type) {
				case TS_SECTION:
					out (3,"[SECTION: %s]",dvbstrTableID(p->id) );
					break;

				case TS_PES:
					out (3,"[PS/PES: %s]",dvbstrPESstream_ID(p->id) );
					break;

				case TS_STUFFING:
					out (3,"[stuffing]");
					break;

				case TS_ERROR:
					out (3,"[packet error]");
					break;

				case TS_SCRAMBLED:
					out (3,"[scrambled]");
					break;

				case TS_UNKNOWN:
				default:
					out (3,"[unknown]");
					break;
			}
			out_NL (1);
		}

	}


   } // while



  free (dmxfd);
  free (pidArray);
  return 0;

}



static int analyze_ts_pid (u_char *buf, int len)
{
	int  i;
	int  pid;
	int  found = 0;

	// find TS sync byte...
	// SYNC ...[188 len] ...SYNC...
	
	for (i=0; i < len; i++) {
		if (buf[i] == TS_SYNC_BYTE) {
		   if ((i+TS_LEN) < len) {
		      if (buf[i+TS_LEN] != TS_SYNC_BYTE) continue;
		   }
		   break;
		}
	}
	// $$$ TODO: sync output report?

	for (; i < len; ) {
		if (buf[i] == TS_SYNC_BYTE) {
			TS_PID *pa;

			pid	 = getBits (buf, i, 11, 13);

			pa = (pidArray+pid);
			pa->count++;
			if ( (pa->type == TS_NOPID) || (pa->type == TS_UNKNOWN) ) {
				found = 1;
				ts_payload_check (buf+i, pid, pa);
			}

			i += TS_LEN;

		} else {
			i++;	// no sync on byte
		}
	}


  	return found;
}






static TS_PID *ts_payload_check (u_char *b, int pid, TS_PID *tspid)
{

	// $$$ TODO speedup by b[1] & 0x80  or  & 0x40;
  	int err_bit 		= getBits (b, 0, 8, 1);
	int payload_start 	= getBits (b, 0, 9, 1);
	int scrambled		= getBits (b, 0,24, 2);


	if (err_bit) {
		return (TS_PID *) NULL;
	}

	if (scrambled) {
		tspid->type = TS_SCRAMBLED;
		return tspid;
	}

	if (payload_start != 0) {
		int j;
  		int adaptation_field_ctrl	= getBits (b, 0,26, 2);

		tspid->type = TS_UNKNOWN;
		j = 4;
		if (adaptation_field_ctrl & 0x2)  j += b[j] + 1;	// add adapt.field.len

		if (adaptation_field_ctrl & 0x1) {
			if (b[j]==0x00 && b[j+1]==0x00 && b[j+2]==0x01) {
				// -- PES/PS
				tspid->type = TS_PES;
				tspid->id   = b[j+3];
			} else {
				// -- section (eval pointer field)
				int offset = j + b[j] +1;
				tspid->type = TS_SECTION;
				tspid->id   = b[offset];
			}
			return tspid;
		}

		return tspid;
	}

	if (pid == 0x1FFF) {
		tspid->type = TS_STUFFING;
		return tspid;
	}


	return (TS_PID *) NULL;
}






// $$$ TODO:   optional: Pidscan by -tsraw
// read full transponder stream and do pid analyzing
// currently I do not know if there is any reel improvment by this,
// because budget card have a huge amount of filters.


// $$$ TODO: problems on twinhan budget card (driver issue/suse9.2?)
// to be checked
