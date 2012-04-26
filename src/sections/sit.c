/*
$Id: sit.c,v 1.11 2006/01/02 18:24:24 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)

   -- SIT section
   -- Selection Information Table
   -- ETSI EN 300 469  7.1.2



$Log: sit.c,v $
Revision 1.11  2006/01/02 18:24:24  rasc
just update copyright and prepare for a new public tar ball

Revision 1.10  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.9  2004/04/15 03:38:51  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.8  2004/02/12 21:21:21  rasc
MHP AIT descriptors
some smaller changes

Revision 1.7  2004/02/07 01:28:04  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.6  2004/01/02 16:40:40  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.5  2004/01/01 20:09:31  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.4  2003/10/24 22:17:21  rasc
code reorg...

Revision 1.3  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS



*/




#include "dvbsnoop.h"
#include "sit.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"



void section_SIT (u_char *b, int len)
{

 typedef struct  _SIT {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;
    u_int      reserved_3;
    u_int      reserved_4;
    u_int      version_number;
    u_int      current_next_indicator;
    u_int      section_number;
    u_int      last_section_number;
    u_int      reserved_5;
    u_int      transmission_info_loop_length;

    // N  descriptor
    // N1 SIT_LIST2

    unsigned long crc;
 } SIT;


 typedef struct _SIT_LIST2 {
    u_int      service_id;
    u_int      reserved_1; 
    u_int      running_status;
    u_int      service_loop_length;

    // N2 descriptor

 } SIT_LIST2;



 SIT        s;
 SIT_LIST2  s2;
 int        len1,len2;


 
 s.table_id 			 = b[0];
 s.section_syntax_indicator	 = getBits (b, 0,  8,  1);
 s.reserved_1 			 = getBits (b, 0,  9,  1);
 s.reserved_2 			 = getBits (b, 0, 10,  2);
 s.section_length		 = getBits (b, 0, 12, 12);
 s.reserved_3 			 = getBits (b, 0, 24, 16);
 s.reserved_4 			 = getBits (b, 0, 40,  2);
 s.version_number 		 = getBits (b, 0, 42, 5);
 s.current_next_indicator	 = getBits (b, 0, 47, 1);
 s.section_number 		 = getBits (b, 0, 48, 8);
 s.last_section_number 		 = getBits (b, 0, 56, 8);
 s.reserved_5	 		 = getBits (b, 0, 64, 4);
 s.transmission_info_loop_length = getBits (b, 0, 68, 12);


 
 out_nl (3,"SIT-decoding....");
 out_S2B_NL (3,"Table_ID: ",s.table_id, dvbstrTableID (s.table_id));
 if (s.table_id != 0x7F) {
   out_nl (3,"wrong Table ID");
   return;
 }


 out_SB_NL (3,"section_syntax_indicator: ",s.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",s.reserved_1);
 out_SB_NL (6,"reserved_2: ",s.reserved_2);
 out_SW_NL (5,"Section_length: ",s.section_length);

 out_SW_NL (6,"reserved_3: ",s.reserved_3);
 out_SB_NL (6,"reserved_4: ",s.reserved_4);

 out_SB_NL (3,"Version_number: ",s.version_number);
 out_S2B_NL(3,"current_next_indicator: ",s.current_next_indicator, dvbstrCurrentNextIndicator(s.current_next_indicator));
 out_SB_NL (3,"Section_number: ",s.section_number);
 out_SB_NL (3,"Last_Section_number: ",s.last_section_number);

 out_SB_NL (6,"reserved_5: ",s.reserved_5);
 out_SW_NL (5,"Transmission_info_loop_length: ",s.transmission_info_loop_length);


 // - header data after length value
 len1 = s.section_length - 7;
 b   += 10;

 len2 = s.transmission_info_loop_length;
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
 indent (+1);
 while (len1 > 4) {

   s2.service_id		 = getBits (b, 0,  0, 16);
   s2.reserved_1		 = getBits (b, 0, 16,  1);
   s2.running_status		 = getBits (b, 0, 17,  3);
   s2.service_loop_length	 = getBits (b, 0, 20, 12);

   b    += 4;
   len1 -= 4;


   out_NL (3);
   out_S2W_NL (3,"Service_ID: ",s2.service_id, 
          " --> refers to PMT program_number");
   out_SB_NL  (6,"reserved_1: ",s2.reserved_1);
   out_S2B_NL (3,"Running_status: ",s2.running_status,
          dvbstrRunningStatus_FLAG (s2.running_status));

   out_SW_NL  (5,"Service_loop_length: ",s2.service_loop_length);


   len2 = s2.service_loop_length;

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

 } // while len1
 indent (-1);


 s.crc		 		 = getBits (b, 0, 0, 32);
 out_SL_NL (5,"CRC: ",s.crc);

}



