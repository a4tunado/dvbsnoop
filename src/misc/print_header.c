/*
$Id: print_header.c,v 1.7 2006/01/02 18:24:04 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)




$Log: print_header.c,v $
Revision 1.7  2006/01/02 18:24:04  rasc
just update copyright and prepare for a new public tar ball

Revision 1.6  2005/10/20 22:25:07  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.5  2005/09/12 20:56:16  rasc
Make dvbsnoop compile on Cygwin / Windows

Revision 1.4  2004/11/16 23:02:50  rasc
cmd option "-tsraw" for full/raw TS read (if supported by hard-/firmware)

Revision 1.3  2004/10/12 20:37:48  rasc
 - Changed: TS pid filtering from file, behavior changed
 - New: new cmdline option -maxdmx <n>  (replaces -f using pidscan)
 - misc. changes

Revision 1.2  2004/01/01 20:09:26  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.1  2003/12/28 14:00:27  rasc
bugfix: section read from input file
some changes on packet header output



*/


#include <stdio.h>

#include "dvbsnoop.h"
#include "print_header.h"
#include "misc/cmdline.h"
#include "misc/output.h"
#include "misc/pkt_time.h"




void  print_packet_header (OPTION *opt, char *packetTyp, u_int pid, int count, int length)

{
   char  str[50];
   char  *s;


   if (pid != DUMMY_PID) {
   	sprintf (str,"%u (0x%04x)",pid,pid);
	s = str;
   } else {
	s = "(Unkown PID)";
   }

   // Full Transport Stream Read?
   if (opt->ts_raw_mode && (opt->packet_mode == TS)) {
	s = "(Full TS read)";
   }


   out_nl (1,"\n------------------------------------------------------------");
   out_nl (1,"%s-Packet: %08ld   PID: %s, Length: %d (0x%04x)",
		packetTyp, count, s, length,length);

   if (opt->inpPidFile) {
   	out_nl (1,"from file: %s",opt->inpPidFile);
   } else {
   	out_receive_time (1, opt);
   }

//   if (skipped_bytes) {
//       out_nl (1,"Syncing %s... (%ld bytes skipped)",
//		packetTyp,skipped_bytes);
//   }

   out_nl (1,"------------------------------------------------------------");


}



