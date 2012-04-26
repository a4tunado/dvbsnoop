/*
$Id: biop_servgatinf.c,v 1.3 2006/03/06 00:04:49 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc  BIOP::ServiceGatewayInfo()
 -- TR 101 202 v1.2.1  4.7.5.2




$Log: biop_servgatinf.c,v $
Revision 1.3  2006/03/06 00:04:49  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.2  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/02/24 23:03:04  rasc
private data of DSMCC::DSI
BIOP::ServiceGatewayInformation()
IOP::IOR()





*/




#include "dvbsnoop.h"
#include "biop_servgatinf.h"
#include "biop_tag_tap.h"
#include "iop_ior.h"
#include "dsmcc_misc.h"
#include "descriptors/descriptor.h"

#include "misc/output.h"
#include "misc/hexprint.h"

#include "strings/dsmcc_str.h"
#include "strings/dvb_str.h"




/*
 * dsmcc BIOP::ServiceGatewayInfo()
 * TR 101 202 v 1.2.1
 * return: length used
 */


int BIOP_ServiceGatewayInfo (int v, u_char *b, u_int len)
{
   int   	len_org = len;
   int		i;
   int 		nx,n1,n2;



	out_nl (v, "BIOP::ServiceGatewayInfo:");

	indent (+1);

	nx = IOP_IOR (v,b);
	b   += nx;
	len -= nx;


	n1 = outBit_Sx_NL (v,"downloadTaps_count: ",		b,  0,  8);
	b++;
	len--;
	for (i=0; i < n1; i++) {
		int   n3;

		n3 = BIOP_TAP (v, "DSM", b);
		b   += n3;
		len -= n3;
	}


	n1 = outBit_Sx_NL (v,"serviceContextList_count: ",	b,  0,  8);
	b++;
	len--;
	for (i=0; i < n1; i++) {
		outBit_Sx_NL (v,"context_id: ",			b,  0,  32);
		n2 = outBit_Sx_NL (v,"context_data_length: ",	b,  32, 16);

		print_databytes (v,"context_data:", b+6, n2);   // $$$ TODO

		b += 6 + n2;
		len -= 6 + n2;
	}


	n1 = outBit_Sx_NL (v,"userInfoLength: ",		b,  0,  16);
	dsmcc_CarouselDescriptor_Loop ("userInfo", b+2, n1);
	b   += 2+n1;
	len -= 2+n1;


	indent (-1);

	return len_org;
}







// BIOP::ServiceGatewayInfo()::
// The user info field shall be structured as a descriptor loop.
// The descriptors in this loop shall be either descriptors as
// defined in the DVB Data Broadcasting Specification or private descriptors.


