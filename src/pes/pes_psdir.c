/*
$Id: pes_psdir.c,v 1.4 2007/02/08 19:17:41 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- PES PSD (Program Stream Directory) ISO/IEC 13818-1 ITU H.222.0, 2.5.5



$Log: pes_psdir.c,v $
Revision 1.4  2007/02/08 19:17:41  rasc
Bugfix on PS Program Stream Map  - tnx to "jack" for reporting

Revision 1.3  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.1  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured




*/




#include "dvbsnoop.h"
#include "strings/dvb_str.h"
#include "misc/output.h"

#include "pes_misc.h"
#include "pes_psdir.h"



static int print_PESDIR_directory_offset (int v, const char *str, u_char *b);


/*
   -- Program Stream Directory
   -- ISO/IEC 13818-1 ITU H.222.0, 2.5.5
   -- buffer starts after packet_length
*/


void  PES_decodePSDIR (u_char *b, int len)

{
   int n1,n2;
   int au,i;


   // -- already processed:
   // --- packet_start_code_prefix 	24 bslbf
   // --- stream_id 			 8 uimsbf
   // --- packet_length			16 uimsbf


   au = outBit_Sx_NL  (4,"number_of_access_unuits: ",	b, 0, 15);
        outBit_Sx_NL  (4,"marker_bit: ",		b,15,  1);
   n1 = print_PESDIR_directory_offset (4,"prev",b+2);
   n2 = print_PESDIR_directory_offset (4,"next",b+2+n1);
   b   += n1+n2+2;
   len -= n1+n2+2; 

   for (i=0; i < au; i++) {

	out_nl (4,"Access Unit %d (0x%04x)",i,i);
	indent (+1);

	outBit_S2x_NL (4,"packet_stream_id: ",		b, 0, 8,
				(char *(*)(u_long)) dvbstrPESstream_ID);

	{
	 int sign;
	 int off_43_30, off_29_15, off_14_0;
	 long long ll;

   	 out_nl (4,"PES_header_position: ");
   	 indent (+1);
         sign = outBit_Sx_NL  (4,"..._sign: ",			b, 8, 1);
	 off_43_30 = outBit_Sx_NL  (4,"offset[43..30]: ",	b, 9, 14);
	 outBit_Sx_NL  (4,"marker_bit: ",			b,23,  1);
	 off_29_15 = outBit_Sx_NL  (4,"offset[29..15]: ",	b,24, 15);
	 outBit_Sx_NL  (4,"marker_bit: ",			b,39,  1);
	 off_14_0  = outBit_Sx_NL  (4,"offset[14.. 0]: ",	b,40, 15);
	 outBit_Sx_NL  (4,"marker_bit: ",			b,55,  1);

	 ll = (off_43_30 << 30) + (off_29_15 << 15) + off_14_0;
	 if (sign) ll = -ll ;
	 out_nl  (4," ==> PES_header_position_offset:  %lld [bytes]", ll);
	 indent (-1);
	}


	outBit_Sx (4,"reference_offset: ",		b,56, 16);
	out_nl (4, "  [bytes]");
	outBit_Sx_NL  (4,"marker_bit: ",		b,72,  1);
	outBit_Sx_NL  (6,"reserved: ",			b,73,  3);
	print_xTS_field (4,"PTS", b, 76);

	{
	 u_long  btr_1, btr_2;
	 u_long  ul;

	 btr_1  = outBit_Sx_NL  (4,"bytes_to_read[22.. 8]: ",	b, 112, 15);
		  outBit_Sx_NL  (4,"marker_bit: ",		b, 127,  1);
	 btr_2  = outBit_Sx_NL  (4,"bytes_to_read[ 7.. 0]: ",	b, 128,  8);
	 ul = (btr_1 << 8) + btr_2;
	 out_nl  (4," ==> bytes_to_read:  %lu  (0x%06lx) [bytes]", ul,ul);

	}

	outBit_Sx_NL  (4,"marker_bit: ",			b, 136,  1);
	outBit_Sx_NL  (4,"intra_coded_indicator: ",		b, 137,  1);	// $$$ TODO table
	outBit_Sx_NL  (4,"coding_parameter_indicator: ",	b, 138,  2);	// $$$ TODO Table
	outBit_Sx_NL  (6,"reserved: ",				b, 140,  4);

	indent (-1);
   }


}


static int print_PESDIR_directory_offset (int v, const char *str, u_char *b)
{
   int  off_44_30, off_29_15, off_14_0;
   long long  ll;
   int  v1 = v+1;


   out_nl (v,"%s_directory: ",str);
   indent (+1);

   off_44_30 = outBit_Sx_NL  (v1,"..._offset[44..30]: ",	b, 0, 15);
   outBit_Sx_NL  (v1,"marker_bit: ",			b,15,  1);
   off_29_15 = outBit_Sx_NL  (v1,"..._offset[29..15]: ",	b,16, 15);
   outBit_Sx_NL  (v1,"marker_bit: ",			b,31,  1);
   off_14_0  = outBit_Sx_NL  (v1,"..._offset[14.. 0]: ",	b,32, 15);
   outBit_Sx_NL  (v1,"marker_bit: ",			b,47,  1);

   ll = (off_44_30 << 30) + (off_29_15 << 15) + off_14_0;
   out_nl  (v," ==> %s_directory_offset:  %lld (0x%012llx)  [bytes]",
		   str, ll,ll);

   indent (-1);
   return 6;
}








