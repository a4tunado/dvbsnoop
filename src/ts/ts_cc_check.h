/*
$Id: ts_cc_check.h,v 1.2 2006/01/02 18:24:34 rasc Exp $


   
 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


*/


#ifndef __TS_CC_CHECK_H
#define __TS_CC_CHECK_H


void ts_cc_init (void);
void ts_cc_free (void);
void ts_cc_SetPid (int pid);
char *ts_cc_StatusStr (int cc);


#endif


