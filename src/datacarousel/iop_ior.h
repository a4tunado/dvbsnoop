/*
$Id: iop_ior.h,v 1.3 2006/03/06 00:04:50 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


*/


#ifndef _IOP_IOR
#define _IOP_IOR


int    IOP_IOR (int v, u_char *b);
u_long IOP_taggedProfile (int v, u_char *b);


#endif


