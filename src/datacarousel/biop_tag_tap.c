/*
$Id: biop_tag_tap.c,v 1.2 2006/03/06 20:25:37 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- dsmcc  BIOP/IOR/LITE  Tag Dispatch
 -- ETSI TR 101 202
 -- ETSI TS 102 812
 -- ISO 13818-6
 -- ATSC A95
 -- ATSC A47




$Log: biop_tag_tap.c,v $
Revision 1.2  2006/03/06 20:25:37  rasc
DSM-CC Carousell, lots of Bugfixes, BIOP::Message not yet decodable (ddb has to collect Modules)

Revision 1.1  2006/03/06 00:04:49  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...





*/




#include "dvbsnoop.h"
#include "biop_tag_tap.h"
#include "biop.h"
#include "biop_dsm.h"
#include "biop_message.h"
#include "dsmcc_misc.h"

#include "misc/output.h"
#include "misc/hexprint.h"
#include "strings/dsmcc_str.h"




/*
 * dsmcc BIOP TAG Dispatch
 * This is an universal DSM/BIOP/LITE dispatcher
 * using a id_tag prefetch to decide where to branch...
 *
 * to be called from:
 *   IOP_IOR
 *   LiteOptionsProfileBody
 *   BIOPs
 *   etc.
 *
 * return: len
 */


u_long  BIOP_TAG_dispatch (int v, u_char *b)
{
  u_long   id_tag;
  u_long   len;


	id_tag = getBits (b, 0, 0, 32);		// ID_tag  prefetch

	switch (id_tag) {

	    case 0x42494F50:		// "BIOP"
		    // BIOP::FileMessage
		    // BIOP::DirectoryMessage
		    // BIOP::StreamMessage
		    // BIOP::StreamEventMessage
		    len = BIOP_Message (v, b);
		    break;

	    case 0x49534f05:		// TAG_LITE_OPTIONS
		    len = BIOP_LiteOptionsProfileBody (v, b);
		    break;

	    case 0x49534f06:		// TAG_BIOP
		    // BIOPProfileBody
		    len = BIOP_BIOPProfileBody (v, b);
		    break;

	    case 0x49534f40:		// TAG_ConnBinder
		    // DSM::ConnBinder
		    len = BIOP_DSM_ConnBinder (v, b);
		    break;

	    case 0x49534f46:		// TAG_SERVICE_LOCATION
		    len = BIOP_DSM_ServiceLocation (v, b);
		    break;

	    case 0x49534f50:		// TAG_ObjectLocation
		    // DSM::ConnBinder
		    len = BIOP_ObjectLocation (v, b);
		    break;

	    default:			// unknown !!!
		    // $$$ TODO:  we wildly guess, that there is a 32b length field!
		    // $$$ TODO:  this may break the decoding process, if not true
		    outBit_S2x_NL (v,"profileId_tag: ",			b,   0, 32,
 			(char *(*)(u_long)) dsmccStrIOP_ProfileID );
		    len = outBit_Sx_NL (v,"profile_data_length: ",	b,  32, 32);
		    print_databytes (v,"unkown profile_data:", b+8, len); 
		    len += 8;
		    break;

	}
		
  out_NL (v);
  return len;
}


// NOT (yet) implemented...
//
//	    case 0x49534f00:		// TAG_MIN
//	    case 0x49534f01:		// TAG_CHILD
//	    case 0x49534f02:		// TAG_OPTIONS
//	    case 0x49534f03:		// TAG_LITE_MIN
//	    case 0x49534f04:		// TAG_LITE_CHILD
//







/*
 * dsmcc  BIOP DSM::TAP();
 * return: length
 */

int BIOP_TAP (int v, const char *str, u_char *b)
{
  u_char       *b_org = b;
  int          use;
  int          n;


   out_nl (v, "%s::TAP:");
   indent (+1);

         outBit_Sx_NL (v,"id: ",			b,  0, 16);
   use = outBit_S2x_NL(v,"use: ",			b, 16, 16,
			(char *(*)(u_long))dsmccStrBIOP_TAP_Use );

         outBit_Sx_NL (v,"association_tag: ",		b, 32, 16);



   n   = outBit_Sx_NL (v,"selector_length: ",		b, 48,  8);
   b += 7;


   // -- a TAP may have a Selector()
   if (n >= 2) {
	int stype;
	
	stype = outBit_S2x_NL(v,"selector_type: ",	b,  0, 16,
			(char *(*)(u_long))dsmccStrBIOP_TAP_SelectorType );
	indent (+1);
	switch (stype) {

		case 0x0001:			// MessageSelector
			dsmcc_print_transactionID_32 (v, b+2);
   			outBit_S2Tx_NL (v,"timeout: ",	b, 48,  32, "usec.");
			break;

		case 0x0109:			// ATSC A95: TSFS_selector
   			outBit_Sx_NL   (v,"carouselId: ",  b, 16,  32);
   			outBit_S2Tx_NL (v,"DSI_timeout: ", b, 48,  32, "usec.");
			if (n > 10) {
	 		   print_databytes (v,"URI_byte:",   b+10, n-10); 
			}
			break;

		case 0x0000:			// ISO/IEC reserved
		default:			// unknown, default
	 		print_databytes (v,"selector_data:", 	b+2, n-2); 
			break;

	}
	indent (-1);

   } else {
	if (n > 0) {
		print_databytes (v,"selector_data:", 	b, n); 
	}
   }


   b += n;


   indent (-1);
   out_NL (v);
   return (int) (b - b_org);
}
 






