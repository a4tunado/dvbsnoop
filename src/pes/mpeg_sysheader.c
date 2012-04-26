/*
$Id: mpeg_sysheader.c,v 1.2 2006/01/02 18:24:12 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)







$Log: mpeg_sysheader.c,v $
Revision 1.2  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2005/11/10 00:07:18  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix





*/




#include "dvbsnoop.h"
#include "mpeg_sysheader.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"






/*
 *  PS System header
 *  if (len == -1) then
 *        system_header is in a PS
 *        do not print packet_start_code & ID (already printed by caller)
 *  else
 *        pack_header is within a pes packet (pack_header)
 *        print packet_start_code
 */


void mpeg_system_header (int v, u_char *b, int len)
{

	/* z.B. H.222 ISO 13818-1 Table 2-34 */
	/* 	ISO 11172-1 system header */


   if (len == 0) return;

   out_nl (v,"System_header: ");
   indent (+1);

   if (len > 0) {
	// -- within PES packet, not PS!
	outBit_Sx_NL (v,"system_header_start_code: ",	b,  0, 32);
   }



   // -- get real length from system_header data
   len = outBit_Sx_NL (v,"header_length: ",	b,  32, 16);

   outBit_Sx_NL (v,"marker_bit: ",		b,  48,  1);
   outBit_Sx_NL (v,"rate_bound: ",		b,  49,  22);
   outBit_Sx_NL (v,"marker_bit: ",		b,  71,  1);
   outBit_Sx_NL (v,"audio_bound: ",		b,  72,  6);
   outBit_Sx_NL (v,"fixed_flag: ",		b,  78,  1);
   outBit_Sx_NL (v,"CSPS_flag: ",		b,  79,  1);
   outBit_Sx_NL (v,"system_audio_lock_flag: ",	b,  80,  1);
   outBit_Sx_NL (v,"system_video_lock_flag: ",	b,  81,  1);
   outBit_Sx_NL (v,"marker_bit: ",		b,  82,  1);
   outBit_Sx_NL (v,"video_bound: ",		b,  83,  5);
   outBit_Sx_NL (v,"packet_rate_restriction_flag: ",	b,  88,  1);
   outBit_Sx_NL (v,"reserved_byte: ",		b,  89,  7);

   b += 12;
   len -= 12;


   // while (nextbits () == '1') {	
   // while  ((bit = getBits (b, 0,0,1)) == 0x01) {
   while  ( (*b & 0x80) ) {
	if (len <= 0)  break;

	out_NL (v);
	outBit_S2x_NL(v,"Stream_id: ",			b,  0,  8,
		 	(char *(*)(u_long))dvbstrPESstream_ID );
   	outBit_Sx_NL (v,"fixed (0x02): ",		b,  8,  2);
   	outBit_Sx_NL (v,"P-STD_buffer_bound_scale: ",	b, 10,  1);
   	outBit_Sx_NL (v,"P-STD_buffer_size_bound: ",	b, 11, 13);

	b   += 3;
	len -= 3;
	if (len < 0)  out_nl (1, "$$$ something wrong here (length<0)");
   }


   indent (-1);
}






