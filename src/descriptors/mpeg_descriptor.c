/*
$Id: mpeg_descriptor.c,v 1.29 2006/02/12 23:17:11 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 -- MPEG Descriptors  ISO/IEC 13818-1/6
 -- all descriptors are returning their length used in buffer




$Log: mpeg_descriptor.c,v $
Revision 1.29  2006/02/12 23:17:11  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.28  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.27  2005/11/10 23:34:37  rasc
Some H.222.1 AMD 4+5 update

Revision 1.26  2004/11/03 21:00:52  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.25  2004/08/13 11:05:29  rasc
Metadata_STD_descriptor

Revision 1.24  2004/08/12 22:57:18  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.23  2004/08/01 21:33:08  rasc
minor TVA stuff (TS 102 323)

Revision 1.22  2004/07/26 20:58:03  rasc
RNT completed..  (TS 102 323)

Revision 1.21  2004/07/25 20:12:58  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.20  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.19  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.18  2004/02/24 23:03:05  rasc
private data of DSMCC::DSI
BIOP::ServiceGatewayInformation()
IOP::IOR()

Revision 1.17  2004/02/20 22:18:39  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.16  2004/01/17 23:06:08  rasc
minor stuff, some restructs in output

Revision 1.15  2004/01/15 21:27:22  rasc
DSM-CC stream descriptors

Revision 1.14  2004/01/12 23:05:25  rasc
no message

Revision 1.13  2004/01/02 16:40:34  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.12  2004/01/01 20:35:26  rasc
PES program stream map, minor descriptor cleanup

Revision 1.11  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.10  2004/01/01 20:09:20  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.9  2003/11/26 16:27:45  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.8  2003/10/27 22:43:49  rasc
carousel info descriptor and more

Revision 1.7  2003/10/26 19:06:27  rasc
no message

Revision 1.6  2003/10/25 19:11:49  rasc
no message

Revision 1.5  2003/10/24 22:45:04  rasc
code reorg...

Revision 1.4  2003/10/24 22:17:17  rasc
code reorg...

Revision 1.3  2003/10/17 18:16:54  rasc
- started more work on newer ISO 13818  descriptors
- some reorg work started

Revision 1.2  2003/09/09 05:12:45  obi
print format identifier of registration descriptor in ascii.
looks quite strange but is nice to see :)

Revision 1.1  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "mpeg_descriptor.h"
#include "descriptor_misc.h"
#include "private/userdefs.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"
#include "misc/pid_mem.h"







/*
  determine MPEG descriptor type and print it...
  return byte length
  2004-08-11  updated H.222.0 AMD1
*/

int  descriptorMPEG  (u_char *b)

{
 int len;
 int tag;



  out_NL (4);
  tag = outBit_S2x_NL (4,"MPEG-DescriptorTag: ",	b,   0,  8,
		(char *(*)(u_long))dvbstrMPEGDescriptorTAG); 
  len = outBit_Sx_NL  (4,"descriptor_length: ",	 	b,   8,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x02:  descriptorMPEG_VideoStream  (b);  break;
     case 0x03:  descriptorMPEG_AudioStream  (b);  break;
     case 0x04:  descriptorMPEG_Hierarchy  (b);  break;
     case 0x05:  descriptorMPEG_Registration  (b);  break;
     case 0x06:  descriptorMPEG_DataStreamAlignment (b);  break;
     case 0x07:  descriptorMPEG_TargetBackgroundGrid (b);  break;
     case 0x08:  descriptorMPEG_VideoWindow (b);  break;
     case 0x09:  descriptorMPEG_CA  (b);  break;
     case 0x0A:  descriptorMPEG_ISO639_Lang  (b);  break;
     case 0x0B:  descriptorMPEG_SystemClock (b);  break;
     case 0x0C:  descriptorMPEG_MultiplexBufUtil (b);  break;
     case 0x0D:  descriptorMPEG_Copyright  (b);  break;
     case 0x0E:  descriptorMPEG_MaxBitrate  (b);  break;
     case 0x0F:  descriptorMPEG_PrivateDataIndicator  (b);  break;
     case 0x10:  descriptorMPEG_SmoothingBuf  (b);  break; 
     case 0x11:  descriptorMPEG_STD  (b);  break; 
     case 0x12:  descriptorMPEG_IBP  (b);  break; 

     /* 0x13 - 0x1A  DSM-CC ISO13818-6,  TR 102 006 */
     case 0x13:  descriptorMPEG_Carousel_Identifier (b);  break; 
     case 0x14:  descriptorMPEG_Association_tag (b);  break; 
     case 0x15:  descriptorMPEG_Deferred_Association_tags (b);  break; 

     /* DSM-CC stream descriptors */
     // case 0x16: reserved....
     case 0x17:  descriptorMPEG_NPT_reference (b);  break; 
     case 0x18:  descriptorMPEG_NPT_endpoint (b);  break; 
     case 0x19:  descriptorMPEG_stream_mode (b);  break; 
     case 0x1A:  descriptorMPEG_stream_event (b);  break; 

     /* MPEG 4 */
     case 0x1B:  descriptorMPEG_MPEG4_video (b);  break; 
     case 0x1C:  descriptorMPEG_MPEG4_audio (b);  break; 
     case 0x1D:  descriptorMPEG_IOD (b);  break; 
     case 0x1E:  descriptorMPEG_SL (b);  break; 
     case 0x1F:  descriptorMPEG_FMC (b);  break; 
     case 0x20:  descriptorMPEG_External_ES_ID (b);  break; 
     case 0x21:  descriptorMPEG_MuxCode (b);  break; 
     case 0x22:  descriptorMPEG_FMXBufferSize (b);  break; 
     case 0x23:  descriptorMPEG_MultiplexBuffer (b);  break; 
     case 0x24:  descriptorMPEG_ContentLabeling(b);  break;

     /* TV ANYTIME, TS 102 323 */
     case 0x25:  descriptorMPEG_TVA_metadata_pointer (b);  break; 
     case 0x26:  descriptorMPEG_TVA_metadata (b);  break; 
     case 0x27:  descriptorMPEG_TVA_metadata_STD (b);  break; 

     /* H.222.0 AMD 3 */
     case 0x28:  descriptorMPEG_AVC_video (b);  break; 
     case 0x29:  descriptorMPEG_IPMP (b);  break; 
     case 0x2A:  descriptorMPEG_AVC_timing_and_HRD (b);  break; 

     /* H.222.0 Corr 4 */
     case 0x2B:  descriptorMPEG_MPEG2_AAC_audio (b);  break;
     case 0x2C:  descriptorMPEG_FlexMuxTiming (b);  break;

     default: 
	if (tag < 0x80) {
	   out_nl (0,"  ----> ERROR: unimplemented descriptor (mpeg context), Report!");
	}
	descriptor_PRIVATE (b,MPEG);
	break;
  } 


  return len+2;   // (descriptor total length)
}











/* --------------------------------------------------------------- 
  well known MPEG descriptors
   --------------------------------------------------------------- */


/*
  0x02  VideoStream  descriptor 
  ISO 13818-1   2.6.xx
*/

void descriptorMPEG_VideoStream (u_char *b)

{

 typedef struct  _descVidStream {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      multiple_frame_rate_flag;
    u_int      frame_rate_code;
    u_int      MPEG_1_only_flag;
    u_int      constrained_parameter_flag;
    u_int      still_picture_flag;

    // if MPEG_1_only_flag == 1

    u_int	profile_and_level_indication;
    u_int	chroma_format;
    u_int	frame_rate_extension_flag;
    u_int	reserved_1;

 } descVidStream;


 descVidStream  d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.multiple_frame_rate_flag	 = getBits (b, 0, 16, 1);
 d.frame_rate_code		 = getBits (b, 0, 17, 4);
 d.MPEG_1_only_flag		 = getBits (b, 0, 21, 1);
 d.constrained_parameter_flag	 = getBits (b, 0, 22, 1);
 d.still_picture_flag		 = getBits (b, 0, 23, 1);

 
 out_SB_NL (4,"multiple_frame_rate_flag: ",d.multiple_frame_rate_flag);
 out_SW_NL (4,"frame_rate_code: ",d.frame_rate_code);
 out_SB_NL (4,"MPEG_1_only_flag: ",d.MPEG_1_only_flag);
 out_SB_NL (4,"constrained_parameter_flag: ",d.constrained_parameter_flag);
 out_SB_NL (4,"still_picture_flag: ",d.still_picture_flag);


 if (d.MPEG_1_only_flag == 1) {
    d.profile_and_level_indication	= getBits (b, 0, 24, 8);
    d.chroma_format			= getBits (b, 0, 32, 2);
    d.frame_rate_extension_flag		= getBits (b, 0, 34, 1);
    d.reserved_1			= getBits (b, 0, 35, 5);

    out_SB_NL (4,"profile_and_level_indication: ",d.profile_and_level_indication);
    out_SB_NL (4,"chroma_format: ",d.chroma_format);
    out_SB_NL (4,"frame_rate_extension_flag: ",d.frame_rate_extension_flag);
    out_SB_NL (6,"reserved_1: ",d.reserved_1);
 } 

}




/*
  0x03  AudioStream  descriptor 
  ISO 13818-1   2.6.4
*/

void descriptorMPEG_AudioStream (u_char *b)

{

 typedef struct  _descAudioStream {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      free_format_flag;
    u_int      ID;
    u_int      layer;
    u_int      variable_rate_audio_indicator;
    u_int      reserved_1;

 } descAudioStream;


 descAudioStream  d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.free_format_flag		 = getBits (b, 0, 16, 1);
 d.ID				 = getBits (b, 0, 17, 1);
 d.layer			 = getBits (b, 0, 18, 2);
 d.variable_rate_audio_indicator = getBits (b, 0, 20, 1);
 d.reserved_1			 = getBits (b, 0, 21, 3);

 
 out_SB_NL (4,"free_format_flag: ",d.free_format_flag);
 out_SB_NL (4,"ID: ",d.ID);
 out_SB_NL (4,"layer: ",d.layer);
 out_SB_NL (4,"variable_rate_audio_indicator: ",d.variable_rate_audio_indicator);
 out_SB_NL (6,"reserved_1: ",d.reserved_1);

}




/*
  0x04 Hierarchy  descriptor
  ISO 13818-1 2.6.6
*/

void descriptorMPEG_Hierarchy (u_char *b)

{
 typedef struct  _descHierarchy {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_int      hierarchy_type;
    u_int      reserved_2;
    u_int      hierarchy_layer_index;
    u_int      reserved_3;
    u_int      hierarchy_embedded_layer_index;
    u_int      reserved_4;
    u_int      hierarchy_channel;

 } descHierarchy;


 descHierarchy  d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 4);
 d.hierarchy_type 		 = getBits (b, 0, 20, 4);
 d.reserved_2			 = getBits (b, 0, 24, 2);
 d.hierarchy_layer_index	 = getBits (b, 0, 26, 6);
 d.reserved_3			 = getBits (b, 0, 32, 2);
 d.hierarchy_embedded_layer_index = getBits (b, 0, 34, 6);
 d.reserved_4			 = getBits (b, 0, 40, 2);
 d.hierarchy_channel		 = getBits (b, 0, 42, 6);


 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_S2B_NL (4,"hierarchy_type: ",d.hierarchy_type,
	dvbstrHierarchy_TYPE(d.hierarchy_type));
 out_SB_NL (6,"reserved_2: ",d.reserved_2);
 out_SB_NL (4,"hierarchy_layer_index: ",d.hierarchy_layer_index);
 out_SB_NL (6,"reserved_3: ",d.reserved_3);
 out_SB_NL (4,"hierarchy_embedded_layer_index: ",d.hierarchy_embedded_layer_index);
 out_SB_NL (6,"reserved_4: ",d.reserved_4);
 out_SB_NL (4,"hierarchy_channel: ",d.hierarchy_channel);

}




/*
  0x05 Registration  descriptor
  ISO 13818-1 2.6.8
*/

void descriptorMPEG_Registration (u_char *b)

{
 typedef struct  _descRegistration {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_long      format_identifier;
    // N   add. info

 } descRegistration;


 descRegistration  d;


 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.format_identifier		 = getBits (b, 0, 16, 32);


 out_S2L_NL (4,"format_identifier: ",d.format_identifier,"see: SC29");
 indent(+1);
 printasciiline_buf (4, b+2, 4);
 indent(-1);

 print_databytes (4,"add. info:", b+6, d.descriptor_length -4);

}





/*
  0x06  DataStreamAlignment descriptor 
  ISO 13818-1   2.6.11
*/

void descriptorMPEG_DataStreamAlignment (u_char *b)

{

 typedef struct  _descDataStreamAlignment {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      alignment_type;

 } descDataStreamAlignment;


 descDataStreamAlignment d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.alignment_type		 = b[2];


 
 out_SB_NL (4,"alignment_type: ",d.alignment_type);
 out (4,"   as VideoStream:  (= %s)",
	dvbstrDataStreamVIDEOAlignment_TYPE(d.alignment_type));
 out (4,"   as AudioStream:  (= %s)",
	dvbstrDataStreamAUDIOAlignment_TYPE(d.alignment_type));
 out_NL (4);

}







/*
  0x07 Target Background Grid  descriptor
  ISO 13818-1 2.6.12
*/

void descriptorMPEG_TargetBackgroundGrid (u_char *b)

{
 typedef struct  _descTBGG {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      horizontal_size;
    u_int      vertical_size;
    u_int      aspect_ratio_information;


 } descTBGG;


 descTBGG  d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.horizontal_size		 = getBits (b, 0, 16, 14);
 d.vertical_size		 = getBits (b, 0, 30, 14);
 d.aspect_ratio_information	 = getBits (b, 0, 44, 4);

 out_S2W_NL (4,"horizontal_size: ",d.horizontal_size,"pixel");
 out_S2W_NL (4,"vertical_size: ",d.vertical_size,"pixel");
 out_S2B_NL  (4,"aspect_ratio_information: ",
	d.aspect_ratio_information,
	dvbstrAspectRatioInfo_FLAG(d.aspect_ratio_information));

}




/*
  0x08 Video Window  descriptor
  ISO 13818-1 2.6.14
*/

void descriptorMPEG_VideoWindow (u_char *b)

{
 typedef struct  _descVidWin {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      horizontal_offset;
    u_int      vertical_offset;
    u_int      window_priority;


 } descVidWin;


 descVidWin  d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.horizontal_offset		 = getBits (b, 0, 16, 14);
 d.vertical_offset		 = getBits (b, 0, 30, 14);
 d.window_priority		 = getBits (b, 0, 44, 4);

 out_S2W_NL (4,"horizontal_offset: ",d.horizontal_offset,"pixel");
 out_S2W_NL (4,"vertical_offset: ",d.vertical_offset,"pixel");
 out_S2B_NL (4,"window_priority: ",d.window_priority,"(15 = highest)");

}





/*
  0x09 CA descriptor  (condition access)
*/

void descriptorMPEG_CA (u_char *b)

{
 /* IS13818-1  2.6.1 */

 typedef struct  _descCA {
    u_int      descriptor_tag;
    u_int      descriptor_length;		
    u_int      CA_system_ID;
    u_int      reserved;
    u_int      CA_PID;

    // private data bytes

 } descCA;


 descCA  d;
 int     len;


 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];
 d.CA_system_ID			 = getBits (b, 0, 16, 16);
 d.reserved			 = getBits (b, 0, 32, 3);
 d.CA_PID			 = getBits (b, 0, 35, 13);

 store_PidToMem (d.CA_PID);



 out_S2W_NL (4,"CA_system_ID: ",d.CA_system_ID,
     dvbstrCASystem_ID(d.CA_system_ID));
 out_SB_NL  (6,"reserved: ",d.reserved);
 out_SW_NL  (4,"CA_PID: ",d.CA_PID);

 len = d.descriptor_length-4;
 if (len > 0) {
    print_private_data (4, b+6,len);
 }

}






/*
  -- 0x0A ISO 639 Language descriptor
*/

void descriptorMPEG_ISO639_Lang (u_char *b)

{
 /* ISO 13818-1   2.6.19 */

 typedef struct  _descISO639 {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    // N ISO639 desc

 } descISO639;

 typedef struct  _descISO639List {
    u_char      ISO_639_language_code[4];
    u_int      audio_type;
 } descISO639List;


 descISO639      d;
 descISO639List  d2;
 int             len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 len = d.descriptor_length;
 b  += 2;
 indent (+1);
 while ( len > 0) {
    getISO639_3 (d2.ISO_639_language_code, b);	
    d2.audio_type		= getBits (b,0,24,8);

    b += 4;
    len -= 4;

    out_nl (4,"ISO639_language_code:  %3.3s", d2.ISO_639_language_code);
    out_S2B_NL (4,"Audio_type: ", d2.audio_type,
	dvbstrAudio_TYPE (d2.audio_type));
    out_NL(4);
 }
 indent (-1);

}






/*
  0x0B  System Clock  descriptor 
  ISO 13818-1   2.6.xx
*/

void descriptorMPEG_SystemClock (u_char *b)

{

 typedef struct  _descSysClock {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      external_clock_reference_indicator;
    u_int      reserved_1;
    u_int      clock_accuracy_integer;
    u_int      clock_accuracy_exponent;
    u_int      reserved_2;

 } descSysClock;


 descSysClock d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.external_clock_reference_indicator = getBits (b, 0, 16, 1);
 d.reserved_1			 = getBits (b, 0, 17, 1);
 d.clock_accuracy_integer	 = getBits (b, 0, 18, 6);
 d.clock_accuracy_exponent	 = getBits (b, 0, 24, 3);
 d.reserved_2			 = getBits (b, 0, 27, 5);

 
 out_SB_NL (4,"external_clock_reference_indicatior: ",
	d.external_clock_reference_indicator);
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_SB_NL (4,"clock_accuracy_integer: ",d.clock_accuracy_integer);
 out_SB_NL (4,"clock_accuracy_exponent: ",d.clock_accuracy_exponent);
 out_nl    (4,"    == : %u * 10^(-%u) ",
		d.clock_accuracy_integer,d.clock_accuracy_exponent);
 out_SB_NL (6,"reserved_2: ",d.reserved_2);

}






/*
  0x0C  Multiplex Buffer Utilization  descriptor 
  ISO 13818-1   2.6.xx
*/

void descriptorMPEG_MultiplexBufUtil  (u_char *b)

{

 typedef struct  _descMBU {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      bound_valid_flag;
    u_int      LTW_offset_lower_bound;
    u_int      reserved_1;
    u_int      LTW_offset_upper_bound;

 } descMBU;


 descMBU  d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.bound_valid_flag		 = getBits (b, 0, 16, 1);
 d.LTW_offset_lower_bound	 = getBits (b, 0, 17, 15);
 d.reserved_1			 = getBits (b, 0, 32, 1);
 d.LTW_offset_upper_bound	 = getBits (b, 0, 33, 15);

 
 out_SB_NL (4,"bound_valid_flag: ",d.bound_valid_flag);
 out_S2W_NL (4,"LTW_offset_lower_bound: ",d.LTW_offset_lower_bound,
	"(27 MHz/300 clock periods)");
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_S2W_NL (4,"LTW_offset_upper_bound: ",d.LTW_offset_upper_bound,
	"(27 MHz/300 clock periods)");

}








/*
  0x0D  Copyright  descriptor 
  ISO 13818-1   2.6.xx
*/

void descriptorMPEG_Copyright  (u_char *b)

{

 typedef struct  _descCopyright {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_long     copyright_identifier;

    // add. info

 } descCopyright;


 descCopyright d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.copyright_identifier		 = getBits (b, 0, 16, 32);

 
 out_S2L_NL (4,"copyright_identifier: ",d.copyright_identifier,"see: SC29");
 print_databytes (4,"add. info:", b+6, d.descriptor_length -4);

}











/*
  0x0E  Maximum Bitrate  descriptor 
  ISO 13818-1   2.6.xx
*/

void descriptorMPEG_MaxBitrate (u_char *b)

{

 typedef struct  _descMaxBitrate {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_long     maximum_bitrate;

 } descMaxBitrate;


 descMaxBitrate d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 2);
 d.maximum_bitrate		 = getBits (b, 0, 18, 22);

 
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_nl    (4,"maximum_bitrate: %lu (0x%08lx)  (= %lu Bytes/sec)",
	d.maximum_bitrate, d.maximum_bitrate,
	d.maximum_bitrate * 50);

}




/*
  0x0F  Private Data Indicator descriptor 
  ISO 13818-1   2.6.x
*/

void descriptorMPEG_PrivateDataIndicator  (u_char *b)

{
   descriptor_any (b);
}





/*
  0x10  Smoothing Buffer  descriptor 
  ISO 13818-1   2.6.30
*/

void descriptorMPEG_SmoothingBuf  (u_char *b)

{

 typedef struct  _descSmoothingBuf {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_long     sb_leak_rate;
    u_int      reserved_2;
    u_long     sb_size;



 } descSmoothingBuf;


 descSmoothingBuf d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 2);
 d.sb_leak_rate			 = getBits (b, 0, 18, 22);
 d.reserved_2			 = getBits (b, 0, 40, 2);
 d.sb_size			 = getBits (b, 0, 42, 22);

 
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_nl    (4,"sb_leak_rate: %lu  (= %lu bits/sec)",
	d.sb_leak_rate,d.sb_leak_rate/400);
 out_SB_NL (6,"reserved_2: ",d.reserved_2);
 out_nl    (4,"sb_size: %lu  bytes", d.sb_size);

}









/*
  0x11  STD    descriptor 
  ISO 13818-1   2.6.32
*/

void descriptorMPEG_STD (u_char *b)

{

 typedef struct  _descSTD {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_int      leak_valid_flag;

 } descSTD;


 descSTD d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 7);
 d.leak_valid_flag		 = getBits (b, 0, 23, 1);

 
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_SB_NL (4,"leak_valid_flag: ",d.leak_valid_flag);

}










/*
  0x12  IBP  descriptor 
  ISO 13818-1   2.6.34
*/

void descriptorMPEG_IBP  (u_char *b)

{

 typedef struct  _descIBP {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      closed_gop_flag;
    u_int      identical_gop_flag;
    u_int      max_gop_length;

 } descIBP;


 descIBP d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.closed_gop_flag		 = getBits (b, 0, 16, 1);
 d.identical_gop_flag		 = getBits (b, 0, 17, 1);
 d.max_gop_length		 = getBits (b, 0, 18, 14);

 
 out_SB_NL (4,"Closed_gop_flag: ",d.closed_gop_flag);
 out_SB_NL (4,"Identical_gop_flag: ",d.identical_gop_flag);
 out_SW_NL (4,"Max_gop_length: ",d.max_gop_length);

}




/*
 * ------------------------------------------------------------
 *
 * -- DSM-CC  Descriptors  ISO 13818-6  TR 102 006
 *
 */


/*
  0x13  Carousel Identifier  descriptor 
  ISO 13818-6  / TR 102 006
*/

void descriptorMPEG_Carousel_Identifier (u_char *b)

{

 typedef struct  _descCarouselIdentifier {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_long     carousel_id;
    u_int      format_id;

    // -- optional
    // FormatSpecifier
    u_int      module_version;
    u_int      module_id;
    u_int      block_size;
    u_int      module_size;
    u_long     CompressionMethod;
    u_int      original_size;
    u_long     timeout;
    u_int      object_key_length;
       // N...
    u_int      object_key_data;

    // private data
 } descCarouselIdentifier;


 descCarouselIdentifier d;
 int			len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.carousel_id			 = getBits (b, 0, 16, 32);
 d.format_id			 = getBits (b, 0, 48,  8);
 b  += 7;
 len = d.descriptor_length - 5;


 out_SL_NL (4,"Carousel_id: ",d.carousel_id);
 out_SB_NL (4,"format_id: ",d.format_id);		/* $$$$ ??? */


 indent (+1);
 if (d.format_id == 0x01) {
	// -- TR 101 202   4.7.xx
	// -- FormatSpecifier
	
	d.module_version		 = getBits (b, 0,  0,  8);
	d.module_id			 = getBits (b, 0,  8, 16);
	d.block_size			 = getBits (b, 0, 24, 16);
	d.module_size			 = getBits (b, 0, 40, 32);
	d.CompressionMethod		 = getBits (b, 0, 72,  8);
	d.original_size			 = getBits (b, 0, 80, 32);
	d.timeout 			 = getBits (b, 0,112,  8);
	d.object_key_length		 = getBits (b, 0,120,  8);
	b   += 16;
	len -= 16;

 	out_SB_NL (4,"Module_version: ",d.module_version);		/* $$$$ Tables? */
 	out_SW_NL (4,"Module_id: ",d.module_version);
 	out_SW_NL (4,"Block_size: ",d.block_size);
 	out_SL_NL (4,"Module_size: ",d.module_size);
 	out_SB_NL (4,"Compression_method: ",d.CompressionMethod);
 	out_SL_NL (4,"Original_size: ",d.original_size);
 	out_SB_NL (4,"Timeout: ",d.timeout);
 	out_SB_NL (4,"Object_key_length: ",d.object_key_length);

 	print_databytes (4,"Object_key_data:", b, d.object_key_length);
		b   += d.object_key_length;
		len -= d.object_key_length;
 }
 indent (-1);

 print_private_data (4, b, len);

}





/*
  0x14  association tag  descriptor 
  ISO 13818-6  / TR 102 006
*/

void descriptorMPEG_Association_tag (u_char *b)

{

 typedef struct  _descAssociationTag {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      association_tag;
    u_int      use;

    u_int      selector_length;
    // -- optional
    //         selector_length;
    u_long     transaction_id;
    u_long     timeout;

    // -- optional
    //         selector_length;

    // -- optional
    //         selector_length;
    //         selector_bytes;

 } descAssociationTag;


 descAssociationTag  d;
 int                 len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.association_tag		 = getBits (b, 0, 16, 16);
 d.use                           = getBits (b, 0, 32, 16);
 d.selector_length		 = getBits (b, 0, 40,  8); /* normally in the opt branches... */
 b  += 7;
 len = d.descriptor_length - 5;


 out_SW_NL (4,"Association_tag: ",d.association_tag);		/* $$$$ Tables? */
 out_SW_NL (4,"Use: ",d.use);
 out_SB_NL (4,"Selector_length: ",d.selector_length);

 if (d.use == 0x0000) {

 	d.transaction_id 	 = getBits (b, 0,  0, 32);
 	d.timeout		 = getBits (b, 0, 32, 32);
	b   += 8;
	len -= 8;
 	out_SL_NL (4,"Transaction_ID: ",d.transaction_id);
 	out_SL_NL (4,"Timeout: ",d.timeout);

 } else if (d.use == 0x0001) {

	 /* selector length == 0x00; */

 } else {
	print_databytes (4,"Selector bytes:", b, d.selector_length);
 }

 print_private_data (4, b, len);

}







/*
  0x15  deferred association tag  descriptor 
  ISO 13818-6  / TR 102 006
*/

void descriptorMPEG_Deferred_Association_tags (u_char *b)

{

 typedef struct  _descDefAssocTags {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      association_tags_loop_length;
    // association tag loop
    u_int	association_tag;

    u_int      transport_stream_id;
    u_int      program_number;
    u_int      org_network_id;

    // private bytes

 } descDefAssocTags;


 descDefAssocTags  d;
 int               len,i;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.association_tags_loop_length	 = getBits (b, 0, 16,  8);
 b  += 3;
 len = d.descriptor_length - 1;


 out_SW_NL (4,"Association_tags_loop_length: ",d.association_tags_loop_length);

 /* -- association tags */
 out_nl (4,"Association tag loop:");
 	indent (+1);
	for (i=0; i < d.association_tags_loop_length; ) {
 		d.association_tag	 = getBits (b, 0, i,  16);
 		out_SW_NL (4,"Association_tag: ",d.association_tag);
		i += 2;
	}
	indent (-1);
	b   += d.association_tags_loop_length;
	len -= d.association_tags_loop_length;


 d.transport_stream_id			= getBits (b, 0,  0,  16);
 d.program_number			= getBits (b, 0, 16,  16);
 d.org_network_id			= getBits (b, 0, 32,  16);
 b   += 6;
 len -= 6;

 out_SW_NL  (4,"Transport_stream_ID: ",d.transport_stream_id);
 out_SW_NL  (4,"Program_number: ",d.program_number);
 out_S2W_NL (4,"Original_network_ID: ",d.org_network_id,
	dvbstrOriginalNetwork_ID(d.org_network_id));


 print_private_data (4, b, len);

}




/*
 * ------------------------------------------------------------
 *
 * -- DSM-CC  STREAM Descriptors  ISO 13818-6
 *
 */




/*
  0x17   DSMCC  NPT-reference descriptor 
  ISO 13818-6 
*/

void descriptorMPEG_NPT_reference (u_char *b)
{
   // descriptor_tag		 = b[0];
   // descriptor_length       	 = b[1];

   outBit_S2x_NL(4,"postDiscontinuityIndicator: ",  	b,16, 1,
	   	(char *(*)(u_long)) dsmccStr_postDiscontinuityIndicator);
   outBit_Sx_NL (4,"contentId: ",		  	b,17, 7);
   outBit_Sx_NL (6,"reserved: ",		  	b,24, 7);

   outBit64_Sx  (4,"STC_Reference: ",		  	b,31,33);
   	out_nl  (4,"  [= ref/300 * 90 kHz]");
 
   outBit_Sx_NL (6,"reserved: ",		  	b,64,31);
   outBit64_Sx_NL (4,"NPT_Reference: ",		  	b,75,33);
   outBit_Sx_NL (4,"scaleNumerator: ",		  	b,108,16);
   outBit_Sx_NL (4,"scaleDenominator: ",	  	b,124,16);

}



/*
  0x18   DSMCC  NPT-endpoint descriptor 
  ISO 13818-6 
*/

void descriptorMPEG_NPT_endpoint (u_char *b)
{
   unsigned long long t;

   // descriptor_tag		 = b[0];
   // descriptor_length       	 = b[1];

   outBit_Sx_NL (6,"reserved: ",		  	b,16,15);

   t = outBit64_Sx (4,"startNPT: ",		  	b,31,33);
       out_nl_calc_NPT (4,t); 

   outBit_Sx_NL (6,"reserved: ",		  	b,64,15);

   t = outBit64_Sx (4,"stopNPT: ",			b,79,33);
       out_nl_calc_NPT (4,t); 

}





/*
  0x19   DSMCC  stream_mode descriptor 
  ISO 13818-6 
*/

void descriptorMPEG_stream_mode (u_char *b)
{
   // descriptor_tag		 = b[0];
   // descriptor_length       	 = b[1];

   outBit_S2x_NL(4,"streamMode: ",		  	b,16, 8,
		   	(char *(*)(u_long)) dsmccStr_streamMode);
   outBit_Sx_NL (6,"reserved: ",		  	b,24, 8);
 
}





/*
  0x1A   DSMCC  stream_event descriptor 
  ISO 13818-6 
*/

void descriptorMPEG_stream_event (u_char *b)
{
   unsigned long long t;
   int len;

   // descriptor_tag	 = b[0];
   len		       	 = b[1];

   outBit_Sx_NL (4,"eventId: ",		  		b,16,16);
   outBit_Sx_NL (6,"reserved: ",		  	b,32,31);
   t = outBit64_Sx (4,"eventNPT: ",		  	b,63,33);
       out_nl_calc_NPT (4,t); 
   
   b += 12;
   len -= 10;

   print_private_data (4, b, len);

}








/*
 * ------------------------------------------------------------
 *
 * -- MPEG4 Descriptors  ISO 13818-1
 *
 */



/*
  0x1B  MPEG4 video  descriptor 
  ISO 13818-1  
*/

void descriptorMPEG_MPEG4_video (u_char *b)

{
 // d.descriptor_tag		 = b[0];
 // d.descriptor_length       	 = b[1];
 outBit_Sx_NL (4,"MPEG4 visual profile and level: ",  	b,16,8); /* $$$  Table */
}


 
/*
  0x1C  MPEG4 audio  descriptor 
  ISO 13818-1  
*/

void descriptorMPEG_MPEG4_audio (u_char *b)

{
 // d.descriptor_tag		 = b[0];
 // d.descriptor_length       	 = b[1];

 outBit_Sx_NL (4,"MPEG4 audio profile and level: ",  	b,16,8); /* $$$  Table */
}




/*
  0x1D  IOD - InitialObjectDescriptor
  ISO 13818-1  
*/

void descriptorMPEG_IOD (u_char *b)

{
 // d.descriptor_tag		 = b[0];
 // d.descriptor_length       	 = b[1];

 outBit_Sx_NL (4,"Scope_of_IOD: ",  	b,16,8);
 outBit_Sx_NL (4,"IOD_label: ",  	b,24,8);
 outBit_Sx_NL (4,"InitialObjectDescriptor: ", b,32,8);	// $$$ TODO defined in subclause 8.6.3.1 of ISO/IEC 14496-1
}



/*
  0x1E  SL descriptor
  ISO 13818-1  
*/

void descriptorMPEG_SL (u_char *b)

{ 
 // d.descriptor_tag		 = b[0];
 // d.descriptor_length       	 = b[1];

 outBit_Sx_NL (4,"ES_ID: ",  	b,16,16);
}




/*
  0x1F  FMC descriptor
  ISO 13818-1  
*/

void descriptorMPEG_FMC (u_char *b)

{
  int descriptor_length;

  // d.descriptor_tag		 = b[0];
  descriptor_length       	 = b[1];

  b += 2;
  while (descriptor_length > 0 ) {
 	outBit_Sx_NL (4,"ES_ID: ",  		b, 0,16);
 	outBit_Sx_NL (4,"FlexMuxChannel: ",  	b,16, 8);
	b += 3;
	descriptor_length -= 3;
  }

}



/*
  0x20  External SL descriptor
  ISO 13818-1  
*/

void descriptorMPEG_External_ES_ID (u_char *b)

{ 
 // d.descriptor_tag		 = b[0];
 // d.descriptor_length       	 = b[1];

 outBit_Sx_NL (4,"ES_ID: ",  	b,16,16);
}





/*
  0x21  MuxCode descriptor
  ISO 13818-1  
*/

void descriptorMPEG_MuxCode (u_char *b)

{
  int len;

  // tag		 = b[0];
  len       	 = b[1];



  print_databytes (4,"MuxCodeTableEntry", b+2, len); // $$$ TODO

   // $$$ TODO  defined in subclause 11.2.4.3 of ISO/IEC 14496-1.
   // Muxcode_descriptor () {
   // 	descriptor_tag 8 uimsbf
   // 	descriptor_length 8 uimsbf
   // 	for (i = 0; i < N; i++) {
   // 		MuxCodeTableEntry ()
   // 	}
   // }


}


/*
  0x22  FMX Buffer Size descriptor
  ISO 13818-1  
*/

void descriptorMPEG_FMXBufferSize (u_char *b)

{
  int len;

  // tag	 = b[0];
  len       	 = b[1];



  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO
  indent (-1);


   // $$$ TODO defined in subclause 11.2 of ISO/IEC 14496-1.
   // FmxBufferSize_descriptor () {
   // 	descriptor_tag 8 uimsbf
   // 	descriptor_length 8 uimsbf
   // 	DefaultFlexMuxBufferDescriptor()
   // 	for (i=0; i<descriptor_length; i += 4) {
   // 		FlexMuxBufferDescriptor()
   // 	}
   // }

}


/*
  0x23   Multiplex Buffer descriptor
  ISO 13818-1  
*/

void descriptorMPEG_MultiplexBuffer (u_char *b)

{
  // d.descriptor_tag		 = b[0];
  // d.descriptor_length       	 = b[1];


 outBit_S2Tx_NL (4,"MB_buffer_size: ", 	b,16,24,"bytes");
 outBit_S2Tx_NL (4,"TB_leak_rate: ",  	b,40,24,"(x 400 bit/s)");

}








/*
  0x24   Content Labeling descriptor
  ITU-T H.222.0 AMD 1
*/

void descriptorMPEG_ContentLabeling (u_char *b)

{
  int     len;
  u_int   maf;
  u_int   crirf;
  u_int   ctbi;


  // tag	= b[0];
  len		= b[1];


// $$$ TODO 
  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO  H.222.0 AMD 1
  indent (-1);


  maf = outBit_S2x_NL   (4,"metadata_application_format: ",  	b, 16, 16,
  		   	(char *(*)(u_long)) dvbstrMPEG_metadata_application_format);

  b   += 4;
  len -= 2;
  if (maf == 0xFFFF) {
  	outBit_Sx_NL   (4,"metadata_application_format_identifier: ",  	b,  0, 32);
	b   += 4;
	len -= 4;
  }


  crirf = outBit_Sx_NL (4,"content_reference_id_record_flag: ",	b,  0,  1);
  ctbi  = outBit_S2x_NL(4,"content_time_base_indicator: ",  	b,  1,  4,
		 (char *(*)(u_long)) dvbstrMPEG_Content_time_base_indicator);
  outBit_Sx_NL   (6,"reserved: ",  				b,  5,  3);
  b++;
  len --;

  if (crirf == 1) {
	u_int  len2;

  	len2 = outBit_Sx_NL (4,"content_reference_id_record_length: ", b, 0, 8);
	print_databytes (4,"content_reference_id_byte:", b+1, len2);
	b   += len2 + 1;
	len -= len2 + 1;
  }



  if ( (ctbi == 1) || (ctbi == 2)) {
	long long ll;

  	outBit_Sx_NL   (6,"reserved: ",  	b,  0,  7);
	ll = getBits48 (b, 0,  7, 33);
	out_S2LL_NL(4,"content_time_base_value: ",ll,"90kHz units");
	// -- following is wrong, because of different unit measuring
	// out (4,"content_time_base_value: ");
	// print_timebase90kHz (4, ll);
	// out_NL (4);

  	outBit_Sx_NL   (6,"reserved: ",  	b, 40,  7);
	ll = getBits48 (b, 0,  47, 33);
	out_S2LL_NL(4,"metadata_time_base_value: ",ll,"90kHz units");
	// -- following is wrong, because of different unit measuring  $$$ TODO: check
	// out (4,"metadata_time_base_value: ");
	// print_timebase90kHz (4, ll);
	// out_NL (4);

	b   += 10;
	len -= 10;
  }

  if (ctbi == 2) {
  	outBit_Sx_NL   (6,"reserved: ",  	b,  0,  1);
  	outBit_Sx_NL   (4,"contentId: ",  	b,  1,  7);
	b++;
	len --;
  }

  if ( (ctbi >= 3) && (ctbi <= 7)) {
	u_int  len2;

  	len2 = outBit_Sx_NL (4,"time_base_association_data_length: ", b, 0, 8);
	print_databytes (6,"reserved:", b+1, len2);
	b   += len2 + 1;
	len -= len2 + 1;
  }


  print_private_data (4, b, len);
}







/*
  0x25  TVA metadata pointer descriptor
  TS 102 323  TV ANYTIME 
*/

void descriptorMPEG_TVA_metadata_pointer (u_char *b)

{
  int  len;

  // tag	= b[0];
  len		= b[1];


  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO TS 102 323, where defined?
  indent (-1);
}



/*
  0x26  TVA metadata descriptor
  TS 102 323  TV ANYTIME 
*/

void descriptorMPEG_TVA_metadata (u_char *b)

{
  int  len;

  // tag	= b[0];
  len		= b[1];


  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO TS 102 323, where defined?
  indent (-1);
}




/*
  0x27  TVA metadata STD descriptor
  ISO/IEC 13818-1:2000/DAM-1:2001(E)
*/

void descriptorMPEG_TVA_metadata_STD (u_char *b)

{
  // tag	= b[0];
  // len	= b[1];

  outBit_Sx_NL   (6,"reserved: ",  			b,  16,  2);
  outBit_S2Tx_NL (4,"metadata_input_leak_rate: ",  	b,  18, 22,"(x 400 bit/s)");
  outBit_Sx_NL   (6,"reserved: ",  			b,  40,  2);
  outBit_S2Tx_NL (4,"metadata_buffer_size: ", 		b,  42, 22,"(x 1024 bytes)");
  outBit_Sx_NL   (6,"reserved: ",  			b,  64,  2);
  outBit_S2Tx_NL (4,"metadata_output_leak_rate: ",  	b,  66, 22,"(x 400 bit/s)");
}



/*
  0x28  AVC video descriptor
  H.222.0 AMD 3
*/

void descriptorMPEG_AVC_video (u_char *b)

{
  int  len;

  // tag	= b[0];
  len		= b[1];


  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO 
  indent (-1);
}




/*
  0x29  IPMP descriptor
  H.222.0 AMD 3
*/

void descriptorMPEG_IPMP (u_char *b)

{
  int  len;

  // tag	= b[0];
  len		= b[1];


  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO 
  indent (-1);
}





/*
  0x2A  AVC_timing_and_HRD descriptor
  H.222.0 AMD 3
*/

void descriptorMPEG_AVC_timing_and_HRD (u_char *b)

{
  int  len;

  // tag	= b[0];
  len		= b[1];


  indent (+1);
  printhex_buf (4, b+2, len);  // $$$ TODO 
  indent (-1);
}





/*
  0x2B  MPEG-2_AAC_audio descriptor
  H.222.0 AMD 4
  ISO/IEC 13818-1:2000/Amd.5:2005 (E)
*/

void descriptorMPEG_MPEG2_AAC_audio (u_char *b)
{
  // d.descriptor_tag		 = b[0];
  // d.descriptor_length       	 = b[1];

  outBit_Sx_NL   (4,"MPEG-2_AAC_profile: ",  			b, 16,  8);
	// $$$ TODO:  ISO/IEC 13818-7:2004 subclause 7.1 Table 31.

  outBit_Sx_NL   (4,"MPEG-2_AAC_channel_configuration: ",  	b, 24,  8);
	// $$$ TODO:  ISO/IEC 13818-7:2004 subclause 8.9 Table 42

  outBit_Sx_NL   (4,"MPEG-2_AAC_additional_information: ",  	b, 32,  8);
  	// $$$ TODO:  ISO/IEC 13818-7:2004 is embedded in the AAC bitstream according to Table Amd.5-2.

}




/*
   0x2C   Flex-Mux-Timing descriptor
   ITU-T H.222.0-I-Cor1 
*/
 
void descriptorMPEG_FlexMuxTiming (u_char *b)
{
  // d.descriptor_tag		 = b[0];
  // d.descriptor_length       	 = b[1];


  outBit_Sx_NL   (4,"FCR_ES_ID: ",  	b,16,16);
  outBit_S2Tx_NL (4,"FCRResolution: ", 	b,32,32,"(cycles/s)");
  outBit_Sx_NL   (4,"FCRLength: ",  	b,64, 8);
  outBit_Sx_NL   (4,"FCRRateLength: ", 	b,72, 8);
 
}


