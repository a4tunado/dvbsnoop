/*
$Id: descriptor_private_default.c,v 1.2 2006/01/02 18:24:16 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Descriptors 




$Log: descriptor_private_default.c,v $
Revision 1.2  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/11/03 21:01:00  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections



*/


#include "dvbsnoop.h"
#include "descriptor_private_default.h"
#include "misc/helper.h"
#include "misc/output.h"






/*
  User defined descriptor  (Basic Descriptor output)
  ETSI 300 468 // ISO 13818-1
*/

void descriptor_PRIVATE_default (u_char *b)
{
 int  len;

 // tag		 = b[0];
 len       	 = b[1];

 print_databytes (4,"Descriptor-data:", b+2, len);
}


