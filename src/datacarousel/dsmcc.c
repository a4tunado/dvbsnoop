/*
$Id: dsmcc.c,v 1.11 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  DSM-CC Section
 --  DSM-CC Data Carousel
 --   ETSI TR 101 202
 --   ISO/IEC 13818-6



$Log: dsmcc.c,v $
Revision 1.11  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.10  2004/10/17 22:20:35  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.9  2004/02/15 18:58:27  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.8  2004/02/15 01:01:00  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed

Revision 1.7  2004/02/14 01:24:44  rasc
DSM-CC started  (DSI/DII, DDB)

Revision 1.6  2004/01/22 22:26:34  rasc
pes_pack_header
section read timeout

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

Revision 1.1  2003/12/27 00:21:16  rasc
dsmcc section tables




*/



#include "dvbsnoop.h"
#include "dsmcc.h"
#include "dsmcc_ddb.h"
#include "dsmcc_unm.h"
#include "dsmcc_misc.h"
#include "llc_snap.h"

#include "descriptors/descriptor.h"
#include "strings/dsmcc_str.h"
#include "strings/dvb_str.h"

#include "misc/output.h"
#include "misc/hexprint.h"




static void DSMCC_descriptor_list (u_char *b, int len);



void section_DSMCC (u_char *b, int len)
{
 /* TR 101 202 */

 int        len1;
 u_int      table_id;
 u_int      section_length;
 u_int      section_syntax_indicator;
 u_int      private_indicator;
 u_int	    sect_nr;
 u_int      last_sect_nr;



 out_nl (3,"DSM-CC-decoding....");
 table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
 if (table_id < 0x3a || table_id > 0x3e) {
   out_nl (3,"wrong Table ID");
   return;
 }


 section_syntax_indicator =
	 outBit_Sx_NL (4,"Section_syntax_indicator: ",	b, 8, 1);
 private_indicator = 
	 outBit_Sx_NL (4,"private_indicator: ",		b, 9, 1);
 outBit_Sx_NL (6,"reserved_1: ",			b,10, 2);
 section_length =
	 outBit_Sx_NL (5,"dsmcc_section_length: ",	b,12,12);


 outBit_Sx_NL (3,"table_id_extension: ",		b,24,16);
 outBit_Sx_NL (6,"reserved_3: ",		b,40, 2);

 outBit_Sx_NL (3,"Version_number: ",		b,42, 5);
 outBit_S2x_NL(3,"Current_next_indicator: ",	b,47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );

 sect_nr      = outBit_Sx_NL (3,"Section_number: ",		b,48, 8);
 last_sect_nr = outBit_Sx_NL (3,"Last_section_number: ",	b,56, 8);


 b += 8;
 len1 = section_length - 5 - 4;	    	// -4 == CRC/Checksum



 if (table_id == 0x3A) {

	llc_snap (3,b);		 	//  ISO/IEC 8802-2 

 } else if (table_id == 0x3B) {

	dsmcc_UserNetworkMessage (4, b, len1);

 } else if (table_id == 0x3C) {

	dsmcc_DownloadDataMessage (4, b, len1);

 } else if (table_id == 0x3D) {

	DSMCC_descriptor_list (b,len1);

 } else if (table_id == 0x3E) {	 	// $$$ Remark: DVB defines 0x3E as datagram!!

	 print_private_data (4, b, len1);

 }

 b += len1;



 outBit_Sx_NL (5, (section_syntax_indicator)
		   ?"CRC: " :"Checksum: ",	b,0,32);
}





/*
NOTE 1: The DownloadServerInitiate message, the DownloadInfoIndication
	message, and the DownloadCancel message are in the
	userNetworkMessage class.
NOTE 2: The DownloadDataBlock message is within the downloadMessage class.
*/



static void DSMCC_descriptor_list (u_char *b, int len)
{
   int x;

   while (len > 0) {
	  x = descriptor (b, DSMCC_STREAM);
	  b += x;
	  len -= x;
   }

}






/*
 * $$$ TODO
 *
 *
table_id_extension: This 16-bit field is set as shown below according to table_id field:
When the value of the table_id field equals 0x3B, this field must convey a copy of the least
significant two bytes of the transaction_id field .
When the value of the table_id field equals 0x3C, this field must convey a copy of the module_id
field.



B.2.4.3.4 DSM-CC sections for DSMCC_descriptor_list()
If the table_id .eld equals 0x3D the current_next_indicator bit shall be set to "1".
B.2.4.3.5 Encoding of table id extension
The section's table id extension .eld provides information on the stream descriptor(s)carried by the section:
Table B.31 :Encoding of table id extension for DSMCC_descriptor_lists
table_id_extension bits
Payload of DSM-CC section with table ID 0x3D
[15 ][14 ][13 …0 ]
0 0 eventID [13 …0 ]Section carries a single "do it now"event
0 1 xx xxxx xxxx Section carries NPT reference descriptors
1 0 xx xxxx xxxx
Section carries one or more other stream descriptors.I.e
-Stream event descriptor(s)with a future eventNPTs
-Stream mode descriptor (can be ignored in this speci .cation)
-NPT endpoint descriptor (can be ignored in this speci .cation)
1 1 reserved for future use

The value of eventID for "do it now"events shall be in the range 0x0001 …0x3FFF.The value of eventID for scheduled
events shall be in the range 0x8000 …0xBFFF.The value 0 is not allowed (see 5.5.2.2.1 in ISO/IEC 13818-6 [26 ]).


*/





