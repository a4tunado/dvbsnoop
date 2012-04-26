/*
$Id: pkt_time.h,v 1.10 2006/01/02 18:24:04 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)





$Log: pkt_time.h,v $
Revision 1.10  2006/01/02 18:24:04  rasc
just update copyright and prepare for a new public tar ball

Revision 1.9  2004/12/07 21:01:42  rasc
Large file support (> 2 GB) for -if cmd option. (tnx to K.Zheng,  Philips.com for reporting)

Revision 1.8  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured

Revision 1.7  2004/01/02 16:40:37  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.6  2004/01/01 20:09:26  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/12/14 23:38:46  rasc
- bandwidth reporting for a PID

Revision 1.4  2003/11/26 19:55:33  rasc
no message

Revision 1.3  2003/11/26 16:27:46  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.2  2001/10/02 21:52:44  rasc
- init der time_delta
- PES erweitert, PES arbeitet im read() noch nicht richtig!!
- muss tmbinc fragem, ob ich Mist baue, oder der Treiber (??)

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/


#ifndef __PKT_TIME
#define __PKT_TIME


#include "cmdline.h"
#include "sys/time.h"



void  out_receive_time (int verbose, OPTION *opt);
void  init_receive_time (void);
long delta_time_ms (struct timeval *tv, struct timeval *tv_last);


#endif


