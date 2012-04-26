/*
$Id: descriptor_private_default.h,v 1.2 2006/01/02 18:24:16 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



$Log: descriptor_private_default.h,v $
Revision 1.2  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/11/03 21:01:00  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections


*/


#ifndef __DESCRIPTOR_PRIVATE_DEFAULT_H
#define __DESCRIPTOR_PRIVATE_DEFAULT_H


void  descriptor_PRIVATE_default (u_char *b);


#endif


