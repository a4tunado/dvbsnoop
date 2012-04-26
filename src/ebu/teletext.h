/*
$Id: teletext.h,v 1.5 2006/01/02 18:24:03 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- misc routines for EBU teletext



*/

#ifndef _TELETEXT_H_
#define _TELETEXT_H_


int    print_teletext_control_decode (int v, u_char *b, int len);
void   print_teletext_data_x0_x25 (int v, char *s, u_char *b, int len);



#endif


