/*
$Id: dit.c,v 1.7 2006/01/02 18:24:24 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


   -- DIT section
   -- Discontinuity Information Table
   -- ETSI EN 300 468     5.2.9




$Log: dit.c,v $
Revision 1.7  2006/01/02 18:24:24  rasc
just update copyright and prepare for a new public tar ball

Revision 1.6  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.5  2004/01/01 20:09:31  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.4  2003/10/24 22:45:06  rasc
code reorg...

Revision 1.3  2003/10/24 22:17:20  rasc
code reorg...

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS



*/




#include "dvbsnoop.h"
#include "dit.h"
#include "strings/dvb_str.h"
#include "misc/output.h"



void section_DIT (u_char *b, int len)
{

 typedef struct  _DIT {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;
    u_int      transition_flag;
    u_int      reserved_3;

 } DIT;



 DIT        d;

 
 d.table_id 			 = b[0];
 d.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 d.reserved_1 			 = getBits (b, 0, 9, 1);
 d.reserved_2 			 = getBits (b, 0, 10, 2);
 d.section_length		 = getBits (b, 0, 12, 12);
 d.transition_flag		 = getBits (b, 0, 24, 1);
 d.reserved_3 			 = getBits (b, 0, 25, 7);


 out_nl (3,"DIT-decoding....");
 out_S2B_NL (3,"Table_ID: ",d.table_id, dvbstrTableID (d.table_id));
 if (d.table_id != 0x7E) {
   out_nl (3,"wrong Table ID");
   return;
 }

 out_SB_NL (3,"section_syntax_indicator: ",d.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_SB_NL (6,"reserved_2: ",d.reserved_2);
 out_SW_NL (5,"Section_length: ",d.section_length);

 out_S2B_NL (3,"transition_flag: ",d.transition_flag,
        (d.transition_flag) ? "due to change of the originating source"
                            : "due to change selection only"); 
 out_SB_NL (6,"reserved_3: ",d.reserved_3);

}




