/*
$Id: st.c,v 1.8 2006/01/02 18:24:24 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- ST section (stuffing)



$Log: st.c,v $
Revision 1.8  2006/01/02 18:24:24  rasc
just update copyright and prepare for a new public tar ball

Revision 1.7  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

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
#include "st.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"




/*
 -- ST section (stuffing)
 -- ETSI EN 300 468   5.2.8
*/

void section_ST (u_char *b, int len)
{

 typedef struct  _ST {
    u_int      table_id;
    u_int      section_syntax_indicator;		
    u_int      reserved_1;
    u_int      reserved_2;
    u_int      section_length;

    // N  databytes

 } ST;


 ST s;


 
 s.table_id 			 = b[0];
 s.section_syntax_indicator	 = getBits (b, 0, 8, 1);
 s.reserved_1 			 = getBits (b, 0, 9, 1);
 s.reserved_2 			 = getBits (b, 0, 10, 2);
 s.section_length		 = getBits (b, 0, 12, 12);


 out_nl (3,"ST-decoding....");
 out_S2B_NL (3,"Table_ID: ",s.table_id, dvbstrTableID (s.table_id));
 if (s.table_id != 0x72) {
   out_nl (3,"wrong Table ID");
   return;
 }

 out_SB_NL (3,"section_syntax_indicator: ",s.section_syntax_indicator);
 out_SB_NL (6,"reserved_1: ",s.reserved_1);
 out_SB_NL (6,"reserved_2: ",s.reserved_2);
 out_SW_NL (5,"Section_length: ",s.section_length);

 b += 3;
 print_databytes (3,"Section data:", b, s.section_length);

}
