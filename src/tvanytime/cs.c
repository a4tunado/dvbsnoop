/*
$Id: cs.c,v 1.2 2006/01/02 18:24:46 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  Container section (CS)
 --  TS 102 323



$Log: cs.c,v $
Revision 1.2  2006/01/02 18:24:46  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2005/07/18 21:13:05  rasc
TVA Content Section




*/




#include "dvbsnoop.h"
#include "cs.h"

#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"





void section_TVA_CS (u_char *b, int len)
{
 /* TS 102 323  */

 u_int      table_id;
 u_int      section_length;
 int	    len1;



  out_nl (3,"CS-decoding....");
  table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
  if (table_id != 0x75) {
    out_nl (3,"wrong Table ID");
    return;
  }


  outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8,  1);
  outBit_Sx_NL (3,"private_indicator: ",	b, 9,  1);
  outBit_Sx_NL (6,"reserved: ",			b,10,  2);
  section_length = outBit_Sx_NL (5,"section_length: ",	b,12,12);

  outBit_Sx_NL (3,"container_id: ",		b,24, 16);
  outBit_Sx_NL (6,"reserved: ",			b,40,  2);
  outBit_Sx_NL (3,"version_number: ",		b,42,  5);

  outBit_S2x_NL(3,"Current_next_indicator: ",	b,47,  1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
  outBit_Sx_NL (3,"Section_number: ",		b,48,  8);
  outBit_Sx_NL (3,"Last_section_number: ",	b,56,  8);


  b += 8;
  len1 = section_length - 5;


  // common descriptor loop 

  out_nl (3,"Container_data:");
  indent (+1);
   // $$$TODO  -- compression wrapper, container data
   print_private_data (3,b,len1);   
   b += len1;

  indent (-1);

  outBit_Sx_NL (5,"CRC: ",	b,0,32);
}






// Annotation:
//
// $$$ TODO:  CS is untested so far !!!
//  need stream with  CS data
