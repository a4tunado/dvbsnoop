/*
$Id: dsmcc_unm_dsi.c,v 1.8 2006/03/06 00:04:50 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc download Server Initiate
 -- to be called from U-N-Message



$Log: dsmcc_unm_dsi.c,v $
Revision 1.8  2006/03/06 00:04:50  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.7  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.6  2004/02/29 20:42:55  rasc
no message

Revision 1.5  2004/02/28 12:13:03  rasc
minor stuff

Revision 1.4  2004/02/24 23:03:04  rasc
private data of DSMCC::DSI
BIOP::ServiceGatewayInformation()
IOP::IOR()

Revision 1.3  2004/02/17 23:54:12  rasc
Bug (not fixed yet): DSM-CC  DII Carousel Descriptor Loop is strange

Revision 1.2  2004/02/15 20:46:09  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.1  2004/02/15 18:58:28  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)





*/




#include "dvbsnoop.h"
#include "dsmcc_unm_dsi.h"
#include "dsmcc_misc.h"
#include "dsmcc_grpinfind.h"
#include "biop_servgatinf.h"
#include "misc/output.h"
#include "misc/hexprint.h"





/*
 * ISO/IEC 13818-6
 * dsmcc_Download Server Initiate
 */


int dsmcc_DownloadServerInitiate (int v, u_char *b, u_int len)
{
   int   	len_org = len;
   int		len2;
   int		x;
   u_long	uu_type_id;




	// already read  dsmcc_MessageHeader (v, b, len, &dmh);

	dsmcc_carousel_NSAP_address_B20 (v, "Server-ID", b);

	x = dsmcc_CompatibilityDescriptor (b+20);
	b += 20+x;
	// len -= 20+x;

	len2 = outBit_Sx_NL (v,"privateDataLength: ",	b,  0, 16);
	b += 2; 
	// len -= 2;

	// DataCarousel: GroupInfoByte structure + dsmcc_CarouselDescriptors
	// ObjectCarousel: BIOP::ServiceGatewayInformation
	// because we do not know, if DC or OC, we make a check for BIOP
	// U-U Objects type_id "srg\0"  and "DSM:"
	// (normally we should remember a databroadcast_id for decision)

	if (len2 >= 8) {
		out (v,"guessing private data: ");
		uu_type_id = getBits (b+4, 0, 0, 32);
	} else {
		uu_type_id = 0;
	}

	if (len > 0) {
		if (uu_type_id != 0x73726700 && uu_type_id != 0x53443a4d ) {
			// Data Carousel
			dsmcc_GroupInfoIndication (v, b, len2);
		} else {
			// Object Carousel
			BIOP_ServiceGatewayInfo   (v, b, len2);
		}
	}

	// b += len2;
	// len -= len2;

	return len_org;
}







// EN 301 192:
// 8.1.2 DownloadServerInitiate message
// 
// The DownloadServerInitiate message is used to build a SuperGroup.
// The semantics for DVB data carousels are as follows:
//
// serverId: this field shall be set to 20 bytes with the value of 0xFF.
//
// compatibilityDescriptor(): this structure shall only contain the
// compatibilityDescriptorLength field of the compatibilityDescriptor()
// as defined in DSM-CC (see ISO/IEC 13818-6 [5]). It shall be set to
// the value of 0x0000. The privateDataByte fields shall contain the
// GroupInfoIndication structure as defined in table 37.
//
// privateDataLength: this field defines the length in bytes of the
// following GroupInfoIndication structure.
//
// privateDataByte: these fields shall convey the GroupInfoIndication
// structure as defined in table 37.
//
// --> SuperGroupInfo
// groupInfobyte may contain BIOP, descriptor_carousel_loopm etc.

// Or 
//
// PrivateDataBytes   may Contain BIOP::ServiceGateway Info
// $$$ TO be checked!!!!!


// TS 102 812 v1.2.1 B2.2.3:
//   MHP: contains ServiceGatewayInformation
//


