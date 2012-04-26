/*
$Id: mpe_fec.c,v 1.3 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  MPE_FEC Section
 --  EN 301 192  v1.4.1



$Log: mpe_fec.c,v $
Revision 1.3  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2004/10/17 22:20:35  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.1  2004/07/24 11:47:08  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes




*/




#include "dvbsnoop.h"
#include "mpe_fec.h"

#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/output.h"





void section_MPE_FEC (u_char *b, int len)
{
 /* EN 301 192 7.x */

 u_int      i;
 u_int      table_id;
 u_int      section_length;



  out_nl (3,"MPE_FEC-decoding....");
  table_id = outBit_S2x_NL (3,"Table_ID: ",	b, 0, 8,
				(char *(*)(u_long))dvbstrTableID );
  if (table_id != 0x78) {
    out_nl (3,"wrong Table ID");
    return;
  }


  outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8, 1);
  outBit_Sx_NL (3,"private_indicator: ",		b, 9, 1);
  outBit_Sx_NL (6,"reserved_1: ",		b,10, 2);
  section_length = outBit_Sx_NL (5,"section_length: ",	b,12,12);
  outBit_Sx_NL (3,"padding_columns: ",		b,24, 8);

  outBit_Sx_NL (6,"reserved_for_future_use: ",	b,32, 8);
  outBit_Sx_NL (6,"reserved_3: ",		b,40, 2);

  outBit_Sx_NL (6,"reserved_for_future_use: ",	b,42, 5);
  outBit_S2x_NL(3,"Current_next_indicator: ",	b,47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
  outBit_Sx_NL (3,"Section_number: ",		b,48, 8);
  outBit_Sx_NL (3,"Last_section_number: ",	b,56, 8);

  b += 8;
  section_length -= 5;

  i = real_time_parameters(b);
  b += i;
  section_length -= i;


  print_databytes (4,"rs_data_bytes:", b,section_length-4);
  b += section_length-4;


  outBit_Sx_NL (5,"CRC: ",	b,0,32);
}






//
// -- real time parameter block
// -- EN 301 192 v 1.4.1
//

int real_time_parameters (u_char *b)
{
   int  delta_t;

   out_nl (3,"Real time parameters:");
   indent (1);

   delta_t = outBit_Sx (3,"delta_t: ",	b,  0, 12);
   	if (delta_t) out_nl (3," [= %d.%02d sec]", delta_t/100, delta_t%100);
	else         out_nl (3," [= no more bursts]");


   outBit_S2x_NL (3,"table_boundary: ",	b, 12,  1,
		(char *(*)(u_long))dvbstrMPE_FEC_table_frame_boundary );
   outBit_S2x_NL (3,"frame_boundary: ",	b, 13,  1,
		(char *(*)(u_long))dvbstrMPE_FEC_table_frame_boundary );

   outBit_Sx_NL  (3,"address: ",	b, 14, 18);

   indent (-1);
   return 4;
}





