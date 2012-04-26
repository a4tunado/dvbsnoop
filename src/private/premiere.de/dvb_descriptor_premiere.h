/*
$Id: dvb_descriptor_premiere.h,v 1.3 2006/04/04 17:16:54 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- private DVB Descriptors  Premiere.de



$Log: dvb_descriptor_premiere.h,v $
Revision 1.3  2006/04/04 17:16:54  rasc
finally fix typo in premiere descriptor name

Revision 1.2  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/11/03 21:01:02  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections


*/


#ifndef _PREMIERE_DVB_DESCRIPTOR_H
#define _PREMIERE_DVB_DESCRIPTOR_H 


void descriptor_PRIVATE_PremiereDE_ContentOrder (u_char *b);
void descriptor_PRIVATE_PremiereDE_ParentalInformation (u_char *b);
void descriptor_PRIVATE_PremiereDE_ContentTransmission (u_char *b);


#endif

