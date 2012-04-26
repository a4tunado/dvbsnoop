/*
$Id: pes_std.c,v 1.8 2006/01/15 17:50:31 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PES Decode Standard(?)



$Log: pes_std.c,v $
Revision 1.8  2006/01/15 17:50:31  rasc
no message

Revision 1.7  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.6  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.5  2005/11/08 23:15:25  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.4  2004/08/12 22:57:18  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.3  2004/02/02 23:34:08  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff

Revision 1.2  2004/01/22 22:26:35  rasc
pes_pack_header
section read timeout

Revision 1.1  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured



*/




#include "dvbsnoop.h"
#include "pes_std.h"
#include "pes_data.h"
#include "pes_misc.h"
#include "mpeg_packheader.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"






/*
 *  PES  Decoding
 *  -- updated 2004-08-12  from ITU-T H.222.0 AMD2
 */

void  PES_decode_std (u_char *b, int len, u_int PES_streamID)
{
 /* IS13818-1  2.4.3.6  */

 typedef struct  _PES2_Packet {
        u_int     reserved1;
        u_int     PES_scrambling_control;
        u_int     PES_priority;
        u_int     data_alignment_indicator;
        u_int     copyright;
        u_int     original_or_copy;
        u_int     PTS_DTS_flags;
        u_int     ESCR_flag;
        u_int     ES_rate_flag;
        u_int     DSM_trick_mode_flag;
        u_int     additional_copy_info_flag;
        u_int     PES_CRC_flag;
        u_int     PES_extension_flag;
        u_int     PES_header_data_length;

	// N ... data

 } PES2_Packet;




 PES2_Packet  p;
 u_char       *b_start = b;


 p.reserved1				= getBits (b, 0,  0, 2);
 p.PES_scrambling_control		= getBits (b, 0,  2, 2);
 p.PES_priority				= getBits (b, 0,  4, 1);
 p.data_alignment_indicator		= getBits (b, 0,  5, 1);
 p.copyright				= getBits (b, 0,  6, 1);
 p.original_or_copy			= getBits (b, 0,  7, 1);
 p.PTS_DTS_flags			= getBits (b, 0,  8, 2);
 p.ESCR_flag				= getBits (b, 0, 10, 1);
 p.ES_rate_flag				= getBits (b, 0, 11, 1);
 p.DSM_trick_mode_flag			= getBits (b, 0, 12, 1);
 p.additional_copy_info_flag		= getBits (b, 0, 13, 1);
 p.PES_CRC_flag				= getBits (b, 0, 14, 1);
 p.PES_extension_flag			= getBits (b, 0, 15, 1);
 p.PES_header_data_length		= getBits (b, 0, 16, 8);


 // $$$ TODO own subroutine for PES_header (get and out)

 out_SB_NL  (6,"reserved1: ",p.reserved1);
 out_S2B_NL (3,"PES_scrambling_control: ",p.PES_scrambling_control,
	dvbstrPESscrambling_ctrl_TYPE(p.PES_scrambling_control));
 out_SB_NL  (3,"PES_priority: ",p.PES_priority);
 out_SB_NL  (3,"data_alignment_indicator: ",p.data_alignment_indicator);
 out_SB_NL  (3,"copyright: ",p.copyright);
 out_SB_NL  (3,"original_or_copy: ",p.original_or_copy);
 out_SB_NL  (3,"PTS_DTS_flags: ",p.PTS_DTS_flags);
 out_SB_NL  (3,"ES_rate_flag: ",p.ES_rate_flag);
 out_SB_NL  (3,"additional_copy_info_flag: ",p.additional_copy_info_flag);
 out_SB_NL  (3,"PES_CRC_flag: ",p.PES_CRC_flag);
 out_SB_NL  (3,"PES_extension_flag: ",p.PES_extension_flag);
 out_SB_NL  (3,"PES_header_data_length: ",p.PES_header_data_length);

 b += 3;


 if (p.PTS_DTS_flags & 0x02) {    // 10
   out_nl (3,"PTS: ");
   indent (+1);
   outBit_Sx_NL (3,"Fixed: ",b,0,4);
   print_xTS_field (3,"PTS", b, 4) ;
   indent (-1);
   b += 5;
 }

 if (p.PTS_DTS_flags == 0x03) {    // 10 + 01
   // PTS already printed, from "if" before...
   out_nl (3,"DTS: ");
   indent (+1);
   outBit_Sx_NL (3,"Fixed: ",b,0,4);
   print_xTS_field (3,"DTS",b, 4) ;
   indent (-1);
   b += 5;
 }

 if (p.ESCR_flag == 0x01) {
   out_nl (3,"ESCR_flag: ");
   outBit_Sx_NL (6,"reserved: ",      b,0,2);
   indent (+1);
   print_xTS_field (3,"ESCR_base",b, 2) ;
   outBit_Sx_NL (3,"ESCR_extension: ",b,38,9);
   outBit_Sx_NL (3,"marker_bit: ",    b,47,1);
   indent (-1);
   b += 6;
 }



 if (p.ES_rate_flag == 0x01) {
   out_nl (3,"ES_rate_flag: ");
   indent (+1);
   outBit_Sx_NL (3,"marker_bit: ",b, 0, 1);
   outBit_Sx_NL (3,"ES_rate: ",   b, 1,22);
   outBit_Sx_NL (3,"marker_bit: ",b,23, 1);
   indent (-1);
   b += 3;
 }

 if (p.DSM_trick_mode_flag == 0x01) {
   u_int  trick_mode_control;


   out_nl (3,"Trick_mode_control: ");
   indent (+1);

   trick_mode_control = outBit_S2x_NL  (3,"trick_mode_control: ", b,0,3,
		   (char *(*)(u_long)) dvbstrPESTrickModeControl);

   if ( (trick_mode_control == 0x0) ||			/* fast forward */
        (trick_mode_control == 0x3) ) {			/* fast reverse */

	   outBit_Sx_NL (3,"field_id: ",b, 3, 2);	/* $$$ TABLE ?? */
	   outBit_Sx_NL (3,"intra_slice_refresh: ",b, 5, 1);
	   outBit_Sx_NL (3,"frequency_truncation: ",b, 6, 2);

   } else if ( (trick_mode_control == 0x1) ||		/* slow motion  */
               (trick_mode_control == 0x4) ) {		/* slow reverse */

	   outBit_Sx_NL (3,"rep_control: ",b, 3, 5);

   } else if (trick_mode_control == 0x2) {		/* freeze frame */

	   outBit_Sx_NL (3,"field_id: ",b, 3, 2);	/* $$$ TABLE ?? */
	   outBit_Sx_NL (6,"reserved: ",b, 5, 3);

   } else {						/* reserved     */

	   outBit_Sx_NL (6,"reserved: ",b, 3, 8);

   }

   indent (-1);
   b += 1;

 }  /* p.DSM_trick_mode_flag  */


 if (p.additional_copy_info_flag == 0x01) {

   out_nl (3,"additional_copy_info: ");
   indent (+1);
   outBit_Sx_NL (3,"marker_bit: ",b, 0, 1);
   outBit_Sx_NL (3,"additional_copy_info: ",b, 1, 7);
   b += 1;
   indent (-1);

 }


 if (p.PES_CRC_flag == 0x01) {

   out_nl (3,"PES_CRC: ");
   indent (+1);
   outBit_Sx_NL (3,"previous_PES_packet_CRC: ",b, 0, 16);
   b += 2;
   indent (-1);

 }


 if (p.PES_extension_flag == 0x01) {

   u_int  PES_private_data_flag;
   u_int  pack_header_field_flag;
   u_int  program_packet_sequence_counter_flag;
   u_int  P_STD_buffer_flag;
   u_int  reserved;
   u_int  PES_extension_flag2;


   out_nl (3,"PES_extension: ");
   indent (+1);

   PES_private_data_flag                  = getBits (b, 0,  0,  1);
   pack_header_field_flag                 = getBits (b, 0,  1,  1);
   program_packet_sequence_counter_flag   = getBits (b, 0,  2,  1);
   P_STD_buffer_flag                      = getBits (b, 0,  3,  1);
   reserved                               = getBits (b, 0,  4,  3);
   PES_extension_flag2                    = getBits (b, 0,  7,  1);
   b += 1;

   out_SB_NL  (3,"PES_private_data_flag: ", PES_private_data_flag);
   out_SB_NL  (3,"pack_header_field_flag: ",  pack_header_field_flag);
   out_SB_NL  (3,"program_packet_sequence_counter_flag: ", program_packet_sequence_counter_flag);
   out_SB_NL  (3,"P-STD_buffer_flag: ", P_STD_buffer_flag);
   out_SB_NL  (6,"reserved: ", reserved);
   out_SB_NL  (3,"PES_extension_flag2: ", PES_extension_flag2);


   if (PES_private_data_flag == 0x01) {

	print_databytes (3,"PES_private_data", b, 16);
   	b += 16;

   }


   if (pack_header_field_flag == 0x01) {		/* ISO 11172-1 pack header */
	
	int pack_field_length;

   	out_nl (3,"pack_header_field: ");
	indent (+1);
	pack_field_length             = getBits (b, 0,  0,  8);
   	out_SB_NL  (3,"pack_field_length: ", pack_field_length);
	mpeg_pack_header (3, b+1, pack_field_length);
   	b += pack_field_length +1;
   	indent (-1);

   }



   if (program_packet_sequence_counter_flag == 0x01) {

   	out_nl (3,"program_packet_sequence_counter: ");
	indent (+1);
	out_SB_NL  (3,"Marker_bit: ", getBits (b, 0,  0,  1) );
	out_SB_NL  (3,"program_packet_sequence_counter: ", getBits (b, 0,  1,  7) );
	out_SB_NL  (3,"Marker_bit: ", getBits (b, 0,  8,  1) );
	out_SB_NL  (3,"MPEG1_MPEG2_identifier: ", getBits (b, 0,  9,  1) );
	out_SB_NL  (3,"original_stuff_length: ", getBits (b, 0, 10,  6) );
	b += 2;
   	indent (-1);

   }


   if (P_STD_buffer_flag == 0x01) {

   	out_nl (3,"P-STD_buffer: ");
	indent (+1);
	out_SB_NL  (6,"Fix 01: ",             getBits (b, 0,  0,  2) );
	out_SB_NL  (3,"P-STD_buffer_scale: ", getBits (b, 0,  2,  1) );
	out_SB_NL  (3,"P-STD_buffer_size: ",  getBits (b, 0, 3,  13) );
	b += 2;
   	indent (-1);

   }


   if (PES_extension_flag2 == 0x01) {
	// -- ITU-T Rec. H.222.0 (2000)/Amd.2 (06/2003)

	u_int  PES_extension_field_length;
	u_int  streamID_extension_flag;

   	out_nl (3,"PES_extension_2: ");
	indent (+1);
	out_SB_NL  (3,"Marker_bit: ", getBits (b, 0,  0,  1) );

	PES_extension_field_length = outBit_Sx_NL (4,"PES_extension_field_length: ",	b,  1, 7);
	streamID_extension_flag    = outBit_Sx_NL(4,"stream_id_extension_flag: ",	b,  8, 1);

	if (streamID_extension_flag == 0) {
	    outBit_S2x_NL(4,"stream_id_extension_flag: ",	b,   9, 7,
			(char *(*)(u_long)) dvbstrPESstream_ID_Extension);
	    print_databytes (6,"reserved:", b+2, PES_extension_field_length-1);
	}


	b += PES_extension_field_length + 1;
   	indent (-1);

   }

   indent (-1);

 } /* p.PES_extension_flag */




  // PES_header_data_length : An 8-bit field specifying the total number of
  // bytes occupied by the optional fields and any stuffing bytes contained
  // in this PES packet header. The presence of optional fields is indicated
  // in the byte that precedes the PES_header_data_length field.
  // (PES_header_data_length has the length up to this point)
 




  // stuffing_byte:
  // This is a fixed 8-bit value equal to '1111 1111' that
  // can be inserted by the encoder, for example to meet the requirements
  // of the channel. It is discarded by the decoder. No more than 32 stuffing
  // bytes shall be present in one PES packet header.

  {
    int    i   = 0;
    u_char *bx = b;

    while (*bx++ == 0xFF) i++;
    if (i > 0) {
    	print_databytes (4,"stuffing bytes:", b, i);
    	b += i;
    }

  }



  // -- PES packet_data_bytes
  // -- check streamID
  // $$$ TODO: data_identifier (Teletext, DVB subtitles, etc...)

  {
    // $$$ TODO: unbound streams: len = 0 !!
    int len2 = len - (b - b_start);


    if (len2 > 0) {
      switch (PES_streamID) {

	case 0xBD:	// Data Stream, privat_stream_1 (EN301192-1.3.1 S.11)
    		out_nl (3,"PES_data (private_stream_1):");
		indent (+1);
		PES_decodeDATA_private_stream_1 (b, len2);
		indent (-1);
		break;

	default:
		print_databytes (4,"PES_packet_data_bytes:", b, len2);
		break;
      }
    } // if

  }



}



