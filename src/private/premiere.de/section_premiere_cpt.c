/*
$Id: section_premiere_cpt.c,v 1.3 2006/01/02 18:24:16 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- User defined table // Private
  -- Premiere Content Information Table CIT



$Log: section_premiere_cpt.c,v $
Revision 1.3  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2004/11/04 19:21:11  rasc
Fixes and changes on "premiere.de" private sections
Cleaning up "premiere.de" private descriptors (should be final now)

Revision 1.1  2004/11/03 21:01:02  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections




*/




#include "dvbsnoop.h"
#include "section_premiere_cpt.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"



void section_PRIVATE_PremiereDE_CPT (u_char *b, int len)
{
 u_int      table_id;
 u_int      section_syntax_indicator;
 u_int      section_length;
 u_int      time_MJD, time_UTC;
 u_int 	    i, content_list_length;



 out_nl (3,"User_Defined-decoding....");
 table_id = outBit_S2Tx_NL (3,"Table_ID: ",	b, 0, 8,
		 "Premiere Content Presentation Table");

 if (table_id != 0xa1) {
   out_nl (3,"wrong Table ID");
   return;
 }


 section_syntax_indicator = 
 	outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8, 1);	// == 1
 	outBit_Sx_NL (3,"private_indicator: ",		b, 9, 1);
 	outBit_Sx_NL (6,"reserved: ",			b,10, 2);
 section_length =
	outBit_Sx_NL (5,"private_section_length: ",	b,12,12);




 	outBit_Sx_NL (3,"table_id_extension: ",		b, 24,16);
 	outBit_Sx_NL (6,"reserved: ",			b, 40, 2);
 	outBit_Sx_NL (3,"Version_number: ",		b, 42, 5);
	outBit_S2x_NL(3,"Current_next_indicator: ",	b, 47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
	outBit_Sx_NL (3,"Section_number: ",		b, 48, 8);
	outBit_Sx_NL (3,"Last_section_number: ",	b, 56, 8);

	b += 8;
	section_length -= 5;


   //
   // -- Premiere Content Presentation Table CIT
   // -- provided by  Peter.Pavlov (Premiere.de)
   //


	outBit_Sx_NL (4,"Transport_stream_ID: ",b, 0, 16);
 	outBit_Sx_NL (4,"Original_network_ID: ",b, 16, 16);
 	outBit_Sx_NL (4,"virtual_channel_id: ",b, 32, 32);
 	outBit_Sx_NL (4,"virtual_channel_name_length: ",b, 64, 8);
	b+=8;
	print_text_468A (4, "virtual_channel_name: ", b+1, *b);
	section_length -= 9+*b;
	b += *b+1;
	outBit_Sx_NL  (4,"reserved: ",b, 0, 4);
	outBit_Sx_NL  (4,"virtual_channel_info_length: ",b, 4, 12);
	b+=2;
	section_length -= 2;

	while (section_length > 4) {

 		time_MJD = getBits (b, 0, 0, 16);
 		time_UTC = getBits (b, 0, 16, 24);
 		out (4,"start_time: ");
 		print_time40 (4, time_MJD, time_UTC);
 		out_NL (4);
    		out_nl (4,"duration: %02x:%02x:%02x",
			*(b+5), *(b+6), *(b+7));
		b+=8;
		outBit_Sx_NL  (4,"virtual_event_name_length: ",b, 0, 8);
		print_text_468A (4, "virtual_event_name: ", b+1, *b);

		section_length -= *b+9;
		b += *b+1;

		outBit_Sx_NL  (4,"virtual_event_info_length: ",b, 0, 8);
		print_text_468A (4, "virtual_event_info: ", b+1, *b);

		section_length -= *b+1;
		b += *b+1;

		outBit_Sx_NL  (4,"reserved: ",b, 0, 4);
		outBit_Sx_NL  (4,"content_list_length: ",b, 4, 12);
		content_list_length = ((b[0]&15)<<8)+b[1];
		for(i=0, b+=2; i<content_list_length; i+=4, b+=4)
			{
 			outBit_Sx_NL (4,"content_id: ",b, 0, 32);
			}
		section_length -= content_list_length+2;
	}


 	outBit_Sx_NL (5,"CRC: ",		b, 0, 32);

}




