/*
$Id: biop_dsm.h,v 1.1 2006/03/06 00:04:49 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


*/


#ifndef _BIOP_DSM
#define _BIOP_DSM


int  BIOP_DSM_ConnBinder (int v, u_char *b);
int  BIOP_DSM_ServiceLocation (int v, u_char *b);
int  BIOP_DSM_ServiceDomain (int v, u_char *b, int len);
int  BIOP_DSM_CosNaming_Name (int v, u_char *b);
int  BIOP_DSM_Stream_Info_T (int v, u_char *b);
int  BIOP_DSM_Event_EventList_T (int v, u_char *b);


#endif


