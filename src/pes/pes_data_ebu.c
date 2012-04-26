/*
$Id: pes_data_ebu.c,v 1.5 2006/01/02 18:24:12 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PES Data: Teletext, VPS, WSS, closed caption, etc.
 -- EBU data (see EN 300 472, EN 301 775, and some more)



$Log: pes_data_ebu.c,v $
Revision 1.5  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.4  2004/03/10 21:05:53  rasc
WSS (Wide Screen Signalling)  data decoding

Revision 1.3  2004/03/09 20:59:23  rasc
VPS decoding (someone check the NPP & PTY code output please...)

Revision 1.2  2004/02/04 22:36:29  rasc
more EBU/teletext stuff

Revision 1.1  2004/02/02 23:41:23  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream, restructuring
- some other stuff





*/




#include "dvbsnoop.h"
#include "pes_data_ebu.h"
#include "strings/dvb_str.h"
#include "ebu/teletext.h"
#include "ebu/vps.h"
#include "ebu/wss.h"
#include "ebu/ebu_misc.h"
#include "misc/helper.h"
#include "misc/hexprint.h"
#include "misc/output.h"



static int teletext_data_field (int v, u_char *b, int len);
static int vps_data_field (int v, u_char *b, int len);
static int wss_data_field (int v, u_char *b, int len);
static int closed_caption_data_field (int v, u_char *b, int len);
static int monochrome_data_field (int v, u_char *b, int len);





/*
   -- Data Teletext
*/

void PES_decodeDATA_EBU_etc (u_char *b, int len)
{
	
   // -- PES_DATA_bytes EBU
   // -- Data Buffer starts at PES_DATA_BYTES...
   // --> see parent

   int  data_identifier;

   out_nl (4,"EBU data:");
   indent (+1);

   data_identifier		= getBits (b, 0,  0,  8);
   outBit_S2x_NL (4,"data_identifier: ",	b, 0, 8,
			(char *(*)(u_long)) dvbstrPESDataIdentifier);
   b++;
   len--;

   while (len > 0) {
	int len2;
	int dui;
	int n=0;


	out_NL (4);
   	dui  = outBit_S2x_NL (4,"data_unit_id: ",	b, 0, 8,
			(char *(*)(u_long)) dvbstrPES_EBUDataUnitID);

   	len2 = outBit_Sx_NL (4,"data_unit_length: ",	b, 8, 8);
	b += 2;
	len -= 2;

	if (dui==0x02 || dui==0x03 || dui==0xC0 || dui==0xC1) {
		n = teletext_data_field (4, b, len2);
	} else if (dui==0xC3) {
		n = vps_data_field(4, b,len2);
	} else if (dui==0xC4) {
		n = wss_data_field (4, b,len2);
	} else if (dui==0xC5) {
		n = closed_caption_data_field (4, b,len2);
	} else if (dui==0xC6) {
		n = monochrome_data_field (4, b,len2);
	} else if (dui==0xFF) {
		/* No data field */
		n = 0;
	}

	if ( (len2-n) > 0 ) {
		print_databytes (4,"stuffing bytes:", b+n, len2-n);
	}

	b += len2;
	len -= len2;
   }


   indent (-1);
}















// EN 300 472  and  EN 300 706

static int teletext_data_field (int v, u_char *b, int len)
{
   int  v1 = v+1;
   int  len2;


   out_nl (v,"Teletext data:");
   indent (+1);

   	ebu_rfl_out (v1,b);
   	outBit_S2x_NL (v1,"frame_coding: ", b, 8, 8,
			(char *(*)(u_long)) dvbstrTELETEXT_framingcode );
	b += 2;
	len -= 2;


	print_databytes (8,"data_block:", b, 42);
	out_nl (v1," => decoded:");
		indent (+1);

		invertBuffer (b, 42);
		len2 = print_teletext_control_decode (v1, b, 42);
		b += len2;
		len -= len2;

		indent (-1);


   indent (-1);
   return 44;
}





// EN 300 231

static int vps_data_field (int v, u_char *b, int len)
{
   int  v1 = v+1;

   out_nl (v,"VPS (Video Programming System) data:");
   indent (+1);

   	ebu_rfl_out (v1,b);
	print_vps_decode (v1, b+1, 13);

   indent (-1);
   return 14;
}





// EN 300 294

static int wss_data_field (int v, u_char *b, int len)
{
   int  v1 = v+1;

   out_nl (v,"WSS (Wide Screen Signalling) data:");
   indent (+1);

   	ebu_rfl_out (v1,b);
	b++;
	print_wss_decode (v1, b);		// 14 bit
   	outBit_Sx_NL (v1,"reserved: ",		b,14, 2);

   indent (-1);
   return 3;
}






// Closed Captioning data packets EIA-608 Revision A

static int closed_caption_data_field (int v, u_char *b, int len)
{
   int  v1 = v+1;

   out_nl (v,"CC (Closed Caption) data:");
   indent (+1);

   	ebu_rfl_out (v1,b);

	// $$$ TODO
   	outBit_Sx_NL (v1,"closed_caption_data_block: ",	b, 8,16);

   indent (-1);
   return 3;
}





// Monochrome 4:2:2: ITU-R BT.601-1 and ITU-R BT.656

static int monochrome_data_field (int v, u_char *b, int len)
{
   int  v1 = v+1;
   int  n;


   out_nl (v,"Monochrome 4:2:2 sample data:");
   indent (+1);

   	outBit_Sx_NL (v1,"first_segment_flag: ",b, 0, 1);
   	outBit_Sx_NL (v1,"last_segment_flag: ", b, 1, 1);
   	outBit_Sx_NL (v1,"field_parity: ",	b, 2, 1);
   	outBit_Sx_NL (v1,"line_offset: ",	b, 3, 5);

   	outBit_Sx_NL (v1,"first_pixel_position: ",b, 8, 16);
   	n = outBit_Sx_NL (v1,"n_pixel: ",	b, 24, 8);

	print_databytes (v1,"Y_values:", b+3, n);

   indent (-1);
   return 3+n;
}













