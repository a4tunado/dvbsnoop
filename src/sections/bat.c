/*
$Id: bat.c,v 1.11 2006/01/02 18:24:24 rasc Exp $

 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


   -- BAT section
   -- Bouquet Allocation Table
   -- ETSI EN 300 468     5.2.2



$Log: bat.c,v $
Revision 1.11  2006/01/02 18:24:24  rasc
just update copyright and prepare for a new public tar ball

Revision 1.10  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.9  2004/02/12 21:21:21  rasc
MHP AIT descriptors
some smaller changes

Revision 1.8  2004/02/07 01:28:04  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.7  2004/01/01 20:09:31  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.6  2003/10/24 22:17:20  rasc
code reorg...

Revision 1.5  2003/10/16 19:02:26  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.4  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.3  2001/12/01 12:34:44  rasc
pespacket weitergestrickt, leider z.Zt. zuwenig Zeit um es richtig fertig zu machen.

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS



*/




#include "dvbsnoop.h"
#include "bat.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"




void section_BAT (u_char *b, int len)
{

 typedef struct  _BAT {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;
    u_int      bouquet_id;
    u_int      reserved_3;
    u_int      version_number;
    u_int      current_next_indicator;
    u_int      section_number;
    u_int      last_section_number;
    u_int      reserved_4;
    u_int      bouquet_descriptors_length;

    // N  descriptor

    u_int      reserved_5;
    u_int      transport_stream_loop_length;

    // N1 BAT_LIST2

    unsigned long crc;
 } BAT;


 typedef struct _BAT_LIST2 {
    u_int      transport_stream_id;
    u_int      original_network_id; 
    u_int      reserved_1;
    u_int      transport_descriptors_length;

    // N2 descriptor

 } BAT_LIST2;



 BAT        t;
 BAT_LIST2  t2;
 int        len1,len2;


 
 t.table_id 			 = b[0];
 t.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 t.reserved_1 			 = getBits (b, 0, 9, 1);
 t.reserved_2 			 = getBits (b, 0, 10, 2);
 t.section_length		 = getBits (b, 0, 12, 12);
 t.bouquet_id			 = getBits (b, 0, 24, 16);
 t.reserved_3 			 = getBits (b, 0, 40, 2);
 t.version_number 		 = getBits (b, 0, 42, 5);
 t.current_next_indicator	 = getBits (b, 0, 47, 1);
 t.section_number 		 = getBits (b, 0, 48, 8);
 t.last_section_number 		 = getBits (b, 0, 56, 8);
 t.reserved_4	 		 = getBits (b, 0, 64, 4);
 t.bouquet_descriptors_length	 = getBits (b, 0, 68, 12);


 out_nl (3,"BAT-decoding....");
 out_S2B_NL (3,"Table_ID: ",t.table_id, dvbstrTableID (t.table_id));
 if (t.table_id != 0x4A) {
   out_nl (3,"wrong Table ID");
   return;
 }

 out_SB_NL (3,"section_syntax_indicator: ",t.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",t.reserved_1);
 out_SB_NL (6,"reserved_2: ",t.reserved_2);
 out_SW_NL (5,"Section_length: ",t.section_length);
 out_S2W_NL(3,"Bouquet_ID: ",t.bouquet_id,dvbstrBouquetTable_ID(t.bouquet_id));
 out_SB_NL (6,"reserved_3: ",t.reserved_3);
 out_SB_NL (3,"Version_number: ",t.version_number);
 
 out_S2B_NL(3,"current_next_indicator: ",t.current_next_indicator, dvbstrCurrentNextIndicator(t.current_next_indicator));
 out_SB_NL (3,"Section_number: ",t.section_number);
 out_SB_NL (3,"Last_Section_number: ",t.last_section_number);

 out_SB_NL (6,"reserved_4: ",t.reserved_4);
 out_SW_NL (5,"Bouquet_descriptors_length: ",t.bouquet_descriptors_length);


 len1 = t.section_length - 10;
 b   += 10;

 len2 = t.bouquet_descriptors_length;
 indent (+1);
 while (len2 > 0) {
   int x;

   x = descriptor (b, DVB_SI);
   len2 -= x;
   b += x;
   len1 -= x;
 }
 indent (-1);
 out_NL (3);


 t.reserved_5	 		 = getBits (b, 0, 0, 4);
 t.transport_stream_loop_length	 = getBits (b, 0, 4, 12);

 out_SB_NL (6,"reserved_5: ",t.reserved_5);
 out_SW_NL (5,"Transport_stream_loop_length: ",t.transport_stream_loop_length);

 b += 2;


 indent(+1);
 while (len1 > 4) {

   t2.transport_stream_id	 = getBits (b, 0,  0,  16);
   t2.original_network_id	 = getBits (b, 0, 16,  16);
   t2.reserved_1		 = getBits (b, 0, 32,   4);
   t2.transport_descriptors_length = getBits (b, 0, 36,  12);

   out_NL (3);
   out_SW_NL  (3,"Transport_stream_ID: ",t2.transport_stream_id);
   out_S2W_NL (3,"Original_network_ID: ",t2.original_network_id,
        dvbstrOriginalNetwork_ID(t2.original_network_id));
   out_SB_NL  (6,"reserved_1: ",t2.reserved_1);
   out_SW_NL  (5,"Transport_descriptors_length: ",
        t2.transport_descriptors_length);


   b    += 6;
   len1 -= 6;
   len2  = t2.transport_descriptors_length;

   indent (+1);
   while (len2 > 0) {
      int x;

      x = descriptor (b, DVB_SI);
      len2 -= x;
      b    += x;
      len1 -= x;
   }
   indent (-1);
   out_NL (3);


 } // while len1
 indent (-1);


 t.crc		 		 = getBits (b, 0, 0, 32);
 out_SL_NL (5,"CRC: ",t.crc);

}




