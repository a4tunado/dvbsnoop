/*
$Id: dsmcc_misc.c,v 1.23 2006/03/06 20:25:37 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)




$Log: dsmcc_misc.c,v $
Revision 1.23  2006/03/06 20:25:37  rasc
DSM-CC Carousell, lots of Bugfixes, BIOP::Message not yet decodable (ddb has to collect Modules)

Revision 1.22  2006/03/06 00:04:49  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.21  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.20  2005/12/29 02:43:37  rasc
gcc fixes, man page update

Revision 1.19  2004/08/07 22:10:00  rasc
Bugfix: NIT cable frequency display (reported by Karsten Siebert )

Revision 1.18  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42

Revision 1.17  2004/07/25 20:12:58  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.16  2004/04/15 03:38:50  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.15  2004/04/05 17:32:12  rasc
mass typo fix adaption --> adaptation

Revision 1.14  2004/02/29 20:42:55  rasc
no message

Revision 1.13  2004/02/24 23:03:04  rasc
private data of DSMCC::DSI
BIOP::ServiceGatewayInformation()
IOP::IOR()

Revision 1.12  2004/02/20 23:13:17  rasc
BIOP:  TapUse

Revision 1.11  2004/02/20 22:18:38  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.10  2004/02/17 23:54:12  rasc
Bug (not fixed yet): DSM-CC  DII Carousel Descriptor Loop is strange

Revision 1.9  2004/02/15 20:46:09  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.8  2004/02/15 18:58:27  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.7  2004/02/15 01:01:00  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed

Revision 1.6  2004/02/14 01:24:44  rasc
DSM-CC started  (DSI/DII, DDB)

Revision 1.5  2004/01/02 22:25:34  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.4  2004/01/02 16:40:33  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.3  2004/01/01 20:09:16  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.2  2003/12/27 14:35:00  rasc
dvb-t descriptors
DSM-CC: SSU Linkage/DataBroadcast descriptors

Revision 1.1  2003/12/26 23:27:39  rasc
DSM-CC  UNT section




*/




#include "dvbsnoop.h"
#include "dsmcc_misc.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"
#include "pes/pes_misc.h"



static int subDescriptor (u_char *b);





/*
 * -- dsmcc descriptor loops  (name, buffer)
 * --- P latform_descriptors
 * --- T arget_descriptors
 * --- O perational descriptors
 * -- return: len
 */

int dsmcc_pto_descriptor_loop (char *name, u_char *b)
{
   int loop_length;
   int len,i;

   out_NL (3);
   out_nl (3,"%s_descriptor_loop:",name);
   indent (+1);

     outBit_Sx_NL (6,"reserved: ",		b,0,4);

     out (4,name);
     loop_length = outBit_Sx_NL (4,"_loop_length: ",	b,4,12);
     len = loop_length;
     b += 2;

     indent (+1);
     while (len > 0) {
	 i   = descriptor (b, DSMCC_INT_UNT);
	 b   += i;
	 len -= i;
     }
     out_NL (4);

   indent (-2);
   return  (loop_length +2);
}






/*
 * ETSI TS 102 006 V1.2.1 (2002-10)
 * ISO/IEC 13818-6
 * This is a special descriptor loop
 */

int dsmcc_CompatibilityDescriptor(u_char *b)
{
   int  len, len_descr;
   int  count;


   out_nl (3,"DSMCC_Compatibility Descriptor (loop):");

   indent (+1);
   len   = outBit_Sx_NL (4,"compatibilityDescriptorLength: ",	b, 0,16);
   len_descr = len + 2;

   if (len > 0) {

   	count = outBit_Sx_NL (4,"DescriptorCount: ",		b,16,16);
	b += 4;
	len -= 4;


	while (count-- > 0) {
		int  subDesc_count;


		if (len <= 0) break;

		out_nl (4,"Descriptor (loop):");
		indent (+1);

   		outBit_S2x_NL (4,"descriptorType: ",		b, 0, 8,
				(char *(*)(u_long))dsmccStr_DescriptorType );
   		outBit_Sx_NL (4,"descriptorLength: ",		b, 8, 8);

   		outBit_S2x_NL (4,"specifierType: ",		b,16, 8,
				(char *(*)(u_long))dsmccStr_SpecifierType );
   		outBit_S2x_NL (4,"specifierData: ",		b,24,24,
				(char *(*)(u_long))dsmccStrOUI );
   		outBit_Sx_NL (4,"Model: ",			b,48,16);
   		outBit_Sx_NL (4,"Version: ",			b,64,16);

   		subDesc_count = outBit_Sx_NL (4,"SubDescriptorCount: ", b,80, 8);
		b   += 11;
		len -= 11;

		while (subDesc_count > 0) {
			int  i;

			if (len <= 0) break;

			out_nl (5,"SubDescriptor (loop):");
			indent (+1);
			i = subDescriptor (b);
   			indent (-1);
			b += i;
			len -= i;
		}
   		indent (-1);
   	}

   } // len > 0


   indent (-1);
   return len_descr;
}





static int subDescriptor (u_char *b)

{
  int len;

  outBit_Sx_NL (5,"SubDescriptorType: ", 	b, 0, 8); 
  len = outBit_Sx_NL (5,"SubDescriptorlength: ",b, 8, 8);

  print_databytes (4,"Additional Information:", b+2, len);

  return len + 2;
}











/*
 * ISO/IEC 13818-6
 * dsmccMessageHeader() 
 * returns some header info in DSM_MSG_HD struct
 * (msg_len is len after read header incl. adaptation field)
 */

int dsmcc_MessageHeader (int v, u_char *b, int len,  DSMCC_MSG_HD *d)
{
   u_char *b_start = b;
   int    adapt_len;
   int    pdiscr;


   	d->dsmccType = 0;
   	d->messageId = 0;
   	d->transaction_id = 0;
   	d->msg_len = 0;

	out_nl (v, "DSM-CC Message Header:");
	indent (+1);
  	pdiscr = outBit_Sx_NL (v,"protocolDiscriminator: ", 	b  , 0, 8);   // $$$ TODO table 
	if (pdiscr != 0x11) {
		out_nl (v, " ==> wrong protocol discriminator (should be 0x11)");
		print_databytes (4, "Message header bytes: ", b+1, len-1);
		return len;
	}



  	d->dsmccType = outBit_S2x_NL (4,"dsmccType: ",	b+1, 0, 8,
			(char *(*)(u_long))dsmccStr_dsmccType);
  
  	d->messageId = outBit_S2x_NL (v,"messageId: ", 	b+2, 0, 16,
			(char *(*)(u_long))dsmccStr_messageID);	


  	d->transaction_id = (d->dsmccType == 0x03 && d->messageId == DownloadDataBlock)
		? outBit_Sx_NL (v,"downloadId: ",  b+4, 0, 32)
		: dsmcc_print_transactionID_32 (v, b+4);


  		      outBit_Sx_NL (v,"reserved: ", 		b+8, 0,  8);
  	adapt_len   = outBit_Sx_NL (v,"adaptationLength: ",	b+9, 0,  8);
  	d->msg_len  = outBit_Sx_NL (v,"messageLength: ",	b+10,0, 16);
	b += 12;
	// len -= 12;


	if (adapt_len > 0) {
		int x;

		x = dsmcc_AdaptationHeader (v, b, adapt_len);
		b += x;
		// len -= x;
		d->msg_len -= x;
	}

	indent (-1);

	return b - b_start;
}









/*
 * ISO/IEC 13818-6
 * dsmccAdaptationHeader() 
 */

int dsmcc_AdaptationHeader (int v, u_char *b, int len)
{
   int  ad_type;
   int  len_org = len;

 
	out_nl (v, "Adaptation Header:");
 	ad_type = outBit_S2x_NL (4,"adaptationType: ",	b, 0, 8,
			(char *(*)(u_long))dsmccStr_adaptationType);
	b++;
	len--;

	out_NL (v);
	indent (+1);
	switch (ad_type) {

		case 0x01: 		// conditional Access
			dsmcc_ConditionalAccess (v, b, len);
			break;

		case 0x02: 		// user ID
			dsmcc_UserID (v, b, len);
			break;

		case 0x03: 		// DIImsgNumber (ISO 13818-6:1998 AMD)
			outBit_Sx_NL  (v,"DIImsgNumber: ", 	b, 0,  8);
			break;

		case 0x04: 		// pts (ATSC a91)
			outBit_Sx_NL  (v,"reserved: ", 			b,  0, 16);
			outBit_Sx_NL  (v,"byte-aligning ('0010'): ", 	b, 16,  4);
			print_xTS_field (v,"PTS", 			b, 20);
			break;

		default:
  			print_databytes (v,"adaptationDataByte:", b, len);
			break;
	}
	indent (-1);
	out_NL (v);


	return len_org;
}




/*
 * ISO/IEC 13818-6
 * dsmccConditionalAccess() 
 */

int dsmcc_ConditionalAccess (int v, u_char *b, int len)
{
   int  len2;

	out_nl (v, "Conditional Acess:");
	indent (+1);
  	outBit_Sx_NL  (v,"reserved: ",	 	b  , 0,  8);
 	outBit_S2x_NL (v,"caSystemId: ",	b+1, 0, 16,
			(char *(*)(u_long)) dvbstrCASystem_ID);

  	len2 = outBit_Sx_NL  (v,"conditionalAccessLength: ", 	b+3, 0, 16);
	print_databytes (v,"conditionaAccessDataByte:", b+5, len2);

	indent (-1);
	return (5 + len2);
}




/*
 * ISO/IEC 13818-6
 * dsmccUserID () 
 */

int dsmcc_UserID (int v, u_char *b, int len)
{
	out_nl (v, "User ID:");
	indent (+1);
  	outBit_Sx_NL  (v,"reserved: ",	 	b  , 0,  8);

	// print_databytes (v,"UserId:", b+1, 20);
	dsmcc_carousel_NSAP_address_B20 (v, "UserId: ", b+1);

	indent (-1);
	return 21;
}



/*
 * print transactionID detail
 * ISO/IEC 13818-6
 * TS 102 812 v1.2.1  B.2.7
 * split transactionID in parts and print
 * return: transaction_id
 */

u_long dsmcc_print_transactionID_32 (int v, u_char *b)
{
  u_long  t_id;

  	t_id = outBit_Sx_NL  (v,"transactionID: ", 	b,  0, 32);

  	outBit_S2x_NL (v,"  ==> originator: ", 		b,  0,  2,
			(char *(*)(u_long)) dsmccStr_transactionID_originator);
  	outBit_Sx_NL  (v,"  ==> version: ", 		b,  2, 14);
  	outBit_Sx_NL  (v,"  ==> identification: ", 	b, 16, 15);
  	outBit_Sx_NL  (v,"  ==> update toggle flag: ", 	b, 31,  1);

	return t_id;
	// $$$ TODO  look for other transaction_id usage
}





/*
 * print carousel NSAP  Address
 * ISO/IEC 13818-6
 * ETSI 301 192  9.2.1
 * len = 20 Bytes
 */

int  dsmcc_carousel_NSAP_address_B20 (int v, const char *s, u_char *b)
{
   int  afi;
   int  type,stype;


	// The AFI (authority and format identifier) shall be set to 0x00.
	// This value is defined in ISO 8348 Annex B as NSAP addresses
	// reserved for private use. As such, the rest of the NSAP address
	// fields are available for private definition.
	//
	// The type field shall be set to 0x00 when the Carousel NSAP
	// address points to a U-U Object Carousel. The values in the
	// range 0x01 to 0x7F shall be reserved to ISO/IEC 13818-6. The
	// values in the range 0x80 to 0xFF shall be user private and
	// their use is outside the scope of this part of ISO/IEC 13818.


  	out_nl  (v,"%s  (NSAP address):", s);
	indent (+1);

  	afi  = outBit_Sx_NL  (v,"Authority and Format Identifier: ", 	b   ,  0,  8);
  	type = outBit_Sx_NL  (v,"Type: ", 				b+1 ,  0,  8);


	if (afi != 0x00 || type != 0x00) {

  		print_databytes (v,"address bytes:", b+2, 18);

	} else {


  		outBit_Sx_NL  (v,"carousel id: ",	b+2 ,  0, 32);
		b += 6;


		stype = outBit_S2x_NL (v,"specifier type: ", 	b, 0,  8,
				   (char *(*)(u_long))dsmccStr_SpecifierType );
		if (stype == 0x01) {
			outBit_S2x_NL (v,"OUI: ", 		b, 8, 24,
				   (char *(*)(u_long))dsmccStrOUI );
		} else {
  			outBit_Sx_NL  (v,"specifier: ",		b,  8, 24);
		}



		// -- private data...
		dsmcc_DVB_service_location (v, b);

	}

	indent (-1);
	return 20;
}


/*
 * DVB Service Location
 * ETSI EN 3001 192
 * return: len (=10)
 */

int dsmcc_DVB_service_location (int v, u_char *b)
{

	outBit_Sx_NL  (v,"transport_stream_ID: ",	b,  0, 16);
	outBit_S2x_NL (v,"Original_network_id: ",	b, 16, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);
	outBit_S2Tx_NL(v,"service_ID: ",		b, 32, 16,
			  "--> refers to PMT program_number"); 
	outBit_Sx_NL  (v,"reserved: ",			b, 48, 32);

	return 10;
}







/*
 * carousel descriptor loop
 * ETSI EN 301 192 v1.3.1  8.1.3
 */

int dsmcc_CarouselDescriptor_Loop (const char *s, u_char *b, int len)
{
   int len_org = len;


  if (len > 0) {
	  out_nl (4,"%s  (Carousel Descriptor loop):", s);

	  indent (+1);
	  while (len > 0) {
		int  x;

 		x   = descriptor (b,  DSMCC_CAROUSEL);
		b += x;
		len -= x;
  	}
	  out_NL (4);
  	indent (-1);
  }

  return len_org;
}







