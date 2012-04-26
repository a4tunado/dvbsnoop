/*
$Id: biop.c,v 1.2 2006/03/06 20:25:37 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc  BIOP  LITE_TAG...
 -- ISO/IEC 13818-6
 -- ETSI TS 101 202
 -- ETSI TS 102 812
 -- ATSC A95
 -- ATSC A47




$Log: biop.c,v $
Revision 1.2  2006/03/06 20:25:37  rasc
DSM-CC Carousell, lots of Bugfixes, BIOP::Message not yet decodable (ddb has to collect Modules)

Revision 1.1  2006/03/06 00:04:49  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...





*/




#include "dvbsnoop.h"
#include "biop.h"
#include "biop_tag_tap.h"
#include "dsmcc_misc.h"

#include "misc/output.h"
#include "strings/dsmcc_str.h"



static u_long  _ProfileBody  (int v, u_char *b);









/*
  -- dsmcc BIOP LiteOptionsProfileBody
  -- return: len
 */

u_long  BIOP_LiteOptionsProfileBody  (int v, u_char *b)
{
  u_long   len;

   //  first component should be a DSM:ServiceLocation()

  out_nl (v, "LiteOptionsProfileBody"); 
  indent (+1);
  len = _ProfileBody  (v, b);
  indent (-1);
  return len;
}



/*
  -- dsmcc BIOP BIOPProfileBody
  -- return: len
 */

u_long  BIOP_BIOPProfileBody  (int v, u_char *b)
{
  u_long   len;

   //  first  component should be a BIOP::ObjectLocation()
   //  second component should be a DSM::ConBinder()
  out_nl (v, "BIOPProfileBody"); 
  indent (+1);
  len = _ProfileBody  (v, b);
  indent (-1);
  return len;
}




/*
  -- dsmcc Basic   BIOP/Lite ProfileBody
  -- return: len
 */

u_long  _ProfileBody  (int v, u_char *b)
{
  u_char   *b_org = b;
  u_long   len;
  int      byte_order;
  int      N1;



                outBit_S2x_NL(v,"profileId_tag: ",		b,   0, 32,
			(char *(*)(u_long)) dsmccStrIOP_ProfileID );
   len 	      = outBit_Sx_NL (v,"profile_data_length: ",	b,  32, 32);


   byte_order = outBit_S2x_NL(v,"profile_data_byte_order: ",	b,  64,  8,
		   	(char *(*)(u_long)) dsmccStrBIOP_EndianType );
   if (byte_order != 0x00) {
	   out_nl (v, "==> Error: unsupported byte endian order");
	   print_databytes (v,"profile_data:", b+9, len-1); 
	   return len + 8;
   }

   
   // -- do components
 
   N1        = outBit_Sx_NL (v,"lite_component_count: ",	b,  72,  8);
   b += 10;

   out_nl (v,"LiteComponents:");
   for (; N1 > 0; N1--) {
	int   len2;

   	indent (+1);
	len2  = BIOP_LiteComponent (v,b);
	b += len2;
   	indent (-1);
   }


   return (u_long) (b - b_org);
}





/*
  -- dsmcc BIOP::LiteComponent
  -- return: len
 */

u_long  BIOP_LiteComponent (int v, u_char *b)
{
  u_long   len;


  len = BIOP_TAG_dispatch (v, b);
  return  len;
}





/*
  -- dsmcc BIOP::ObjectLocation
  -- return: len
 */

u_long  BIOP_ObjectLocation (int v, u_char *b)
{
  int   len;
  int   n2;


          outBit_S2x_NL(v,"component_tag: ",		b,   0, 32,
			(char *(*)(u_long)) dsmccStrIOP_ProfileID );
  len = outBit_Sx_NL (v,"component_data_length: ",	b,  32,  8);

   	outBit_Sx_NL (v,"carouselId: ",			b,  40, 32);
   	outBit_Sx_NL (v,"moduleId: ",			b,  72, 16);
   	outBit_Sx_NL (v,"version.major: ",		b,  88,  8);
   	outBit_Sx_NL (v,"version.minor: ",		b,  96,  8);

  n2  = outBit_Sx_NL (v,"objectKey_length: ",		b, 104,  8);
	print_databytes (v,"objectKey_data:",		b+14, n2); 


   return len + 5;
}




/*
  -- dsmcc BIOP::Name
  -- Similar to CosNaming::Name  (which is 32bit)
  -- return latest kind_data in *kind (32 bit), if kind != NULL
  -- return: len
 */

int  BIOP_Name (int v, u_char *b, u_long *kind)
{
 u_char   *b_org = b;
 u_long   n2;


   out_nl (v,"BIOP::Name");
   indent (+1);

   n2 = outBit_Sx_NL (v,"nameComponents_count: ",	b++,   0, 8);

   for (; n2 > 0; n2--) {
	u_long    n3,n4;

	n3 = outBit_Sx_NL (v,"id_length: ",		b++,   0,  8);
	print_databytes   (v,"id_data:", 	   	b, n3);
	b  += n3;

	n4 = outBit_Sx_NL (v,"kind_length: ",		b++,   0,  8);
	print_databytes   (v,"kind_data:", 	   	b, n4);
	if (kind) {
		*kind =	getBits (b, 0, 0, 32);	// type aliases
	}
	b  += n4;

   }

   indent (-1);
   return (int) (b - b_org);
}





