/*
$Id: pespacket.c,v 1.37 2006/01/02 18:24:12 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PES Decoding



$Log: pespacket.c,v $
Revision 1.37  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.36  2005/12/27 23:30:29  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.35  2005/11/23 23:06:10  rasc
ISO13818-2  MPEG2 sequence header

Revision 1.34  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.33  2005/11/08 23:15:25  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.32  2005/10/20 22:25:07  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.31  2005/09/06 23:58:50  rasc
typo fix

Revision 1.30  2005/09/06 23:32:04  rasc
no message

Revision 1.29  2005/09/06 23:13:52  rasc
catch OS signals (kill ...) for smooth program termination

Revision 1.28  2005/09/02 14:11:35  rasc
TS code redesign, xPCR and DTS timestamps decoding

Revision 1.27  2005/08/10 21:28:18  rasc
New: Program Stream handling  (-s ps)

Revision 1.26  2005/01/17 19:41:23  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.25  2004/08/24 21:30:22  rasc
more Metadata

Revision 1.24  2004/04/15 03:38:51  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.23  2004/02/09 22:57:00  rasc
Bugfix VBI Data descriptor

Revision 1.22  2004/02/02 23:34:08  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff

Revision 1.21  2004/01/22 22:26:35  rasc
pes_pack_header
section read timeout

Revision 1.20  2004/01/11 22:49:41  rasc
PES restructured

Revision 1.19  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured

Revision 1.18  2004/01/02 16:40:38  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.17  2004/01/02 00:00:41  rasc
error output for buffer overflow

Revision 1.16  2004/01/01 20:09:29  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.15  2003/12/27 14:35:01  rasc
dvb-t descriptors
DSM-CC: SSU Linkage/DataBroadcast descriptors

Revision 1.14  2003/12/17 23:15:04  rasc
PES DSM-CC  ack and control commands  according ITU H.222.0 Annex B

Revision 1.13  2003/11/26 19:55:33  rasc
no message

Revision 1.12  2003/11/26 16:27:47  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.11  2003/11/24 23:52:17  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.10  2003/11/09 20:48:35  rasc
pes data packet (DSM-CC)

Revision 1.9  2003/11/01 17:05:47  rasc
no message

Revision 1.8  2003/10/29 22:39:18  rasc
pes packet complete now...

Revision 1.7  2003/10/29 20:54:56  rasc
more PES stuff, DSM descriptors, testdata

Revision 1.6  2003/10/24 22:17:20  rasc
code reorg...

Revision 1.5  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.4  2001/12/06 15:33:18  rasc
some small work on pespacket.c

Revision 1.3  2001/12/01 12:46:48  rasc
pespacket weitergestrickt, leider z.Zt. zuwenig Zeit um es richtig fertig zu machen.

Revision 1.2  2001/10/02 21:52:44  rasc
- init der time_delta
- PES erweitert, PES arbeitet im read() noch nicht richtig!!

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS



*/




#include "dvbsnoop.h"
#include "pespacket.h"
#include "pes_std.h"
#include "pes_dsmcc.h"
#include "pes_psm.h"
#include "pes_psdir.h"
#include "mpeg_packheader.h"
#include "mpeg_sysheader.h"
#include "mpeg2_video.h"

#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"
#include "misc/print_header.h"
#include "misc/cmdline.h"



//
// -- process PS PES packet (in sync) 
// -- hexdump, decoding
//

void processPS_PES_packet (u_int pid, long pkt_nr, u_char *buf, int len)
{
	
  OPTION *opt  = getOptionPtr();
  char *strx   = (opt->packet_mode == PES) ? "PES" : "PS";


       indent (0);
       print_packet_header (opt, strx, opt->pid, pkt_nr, len);


       if (opt->buffer_hexdump) {
           printhex_buf (0, buf, len);
           out_NL(0);
       }


       // decode protocol
       if (opt->printdecode) {
          decodePS_PES_packet (buf, len ,opt->pid);
          out_nl (3,"==========================================================");
          out_NL (3);
       }


}







void decodePS_PES_packet (u_char *b, u_int len, int pid)
{
 /* IS13818-1  2.4.3.6  */

  u_long    packet_start_code_prefix;		// 24 bit
  u_int     stream_id;
  u_int     PES_packet_length;





 // -- Get/check packet header prefix (sync bits)

 packet_start_code_prefix		 = getBits (b, 0,  0, 24);
 if (packet_start_code_prefix != 0x000001) {
	out_nl (3," !!! Packet_Start_CODE [%06lx] is wrong (= no PES/PS [0x000001])!!!\n",
		packet_start_code_prefix);
	print_databytes (4,"Unknown packet data:", b, len);
	return;
 }
 out_nl (3,"Packet_start_code_prefix: 0x%06lx",packet_start_code_prefix);



 // -- PS/PES stream ID

 stream_id = outBit_S2x_NL(3,"Stream_id: ",	b, 24, 8,
		 (char *(*)(u_long))dvbstrPESstream_ID );





   //
   // -- PES Stream ID 0x00 - 0xB8
   // -- ISO 13818-2
   //

   if (stream_id <= 0xB8) {

   		// $$$ TODO  PES Stream ID 0x00 - 0xB8
		//    reserved	B0
		//    reserved	B1
		//    sequence_error_code	B4  (not for streams)
		//    reserved	B6

	indent (+1);
	switch (stream_id) {

	  case 0x00:			// picture_start_code   00
		MPEG2_decodePictureHeader (4, b, len);
		break;

	  case 0xB2:			// user_data_start_code B2
		MPEG2_decodeUserData (4, b, len);
		break;

	  case 0xB3:			// sequence_header_code B3
		MPEG2_decodeSequenceHeader (4, b, len);
		break;

	  case 0xB5:			// extension_data       B5
		MPEG2_decodeExtension (4, b, len);
		break;

	  case 0xB7:			// sequence_end_code	B7
		MPEG2_decodeSequenceEnd (4, b, len);
		return;

	  case 0xB8:			//    group_start_code	B8
		MPEG2_decodeGroupOfPictures (4, b, len);
		break;

	  default:
					//    slice_start_code	01 through AF
		if (stream_id >= 0x01 && stream_id <= 0xAF) {

			MPEG2_decodeSlice (4, b, len);

		} else {
					//    unkown
		   if (len > 4) {		// sync + stream_id = 4 bytes
			print_databytes (4,"MPEG2 Data (incl. sync + id):", b, len);
		   }

		}
		break;
	}
	indent (-1);

	return;

   }





   //
   // -- PES Stream ID 0xB9 - 0xBB
   // -- check PS decoding (ProgramStream)
   //

   switch (stream_id) {
	case 0xB9:	// MPEG_program_end
			// stream ID already printed, nothing else to do
		return;

	case 0xBA:	// MPEG_pack_header_start
		mpeg_pack_header (3, b, -1);		// startcode & ID already printed
		return;

	case 0xBB:	// MPEG_system_header_start
		mpeg_system_header (3, b, -1);	// startcode & ID already printed
		return;
   }






   // 
   // -- PES decoding ...
   // -- StreamID 0xBC..0xFF
   //

   PES_packet_length = outBit_Sx_NL (3,"PES_packet_length: ",	b,32, 16);
   b   += 6;
   len -= 6;


   switch (stream_id) {

	case 0xBC:		// program_stream_map
		PES_decodePSM (b, PES_packet_length);
		break;

	case 0xBE:		// padding stream!
		print_databytes (3,"Padding_bytes:", b, PES_packet_length);
		break;

	case 0xF2:		// DSMCC stream
		PES_decodeDSMCC (b, PES_packet_length);
		break;

	case 0xFF:		// program_stream_directory
		PES_decodePSDIR (b, PES_packet_length);
		break;


	case 0xBF:		// private_stream_2  (EN301192-1.3.1 S.10)
	case 0xF0:		// ECM
	case 0xF1:		// EMM
	case 0xF8:		// ITU-T Rec. H.222.1 type E
		print_databytes (3,"PES_packet_data_bytes:", b, PES_packet_length);
		break;

	// case 0xFC:		// metadata stream	(see: H.222.0 AMD1)
	// $$$ TODO 

	// case 0xBD:		// Data Stream, privat_stream_1 (EN301192-1.3.1 S.11)
	// case 0xC0-0xDF	// ISO/IEC 13818-3 or 11172-3 or 13818-7 or 14496-3 audio stream 
	// case 0xE0-0xEF	// ITU-T Rec. H.262 | ISO/IEC 13818-2 or 11172-2 or 14496-2 video stream
	// case 0xF3		// ISO/IEC_13522_stream
	// case 0xF4		// ITU-T Rec. H.222.1 type A
	// case 0xF5		// ITU-T Rec. H.222.1 type B
	// case 0xF6		// ITU-T Rec. H.222.1 type C
	// case 0xF7		// ITU-T Rec. H.222.1 type D
	// case 0xF9		// ancillary_stream
	// case 0xFA		// ISO/IEC14496-1_SL-packetized_stream
	// case 0xFB		// ISO/IEC14496-1_FlexMux_stream
	// case 0xFD		// extended_stream_id
	// case 0xFE		// reserved data stream
	
	default:
		{
		   int xlen = PES_packet_length;

 		   if ((PES_packet_length==0) && ((stream_id & 0xF0)==0xE0)) {
			 out_nl (3," ==> unbound video elementary stream... \n");
			 xlen = len;	// PES len field == 0, use read packet len
 		   }
		   if (xlen > 0) {
			indent (+1);
			PES_decode_std (b, xlen, stream_id);
			indent (-1);
		   }

		}
		break;

   } // switch


}


 // Annotation:
 // ISO 13818-1, 2.4.3.6:
 // PES_packet_length:  A 16-bit field specifying the number of bytes in the
 // PES packet following the last byte of the field. A value of 0 indicates that
 // the PES packet length is neither specified nor bounded and is allowed only
 // in PES packets whose payload consists of bytes from a video elementary
 // stream contained in Transport Stream packets.








// Annotations: 
//
//
// $$$ TODO  0x00000100-B8 ISO 13818-2  Start codes
//



