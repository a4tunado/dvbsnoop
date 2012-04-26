/*
$Id: mpeg_packheader.c,v 1.2 2005/12/27 23:30:29 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)





$Log: mpeg_packheader.c,v $
Revision 1.2  2005/12/27 23:30:29  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.1  2005/11/10 00:07:18  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix





*/




#include "dvbsnoop.h"
#include "mpeg_packheader.h"
#include "mpeg_sysheader.h"
#include "pes_misc.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"




/*
 *  PES/PS  Pack Header
 *  if (len == -1) then
 *        pack_header is in a PS
 *        do not print packet_start_code (already printed by caller)
 *  else
 *        pack_header is within a pes packet
 *        and check if a system_header is within len
 */



void mpeg_pack_header (int v, u_char *b, int len)
{

	/* z.B. H.222 ISO 13818-1 Table 2-33 */
	/* 	ISO 11172-1 pack header */


   int 	v1 = v+1;
   int  pack_stuffing_len;


   if (len == 0) return;

   out_nl (v,"Pack_header: ");
   indent (+1);

   if (len > 0) {
	// -- within PES packet, not PS!
	outBit_Sx_NL (v1,"pack_start_code: ",	b,  0, 32);
   }

   outBit_Sx_NL (v1,"fixed '01': ",		b, 32,  2);
   print_xTS_field (v1, "system_clock_reference_base", 	b, 34) ;   // len 36b
   outBit_Sx_NL (v1,"system_clock_reference_extension: ",b, 70,  9);
   outBit_Sx_NL (v1,"marker_bit: ",		b, 79, 1);

   outBit_Sx   (v1,"program_mux_rate: ",	b, 80,22);
   	out_nl (v1,"  [=  x 50 bytes/sec]");

   outBit_Sx_NL (v1,"marker_bit: ",		b, 102, 1);
   outBit_Sx_NL (v1,"marker_bit: ",		b, 103, 1);
   outBit_Sx_NL (v1,"reserved: ",		b, 104, 5);

   pack_stuffing_len = outBit_Sx_NL (v1,"pack_stuffing_len: ",	b, 109, 3);
   print_databytes (6,"stuffing bytes 0xFF:", b+14, pack_stuffing_len);

   b += 14 + pack_stuffing_len;
   if (len >= 0) len -= 14 + pack_stuffing_len;

   if (len > 0) mpeg_system_header (v1, b, len); 	// only if len > 0 (PES packet)

   indent (-1);
}







