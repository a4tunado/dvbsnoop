/*
$Id: sdt.c,v 1.12 2006/01/02 18:24:24 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


   -- SDT section 
   -- Service Description Table
   -- ETSI EN 300 468    5.2.3



$Log: sdt.c,v $
Revision 1.12  2006/01/02 18:24:24  rasc
just update copyright and prepare for a new public tar ball

Revision 1.11  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.10  2004/04/15 03:38:51  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.9  2004/02/12 21:21:21  rasc
MHP AIT descriptors
some smaller changes

Revision 1.8  2004/02/07 01:28:04  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.7  2004/01/02 16:40:39  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.6  2004/01/01 20:09:31  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/10/24 22:17:21  rasc
code reorg...

Revision 1.4  2003/10/16 19:02:29  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.3  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS



*/




#include "dvbsnoop.h"
#include "sdt.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"


/*
 -- SDT section 
 -- ETSI EN 300 468   5.2.3
*/

void section_SDT (u_char *b, int len)
{

 typedef struct  _SDT {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;
    u_int      transport_stream_id;
    u_int      reserved_3;
    u_int      version_number;
    u_int      current_next_indicator;
    u_int      section_number;
    u_int      last_section_number;
    u_int      original_network_id;
    u_int      reserved_4;

    // N...  SDT_LIST

    u_long     CRC;
 } SDT;

 typedef struct _SDT_LIST {
    u_int      service_id; 
    u_int      reserved_1;
    u_int      EIT_schedule_flag; 
    u_int      EIT_present_following_flag; 
    u_int      running_status; 
    u_int      free_CA_mode; 
    u_int      descriptors_loop_length; 

    // N2 ... descriptors

 } SDT_LIST;



 SDT      s;
 SDT_LIST s2;
 int      len1,len2;


 
 s.table_id 			 = b[0];
 s.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 s.reserved_1 			 = getBits (b, 0, 9, 1);
 s.reserved_2 			 = getBits (b, 0, 10, 2);
 s.section_length		 = getBits (b, 0, 12, 12);
 s.transport_stream_id		 = getBits (b, 0, 24, 16);
 s.reserved_3 			 = getBits (b, 0, 40, 2);
 s.version_number 		 = getBits (b, 0, 42, 5);
 s.current_next_indicator	 = getBits (b, 0, 47, 1);
 s.section_number 		 = getBits (b, 0, 48, 8);
 s.last_section_number 		 = getBits (b, 0, 56, 8);
 s.original_network_id		 = getBits (b, 0, 64, 16);
 s.reserved_4 			 = getBits (b, 0, 80, 8);



 out_nl (3,"SDT-decoding....");
 out_S2B_NL (3,"Table_ID: ",s.table_id, dvbstrTableID (s.table_id));
 if (s.table_id != 0x42 && s.table_id != 0x46) {
   out_nl (3,"wrong Table ID");
   return;
 }


 out_SB_NL (3,"section_syntax_indicator: ",s.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",s.reserved_1);
 out_SB_NL (6,"reserved_2: ",s.reserved_2);
 out_SW_NL (5,"Section_length: ",s.section_length);

 out_SW_NL (3,"Transport_Stream_ID: ",s.transport_stream_id);
 out_SB_NL (6,"reserved_3: ",s.reserved_3);

 out_SB_NL (3,"Version_number: ",s.version_number);
 out_S2B_NL(3,"current_next_indicator: ",s.current_next_indicator, dvbstrCurrentNextIndicator(s.current_next_indicator));
 out_SB_NL (3,"Section_number: ",s.section_number);
 out_SB_NL (3,"Last_Section_number: ",s.last_section_number);

 out_S2W_NL (3,"Original_network_ID:  ",s.original_network_id,
      dvbstrOriginalNetwork_ID(s.original_network_id)); 
 out_SB_NL (6,"reserved_4: ",s.reserved_4);


 //  len = len - header - CRC
 len1 = s.section_length - 11 - 4;
 b   += 11;

 out_NL (3);
 indent (+1);
 while (len1 > 0 ) {

   s2.service_id		= getBits (b, 0,  0, 16);
   s2.reserved_1		= getBits (b, 0, 16, 6);
   s2.EIT_schedule_flag		= getBits (b, 0, 22, 1);
   s2.EIT_present_following_flag= getBits (b, 0, 23, 1);
   s2.running_status		= getBits (b, 0, 24, 3);
   s2.free_CA_mode		= getBits (b, 0, 27, 1);
   s2.descriptors_loop_length	= getBits (b, 0, 28, 12);

   out_NL (3);

   out_S2W_NL (3,"Service_id: ",s2.service_id,
	  " --> refers to PMT program_number"); 
   out_SB_NL  (6,"reserved_1: ",s2.reserved_1);
   out_SB_NL  (3,"EIT_schedule_flag: ",s2.EIT_schedule_flag);
   out_SB_NL  (3,"EIT_present_following_flag: ",s2.EIT_present_following_flag);
   out_S2B_NL (3,"Running_status: ",s2.running_status,
	dvbstrRunningStatus_FLAG(s2.running_status));
   out_S2B_NL (3,"Free_CA_mode: ",s2.free_CA_mode,
	(s2.free_CA_mode) ?"streams [partially] CA controlled" :"unscrambled");
   out_SW_NL  (5,"Descriptors_loop_length: ",s2.descriptors_loop_length);

   b    += 5;
   len1 -= 5;
   len2  = s2.descriptors_loop_length;

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

 }
 indent (-1);


 s.CRC = getBits (b,0,0,32);
 out_SL_NL (5,"CRC: ",s.CRC);

}








