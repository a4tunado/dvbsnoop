/*
$Id: tdt.c,v 1.9 2006/01/02 18:24:25 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- TDT section
 -- Time Date Table
 -- ETSI EN 300 468     5.2.5



$Log: tdt.c,v $
Revision 1.9  2006/01/02 18:24:25  rasc
just update copyright and prepare for a new public tar ball

Revision 1.8  2005/10/25 18:41:40  rasc
minor code rewrite

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
#include "tdt.h"
#include "strings/dvb_str.h"
#include "misc/output.h"




void section_TDT (u_char *b, int len)
{

   u_int      table_id;
   u_long     UTC_time_MJD;
   u_long     UTC_time_UTC;



   out_nl (3,"TDT-decoding....");
   table_id = outBit_S2x_NL (3,"Table_ID: ",  b,  0, 8,
		  (char *(*)(u_long)) dvbstrTableID );     
   if (table_id != 0x70) {
	out_nl (3,"wrong Table ID");
	return;
   }



  outBit_Sx_NL (3,"section_syntax_indicator: ",		b,  8,  1);
  outBit_Sx_NL (6,"reserved_1: ",			b,  9,  1);
  outBit_Sx_NL (6,"reserved_2: ",			b, 10,  2);
  outBit_Sx_NL (3,"Section_length: ",			b, 12, 12);


  out (3,"UTC_time: ");
  UTC_time_MJD		 = getBits (b, 0, 24, 16);
  UTC_time_UTC		 = getBits (b, 0, 40, 24);
  print_time40 (3, UTC_time_MJD,UTC_time_UTC);
  out_NL (3);

}




