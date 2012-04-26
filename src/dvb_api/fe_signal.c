/*
$Id: fe_signal.c,v 1.17 2006/01/02 18:23:59 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- Signal Statistics  Current Frequency/Transponder
 --  DVB-API 




$Log: fe_signal.c,v $
Revision 1.17  2006/01/02 18:23:59  rasc
just update copyright and prepare for a new public tar ball

Revision 1.16  2005/09/18 12:23:23  rasc
no message

Revision 1.15  2005/09/13 18:41:15  rasc
... revert cygwin stuff

Revision 1.14  2005/09/06 23:13:51  rasc
catch OS signals (kill ...) for smooth program termination

Revision 1.13  2005/08/13 00:06:56  rasc
no message

Revision 1.12  2004/10/12 20:37:47  rasc
 - Changed: TS pid filtering from file, behavior changed
 - New: new cmdline option -maxdmx <n>  (replaces -f using pidscan)
 - misc. changes

Revision 1.11  2004/04/05 17:32:13  rasc
mass typo fix adaption --> adaptation

Revision 1.10  2004/03/21 13:20:07  rasc
more -feinfo, some restructs on FE code

Revision 1.9  2004/03/21 00:37:47  rasc
Query FrontEnd Info  (option: -s feinfo)

Revision 1.8  2004/03/06 22:33:11  rasc
no message

Revision 1.7  2004/02/28 12:13:03  rasc
minor stuff

Revision 1.6  2004/01/06 20:35:14  rasc
no message

Revision 1.5  2004/01/06 20:06:36  rasc
revert a change for -s signal + small adaptations
(frontend.h uses enums instead of #defines, so commit didn't work...)

Revision 1.4  2004/01/05 02:03:42  rasc
no message

Revision 1.3  2004/01/04 22:03:21  rasc
time for a version leap

Revision 1.2  2004/01/03 16:40:12  rasc
no message

Revision 1.1  2004/01/03 15:40:45  rasc
simple frontend signal status query added "-s signal"



*/


#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>


#include "dvbsnoop.h"
#include "fe_signal.h"
#include "fe_misc.h"

#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/pkt_time.h"
#include "misc/sig_abort.h"

#include "dmx_error.h"
#include "dvb_api.h"









int  do_SignalStrength (OPTION *opt)

{
  int        fd_fe = 0;
  struct timeval tv,last_tv, first_tv;
  u_long     count;
  FE_SIGNAL  s;
  FE_SIG_CAP has;

 


  if (opt->inpPidFile) {
	fprintf (stderr,"Error: FileMode not supported...\n");
	return -1;
  } 


  if((fd_fe = open(opt->devFE,O_RDONLY)) < 0){
     IO_error(opt->devFE);
     return -1;
  }



  // -- check capabilities
 
  has.ber 	= capability_Check (fd_fe, FE_READ_BER);
  has.snr	= capability_Check (fd_fe, FE_READ_SNR);
  has.strength	= capability_Check (fd_fe, FE_READ_SIGNAL_STRENGTH);
  has.status	= capability_Check (fd_fe, FE_READ_STATUS);
  has.ublocks	= capability_Check (fd_fe, FE_READ_UNCORRECTED_BLOCKS);



   indent (0);
   out_NL (2);
   out_nl (2,"---------------------------------------------------------");
   out_nl (2,"Transponder/Frequency signal strength statistics...");
   if (opt->rd_packet_count > 0) {
	   out_nl (2,"max cycle count: %ld ", opt->rd_packet_count);
   }
   out_nl (9,"Capabilities: BER: %d  SNR: %d  SIG: %d  STAT: %d  UBLK: %d",
		   has.ber, has.snr, has.strength, has.status, has.ublocks);
   out_nl (2,"---------------------------------------------------------");




   gettimeofday (&first_tv, NULL);
   last_tv.tv_sec  =  first_tv.tv_sec;
   last_tv.tv_usec =  first_tv.tv_usec;



  count = 0;
  while ( !isSigAbort() ) {
	int  err;
	int  d_tim_ms;


	count++;
	out (6, "cycle: %lu  ",count);

	gettimeofday (&tv, NULL);
   	d_tim_ms = delta_time_ms (&tv, &last_tv);
	if (d_tim_ms <= 0) d_tim_ms = 1;   //  ignore usecs 
	last_tv.tv_sec  =  tv.tv_sec;
	last_tv.tv_usec =  tv.tv_usec;

	out (6, "d_time: %ld.%03ld s  ", d_tim_ms / 1000UL, d_tim_ms % 1000UL);

				   

	err = read_Signal (fd_fe, &s, &has);
	    if (err == -1) return -1;
//	    if (err == -2) {
//		    out_nl (1," No signal...");
//		    continue;
//	    }

	    // & 0xFFFF necessary, due to interface transformations??
	if (has.strength)  out (1,"Sig: %u  ", s.strength & 0xFFFFL);
	if (has.snr)	   out (2,"SNR: %u  ", s.snr & 0xFFFFL);
	if (has.ber)	   out (3,"BER: %lu  ",s.ber);
	if (has.ublocks)   out (4,"UBLK: %ld  ",s.ublocks);
	if (has.status) {
		out (4,"Stat: 0x%02x ",s.status);
		out_status_detail (5,s.status);
	}
	out_NL(1);


	if (opt->timeout_ms) usleep (opt->timeout_ms * 1000);
	if (d_tim_ms == 0) usleep (1000);	// don't kill the system


	// count cycles? ?
	if (opt->rd_packet_count && (opt->rd_packet_count <= count)) break;

  } // while



  close(fd_fe);
  return 0;
}



