/*
$Id: pes_std.h,v 1.4 2006/01/02 18:24:12 rasc Exp $

   
 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



*/

#ifndef __PES_STD_H__
#define __PES_STD_H__ 

void  PES_decode_std (u_char *b, int len, u_int PES_streamID);

#endif

