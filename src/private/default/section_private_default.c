/*
$Id: section_private_default.c,v 1.2 2006/01/02 18:24:16 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- User defined table // Private
  -- ISO 13818-1 // ITU H.222.0 private_section



$Log: section_private_default.c,v $
Revision 1.2  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/11/03 21:01:00  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.5  2004/02/16 22:45:37  rasc
small bugfix: crc is 32 bit

Revision 1.4  2004/01/02 16:40:40  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.3  2004/01/01 20:09:31  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.2  2003/10/24 22:17:21  rasc
code reorg...

Revision 1.1  2003/10/19 13:59:00  rasc
-more table decoding



*/




#include "dvbsnoop.h"
#include "section_private_default.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"



void section_PRIVATE_default (u_char *b, int len)
{
 u_int      table_id;
 u_int      section_syntax_indicator;
 u_int      section_length;



 out_nl (3,"User_Defined-decoding....");
 table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
 if (table_id < 0x80) {
   out_nl (3,"wrong Table ID");
   return;
 }


 section_syntax_indicator = 
 	outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8, 1);
 	outBit_Sx_NL (3,"private_indicator: ",		b, 9, 1);
 	outBit_Sx_NL (6,"reserved: ",			b,10, 2);
 section_length = 
	outBit_Sx_NL (5,"private_section_length: ",	b,12,12);


 if (section_syntax_indicator == 0) {
	b += 3;
 } else {

 	outBit_Sx_NL (3,"table_id_extension: ",		b, 24,16);
 	outBit_Sx_NL (6,"reserved: ",			b, 40, 2);
 	outBit_Sx_NL (3,"Version_number: ",		b, 42, 5);
	outBit_S2x_NL(3,"Current_next_indicator: ",	b, 47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
	outBit_Sx_NL (3,"Section_number: ",		b, 48, 8);
	outBit_Sx_NL (3,"Last_section_number: ",	b, 56, 8);

	b += 8;
	section_length -= (5+4);		// 4:  CRC
 }

 print_private_data (3,b,section_length);
 b += section_length;

 if (section_syntax_indicator != 0) {
 	outBit_Sx_NL (5,"CRC: ",		b, 0, 32);
 }

}




