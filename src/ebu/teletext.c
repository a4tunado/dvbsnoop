/*
$Id: teletext.c,v 1.8 2006/01/02 18:24:03 rasc Exp $



 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- misc routines for EBU teletext




$Log: teletext.c,v $
Revision 1.8  2006/01/02 18:24:03  rasc
just update copyright and prepare for a new public tar ball

Revision 1.7  2005/01/17 19:41:22  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.6  2004/02/09 21:24:59  rasc
AIT descriptors
minor redesign on output routines

Revision 1.5  2004/02/07 01:28:03  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.4  2004/02/05 10:30:56  rasc
no message

Revision 1.3  2004/02/04 22:36:27  rasc
more EBU/teletext stuff

Revision 1.2  2004/02/03 00:11:49  rasc
no message

Revision 1.1  2004/02/02 23:37:54  rasc
added EBU module (teletext), providing basic teletext decoding



*/


#include "dvbsnoop.h"
#include "teletext.h"
#include "ebu_misc.h"
#include "strings/dvb_str.h"
#include "misc/helper.h"
#include "misc/hexprint.h"
#include "misc/output.h"






// Important!
// ==========
// A Teletext packet comprises 360 bits organized as 45 bytes, numbered
// 1 to 45. In each byte, the bits are numbered 1 to 8 (LSB to MSB), and
// are normally transmitted LSB first.
// (against ETSI doc. bytes numbering: -4 diff)
//
// ==>
//  - the first 3 bytes are not part of this module
//    (anyway, the clock-run-in is not part of dvb) 
//    we start with Magazine_and_Packet_addr...
//  - before any decoding, the data packets has to be transformed
//    from LSB...MSB (bits)  to the internal CPU format.
//    Warning: Byte order will not be changed, only bit order in bytes!
//    ==>  so: LSB, MSB words habe still to be tranformed, if needed
//
// ==> 
//  - Some codes are protected by Hamming code 8/4.
//  - Some codes are protected by Hamming code 24/18.
//







//
// -- decode & print magazine & packet address
// -- print page_nr, subpage_nr, if given
// -- !!! BUFFER BYTES HAVE TO BE ALREADY INVERTED!
// -- return: len of decoded bytes
//

int  print_teletext_control_decode (int v, u_char *b, int len)
{
  int  x;
  int  packet_nr = -1;
  int  mag_nr = -1;
  int  page_nr = -1;
  int  sub_page_nr = -1;


  	// -- buffer starts with magazine_and_packet_addr
	// -- len should be 42 bytes

	// PES_data_field(){
	// 	data_identifier 8 uimsbf
	//	for(i=0;i<N;i++){
	// 1:		 data_unit_id 8 uimsbf
	// 2:		 data_unit_length 8 uimsbf
	// 3:			 reserved_future_use 2 bslbf
	//			 field_parity 1 bslbf
	//			 line_offset 5 uimsbf
	// 4:			 framing_code 8 bslbf
	//		-->	 magazine_and_packet_address 16 bslbf
	//		-->	 data_block 320 bslbf
	//	 }


	
	// -- packet nr
	// -- magazine nr

	x = unhamW84(*b,*(b+1));
	packet_nr =  (x >> 3) & 0x1F;
	mag_nr = x & 7;
	if (! mag_nr) mag_nr = 8; // $$$ TODO  is this really correct?

	out_SB_NL  (v,"magazine number (X): ",mag_nr);
	out_S2W_NL (v,"packet number (Y): ",packet_nr, dvbstrTELETEXT_packetnr(packet_nr) );



	// -- normal display packet...
	if (packet_nr > 0 && packet_nr <= 25) {

		unParityTeletextData (b+2, len-2);
		print_teletext_data_x0_x25 (v,"packet data (parity stripped):", b+2, len-2);

		return len;
	}


	// -- special packets?
	// -- Packets X/26, X/28 and M/29 can carry data to enhance a basic Level 1
	// -- Teletext page. The general coding scheme is shown in figure 11. Byte 6
	// -- is used as an additional address byte (designation code), coded Hamming
	// -- 8/4. This allows up to 16 versions of each packet type. The remaining
	// -- 39 bytes are Hamming 24/18 coded, grouped as 13 triplets.

	if (packet_nr > 25) {
		int  designation;

		designation = unhamB84(*(b+2))  & 0x0F;
		out_SB_NL  (v,"designation code: ",designation);

		print_databytes (4,"packet data (hamming 24/18):", b+3, len-3);

		// $$$ TODO   hamming24_18 triplets
		// ... unham24_18 b+3,len-3
		// packet_x26_to_m29 (packet_nr, mag_nr, designation, unhamed_buffer);

		// $$$ TODO $$ DEBUG
//		{
//			u_char xx[len];
//			u_char *xb = b+3;
//			int  xlen = len-3;
//			out_nl (4," DEBUG $$$: len %d ", len-3);
//			while (xlen > 0) {
//........
//			}
//
//		}
		return len;
	}



	// -- page header!! (Packet_nr == 0)
	// if (packet_nr != 0) return  max_len;


	// -- page nr, etc.
	// -- sub page nr


	// EN 300 706
	// The Page Address consists of a Page Number (see clause 9.3.1.1) and a
	// Page Sub-code (see clause 9.3.1.2). The Page Address may take any value
	// except: Page Number = FF and Sub-code = 3F7F. The address XFF:3F7F is
	// reserved as a null page address.

	// If a magazine has only one displayable page (and in some other
	// circumstances), it may be necessary to indicate the completion of the
	// transmission of that page by closing it with another page header packet.
	// Headers with pages addresses in the range XFF:0000 to XFF:3F7E are
	// defined for use for this purpose. These headers may be referred to as
	// "Time Filling Headers", when they are used to keep the real-time clock
	// field updated in a magazine in parallel transmission mode.


	page_nr     = (unhamB84(*(b+2)) & 0xF) | ( (unhamB84(*(b+3))  & 0xF) << 4);
	sub_page_nr = ( unhamW84(*(b+4),*(b+5)) | (unhamW84(*(b+6),*(b+7)) << 8) ) & 0x3F7F;

	out_SW_NL (v,"page number: ",page_nr);
	out_SW_NL (v,"sub-page number: ",sub_page_nr);


	// -- special pages  (A.10)

	{
	   char *s = "";
	   int  x = (mag_nr<<8 | page_nr);

	   if (x == 0x1BE) s = "Automatic Channel Installation (ACI)";
	   if (x == 0x1F0) s = "Basic TOP Table (BTT)";
	   if (page_nr == 0xFD) s = "Magazine Inventory Page (MIP)";
	   if (page_nr == 0xFE) s = "Magazine Organization Table (MOT)";
	   if (page_nr == 0xFF) s = "Time filling and terminator";
	   if (page_nr == 0xFF && sub_page_nr == 0x3F7F) s = "Null packet";

	   if (*s) out_nl (v,"  ==> %s ",s);
	}
	

	out_nl (v,"  ==> teletext display page number: %x%02x/%x",mag_nr,page_nr,sub_page_nr);

	if (page_nr == 0xFF && sub_page_nr == 0x3F7F) return 8;

	

	// -- Control bits   S. 26 EN 300 706
	// -- don't do unham, get bits directly out of hamming code
	
	{
	  u_char x;
	  int    c4,c5,c6,c7,c8,c9,c10,c11;

	  c4 = *(b+5) & 0x80;			// bit 8
	  
	  x  = *(b+7);
	  c5 = x & 0x20;			// bit 6
	  c6 = x & 0x80;			// bit 7

	  x  = *(b+8);
	  c7 = x & 0x02;			// bit 2
	  c8 = x & 0x08;			// bit 4
	  c9 = x & 0x20;			// bit 6
	  c10= x & 0x80;			// bit 8

	  c11  = *(b+9) & 0x02;			// bit 2

	  if (c4|c5|c6|c7|c8|c9|c10|c11) {
		  out_nl (v,"Control bits:");
		  indent (+1);
			if (c4) out_nl(v,"C4 = Erase page");
			if (c5) out_nl(v,"C5 = Newsflash");
			if (c6) out_nl(v,"C6 = Subtitle");
			if (c7) out_nl(v,"C7 = Suppress header");
			if (c8) out_nl(v,"C8 = Update indicator");
			if (c9) out_nl(v,"C9 = Interrupted sequence");
			if (c10) out_nl(v,"C10 = Inhibit display");
			if (c11) out_nl(v,"C11 = Magazine serial");
		  indent (-1);
	  }
	  
	}


	// -- country/language code  (c12,c13,c14)

	{
	  int lang;

	  lang =  (unhamB84(*(b+9))  >> 1) & 7;	// unhammed bits 4,6,8
	  out_S2B_NL (v,"Character subset (c12-c14): ",
			  lang, dvbstrTELETEXT_lang_code(lang) );
	}



	 // Bytes 14 to 45 in page header packets carry 32 character or display
	 // control codes, coded 7 data bits plus one bit odd parity. They are
	 // normally intended for display. Bytes 38 to 45 are usually coded to
	 // represent a real-time clock.


	// -- timestring, etc.

	unParityTeletextData (b+10, len-10);
	print_teletext_data_x0_x25 (v,"page header display string:", b+10, len-10);
	// print_std_ascii (v, "page header dispay string: ", b+10, len-10);


	return len;
}





// -- display teletext data x0..x24

void print_teletext_data_x0_x25 (int v, char *s, u_char *b, int len)
{

  // $$$ TODO  -- decode display codes c < 0x20
  print_databytes (v, s, b, len);

}







// $$$ TODO  Packet 30/8   -- EN 300 231 8.2.1  (VPS via Teletext)
//
//
