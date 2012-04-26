/*
$Id: ts_misc.h,v 1.1 2006/02/12 23:17:13 rasc Exp $


   
 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


*/


#ifndef __TS_MISC_H
#define __TS_MISC_H 


// -- Transport Stream Packet Header Data
 
typedef  struct _tsphd {
	int	sync;
	int	tei;
	int	pusi;
	int	tprio;
	int	tsc;
	int	afc;
	int	pid; 
	int	cc;
} TSPHD;



int decodeTS_PacketHeader (u_char *b, TSPHD *header_data);
int check_TS_PID_special (u_int pid);


#endif


