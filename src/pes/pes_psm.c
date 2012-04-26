/*
$Id: pes_psm.c,v 1.5 2007/02/08 19:17:41 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- PES PSM (Program Stream Map) ISO/IEC 13818-1 ITU H.222.0, 2.5.4



$Log: pes_psm.c,v $
Revision 1.5  2007/02/08 19:17:41  rasc
Bugfix on PS Program Stream Map  - tnx to "jack" for reporting

Revision 1.4  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.3  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.2  2004/01/02 16:40:38  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.1  2004/01/01 20:31:25  rasc
PES program stream map, minor descriptor cleanup




*/




#include "dvbsnoop.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"

#include "pes_psm.h"





/*
   -- Program Stream Map
   -- buffer starts after packet_length

*/


void  PES_decodePSM (u_char *b, int len)

{
   int   psi_len;
   int   esm_len;


   // -- already processed:
   // --- packet_start_code_prefix 	24 bslbf
   // --- stream_id 			 8 uimsbf
   // --- packet_length			16 uimsbf


   outBit_S2x_NL (4,"current_next_indicator: ",		b, 0, 1,
				(char *(*)(u_long)) dvbstrCurrentNextIndicator );
   outBit_Sx_NL  (6,"reserved_1: ",			b, 1, 2);
   outBit_Sx_NL  (4,"program_stream_map_version: ",	b, 3, 5);
   outBit_Sx_NL  (6,"reserved_2: ",			b, 8, 7);
   outBit_Sx_NL  (4,"marker_bit: ",			b,15, 1);
   psi_len = outBit_Sx_NL  (5,"program_stream_info_length: ",	b,16,16);
   b += 4;
   // len -= 4;

   out_nl (4,"Program stream info:");
   indent (+1);
   while (psi_len > 0) {
	int x;

	x = descriptor (b, MPEG);
	b   += x;
	psi_len -= x;
	// len -= x;
   }
   indent (-1);


   esm_len = outBit_Sx_NL  (5,"elementary_stream_map_length: ",	b, 0,16);
   b += 2;
   out_nl (4,"Elementary stream Map:");
   indent (+1);
   while (esm_len > 0) {
	int esi_len;

   	outBit_S2x_NL (4,"stream_type: ",		b, 0, 8,
				(char *(*)(u_long)) dvbstrStream_TYPE);
	outBit_Sx_NL  (5,"elementary_stream_id: ",	b, 8, 8);
   	esi_len = outBit_Sx_NL  (5,"elementary_stream_info_length: ",	b,16,16);
	b += 4;
	esm_len -= 4;
	// len -= 4;

   	out_nl (4,"Elementary stream info:");
        indent (+1);
	while (esi_len > 0) {
		int x;

		x = descriptor (b, MPEG);
		b   += x;
		esi_len -= x;
		esm_len -= x;
		// len -= x;
	}
        indent (-1);

   }
   indent (-1);


   outBit_Sx_NL  (5,"CRC: ",	b, 0, 32);
}






