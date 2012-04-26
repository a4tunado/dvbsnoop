/*
$Id: descriptor.c,v 1.31 2006/02/12 23:17:11 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Descriptors 




$Log: descriptor.c,v $
Revision 1.31  2006/02/12 23:17:11  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.30  2006/01/02 18:23:57  rasc
just update copyright and prepare for a new public tar ball

Revision 1.29  2004/11/03 21:00:50  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.28  2004/09/01 20:20:34  rasc
new cmdline option: -buffersize KB  (set demux buffersize in KBytes)

Revision 1.27  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42

Revision 1.26  2004/07/26 20:58:03  rasc
RNT completed..  (TS 102 323)

Revision 1.25  2004/07/25 20:12:58  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.24  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.23  2004/02/07 01:28:01  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.22  2004/01/25 21:37:27  rasc
bugfixes, minor changes & enhancments

Revision 1.21  2004/01/12 23:05:24  rasc
no message

Revision 1.20  2004/01/11 21:01:31  rasc
PES stream directory, PES restructured

Revision 1.19  2004/01/03 00:30:06  rasc
DSM-CC  STREAM descriptors module (started)

Revision 1.18  2004/01/02 22:59:58  rasc
DSM-CC  modules renaming...

Revision 1.17  2004/01/02 22:25:35  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.16  2004/01/02 16:40:34  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.15  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.14  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.13  2003/12/29 22:14:53  rasc
more dsm-cc INT UNT descriptors

Revision 1.12  2003/10/24 22:45:04  rasc
code reorg...

Revision 1.11  2003/10/24 22:17:14  rasc
code reorg...

Revision 1.10  2003/10/13 23:27:35  rasc
Bugfix, verbose < 4 segfaulted, tnx to 'mws'  for reporting.

Revision 1.9  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?

Revision 1.8  2003/06/24 23:51:03  rasc
bugfixes and enhancements

Revision 1.7  2003/05/03 02:51:08  obi
skip descriptors with length == 0

Revision 1.6  2003/03/17 16:15:11  obi
fixed infinite loop
thanks to Johannes Stezenbach

Revision 1.5  2002/09/29 13:01:35  wjoost
kleiner Fehler



*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "mpeg_descriptor.h"
#include "dvb_descriptor.h"
#include "dsmcc_carousel_descriptor.h"
#include "dsmcc_int_unt_descriptor.h"
#include "mhp_ait_descriptor.h"
#include "tva_rnt_descriptor.h"
#include "misc/hexprint.h"
#include "misc/output.h"







/*
  determine descriptor type and print it...
  return byte length
*/

int  descriptor  (u_char *b, DTAG_SCOPE scope)
{
 int len;
 int id;


  id  =  (int)b[0];  
  len = ((int)b[1]) + 2;   	// total length

  // nothing to print here? 
  // well, I guess all descriptors need a verbosity >=4...
  if (getVerboseLevel() < 4) return len;

  indent (+1);


  switch  (scope) {

     case DSMCC_STREAM:
  		descriptorMPEG (b); 
		break;

     case DSMCC_CAROUSEL:
  		descriptorDSMCC_CAROUSEL (b);
		break;

     case DSMCC_INT_UNT:	// EN 301 192, TS 102 006
  		if (id < 0x40)	descriptorDSMCC_INT_UNT (b);
		else 		descriptorDVB (b);
		break;

     case MHP_AIT:
		descriptorMHP_AIT (b);
		break;

     case TVA_RNT:		// TS 102 323
  		if (id < 0x40)	descriptorMPEG (b);
		else		descriptorTVA (b);
		break;

     case MPEG:
     case DVB_SI:
     default:
  		if (id < 0x40)	descriptorMPEG (b);
		else	 	descriptorDVB (b);
		break;

  }


  indent (-1);

  return len;   // (descriptor total length)
}








/*
  Any  descriptor  (Basic Descriptor output)
  ETSI 300 468 // ISO 13818-1
*/

void descriptor_any (u_char *b)
{
 int  len;


 // tag		 = b[0];
 len       	 = b[1];

 print_databytes (4,"Descriptor-data:", b+2, len);
}





