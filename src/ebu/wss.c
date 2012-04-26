/*
$Id: wss.c,v 1.2 2006/01/02 18:24:03 rasc Exp $



 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 -- misc routines for EBU WSS (Wide Screen Signalling)
 -- ETSI EN 300 294  




$Log: wss.c,v $
Revision 1.2  2006/01/02 18:24:03  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/03/10 21:05:53  rasc
WSS (Wide Screen Signalling)  data decoding




*/


#include "dvbsnoop.h"
#include "wss.h"
#include "strings/dvb_str.h"
#include "misc/helper.h"
#include "misc/hexprint.h"
#include "misc/output.h"






// -- print WSS codes  (Wide Screen Signalling)
// -- length = 14 bit

void  print_wss_decode (int v, u_char *b)
{


   	outBit_Sx_NL (v,"WSS data: ",	b, 0,14);


	// -- data is lsb ... msb !!!
	// -- we don't correct this here, but are working with reversed values

	indent (+1);

	// data group 1
	outBit_S2x_NL (v,"==> aspect ratio: ",	b,  0,  4,
			(char *(*)(u_long)) dvbstrWSS_aspect_ratio );

	// data group 2
	outBit_S2x_NL (v,"==> film bit: ",		b,  4,  1,
			(char *(*)(u_long)) dvbstrWSS_film_bit);
	outBit_S2x_NL (v,"==> colour coding bit: ",b,  5,  1,
			(char *(*)(u_long)) dvbstrWSS_color_coding_bit);
	outBit_S2x_NL (v,"==> helper bit: ",	b,  6,  1,
			(char *(*)(u_long)) dvbstrWSS_helper_bit);
	outBit_Sx_NL  (v,"==> reserved bit: ",	b,  7,  1);

	// data group 3
	outBit_S2x_NL (v,"==> subtitle/teletext: ",	b,  8,  1,
			(char *(*)(u_long)) dvbstrWSS_subtitleTeletext_bit);
	outBit_S2x_NL (v,"==> subtitling mode: ",	b,  9,  2,
			(char *(*)(u_long)) dvbstrWSS_subtitling_mode);

	// data group 4
	outBit_S2x_NL (v,"==> surround bit: ",		b,  11,  1,
			(char *(*)(u_long)) dvbstrWSS_surround_bit);
	outBit_S2x_NL (v,"==> copyright bit: ",	b,  12,  1,
			(char *(*)(u_long)) dvbstrWSS_copyright_bit);
	outBit_S2x_NL (v,"==> copy_generation bit: ",	b,  13,  1,
			(char *(*)(u_long)) dvbstrWSS_copy_generation_bit);

	indent (-1);
}




