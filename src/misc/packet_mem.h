/*
$Id: packet_mem.h,v 1.2 2006/01/02 18:24:04 rasc Exp $


   
 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


*/


#ifndef __PACKET_MEM_H
#define __PACKET_MEM_H


int  packetMem_acquire (u_long  requested_length);
void packetMem_free (int handle);
void packetMem_clear (int handle);
u_long packetMem_length (int handle);
u_char *packetMem_buffer_start (int handle);
int packetMem_add_data (int handle, u_char *buf, u_long len);


#endif


