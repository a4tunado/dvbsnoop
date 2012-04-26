/*
$Id: mpeg2_video.c,v 1.3 2005/12/27 23:30:29 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 ISO 13818-2  MPEG-2  Video



$Log: mpeg2_video.c,v $
Revision 1.3  2005/12/27 23:30:29  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.2  2005/11/23 23:06:10  rasc
ISO13818-2  MPEG2 sequence header

Revision 1.1  2005/11/10 00:07:18  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix





*/




#include "dvbsnoop.h"
#include "mpeg2_video.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"




// -- ISO 13818-2,  6.3.12	Picture display extension
static int  number_of_frame_centre_offsets = 0;






// ------------------------------------------------------------------



/*
   -- MPEG-2 Sequence End
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodeSequenceEnd (int v, u_char *b, int len)
{
   // .. nothing to do...
   return;
}



/*
   -- MPEG-2 User Data
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodeUserData (int v, u_char *b, int len)
{

   // outBit_Sx_NL (3,"packet_start_code: ",	b, 0, 24);
   // outBit_S2x_NL(3,"Stream_id: ",		b, 24, 8,
   // 		   (char *(*)(u_long))dvbstrPESstream_ID );
 
   print_databytes (v,"User data:", b+4, len-4);

}
 



/*
   -- MPEG-2 GOP, Group of Pictures
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodeGroupOfPictures (int v, u_char *b, int len)
{

   // outBit_Sx_NL (3,"packet_start_code: ",	b, 0, 24);
   // outBit_S2x_NL(3,"Stream_id: ",		b, 24, 8,
   // 		   (char *(*)(u_long))dvbstrPESstream_ID );
   // len -= 4;

   b += 4;

   // outBit_Sx_NL (4,"time_code: ",		b,  0, 25); 
   out_nl (v,"time_code:");
   indent (+1);
   	outBit_Sx_NL (v,"drop_frame_flag: ",	b,  0,  1);
   	outBit_Sx_NL (v,"time_code_hours: ",	b,  1,  5);
   	outBit_Sx_NL (v,"time_code_minutes: ",	b,  6,  6);
   	outBit_Sx_NL (v,"marker_bit: ",		b, 12,  1);
   	outBit_Sx_NL (v,"time_code_seconds: ",	b, 13,  6);
   	outBit_Sx_NL (v,"time_code_pictures: ",	b, 19,  6);
   indent (-1);

   outBit_Sx_NL (v,"closed_gop: ",		b, 25,  1);
   outBit_Sx_NL (v,"broken_link: ",		b, 26,  1);


}




/*
   -- MPEG-2 sequence header
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodeSequenceHeader (int v, u_char *b, int len)
{

  int liqm;
  int nliqm;
  int bc;	// bit offset count;


   // outBit_Sx_NL (3,"packet_start_code: ",	b, 0, 24);
   // outBit_S2x_NL(3,"Stream_id: ",		b, 24, 8,
   // 		   (char *(*)(u_long))dvbstrPESstream_ID );
   // len -= 4;

   b += 4;

   outBit_Sx_NL (v,"horizontal_size_value: ",		b,  0,  12);
   outBit_Sx_NL (v,"vertical_size_value: ",		b, 12,  12);
   outBit_S2x_NL(v,"aspect_ratio_information: ",	b, 24,   4,
    		   (char *(*)(u_long))dvbstrAspectRatioInfo_FLAG);
   outBit_S2x_NL(v,"frame_rate_code: ",			b, 28,   4,
    		   (char *(*)(u_long))dvbstrMPEG_FrameRateCode);

   outBit_S2Tx_NL(v,"bit_rate_value: ",			b, 32,  18,
		   "* 400 bit/s");
   outBit_Sx_NL (v,"marker_bit: ",			b, 50,   1);
   outBit_Sx_NL (v,"vbv_buffer_size_value: ",		b, 51,  10);
   outBit_Sx_NL (v,"contraint_parameters_flag: ",	b, 61,   1);

   liqm  = outBit_Sx_NL (v,"load_intra_quantiser_matrix: ",	b, 62,   1);
   bc = 63;
   if (liqm) {
	   // 8x[64]
	   print_BitMatrix (v,"intra_quantiser_matrix: ", b, bc,  8,64);
	   bc += 8*64;
   }

   nliqm = outBit_Sx_NL (v,"load_non_intra_quantiser_matrix: ",	b, bc,   1);
   bc++;
   if (nliqm) {
	   // 8x[64]
	   print_BitMatrix (v,"non_intra_quantiser_matrix: ", b, bc,  8,64);
	   bc += 8*64;
   }


   // -- ISO 13818-2,  6.3.12	Picture display extension
   number_of_frame_centre_offsets = 0;

}
 



/*
   -- MPEG-2 Picture Start
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodePictureHeader (int v, u_char *b, int len)
{

   int pct;
   int bc;	// bit count


   // outBit_Sx_NL (3,"packet_start_code: ",	b, 0, 24);
   // outBit_S2x_NL(3,"Stream_id: ",		b, 24, 8,
   // 		   (char *(*)(u_long))dvbstrPESstream_ID );
   // len -= 4;

   bc = 32;	// b += 4

         outBit_Sx_NL (v,"temporal_reference: ",	b, bc+ 0,  10);
   pct = outBit_S2x_NL(v,"picture_coding_type: ",	b, bc+10,   3,
    		   (char *(*)(u_long)) dvbstrMPEG_PictureCodingType );

         outBit_Sx_NL (v,"vbv_delay: ",			b, bc+13,  16);  // $$$ TODO   90 KHz Clock
   bc += 16;


   if (pct == 2 || pct == 3) {
         outBit_Sx_NL (v,"full_pel_forward_vector: ",	b, bc+0,   1);
         outBit_Sx_NL (v,"forward_f_code: ",		b, bc+1,   3);
	 bc += 4;
   }

   if (pct == 3) {
         outBit_Sx_NL (v,"full_pel_backward_vector: ",	b, bc+0,   1);
         outBit_Sx_NL (v,"backward_f_code: ",		b, bc+1,   3);
	 bc += 4;
   }



   // while (nextbits() == 1)
   while ( outBit_Sx_NL (v,"extra_bit_picture: ",	b, bc+0,   1) ) {
         outBit_Sx_NL (v,"extra_information_picture: ",	b, bc+1,   8);
   	 bc += 9;
   }

}







/*
   -- MPEG-2 Extension 
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodeExtension (int v, u_char *b, int len)
{

   int esci;    // extension_start_code_identifier


   // outBit_Sx_NL (3,"packet_start_code: ",	b, 0, 24);
   // outBit_S2x_NL(3,"Stream_id: ",		b, 24, 8,
   // 		   (char *(*)(u_long))dvbstrPESstream_ID );


   esci =  outBit_S2x_NL (v,"extension_start_code_identifier: ",	b+4,  0,  4,
    		   (char *(*)(u_long)) dvbstrMPEG_ExtensionStartCodeIdentifier);

   switch ( esci ) {

	case 0x01:		//  "Sequence Extension ID" 
		MPEG2_decodeSequenceExtension (v, b, len);
		break;

	case 0x02:		//  "Sequence Display Extension ID" 
		MPEG2_decodeSequenceDisplayExtension (v, b, len);
		break;

	case 0x03:		//  "Quant Matrix Extension ID" 
		MPEG2_decodeQuantMatrixExtension (v, b, len);
		break;

	case 0x04:		//  "Copyright Extension ID" 
		MPEG2_decodeCopyrightExtension(v, b, len);
		break;

	case 0x05:		//  "Sequence Scalable Extension ID" 
		MPEG2_decodeSequenceScalableExtension (v, b, len);
		break;

	case 0x07:		//  "Picture Display Extension ID" 
		MPEG2_decodePictureDisplayExtension (v, b, len);
		break;

	case 0x08:		//  "Picture Coding Extension ID" 
		MPEG2_decodePictureCodingExtension (v, b, len);
		break;

	case 0x09:		//  "Picture Spatial Scalable Extension ID" 
		MPEG2_decodePictureSpatialScalableExtension (v, b, len);
		break;

	case 0x0A:		//  "Picture Temporal Scalable Extension ID" 
		MPEG2_decodePictureTemporalScalableExtension (v, b, len);
		break;

	default:
		print_databytes (v,"Unkown extension data (incl. start_code):", b, len);
		break;

   }

}
 



//
// -- IMPORTANT: on all Extension IDs:
// -- "packet start code"  (sync, streamID) and "extension
// -- start code identifier" already printed.
// -- Buffer pointer and length are from packet start(!).
// -- (so we start decoding at buffer+4 and + 4 bits)
//



/*
   -- MPEG-2 Sequence Extension 
   -- ISO 13818-2
*/

void MPEG2_decodeSequenceExtension (int v, u_char *b, int len)
{
 
   int eb;


   b += 4;


   // outBit_S2x_NL (v,"profile_and_level_indication: ",	b,  4,  8,
   // 		   (char *(*)(u_long)) dvbstrMPEG_ProfileAndLevelIndication);
 
   out_nl (v,"profile_and_level_indication: ");
   indent (+1);
     eb = outBit_Sx_NL (v,"escape_bit: ",			b,  4,  1);
     if (eb == 0) {
        outBit_S2x_NL (v,"profile_indication: ",		b,  5,  3,
    		   (char *(*)(u_long)) dvbstrMPEG_ProfileIndication);
        outBit_S2x_NL (v,"level_indication: ",			b,  8,  4,
    		   (char *(*)(u_long)) dvbstrMPEG_LevelIndication);
     } else {
       outBit_Sx_NL (v,"profile_and_level_indication [0..6]: ",	b,  5,  7);
     }
   indent (-1);


   outBit_Sx_NL  (v,"progressive_sequence: ",			b, 12,  1);
   outBit_S2x_NL (v,"chroma_format: ",				b, 13,  2,
    		   (char *(*)(u_long)) dvbstrMPEG_ChromaFormat);

   outBit_Sx_NL  (v,"horizontal_size_extension: ",		b, 15,  2);
   outBit_Sx_NL  (v,"vertical_size_extension: ",		b, 17,  2);
   outBit_Sx_NL  (v,"bit_rate_extension: ",			b, 19, 12);
   outBit_Sx_NL  (v,"marker_bit: ",				b, 31,  1);
   outBit_Sx_NL  (v,"vbv_buffer_size_extension: ",		b, 32,  8);
   outBit_Sx_NL  (v,"low_delay: ",				b, 40,  1);
   outBit_Sx_NL  (v,"frame_rate_extension_n: ",			b, 41,  2);
   outBit_Sx_NL  (v,"frame_rate_extension_d: ",			b, 43,  5);

}



/*
   -- MPEG-2 Sequence Display Extension
   -- ISO 13818-2
*/

void MPEG2_decodeSequenceDisplayExtension (int v, u_char *b, int len)
{

   int cd;


   b += 4;

        outBit_S2x_NL (v,"video_format: ",			b,  4,  3,
    		   (char *(*)(u_long)) dvbstrMPEG_VideoFormat);
   cd = outBit_Sx_NL  (v,"color_description: ",			b,  7,  1);
   b++;

   if (cd) {
        outBit_S2x_NL (v,"color_primaries: ",			b,  0,  8,
    		   (char *(*)(u_long)) dvbstrMPEG_ColorPrimaries);
        outBit_S2x_NL (v,"transfer_characteristics: ",		b,  8,  8,
    		   (char *(*)(u_long)) dvbstrMPEG_TransferCharacteristics);
        outBit_S2x_NL (v,"matrix_coefficients: ",		b, 16,  8,
    		   (char *(*)(u_long)) dvbstrMPEG_MatrixCoefficients);
	b += 3;
   }

   outBit_Sx_NL  (v,"display_horizontal_size: ",		b,  0, 14);
   outBit_Sx_NL  (v,"marker_bit: ",				b, 14,  1);
   outBit_Sx_NL  (v,"display_vertical_size: ",			b, 15, 14);

}





/*
   -- MPEG-2 Sequence Scalable Extension
   -- ISO 13818-2
*/

void MPEG2_decodeSequenceScalableExtension (int v, u_char *b, int len)
{

   int   sm;
   int   pme;
   int   bc;    // bit count



   bc = 32;

   sm = outBit_S2x_NL (v,"scalable_mode: ",			b, bc+4,  2,
    		   (char *(*)(u_long)) dvbstrMPEG_ScalableMode);
	outBit_Sx_NL  (v,"layer_id: ",				b, bc+6,  4);
   bc += 10;

   if (sm == 1)	{	// spacial scalability
	outBit_Sx_NL  (v,"lower_layer_prediction_horizontal_size: ",	b, bc+ 0, 14);
	outBit_Sx_NL  (v,"marker_bit: ",				b, bc+14,  1);
	outBit_Sx_NL  (v,"lower_layer_prediction_vertical_size: ",	b, bc+15, 14);
	outBit_Sx_NL  (v,"horizontal_subsampling_factor_m: ",		b, bc+29,  5);
	outBit_Sx_NL  (v,"horizontal_subsampling_factor_n: ",		b, bc+34,  5);
	outBit_Sx_NL  (v,"vertical_subsampling_factor_m: ",		b, bc+39,  5);
	outBit_Sx_NL  (v,"vertical_subsampling_factor_n: ",		b, bc+44,  5);
	bc += 49;
   }

   if (sm == 3)	{	// temporal scalability
	pme = outBit_Sx_NL  (v,"picture_mux_enable: ",		b, bc+ 0,  1);
	bc++;
	if (pme) {
	   outBit_Sx_NL  (v,"mux_to_progressive_sequence: ",	b, bc+ 0,  1);
	   bc++;
	}

	outBit_Sx_NL  (v,"picture_mux_order: ",			b, bc+ 0,  3);
	outBit_Sx_NL  (v,"picture_mux_factor: ",		b, bc+ 3,  3);

   }

}




/*
   -- MPEG-2 Picture Coding Extension
   -- ISO 13818-2
*/

void MPEG2_decodePictureCodingExtension (int v, u_char *b, int len)
{

   int   cdf;


   b += 4;
   
   outBit_Sx_NL  (v,"f_code[forward][horizontal]: ",		b,  4,  4);
   outBit_Sx_NL  (v,"f_code[forward][vertical]: ",		b,  8,  4);
   outBit_Sx_NL  (v,"f_code[backward][horizontal]: ",		b, 12,  4);
   outBit_Sx_NL  (v,"f_code[backward][vertical]: ",		b, 16,  4);

   outBit_S2x_NL (v,"intra_dc_precision: ",			b, 20,  2,
    		(char *(*)(u_long)) dvbstrMPEG_Intra_DC_Precision);
   outBit_S2x_NL (v,"picture_structure: ",			b, 22,  2,
    		(char *(*)(u_long)) dvbstrMPEG_PictureStructure);

   outBit_Sx_NL  (v,"top_field_first: ",			b, 24,  1);
   outBit_Sx_NL  (v,"frame_pred_frame_dct: ",			b, 25,  1);
   outBit_Sx_NL  (v,"concealment_motion_vectors: ",		b, 26,  1);
   outBit_Sx_NL  (v,"q_scale_type: ",				b, 27,  1);
   outBit_Sx_NL  (v,"intra_vlc_format: ",			b, 28,  1);
   outBit_Sx_NL  (v,"alternate_scan: ",				b, 29,  1);
   outBit_Sx_NL  (v,"repeat_first_field: ",			b, 30,  1);
   outBit_Sx_NL  (v,"chroma_420_type: ",			b, 31,  1);
   outBit_Sx_NL  (v,"progressive_frame: ",			b, 32,  1);

   cdf = outBit_Sx_NL (v,"composite_display_flag: ",		b, 33,  1);
   if (cdf) {
	outBit_Sx_NL  (v,"v_axis: ",				b, 34,  1);
	outBit_Sx_NL  (v,"field_sequence: ",			b, 35,  3);
	outBit_Sx_NL  (v,"sub_carrier: ",			b, 38,  1);
	outBit_Sx_NL  (v,"burst_amplitude: ",			b, 39,  7);
	outBit_Sx_NL  (v,"sub_carrier_phase: ",			b, 46,  8);
   }


}




/*
   -- MPEG-2 Quant Matrix Extension
   -- ISO 13818-2
*/

void MPEG2_decodeQuantMatrixExtension (int v, u_char *b, int len)
{

   int    bc;
   int    liqm;
   int    lniqm;
   int    lciqm;
   int    lcniqm;



   b += 4;
   

   liqm  = outBit_Sx_NL (v,"load_intra_quantiser_matrix: ",	b,   4,  1);
   bc = 5;

   if (liqm) {
	   // 8x[64]
	   print_BitMatrix (v,"intra_quantiser_matrix: ", 	b, bc,  8,64);
	   bc += 8*64;
   }

   lniqm = outBit_Sx_NL (v,"load_non_intra_quantiser_matrix: ",	b, bc,   1);
   bc++;
   if (lniqm) {
	   // 8x[64]
	   print_BitMatrix (v,"non_intra_quantiser_matrix: ", 	b, bc,  8,64);
	   bc += 8*64;
   }

   lciqm = outBit_Sx_NL (v,"load_chroma_intra_quantiser_matrix: ",	b, bc,   1);
   bc++;
   if (lciqm) {
	   // 8x[64]
	   print_BitMatrix (v,"chroma_intra_quantiser_matrix: ", 	b, bc,  8,64);
	   bc += 8*64;
   }

   lcniqm = outBit_Sx_NL (v,"load_chroma_non_intra_quantiser_matrix: ",	b, bc,   1);
   bc++;
   if (lcniqm) {
	   // 8x[64]
	   print_BitMatrix (v,"chroma_non_intra_quantiser_matrix: ", 	b, bc,  8,64);
	   bc += 8*64;
   }

}




/*
   -- MPEG-2 Picture Display Extension
   -- ISO 13818-2
*/

void MPEG2_decodePictureDisplayExtension (int v, u_char *b, int len)
{

   int    bc;
   int    bit_len;



   bc = 32 + 4;


//
// $$$ TODO
//
// -- ISO 13818-2,  6.3.12	Picture display extension
//
// if ( progressive_sequence == 1) {
// 	if ( repeat_first_field == '1' ) {
// 		if ( top_field_first == '1' )
// 			number_of_frame_centre_offsets = 3
// 		else
// 			number_of_frame_centre_offsets = 2
// 	} else {
// 		number_of_frame_centre_offsets = 1
// 	}
// } else {
// 	if (picture_structure == "field") {
// 		number_of_frame_centre_offsets = 1
// 	} else {
//		if (repeat_first_field == '1' )
//			number_of_frame_centre_offsets = 3
//		else
//			number_of_frame_centre_offsets = 2
//	}
// }


   // -- as long we do not have implemented "number_of_frame_centre_offsets",
   // -- we are using length information...
   //
   // $$$ TODO	for ( i=0; i<number_of_frame_centre_offsets; i++ ) {		
  
   out_NL (v);
   bit_len = (len * 8) - bc;
   while ( bit_len >= 34 ) {
	outBit_Sx_NL  (v,"frame_centre_horizontal_offset: ",	b, bc+ 0, 16);
	outBit_Sx_NL  (v,"marker_bit: ",			b, bc+16,  1);
	outBit_Sx_NL  (v,"frame_centre_vertical_offset: ",	b, bc+17, 16);
	outBit_Sx_NL  (v,"marker_bit: ",			b, bc+33,  1);
	out_NL (v);
	bc += 34;
	bit_len -= 34;
   }

}



/*
   -- MPEG-2 Picture temporal scalable extension
   -- ISO 13818-2
*/

void MPEG2_decodePictureTemporalScalableExtension (int v, u_char *b, int len)
{

   b += 4;

   outBit_Sx_NL  (v,"reference_select_code: ",			b,   4,  2);
   outBit_Sx_NL  (v,"forward_temporal_reference: ",		b,   6, 10);
   outBit_Sx_NL  (v,"marker_bit: ",				b,  16,  1);
   outBit_Sx_NL  (v,"backward_temporal_reference: ",		b,  17, 10);

}




/*
   -- MPEG-2 Picture spatial scalable extension
   -- ISO 13818-2
*/

void MPEG2_decodePictureSpatialScalableExtension (int v, u_char *b, int len)
{


   b += 4;

   outBit_Sx_NL  (v,"lower_layer_temporal_reference: ",		b,   4, 10);
   outBit_Sx_NL  (v,"marker_bit: ",				b,  14,  1);
   outBit_Sx_NL  (v,"lower_layer_horizontal_offset: ",		b,  15, 15);
   outBit_Sx_NL  (v,"marker_bit: ",				b,  30,  1);
   outBit_Sx_NL  (v,"lower_layer_vertical_offset: ",		b,  31, 15);

   outBit_Sx_NL  (v,"spatial_temporal_weight_code_table_index: ", b,46,  2);
   outBit_Sx_NL  (v,"lower_layer_progressive_frame: ",		b,  48,  1);
   outBit_Sx_NL  (v,"lower_layer_deinterlaced_field_select: ",	b,  49,  1);

}




/*
   -- MPEG-2 Copyright Extension
   -- ISO 13818-2
*/

void MPEG2_decodeCopyrightExtension (int v, u_char *b, int len)
{

   b += 4;

   outBit_Sx_NL  (v,"copyright_flag: ",		b,   4,  1);
   outBit_Sx_NL  (v,"copyright_identifier: ",	b,   5,  8);
   outBit_S2x_NL (v,"original_or_copy: ",	b,  13,  1,
    		(char *(*)(u_long)) dvbstrMPEG_Original_Or_Copy);
   outBit_Sx_NL  (v,"reserved: ",		b,  14,  7);
   outBit_Sx_NL  (v,"marker_bit: ",		b,  21,  1);
   outBit_Sx_NL  (v,"copyright_number_1: ",	b,  22, 20);
   outBit_Sx_NL  (v,"marker_bit: ",		b,  42,  1);
   outBit_Sx_NL  (v,"copyright_number_2: ",	b,  43, 22);
   outBit_Sx_NL  (v,"marker_bit: ",		b,  65,  1);
   outBit_Sx_NL  (v,"copyright_number_3: ",	b,  66, 22);
 
}




// ------------------------------------------------------------------



/*
   -- MPEG-2 Picture Data SLICE
   -- ISO 13818-2
   -- Sync and streamID already displayed
*/

void MPEG2_decodeSlice (int v, u_char *b, int len)
{

   // outBit_Sx_NL (3,"packet_start_code: ",	b, 0, 24);
   // outBit_S2x_NL(3,"Stream_id: ",		b, 24, 8,
   // 		   (char *(*)(u_long))dvbstrPESstream_ID );


   // $$$ TODO
 
   print_databytes (v+2,"MPEG-2 Slice (incl. sync + id):", b, len);

}



