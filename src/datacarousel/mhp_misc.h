/*
$Id: mhp_misc.h,v 1.3 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


*/


#ifndef __MHP_MISC_H
#define __MHP_MISC_H 


int  mhp_application_identifier (int  v, u_char *b);
int  mhp_application_profile_version (int  v, u_char *b);


#endif



