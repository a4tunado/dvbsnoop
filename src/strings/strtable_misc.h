/*
$Id: strtable_misc.h,v 1.2 2005/12/27 23:30:30 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



*/


#ifndef __STRTABLE_MISC_H
#define __STRTABLE_MISC_H


#include "dvbsnoop.h"



typedef struct _STR_TABLE {
    u_int       from;          /* e.g. from id 1  */
    u_int       to;            /*      to   id 3  */
    const char  *str;          /*      is   string xxx */
} STR_TABLE;




char *findTableID (STR_TABLE *t, u_int id);


#endif




