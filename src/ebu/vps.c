/*
$Id: vps.c,v 1.4 2006/01/02 18:24:03 rasc Exp $



 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 -- misc routines for EBU Video Programming System
 -- EN 300 231  8.2.2 




$Log: vps.c,v $
Revision 1.4  2006/01/02 18:24:03  rasc
just update copyright and prepare for a new public tar ball

Revision 1.3  2004/03/10 21:05:53  rasc
WSS (Wide Screen Signalling)  data decoding

Revision 1.2  2004/03/09 21:57:58  rasc
VPS decoding (fix NPP)

Revision 1.1  2004/03/09 20:59:22  rasc
VPS decoding (someone check the NPP & PTY code output please...)




*/


#include "dvbsnoop.h"
#include "vps.h"
#include "strings/dvb_str.h"
#include "misc/helper.h"
#include "misc/hexprint.h"
#include "misc/output.h"






// vps_data_block: this field corresponds to the 13 data bytes of a
// VPS line as described in clause 8.2.2.2 of EN 300 231, excluding the
// run-in and start code byte. So, byte 3 up to and including 15 are
// coded. Data bits are inserted in the PES packet in the same order,
// as they would appear in the VBI.


// The parameters listed in clause 6.1 can be regarded as data fields.
// The data-field length and structure is given hereafter, taking into
// account that bit b1 of a data field is the first bit transmitted.
// Unless otherwise specified, a parameter transmitted with all bits set
// to logical "1" should be regarded as carrying irrelevant information.



// The transport of the recording-control commands for suitably equipped
// receiving equipment makes use of a dedicated line in the field-blanking
// interval of a video signal (in Germany, Austria and Switzerland, line
// 16 is dedicated for this purpose).  This transport method is able to
// carry the parameters CNI, PIL, PCS and PTY.










// -- print VPS codes
// -- !!! BUFFER BYTES HAVE TO BE ALREADY INVERTED! (if needed)
// -- return: len of decoded bytes

int  print_vps_decode (int v, u_char *b, int len)
{
	// warning!  Nipples e.g. _2_7 may not be msb...lsb order!
	//           see: ETSI EN 300 231  for this notation!
   u_int  pcs;
   u_int  cni_1_4;
   u_int  pil;
   u_int  pty;

   u_int  day, month, hour, minute;
   u_int  country_5_8;
   u_int  npp, npp_0_1, npp_2_7;



	out_nl (v,"VPS data:");
	print_databytes (8,"Data:", b, len);


	indent (+1);

	// -- starts at EN 300 231 8.2.2 Fig.9 Table 
	// -- Byte 3..15 , so byte 3 => [0]
	// -- vps_data_block:

	// -- Byte 3+4: not relevant
   	outBit_Sx_NL (v,"(not relevant to PDC): ", 	b,    0, 16);

	// -- PCS
   	pcs = outBit_S2x_NL (v,"PCS audio: ",		b+2,  0,  2,
			(char *(*)(u_long)) dvbstrVPS_pcs_audio );
   	pcs = outBit_Sx_NL  (v,"PCS reserved: ",	b+2,  2,  2);


   	cni_1_4  = outBit_Sx (v,"CNI reserved: ", 	b+2,  4,  4);
	if (cni_1_4 == 0x0F) 	out_nl (4, "  [= Unenhanced VPS]");
	else			out_nl (4, "  [= Enhanced VPS]");



   	outBit_Sx_NL (v,"(not relevant to PDC): ", 	b+3,  0, 24);		// byte 6..10
   	outBit_Sx_NL (v,"(not relevant to PDC): ", 	b+3, 24, 16);


	pil 		=  getBits (b,  8,  2, 20);

	npp_0_1		=  getBits (b,  8,  0,  2);
	day 		=  getBits (b,  8,  2,  5);
	month 		=  getBits (b,  8,  7,  4);
	hour 		=  getBits (b,  8, 11,  5);
	minute 		=  getBits (b,  8, 16,  6);

	country_5_8	=  getBits (b,  8, 22,  4);
	npp_2_7		=  getBits (b,  8, 26,  6);
	pty	 	=  getBits (b,  8, 32,  8);			// byte 15


	out_SB_NL  (v,"NPP_1: ", npp_0_1);


	out_ST  (v,"Program Identificaion Label (PIL): ", pil);
	if (day != 0x00) {
		out_nl     (v,"  [= month=%d  day=%d   hour=%d  min=%d]",
				month, day, hour, minute);
	} else {
		char *s;

		switch (pil) {
			case 0x07FFF: s = "Timer-control code (TC)"; break;
			case 0x07FBF: s = "Record inhibit/Terminate (RI/T)"; break;
			case 0x07F7F: s = "Interrruption code (INT)"; break;
			case 0x07F3F: s = "Continuation code"; break;
			case 0xFFFFF: s = "Program selected by PTY"; break;
			default:      s = "UNKOWN code"; break;
		}

		out_nl (v,"  [= %s]",s);
	}


	out_S2B_NL (v,"Country: ", country_5_8,
			dvbstrVPS_cni_countrycode(1+(country_5_8 << 4)) );

	out_SB_NL  (v,"NPP_2: ", npp_2_7);
	npp = (npp_0_1 << 6) + (npp_2_7);	// msb ... lsb
	out_S2B_NL (v,"  ==> Network/Program Provider (NPP): ", npp, dvbstrVPS_npp(npp) );
	out_S2B_NL (v,"Program Type (PTY): ", pty, dvbstrVPS_pty(pty) );



	indent (-1);
	return len;
}




