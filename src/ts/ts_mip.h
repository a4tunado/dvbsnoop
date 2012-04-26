/*
$Id: ts_mip.h,v 1.1 2006/02/12 23:17:13 rasc Exp $


   
 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


*/


#ifndef __TS_MIP_H
#define __TS_MIP_H 


void decodeTS_MIP (u_char *b, int len);

int  MIP_function (u_char *b);

void  MIP_FUNC_tx_time_offset (u_char *b);
void  MIP_FUNC_tx_frequency_offset (u_char *b);
void  MIP_FUNC_tx_power (u_char *b);
void  MIP_FUNC_private_data (u_char *b);
void  MIP_FUNC_cell_id (u_char *b);
void  MIP_FUNC_enable (u_char *b);
void  MIP_FUNC_bandwidth (u_char *b);


#endif


