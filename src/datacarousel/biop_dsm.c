/*
$Id: biop_dsm.c,v 1.2 2006/03/06 20:25:37 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- dsmcc  (BIOP) DSM:: routines
 -- TS 102 812 
 -- TS 101 202
 -- ISO  13818-6  



$Log: biop_dsm.c,v $
Revision 1.2  2006/03/06 20:25:37  rasc
DSM-CC Carousell, lots of Bugfixes, BIOP::Message not yet decodable (ddb has to collect Modules)

Revision 1.1  2006/03/06 00:04:49  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...





*/




#include "dvbsnoop.h"
#include "biop_dsm.h"
#include "biop_tag_tap.h"
#include "dsmcc_misc.h"

#include "misc/output.h"
#include "misc/hexprint.h"

#include "strings/dsmcc_str.h"
#include "strings/dvb_str.h"



/*
 * dsmcc  BIOP DSM::ConnBinder();
 * TS 102 812
 * return: len
 */


int BIOP_DSM_ConnBinder (int v, u_char *b)
{
  int      len;
  int      n3;


   out_nl (v,"DSM::ConnBinder");
   indent (+1);

          outBit_S2x_NL (v,"componentId_tag: ",		b,   0, 32,
			(char *(*)(u_long)) dsmccStrIOP_ProfileID );
   len = outBit_Sx_NL (v,"component_data_length: ",	b,  32,  8);


   n3  = outBit_Sx_NL (v,"tap_count: ",			b,  40,  8);
	 b += 6;
	 indent (+1);
	 for (; n3 > 0; n3--) {
		int  n4;

		n4 =  BIOP_TAP (v, "DSM", b);
		b += n4;
	 }
	 indent (-1);


   indent (-1);
   out_NL (v);
   return len+5;
}





/*
 * dsmcc  BIOP DSM::ServiceLocation ();
 * TS 102 812
 * return: len
 */


int BIOP_DSM_ServiceLocation (int v, u_char *b)
{
  int      len;
  int      sd_len;
  int      n;
  u_long   n5;


   out_nl (v,"DSM::ServiceLocation");
   indent (+1);

                outBit_S2x_NL (v,"componentId_tag: ",		b,   0, 32,
			(char *(*)(u_long)) dsmccStrIOP_ProfileID );
   len 	      = outBit_Sx_NL (v,"component_data_length: ",	b,  32,  8);
   len += 4;
   sd_len     = outBit_Sx_NL (v,"service_domain_length: ",	b,  40,  8);
   b += 6;

   BIOP_DSM_ServiceDomain (v,b, sd_len);
   b += sd_len;

   n = BIOP_DSM_CosNaming_Name (v,b);
   b += n;

   n5 = outBit_Sx_NL (v,"initialContext_length: ",	b,   0, 32);
   print_databytes   (v,"InitialContext_data_byte:",    b+4, n5);
   // b += n5;

   indent (-1);
   out_NL (v);
   return len;
}





/*
 *  ServiceDomain Data for DSM::ServiceLocation
 *  return: len
 */

int  BIOP_DSM_ServiceDomain (int v, u_char *b, int len)
{

   dsmcc_carousel_NSAP_address_B20 (v, "DSM::ServiceDomain", b);
   out_NL (v);
   return len;
}





/*
 *  CosNaming::Name for DSM::ServiceLocation
 *  (Similar to BIOP::Name, but 32bit length fields)
 *  return: len
 */

int  BIOP_DSM_CosNaming_Name (int v, u_char *b)
{
 u_char   *b_org = b;
 u_long   n2;


   out_nl (v,"CosNaming::Name");
   indent (+1);

   n2 = outBit_Sx_NL (v,"nameComponents_count: ",	b,   0, 32);
   b   += 4;

   for (; n2 > 0; n2--) {
	u_long    n3,n4;

	n3 = outBit_Sx_NL (v,"id_length: ",		b,   0, 32);
	print_databytes   (v,"id_data:", 	   	b+4, n3);
	b   += 4 + n3;

	n4 = outBit_Sx_NL (v,"kind_length: ",		b,   0, 32);
	print_databytes   (v,"kind_data:", 	   	b+4, n4);
	b   += 4 + n4;

   }

   indent (-1);
   out_NL (v);
   return (int) (b - b_org);
}






/*
 *  DSM::Stream::Info_T  for BIOP Messages
 *  return: len
 */

int  BIOP_DSM_Stream_Info_T (int v, u_char *b)
{
  int   n;


   out_nl (v,"DSM::Stream::Info_T");
   indent (+1);

   n = outBit_Sx_NL (v,"aDescription_length: ",		b,   0, 8);
   print_databytes   (v,"aDescription:",    		b+1, n);
   b += 1+n;


   outBit_Sx_NL (v,"duration.aSeconds: ",		b,   0, 32);
   outBit_Sx_NL (v,"duration.aMicroSeconds: ",		b,  32, 32);

   outBit_Sx_NL (v,"audio: ",				b,  64,  8);
   outBit_Sx_NL (v,"video: ",				b,  72,  8);
   outBit_Sx_NL (v,"data: ",				b,  80,  8);


   indent (-1);
   out_NL (v);


   // there might be an error in all Standards document????
   // saying:  N2- (N3+10) on a for-loop in BIOP::StreamMessage
   // (the +10 should be: +12)
   // for BIOP::StreamEventMessage calculations are correctly described
   // $$$ TODO: to be checked
 
   return (1 + n + 11);
}






/*
 *  DSM::Event::EventList_T  for BIOP Messages
 *  return: len
 */

int  BIOP_DSM_Event_EventList_T (int v, u_char *b)
{
  u_char  *b_org = b;
  int     n1;



   out_nl (v,"DSM::Event::EventList_T");
   indent (+1);

   n1 = outBit_Sx_NL (v,"eventNames_count: ",		b,   0, 16);
   b += 2;

   indent (+1);
   for (; n1 > 0; n1--) {
	int   n2;

   	n2 = outBit_Sx_NL (v, "eventName_length: ",	b,   0,  8);
	print_text_UTF8   (v, "eventName_data: ", 	b+1, n2);
	b += 1 + n2;
   }
   indent (-1);


   indent (-1);
   out_NL (v);
   return (int) (b - b_org);
}






