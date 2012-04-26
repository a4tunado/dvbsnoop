/*
$Id: biop.h,v 1.1 2006/03/06 00:04:49 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


*/


#ifndef _BIOP
#define _BIOP


u_long  BIOP_BIOPProfileBody  (int v, u_char *b);
u_long  BIOP_LiteOptionsProfileBody (int v, u_char *b);
u_long  BIOP_LiteComponent (int v, u_char *b);
u_long  BIOP_ObjectLocation (int v, u_char *b);
int  BIOP_Name (int v, u_char *b, u_long *p_kinddata);


#endif


