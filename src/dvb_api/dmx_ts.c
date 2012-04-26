/*
$Id: dmx_ts.c,v 1.37 2006/01/02 18:23:58 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- Transport Streams
 --  For more information please see:
 --  ISO 13818 (-1) and ETSI 300 468




$Log: dmx_ts.c,v $
Revision 1.37  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.36  2005/11/08 23:15:25  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.35  2005/10/20 22:25:06  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.34  2005/09/09 14:20:29  rasc
TS continuity sequence check (cc verbose output)

Revision 1.33  2005/09/06 23:13:51  rasc
catch OS signals (kill ...) for smooth program termination

Revision 1.32  2005/08/02 22:57:46  rasc
Option -N, rewrite offline filters (TS & Section)

Revision 1.31  2005/01/23 21:52:01  rasc
DVR device needs to be open in RD only mode...

Revision 1.30  2004/12/07 21:01:41  rasc
Large file support (> 2 GB) for -if cmd option. (tnx to K.Zheng,  Philips.com for reporting)

Revision 1.29  2004/11/16 23:02:50  rasc
cmd option "-tsraw" for full/raw TS read (if supported by hard-/firmware)

Revision 1.28  2004/11/16 09:15:03  obi
show received pid instead of command line pid if pid 0x2000 was specified (full TS)

Revision 1.27  2004/10/12 20:37:47  rasc
 - Changed: TS pid filtering from file, behavior changed
 - New: new cmdline option -maxdmx <n>  (replaces -f using pidscan)
 - misc. changes

Revision 1.26  2004/09/01 20:20:34  rasc
new cmdline option: -buffersize KB  (set demux buffersize in KBytes)

Revision 1.25  2004/04/18 19:30:32  rasc
Transport Stream payload sub-decoding (Section, PES data) improved

Revision 1.24  2004/04/15 22:29:22  rasc
PMT: some brainded section check
TS: filter single pids from multi-pid ts-input-file
minor enhancements

Revision 1.23  2004/04/15 03:38:50  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.22  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.21  2004/02/15 22:22:28  rasc
cmd option: -hexdumpbuffer -nohexdumpbuffer

Revision 1.20  2004/01/25 22:36:52  rasc
minor changes & enhancments

Revision 1.19  2004/01/25 21:37:28  rasc
bugfixes, minor changes & enhancments

Revision 1.18  2004/01/02 02:45:33  rasc
no message

Revision 1.17  2004/01/02 00:00:37  rasc
error output for buffer overflow

Revision 1.16  2004/01/01 20:09:23  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.15  2003/12/30 14:05:37  rasc
just some annotations, so I do not forget these over Sylvester party...
(some alkohol may reformat parts of /devbrain/0 ... )
cheers!

Revision 1.14  2003/12/28 22:53:40  rasc
some minor changes/cleanup

Revision 1.13  2003/12/28 14:00:25  rasc
bugfix: section read from input file
some changes on packet header output

Revision 1.12  2003/12/15 20:09:48  rasc
no message

Revision 1.11  2003/12/10 22:54:11  obi
more tiny fixes

Revision 1.10  2003/11/24 23:52:16  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.9  2003/10/24 22:45:06  rasc
code reorg...

Revision 1.8  2003/10/24 22:17:18  rasc
code reorg...

Revision 1.7  2003/10/16 19:02:28  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.6  2003/05/28 01:35:01  obi
fixed read() return code handling

Revision 1.5  2003/01/07 00:43:58  obi
set buffer size to 256kb

Revision 1.4  2002/11/01 20:38:40  Jolt
Changes for the new API

Revision 1.3  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/


#include "dvbsnoop.h"
#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/sig_abort.h"

#include "ts/tslayer.h"
#include "ts/ts2secpes.h"
#include "ts/ts_cc_check.h"

#include "dvb_api.h"
#include "file_io.h"
#include "dmx_error.h"
#include "dmx_ts.h"




#define TS_PACKET_LEN (188)              /* TS RDSIZE is fixed !! */
#define TS_SYNC_BYTE  (0x47)             /* SyncByte fuer TS  ISO 138181-1 */
#define TS_BUF_SIZE   (256 * 1024)	 /* default DMX_Buffer Size for TS */
#define READ_BUF_SIZE (3*TS_PACKET_LEN)  /* min. 2x TS_PACKET_LEN!!! */



static long ts_SyncRead (int fd, u_char *buf, long max_buflen, long *skipped_bytes);





int  doReadTS (OPTION *opt)

{
  int     fd_dmx = 0, fd_dvr = 0;
  u_char  buf[READ_BUF_SIZE]; 	/* data buffer */
  u_char  *b;			/* ptr for packet start */
  long    count;
  long    filtered_count;
  char    *f;
  int     openMode;
  int     fileMode;
  long    dmx_buffer_size = TS_BUF_SIZE;


  

  if (opt->inpPidFile) {
  	f        = opt->inpPidFile;
  	openMode = O_RDONLY | O_LARGEFILE | O_BINARY;
        fileMode = 1;
  } else {
  	f        = opt->devDvr;
  	openMode = O_RDONLY;
        fileMode = 0;
  } 


  if((fd_dvr = open(f,openMode)) < 0){
      IO_error(f);
      return -1;
  }


  


  /*
   -- init demux
  */

  if (!fileMode) {
    struct dmx_pes_filter_params flt;

    if((fd_dmx = open(opt->devDemux,O_RDWR)) < 0){
        IO_error(opt->devDemux);
	close (fd_dvr);
        return -1;
    }


    // -- alloc dmx buffer for TS
    if (opt->rd_buffer_size > 0) {
	    dmx_buffer_size = opt->rd_buffer_size;
    }

    // -- full Transport Stream Read?? (special DVB-API-PID...)
    if (opt->ts_raw_mode) {
	    opt->pid = PID_FULL_TS;
    }


    if (ioctl(fd_dmx,DMX_SET_BUFFER_SIZE, dmx_buffer_size) < 0) {
	IO_error ("DMX_SET_BUFFER_SIZE failed: ");
	close (fd_dmx);
	close (fd_dvr);
	return -1;
    }

    memset (&flt, 0, sizeof (struct dmx_pes_filter_params));

    flt.pid = opt->pid;
    flt.input  = DMX_IN_FRONTEND;
    flt.output = DMX_OUT_TS_TAP;
    flt.pes_type = DMX_PES_OTHER;
    flt.flags = DMX_IMMEDIATE_START;

    if (ioctl(fd_dmx,DMX_SET_PES_FILTER,&flt) < 0) {
	IO_error ("DMX_SET_PES_FILTER failed: ");
	close (fd_dmx);
	close (fd_dvr);
	return -1;
    }

  }


  // -- acquire TS subdecoding buffer
  if (opt->ts_subdecode) {
	ts2SecPesInit ();
  }
  // -- init TS CC check
  ts_cc_init ();


/*
  -- read TS packets for pid
*/

  count = 0;
  filtered_count = 0;
  while ( ! isSigAbort() ) {
    long   n;
    long   skipped_bytes    = 0;
    int    pid_filter_match = 1;
    int    packet_pid       = -1;



    // -- Sync TS read!
    n = ts_SyncRead (fd_dvr,buf,sizeof(buf), &skipped_bytes);
    b = buf+(skipped_bytes % TS_PACKET_LEN);



    // -- error or eof?
    if (n < 0) {
	int err;
	
	err = IO_error("read");
	// if (err == ETIMEDOUT) break;		// Timout, abort
	continue;
    }

    if (n == 0) {
	if (!fileMode) continue;	// DVRmode = no eof!
	else {			// filemode eof 
	  ts2SecPes_LastPacketReadSubdecode_Output ();
	  break;
	}
    }



    count ++;



    // -- skipped Data to get sync byte?
    if (skipped_bytes) {
	if (! opt->binary_out) {
		out_nl (3,"!!! %ld bytes skipped to get TS sync!!!");
	}
    }

    // -- SyncByte for TS packet and correct len?
    if (b[0] != TS_SYNC_BYTE || n != TS_PACKET_LEN) {
	if (! opt->binary_out) {
		out_nl (3,"!!! Wrong SyncByte or packet length mismatch (= no TS)!!!");
	}
	continue;
    }



    // -- PID soft filter mode
    // -- We alway do this check (even if we are reading directly
    // -- from dvb device and PID has already been filtered by demux)
   
    packet_pid = getBits (b, 0,11, 13);
    if ((opt->pid >= 0) && (opt->pid <= MAX_PID) && (opt->pid != packet_pid)) {
	pid_filter_match = 0;
    }



    // -- packet output ? (binary or decoded)
    // -- This happens, when filter are matching (hard or soft filter)


    if (pid_filter_match) { 

	filtered_count++;


	if (opt->binary_out) {

		// direct write to FD 1 ( == stdout)
		write (1, b, n);

    	} else {

		processTS_packet (packet_pid, filtered_count, b, n);

	} 

    } // pid_filter_match: packet out




    // count packets ?
    if (opt->rd_packet_count > 0) {
       if (count >= opt->rd_packet_count) break;
    }
    if (opt->dec_packet_count > 0) {
       if (filtered_count >= opt->dec_packet_count) break;
    }


  } // while



  // -- release TS subdecoding buffer
  if (opt->ts_subdecode) ts2SecPesFree ();
  // -- release TS CC checka buffer, etc.
  ts_cc_init ();


  // -- Stop Demux
  if (!fileMode) {
     ioctl (fd_dmx, DMX_STOP, 0);

     close(fd_dmx);
  }

  close(fd_dvr);
  return 0;
}






/*
 * -- sync read (optimized = avoid multiple byte reads)
 * -- Seek TS sync-byte and read packet in buffer
 * -- ATTENTION:  packet is not stored at buf[0]
 *  --       -->  packet starts at buf[skipped_bytes % TS_PACKET_LEN] !!!
 * -- return: equivalent to read();
 */

static long  ts_SyncRead (int fd, u_char *buf, long max_buflen, long *skipped_bytes)
{
    int    n1,n2;
    int    i;
    int    found;


    // -- simple TS sync...
    // -- $$$ to be improved:
    // -- $$$  (best would be: check if buf[188] is also a sync byte)
 

    *skipped_bytes = 0;
    found = 0;
    while (! found) {
    	n1 = read(fd,buf,TS_PACKET_LEN);
    	if (n1 <= 0) return n1;			// error or strange, abort

    	for (i=0;i<n1; i++) {			// search sync byte
		if (buf[i] == TS_SYNC_BYTE) {
			found = 1;
			break;
		}
    	}
    	*skipped_bytes += i;
    }

    // -- Sync found!
    // -- read skipped number of bytes per read try

    if (i == 0) return n1;			// already complete packet read...

    n2 = read(fd,buf+n1,TS_PACKET_LEN-n1+i);	// continue read TS packet
    if (n2 >=0) n2 = n1+n2-i; ;			// should be TS_PACKET_LEN anyway...

    return n2;
}










