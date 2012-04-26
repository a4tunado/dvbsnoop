/*
$Id: userdefs.h,v 1.3 2005/12/29 02:43:38 rasc Exp $

 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



*/




#ifndef _USERDEFS_H_
#define _USERDEFS_H_


#include "descriptors/descriptor.h"



typedef struct _PRIVATE_SECTION_STRUCTURES_FUNC {
    u_int    table_id;         	/* section table ID */
    void     (*func)();  	/* function for table decoding */
} PRIV_SECTION_ID_FUNC;


typedef struct _PRIVATE_DESCRIPTOR_STRUCTURES_FUNC {
    u_int      descriptor_tag; 	/* descriptor tag ID */
    DTAG_SCOPE tag_scope;	/* MPEG, DVB_SI, DSMCC_STREAM, ... */
    void       (*func)();  	/* function for descriptor decoding */
} PRIV_DESCR_ID_FUNC;







void section_PRIVATE (u_char *b, int len);
void descriptor_PRIVATE (u_char *b, DTAG_SCOPE scope);

void set_PRIVATE_ProviderStr (char *s);
void list_PRIVATE_ProviderStrs (void);


#endif

