/*
$Id: premiere_de.c,v 1.5 2006/04/04 17:16:54 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- User defined table // Private
  -- Premiere Content Information Table CIT



$Log: premiere_de.c,v $
Revision 1.5  2006/04/04 17:16:54  rasc
finally fix typo in premiere descriptor name

Revision 1.4  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.3  2005/08/10 21:28:19  rasc
New: Program Stream handling  (-s ps)

Revision 1.2  2005/06/29 17:30:38  rasc
some legal notes...

Revision 1.1  2004/11/03 21:01:02  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections




*/




#include "dvbsnoop.h"
#include "premiere_de.h"

#include "section_premiere_cit.h"
#include "section_premiere_cpt.h"
#include "dvb_descriptor_premiere.h"



/*
 
 Please check for legal issues, when using provider specific
 data structures in your own software!
 Using  these data structures may require a certification or
 licensing process by the provider.

 */

static PRIV_DESCR_ID_FUNC pdescriptors[] = {
	{ 0xF0, DVB_SI,   descriptor_PRIVATE_PremiereDE_ContentOrder },
	{ 0xF1, DVB_SI,   descriptor_PRIVATE_PremiereDE_ParentalInformation },
	{ 0xF2, DVB_SI,   descriptor_PRIVATE_PremiereDE_ContentTransmission },
	{ 0x00,	0,        NULL } // end of table  (id = 0x00, funct = NULL)
};


static PRIV_SECTION_ID_FUNC psections[] = {
	{ 0xA0,	section_PRIVATE_PremiereDE_CIT },
	{ 0xA1,	section_PRIVATE_PremiereDE_CPT },
	{ 0x00, NULL }	// end of table  (id = 0x00, funct = NULL)
	
};





//
// -- Return private section/descriptor id tables
// -- for this scope
//

void getPrivate_PremiereDE ( PRIV_SECTION_ID_FUNC **psect,
		PRIV_DESCR_ID_FUNC **pdesc)
{
   *psect = psections;
   *pdesc = pdescriptors;
}




