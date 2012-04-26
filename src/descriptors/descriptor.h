/*
$Id: descriptor.h,v 1.12 2006/01/02 18:23:58 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Descriptors Section




$Log: descriptor.h,v $
Revision 1.12  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.11  2004/11/03 21:00:50  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.10  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.9  2004/02/07 01:28:01  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.8  2004/01/11 21:01:31  rasc
PES stream directory, PES restructured

Revision 1.7  2004/01/02 22:25:35  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.6  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/11/26 19:55:32  rasc
no message

Revision 1.4  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/


#ifndef __DESCRIPTOR_H
#define __DESCRIPTOR_H


// Descriptor tag space/scope...
typedef enum {
	MPEG, DVB_SI,
	DSMCC_STREAM, DSMCC_CAROUSEL, DSMCC_INT_UNT, MHP_AIT, TVA_RNT
} DTAG_SCOPE;


int   descriptor (u_char *b, DTAG_SCOPE s);
void  descriptor_any (u_char *b);


#endif


