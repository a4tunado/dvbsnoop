/*
$Id: pmt.c,v 1.13 2006/01/02 18:24:24 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- PMT section  (Transport Stream Program Map Section)



$Log: pmt.c,v $
Revision 1.13  2006/01/02 18:24:24  rasc
just update copyright and prepare for a new public tar ball

Revision 1.12  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.11  2004/04/19 22:09:33  rasc
minor change

Revision 1.10  2004/04/15 22:29:22  rasc
PMT: some brainded section check
TS: filter single pids from multi-pid ts-input-file
minor enhancements

Revision 1.9  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.8  2004/02/12 21:21:21  rasc
MHP AIT descriptors
some smaller changes

Revision 1.7  2004/02/07 01:28:04  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.6  2004/01/02 16:40:39  rasc
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
#include "pmt.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/pid_mem.h"




void section_PMT (u_char *b, int len)
{
 /* IS13818-1  S. 65 */

 typedef struct  _PMT {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      b_null;		
    u_int      reserved_1;
    int        section_length;
    u_int      program_number;
    u_int      reserved_2;
    u_int      version_number;
    u_int      current_next_indicator;
    u_int      section_number;
    u_int      last_section_number;
    u_int      reserved_3;
    u_int      pcr_pid;
    u_int      reserved_4;
    int        program_info_length;

    // N  descriptor
    // N1 PMT_LIST2

    unsigned long crc;
 } PMT;


 typedef struct _PMT_LIST2 {
    u_int      stream_type;
    u_int      reserved_1; 
    u_int      elementary_PID;
    u_int      reserved_2;
    int        ES_info_length;

    // N2 descriptor

 } PMT_LIST2;



 PMT        p;
 PMT_LIST2  p2;
 int        len1,len2;


 
 p.table_id 			 = b[0];
 p.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 p.b_null			 = getBits (b, 0, 9, 1);
 p.reserved_1 			 = getBits (b, 0, 10, 2);
 p.section_length		 = getBits (b, 0, 12, 12);
 p.program_number		 = getBits (b, 0, 24, 16);
 p.reserved_2 			 = getBits (b, 0, 40, 2);
 p.version_number 		 = getBits (b, 0, 42, 5);
 p.current_next_indicator	 = getBits (b, 0, 47, 1);
 p.section_number 		 = getBits (b, 0, 48, 8);
 p.last_section_number 		 = getBits (b, 0, 56, 8);
 p.reserved_3	 		 = getBits (b, 0, 64, 3);
 p.pcr_pid	 		 = getBits (b, 0, 67, 13);
 p.reserved_4	 		 = getBits (b, 0, 80, 4);
 p.program_info_length 		 = getBits (b, 0, 84, 12);


 out_nl (3,"PMT-decoding....");
 out_S2B_NL (3,"Table_ID: ",p.table_id, dvbstrTableID (p.table_id));
 if (p.table_id != 0x02) {
   out_nl (3,"wrong Table ID");
   return;
 }



 out_SB_NL (3,"section_syntax_indicator: ",p.section_syntax_indicator);
 out_SB_NL (6,"(fixed '0'): ",p.b_null);
 out_SB_NL (6,"reserved_1: ",p.reserved_1);
 out_SW_NL (5,"Section_length: ",p.section_length);
 out_SW_NL (3,"Program_number: ",p.program_number);

 out_SB_NL (6,"reserved_2: ",p.reserved_2);
 out_SB_NL (3,"Version_number: ",p.version_number);
 
 out_S2B_NL(3,"current_next_indicator: ",p.current_next_indicator, dvbstrCurrentNextIndicator(p.current_next_indicator));
 out_SB_NL (3,"Section_number: ",p.section_number);
 out_SB_NL (3,"Last_Section_number: ",p.last_section_number);

 out_SB_NL (6,"reserved_3: ",p.reserved_3);
 out_SW_NL (3,"PCR PID: ",p.pcr_pid);
 // store_PidToMem (p.pcr_pid);    $$$ TODO PCR is no section...

 out_SB_NL (6,"reserved_4: ",p.reserved_4);
 out_SW_NL (5,"Program_info_length: ",p.program_info_length);


 len1 = p.section_length - 9;
 b   += 9 + 3;

 len2 = p.program_info_length;
 indent (+1);
 while (len2 > 0) {
   int x;

   x = descriptor (b, DVB_SI);
   len2 -= x;
   b += x;
   len1 -= x;
 }
 lenCheckErrOut(3,len2);
 indent (-1);
 out_NL (3);


 out_nl (3,"Stream_type loop: ");
 indent (+1);
 while (len1 > 4) {

   p2.stream_type		 = getBits (b, 0,  0,  8);
   p2.reserved_1		 = getBits (b, 0,  8,  3);
   p2.elementary_PID		 = getBits (b, 0, 11, 13);
   p2.reserved_2		 = getBits (b, 0, 24,  4);
   p2.ES_info_length		 = getBits (b, 0, 28, 12);

   if (*dvbstrStream_TYPE_SHORT (p2.stream_type) == 'S') {	// SECTION?
   	store_PidToMem (p2.elementary_PID);			// $$$ TODO maybe PES-Spider too?
   }

   out_NL (3);
   out_S2B_NL (3,"Stream_type: ",p2.stream_type,
	dvbstrStream_TYPE (p2.stream_type));
   out_SB_NL (6,"reserved_1: ",p2.reserved_1);
   out_SW_NL (3,"Elementary_PID: ",p2.elementary_PID);
   out_SB_NL (6,"reserved_2: ",p2.reserved_2);
   out_SW_NL (5,"ES_info_length: ",p2.ES_info_length);


   b    += 5;
   len1 -= 5;
   len2 = p2.ES_info_length;

   indent (+1);
   while (len2 > 0) {
      int x;

      x = descriptor (b, DVB_SI);
      len2 -= x;
      len1 -= x;
      b += x;
   }
   indent (-1);

   // -- this is due to some braindead providers
   lenCheckErrOut(3,len2);

   out_NL (3);


 } // while len1
 indent (-1);


 p.crc		 		 = getBits (b, 0, 0, 32);
 out_SL_NL (5,"CRC: ",p.crc);

}


