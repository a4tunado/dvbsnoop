/*
$Id: rnt.c,v 1.6 2006/04/04 17:27:56 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  Resolution Notification Table (RNT)
 --  Resolution provider Notification Section
 --  TS 102 323



$Log: rnt.c,v $
Revision 1.6  2006/04/04 17:27:56  rasc
no message

Revision 1.5  2006/01/02 18:24:46  rasc
just update copyright and prepare for a new public tar ball

Revision 1.4  2005/07/18 21:11:41  rasc
TVA Content Section

Revision 1.3  2004/10/17 22:20:39  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.2  2004/07/26 20:58:03  rasc
RNT completed..  (TS 102 323)

Revision 1.1  2004/07/25 21:13:37  rasc
do not forget to commit new files
- RNT resolution_authority/provider_notification_section (TS 102 323)



*/




#include "dvbsnoop.h"
#include "rnt.h"

#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"





void section_TVA_RNT (u_char *b, int len)
{
 /* TS 102 323  */

 u_int      len1,len2;
 u_int      table_id;
 u_int      section_length;



  out_nl (3,"RNT-decoding....");
  table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
  if (table_id != 0x79) {
    out_nl (3,"wrong Table ID");
    return;
  }


  outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8,  1);
  outBit_Sx_NL (6,"reserved: ",			b, 9,  1);
  outBit_Sx_NL (6,"reserved: ",			b,10,  2);
  section_length = outBit_Sx_NL (5,"section_length: ",	b,12,12);

  outBit_Sx_NL (3,"context_id: ",		b,24, 16);
  outBit_Sx_NL (6,"reserved_3: ",		b,40,  2);
  outBit_Sx_NL (3,"version_number: ",		b,42,  5);

  outBit_S2x_NL(3,"Current_next_indicator: ",	b,47,  1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
  outBit_Sx_NL (3,"Section_number: ",		b,48,  8);
  outBit_Sx_NL (3,"Last_section_number: ",	b,56,  8);


  outBit_S2x_NL(3,"context_id_type: ",		b,64,  8,
			(char *(*)(u_long))dvbstrTVA_content_id_type );



  len2 = outBit_Sx_NL (3,"common_descriptor_length: ",	b,72, 12);
  outBit_Sx_NL (6,"reserved: ",				b,84,  4);

  b += 11;
  len1 = section_length - 8;


  // common descriptor loop 

  out_nl (3,"Common_descriptor_loop:");
  indent (+1);
  while (len2 > 0) {
	 int i;
	 i   = descriptor (b, TVA_RNT);
	 b    += i;
	 len1 -= i;
	 len2 -= i;
	 out_NL (4);
  }
  indent (-1);


  // resolution provider info loop

  out_nl (3,"resolution_provider_info_loop:");
  indent (+1);
  while (len1 > 0) {
	int len2, len3;

  	len2 = outBit_Sx_NL (3,"resolution_provider_info_length: ",	b,  0, 12);
  	outBit_Sx_NL (6,"reserved: ",					b, 12,  4);

  	len3 = outBit_Sx_NL (3,"resolution_provider_name_length: ",	b, 16,  8);
	print_std_ascii     (3,"resolution_provider_name: ", 		b+3, len3);
	b    += len3 + 3;
	len1 -= len3 + 3;
	len2 -= len3 + 3;


  	// resolution_provider_descriptors loop 

  	len3 = outBit_Sx_NL (3,"resolution_provider_descriptor_length: ", 	b, 0, 12);
  	outBit_Sx_NL (6,"reserved: ",						b, 12, 4);
	b    += 2;
	len1 -= 2;
	len2 -= 2;

	out_nl (3,"resolution_provider_descriptor_loop:");
	indent (+1);
	while (len3 > 0) {
		int i;
		i   = descriptor (b, TVA_RNT);
		b    += i;
		len1 -= i;
		len2 -= i;
		len3 -= i;
	 	out_NL (4);
	}
	indent (-1);


	// CRID_authority loop

	out_nl (3,"CRID_authority_loop:");
	indent (+1);
	while (len2 > 0) {

		len3 = outBit_Sx_NL (3,"CRID_authority_name_length: ",	b,  0,  8);
		print_std_ascii     (3,"CRID_authority_name: ", 	b+1, len3);
		b    += len3 + 1;
		len1 -= len3 + 1;
		len2 -= len3 + 1;


	 	// CRID_authority_descriptors loop 

  		len3 = outBit_Sx_NL (3,"CRID_authority_descriptors_length: ", 	b, 0, 12);
	  	outBit_Sx_NL (6,"reserved: ",					b, 12,  4);
		b    += 2;
		len1 -= 2;
		len2 -= 2;

		out_nl (3,"CRID_authority_descriptor_loop:");
		indent (+1);
		while (len3 > 0) {
			int i;
			i   = descriptor (b, TVA_RNT);
			b    += i;
			len1 -= i;
			len2 -= i;
			len3 -= i;
	 		out_NL (4);
		}
		indent (-1);

	}
	indent (-1);

  }
  indent (-1);



  outBit_Sx_NL (5,"CRC: ",	b,0,32);
}




// Annotation:
//
// $$$ TODO:  RNT is untested so far !!!
//  need stream with  RNT data
