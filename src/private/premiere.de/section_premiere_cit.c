/*
$Id: section_premiere_cit.c,v 1.3 2006/01/02 18:24:16 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- User defined table // Private
  -- Premiere Content Information Table CIT



$Log: section_premiere_cit.c,v $
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
#include "section_premiere_cit.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"



void section_PRIVATE_PremiereDE_CIT (u_char *b, int len)
{
 u_int      table_id;
 u_int      section_syntax_indicator;
 u_int      section_length;


 out_nl (3,"User_Defined-decoding....");
 table_id = outBit_S2Tx_NL (3,"Table_ID: ",	b, 0, 8,
		 "Premiere Content Information Table");
 if (table_id != 0xa0) {
   out_nl (3,"wrong Table ID");
   return;
 }


 section_syntax_indicator = 
 	outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8, 1);	// ==1 
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
   // -- Premiere Content Information Table CIT
   // -- provided by  Peter.Pavlov (Premiere.de)
   //


   out_NL (3);
   outBit_Sx_NL (3,"Content id: ",		b, 0, 32);
   outBit_Sx_NL (3,"Duration: ",			b, 32,24);
   outBit_Sx_NL (3,"Reserved: ",			b, 56, 4);
   outBit_Sx_NL (5,"descriptor_section_length: ",	b, 60,12);

   b += 9;
   section_length -=9;

   while (section_length > 4 ) {
	int x;

      	x = descriptor (b, DVB_SI);
      	if (section_length < x) break;
      	b    += x;
      	section_length -= x;
   }




   outBit_Sx_NL (5,"CRC: ",		b, 0, 32);

}




