/*
$Id: dvb_str.c,v 1.76 2006/07/19 20:05:45 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


  -- DVB-Strings
  -- MPEG-Strings
  -- dvb decoder helper functions






$Log: dvb_str.c,v $
Revision 1.76  2006/07/19 20:05:45  rasc
Special handling for null packets

Revision 1.75  2006/02/12 23:17:12  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.74  2005/12/27 23:30:30  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.73  2005/12/22 16:21:51  rasc
Update and new descriptors EN 300 468 v1.7.1

Revision 1.72  2005/11/23 23:06:10  rasc
ISO13818-2  MPEG2 sequence header

Revision 1.71  2005/11/10 23:34:38  rasc
Some H.222.1 AMD 4+5 update

Revision 1.70  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.69  2005/11/08 23:15:26  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.68  2005/10/23 22:50:27  rasc
 - New:  started ISO 13818-2 StreamIDs
 - New:  decode multiple PS/PES packets within TS packets (-tssubdecode)

Revision 1.67  2005/09/09 14:20:30  rasc
TS continuity sequence check (cc verbose output)

Revision 1.66  2005/09/02 14:11:36  rasc
TS code redesign, xPCR and DTS timestamps decoding

Revision 1.65  2005/08/10 21:28:19  rasc
New: Program Stream handling  (-s ps)

Revision 1.64  2005/07/18 21:11:40  rasc
TVA Content Section

Revision 1.63  2005/01/17 19:41:24  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.62  2004/09/01 20:20:34  rasc
new cmdline option: -buffersize KB  (set demux buffersize in KBytes)

Revision 1.61  2004/08/25 21:33:41  rasc
small fix: Priority wrong in Terr. Sys Delivery descriptor

Revision 1.60  2004/08/25 19:51:09  rasc
 - Update: EN 300 468 v1.6.1 Terrestrial delivery system descriptor

Revision 1.59  2004/08/24 21:30:24  rasc
more Metadata

Revision 1.58  2004/08/13 11:05:29  rasc
Metadata_STD_descriptor

Revision 1.57  2004/08/13 01:15:54  rasc
small change in PID assignment display

Revision 1.56  2004/08/12 22:57:19  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.55  2004/08/01 21:33:09  rasc
minor TVA stuff (TS 102 323)

Revision 1.54  2004/07/26 20:58:03  rasc
RNT completed..  (TS 102 323)

Revision 1.53  2004/07/25 20:12:59  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.52  2004/07/24 11:44:45  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.51  2004/04/15 10:53:22  rasc
minor changes

Revision 1.50  2004/04/05 17:32:13  rasc
mass typo fix adaption --> adaptation

Revision 1.49  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.48  2004/03/21 00:37:47  rasc
Query FrontEnd Info  (option: -s feinfo)

Revision 1.47  2004/03/10 21:05:53  rasc
WSS (Wide Screen Signalling)  data decoding

Revision 1.46  2004/03/09 20:59:23  rasc
VPS decoding (someone check the NPP & PTY code output please...)

Revision 1.45  2004/02/15 18:58:31  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.44  2004/02/12 21:21:22  rasc
MHP AIT descriptors
some smaller changes

Revision 1.43  2004/02/09 22:57:01  rasc
Bugfix VBI Data descriptor

Revision 1.42  2004/02/09 21:25:01  rasc
AIT descriptors
minor redesign on output routines

Revision 1.41  2004/02/04 22:36:29  rasc
more EBU/teletext stuff

Revision 1.40  2004/02/02 23:34:11  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff

Revision 1.39  2004/01/25 21:37:28  rasc
bugfixes, minor changes & enhancments

Revision 1.38  2004/01/12 22:49:53  rasc
get rid of stream descriptor module

Revision 1.37  2004/01/11 22:49:41  rasc
PES restructured

Revision 1.36  2004/01/06 14:06:10  rasc
no message

Revision 1.35  2004/01/06 03:13:25  rasc
TS prints PES/Section ID on payload_start

Revision 1.34  2004/01/05 02:03:42  rasc
no message

Revision 1.33  2004/01/01 20:09:40  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.32  2003/12/30 14:05:38  rasc
just some annotations, so I do not forget these over Sylvester party...
(some alkohol may reformat parts of /devbrain/0 ... )
cheers!

Revision 1.31  2003/12/28 00:01:15  rasc
some minor changes/adds...

Revision 1.30  2003/12/27 18:17:18  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.29  2003/12/27 00:21:17  rasc
dsmcc section tables

Revision 1.28  2003/11/26 19:55:34  rasc
no message

Revision 1.27  2003/11/25 00:17:11  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.26  2003/11/24 23:52:18  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.25  2003/11/24 14:16:07  obi
- corrected transport scrambling control bits according to ETSI ETR 289
- fixed lots of broken strings

Revision 1.24  2003/11/09 20:48:35  rasc
pes data packet (DSM-CC)

Revision 1.23  2003/11/07 16:33:32  rasc
no message

Revision 1.22  2003/11/01 21:40:28  rasc
some broadcast/linkage descriptor stuff

Revision 1.21  2003/10/29 20:54:57  rasc
more PES stuff, DSM descriptors, testdata

Revision 1.20  2003/10/27 22:43:50  rasc
carousel info descriptor and more

Revision 1.19  2003/10/26 23:00:43  rasc
fix

Revision 1.18  2003/10/25 19:11:50  rasc
no message

Revision 1.17  2003/10/21 19:54:43  rasc
no message

Revision 1.16  2003/10/19 22:22:57  rasc
- some datacarousell stuff started

Revision 1.15  2003/10/19 21:05:53  rasc
- some datacarousell stuff started

Revision 1.14  2003/10/19 13:54:25  rasc
-more table decoding

Revision 1.13  2003/10/17 19:04:11  rasc
- started more work on newer ISO 13818  descriptors
- some reorg/update work started

Revision 1.12  2003/10/17 18:16:54  rasc
- started more work on newer ISO 13818  descriptors
- some reorg work started

Revision 1.11  2003/10/16 19:02:28  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.10  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?

Revision 1.9  2003/06/24 23:51:03  rasc
bugfixes and enhancements

Revision 1.8  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.7  2001/12/07 22:17:20  rasc
no message

Revision 1.6  2001/12/06 15:33:18  rasc
some small work on pespacket.c

Revision 1.5  2001/12/01 12:34:17  rasc
pespacket weitergestrickt, leider z.Zt. zuwenig Zeit um es richtig fertig zu machen.

Revision 1.4  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.3  2001/10/05 17:43:37  rasc
typo...

Revision 1.2  2001/10/02 21:52:44  rasc
- init der time_delta
- PES erweitert, PES arbeitet im read() noch nicht richtig!!
- muss tmbinc fragem, ob ich Mist baue, oder der Treiber (??)

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/



#include "dvbsnoop.h"
#include "dvb_str.h"
#include "strtable_misc.h"





/*
  --  PID assignment
*/

char *dvbstrPID_assignment (u_int id)
{
  STR_TABLE  TableIDs[] = {
     {  0x0000, 0x0000,  "ISO 13818-1 Program Association Table (PAT)" },
     {  0x0001, 0x0001,  "ISO 13818-1 Conditional Access Table (CAT)" },
     {  0x0002, 0x0002,  "ISO 13818-1 Transport Stream Description Table (TSDT)" },
     {  0x0003, 0x0003,  "ISO 13818-11 IPMP Control Information " },
     {  0x0004, 0x000F,  "" },
     {  0x0010, 0x0010,  "DVB Network Information Table (NIT), Stuffing Table (ST)" },
     {  0x0011, 0x0011,  "DVB Service Description Table (SDT), Bouquet Association Table (BAT)" },
     {  0x0012, 0x0012,  "DVB Event Information Table (EIT)" },
     {  0x0013, 0x0013,  "DVB Running Status Table (RST)" },
     {  0x0014, 0x0014,  "DVB Time and Date Table (TDT), Time Offset Table (TOT)" },
     {  0x0015, 0x0015,  "DVB Network Synchronization / Mega-Frame Initialization Packet" },
     {  0x0016, 0x0016,  "TV ANYTIME Resolution Notification Table (RNT)" },
     {  0x0017, 0x001B,  "" },
     {  0x001C, 0x001C,  "DVB Inband Signalling" },
     {  0x001D, 0x001D,  "DVB Measurement" },
     {  0x001E, 0x001E,  "DVB Discontinuity Information Table (DIT)" },
     {  0x001F, 0x001F,  "DVB Selection Information Table (SIT)" },

     // $$$ TODO  ATSC Pid assignment
     {  0x0020, 0x1FFE,  "" },

     {  0x1FFF, 0x1FFF,  "Null Packet" },
     {  0,0, NULL }
  };

  return findTableID (TableIDs, id);
}




/*
  --  Table IDs (sections)
 ETSI EN 468   5.2
 EN 301 192
 TR 102 006
 RE 101 202
 ISO 13818-1
 TS 102 323
 TS 101 191
*/

char *dvbstrTableID (u_int id)

{
  STR_TABLE  TableIDs[] = {

 	// updated -- 2003-11-04
	// -- updated 2004-07-26  from ITU-T Rec H.222.0 | ISO/IEC 13818-1:2000/FDAM 1
	// -- updated 2004-08-12  from ITU-T Rec H.222.0 AMD2
	// ATSC Table IDs could be included...

     {  0x00, 0x00,  "Program Association Table (PAT)" },
     {  0x01, 0x01,  "Conditional Access Table (CAT)" },
     {  0x02, 0x02,  "Program Map Table (PMT)" },
     {  0x03, 0x03,  "Transport Stream Description Table (TSDT)" },
     {  0x04, 0x04,  "ISO_IEC_14496_scene_description_section" },	/* $$$ TODO */
     {  0x05, 0x05,  "ISO_IEC_14496_object_description_section" },	/* $$$ TODO */
     {  0x06, 0x06,  "Metadata Table" },				// $$$ TODO H.222.0 AMD1
     {  0x07, 0x07,  "IPMP_Control_Information_section (ISO 13818-11)" }, // $$$ TODO H.222.0 AMD1
     {  0x08, 0x37,  "ITU-T Rec. H.222.0|ISO/IEC13818 reserved" },
     {  0x38, 0x39,  "ISO/IEC 13818-6 reserved" },
     {  0x3a, 0x3a,  "DSM-CC - multiprotocol encapsulated data" },
     {  0x3b, 0x3b,  "DSM-CC - U-N messages (DSI or DII)" },
     {  0x3c, 0x3c,  "DSM-CC - Download Data Messages (DDB)" },    /* TR 101 202 */
     {  0x3d, 0x3d,  "DSM-CC - stream descriptorlist" },
     {  0x3e, 0x3e,  "DSM-CC - private data section  // DVB datagram" }, /* EN 301 192 // ISO 13818-6 */
     {  0x3f, 0x3f,  "ISO/IEC 13818-6 reserved" },

     {  0x40, 0x40,  "Network Information Table (NIT) - actual network" },
     {  0x41, 0x41,  "Network Information Table (NIT) - other network" },
     {  0x42, 0x42,  "Service Description Table (SDT) - actual transport stream" },
     {  0x43, 0x45,  "reserved" },
     {  0x46, 0x46,  "Service Description Table (SDT) - other transport stream" },
     {  0x47, 0x49,  "reserved" },
     {  0x4A, 0x4A,  "Bouquet Association Table (BAT)" },
     {  0x4B, 0x4B,  "Update Notification Table (UNT)" },	/* TR 102 006 */
     {  0x4C, 0x4C,  "IP/MAC Notification Table (INT) [EN 301 192]" },  /* EN 192 */
     {  0x4D, 0x4D,  "reserved" },

     {  0x4E, 0x4E,  "Event Information Table (EIT) - actual transport stream, present/following" },
     {  0x4F, 0x4F,  "Event Information Table (EIT) - other transport stream, present/following" },
     {  0x50, 0x5F,  "Event Information Table (EIT) - actual transport stream, schedule" },
     {  0x60, 0x6F,  "Event Information Table (EIT) - other transport stream, schedule" },
     {  0x70, 0x70,  "Time Date Table (TDT)" },
     {  0x71, 0x71,  "Running Status Table (RST)" },
     {  0x72, 0x72,  "Stuffing Table (ST)" },
     {  0x73, 0x73,  "Time Offset Table (TOT)" },
     {  0x74, 0x74,  "MHP- Application Information Table (AIT)" }, 	/* MHP */
     {  0x75, 0x75,  "TVA- Container Table (CT)" }, 			/* TS 102 323 */
     {  0x76, 0x76,  "TVA- Related Content Table (RCT)" }, 		/* TS 102 323 */
     {  0x77, 0x77,  "TVA- Content Identifier Table (CIT)" },	 	/* TS 102 323 */
     {  0x78, 0x78,  "MPE-FEC Table (MFT)" }, 				/* EN 301 192 v1.4.1*/
     {  0x79, 0x79,  "TVA- Resolution Notification Table (RNT)" },	/* TS 102 323 */
     {  0x80, 0x7D,  "reserved" },
     {  0x7E, 0x7E,  "Discontinuity Information Table (DIT)" },
     {  0x7F, 0x7F,  "Selection Information Table (SIT)" },
     {  0x80, 0x8F,  "DVB CA message section (EMM/ECM)" },   /* ITU-R BT.1300 ref. */
     {  0x90, 0xBF,  "User private" },
     {  0xC0, 0xFE,  "ATSC reserved" },		/* ETR 211e02 */
     {  0xFF, 0xFF,  "forbidden" },
     {  0,0, NULL }
  };


  return findTableID (TableIDs, id);
}


/*
  -- ISO Descriptor table tags
  -- ISO 13818-1, etc.
  -- 2004-08-11 Updated H.222.0 AMD1
  -- 2004-08-12 Updated H.222.0 AMD3
  -- 2005-11-10 Updated H.222.0 (2000)/Cor.4 (09/2005)
*/

char *dvbstrMPEGDescriptorTAG (u_int tag)

{
  STR_TABLE  Tags[] = {
     {  0x00, 0x01,  "Reserved" },
     {  0x02, 0x02,  "video_stream_descriptor" },
     {  0x03, 0x03,  "audio_stream_descriptor" },
     {  0x04, 0x04,  "hierarchy_descriptor" },
     {  0x05, 0x05,  "registration_descriptor" },
     {  0x06, 0x06,  "data_stream_alignment_descriptor" },
     {  0x07, 0x07,  "target_background_grid_descriptor" },
     {  0x08, 0x08,  "video_window_descriptor" },
     {  0x09, 0x09,  "CA_descriptor" },
     {  0x0A, 0x0A,  "ISO_639_language_descriptor" },
     {  0x0B, 0x0B,  "system_clock_descriptor" },
     {  0x0C, 0x0C,  "multiplex_buffer_utilization_descriptor" },
     {  0x0D, 0x0D,  "copyright_descriptor" },
     {  0x0E, 0x0E,  "maximum_bitrate_descriptor" },
     {  0x0F, 0x0F,  "private_data_indicator_descriptor" },
     {  0x10, 0x10,  "smoothing_buffer_descriptor" },
     {  0x11, 0x11,  "STD_descriptor" },
     {  0x12, 0x12,  "IBP_descriptor" },
          /* MPEG DSM-CC */
     {  0x13, 0x13,  "carousel_identifier_descriptor" },
     {  0x14, 0x14,  "association_tag_descriptor" },
     {  0x15, 0x15,  "deferred_association_tag_descriptor" },
     {  0x16, 0x16,  "ISO/IEC13818-6 Reserved" },
     	  /* DSM-CC stream descriptors */
     {  0x17, 0x17,  "NPT_reference_descriptor" },
     {  0x18, 0x18,  "NPT_endpoint_descriptor" },
     {  0x19, 0x19,  "stream_mode_descriptor" },
     {  0x1A, 0x1A,  "stream_event_descriptor" },
          /* MPEG-4 descriptors */
     {  0x1B, 0x1B,  "MPEG4_video_descriptor" },
     {  0x1C, 0x1C,  "MPEG4_audio_descriptor" },
     {  0x1D, 0x1D,  "IOD_descriptor" },
     {  0x1E, 0x1E,  "SL_descriptor" },
     {  0x1F, 0x1F,  "FMC_descriptor" },
     {  0x20, 0x20,  "External_ES_ID_descriptor" },
     {  0x21, 0x21,  "MuxCode_descriptor" },
     {  0x22, 0x22,  "FMXBufferSize_descriptor" },
     {  0x23, 0x23,  "MultiplexBuffer_descriptor" },
     {  0x24, 0x24,  "Content_labeling_descriptor" },
     	/* TV ANYTIME TS 102 323 descriptors, ISO 13818-1 */
     {  0x25, 0x25,  "metadata_pointer_descriptor" },
     {  0x26, 0x26,  "metadata_descriptor" },
     {  0x27, 0x27,  "metadata_STD_descriptor" },
     {  0x28, 0x28,  "AVC_video_descriptor" },
     {  0x29, 0x29,  "IPMP_descriptor (MPEG-2 IPMP, ISO 13818-11)" },
     {  0x2A, 0x2A,  "AVC_timing_and_HRD_descriptor" },

     {  0x2B, 0x2B,  "MPEG-2_AAC_audio_descriptor" },
     {  0x2C, 0x2C,  "FlexMuxTiming_descriptor" },
     {  0x2D, 0x3F,  "ITU-T.Rec.H.222.0|ISO/IEC13818-1 Reserved" },

     {  0x40, 0xFF,  "Forbidden descriptor in MPEG context" },	// DVB Context
     {  0,0, NULL }
  };


  return findTableID (Tags, tag);
}








/*
  -- Descriptor table tags
*/

char *dvbstrDVBDescriptorTAG (u_int tag)

{
  STR_TABLE  Tags[] = {
     {  0x00, 0x3F,  "Forbidden descriptor in DVB context" },   // MPEG Context

	// ETSI 300 468
	// updated EN 302 192 v 1.4.1
     {  0x40, 0x40,  "network_name_descriptor" },
     {  0x41, 0x41,  "service_list_descriptor" },
     {  0x42, 0x42,  "stuffing_descriptor" },
     {  0x43, 0x43,  "satellite_delivery_system_descriptor" },
     {  0x44, 0x44,  "cable_delivery_system_descriptor" },
     {  0x45, 0x45,  "VBI_data_descriptor" },
     {  0x46, 0x46,  "VBI_teletext_descriptor" },
     {  0x47, 0x47,  "bouquet_name_descriptor" },
     {  0x48, 0x48,  "service_descriptor" },
     {  0x49, 0x49,  "country_availibility_descriptor" },
     {  0x4A, 0x4A,  "linkage_descriptor" },
     {  0x4B, 0x4B,  "NVOD_reference_descriptor" },
     {  0x4C, 0x4C,  "time_shifted_service_descriptor" },
     {  0x4D, 0x4D,  "short_event_descriptor" },
     {  0x4E, 0x4E,  "extended_event_descriptor" },
     {  0x4F, 0x4F,  "time_shifted_event_descriptor" },
     {  0x50, 0x50,  "component_descriptor" },
     {  0x51, 0x51,  "mosaic_descriptor" },
     {  0x52, 0x52,  "stream_identifier_descriptor" },
     {  0x53, 0x53,  "CA_identifier_descriptor" },
     {  0x54, 0x54,  "content_descriptor" },
     {  0x55, 0x55,  "parental_rating_descriptor" },
     {  0x56, 0x56,  "teletext_descriptor" },
     {  0x57, 0x57,  "telephone_descriptor" },
     {  0x58, 0x58,  "local_time_offset_descriptor" },
     {  0x59, 0x59,  "subtitling_descriptor" },
     {  0x5A, 0x5A,  "terrestrial_delivery_system_descriptor" },
     {  0x5B, 0x5B,  "multilingual_network_name_descriptor" },
     {  0x5C, 0x5C,  "multilingual_bouquet_name_descriptor" },
     {  0x5D, 0x5D,  "multilingual_service_name_descriptor" },
     {  0x5E, 0x5E,  "multilingual_component_descriptor" },
     {  0x5F, 0x5F,  "private_data_specifier_descriptor" },
     {  0x60, 0x60,  "service_move_descriptor" },
     {  0x61, 0x61,  "short_smoothing_buffer_descriptor" },
     {  0x62, 0x62,  "frequency_list_descriptor" },
     {  0x63, 0x63,  "partial_transport_stream_descriptor" },
     {  0x64, 0x64,  "data_broadcast_descriptor" },
     {  0x65, 0x65,  "scrambling_descriptor" },
     {  0x66, 0x66,  "data_broadcast_id_descriptor" },
     {  0x67, 0x67,  "transport_stream_descriptor" },
     {  0x68, 0x68,  "DSNG_descriptor" },
     {  0x69, 0x69,  "PDC_descriptor" },
     {  0x6A, 0x6A,  "AC3_descriptor" },
     {  0x6B, 0x6B,  "ancillary_data_descriptor" },
     {  0x6C, 0x6C,  "cell_list_descriptor" },
     {  0x6D, 0x6D,  "cell_frequency_list_descriptor" },
     {  0x6E, 0x6E,  "announcement_support_descriptor" },
     {  0x6F, 0x6F,  "application_signalling_descriptor" },
     {  0x70, 0x70,  "adaptation_field_data_descriptor" },
     {  0x71, 0x71,  "service_identifier_descriptor" },
     {  0x72, 0x72,  "service_availability_descriptor" },
     {  0x73, 0x73,  "default_authority_descriptor" }, 		// TS 102 323
     {  0x74, 0x74,  "related_content_descriptor" }, 		// TS 102 323
     {  0x75, 0x75,  "TVA_id_descriptor" }, 			// TS 102 323
     {  0x76, 0x76,  "content_identifier_descriptor" }, 	// TS 102 323
     {  0x77, 0x77,  "time_slice_fec_identifier_descriptor" }, 	// EN 300 468 v1.6.1
     {  0x78, 0x78,  "ECM_repetition_rate_descriptor" }, 	// EN 300 468 v1.6.1
     {  0x79, 0x79,  "S2_satellite_delivery_system_descriptor" }, 	// EN 300 468 v1.7.1
     {  0x7A, 0x7A,  "enhanced_AC-3_descriptor" },	 	// EN 300 468 v1.7.1
     {  0x7B, 0x7B,  "DTS_descriptor" },	 		// EN 300 468 v1.7.1
     {  0x7C, 0x7C,  "AAC_descriptor" },	 		// EN 300 468 v1.7.1
     {  0x7D, 0x7E,  "reserved_descriptor" },	 		// EN 300 468 v1.7.1
     {  0x7F, 0x7F,  "extension_descriptor" },	 		// EN 300 468 v1.7.1
     {  0x80, 0xAF,  "User defined/ATSC reserved" },		/* ETR 211e02 */
     {  0xB0, 0xFE,  "User defined" },
     {  0xFF, 0xFF,  "Forbidden" },
     {  0,0, NULL }
  };


  return findTableID (Tags, tag);
}


/*
 -- current_next_indicator
 -- ISO/IEC13818-1|ITU H.222.0
*/

char *dvbstrCurrentNextIndicator (u_int flag)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "valid next" },
     {  0x01, 0x01,  "valid now" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



/*
 -- delivery desctritor flags
 -- ETSI EN 468 6.2.12.1 ff
*/

char *dvbstrWEST_EAST_FLAG (u_int flag)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "WEST" },
     {  0x01, 0x01,  "EAST" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



char *dvbstrPolarisation_FLAG (u_int flag)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "linear - horizontal" },
     {  0x01, 0x01,  "linear - vertical" },
     {  0x02, 0x02,  "circular - left" },
     {  0x03, 0x03,  "circular - right" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}


char *dvbstrModulationSAT_FLAG (u_int flag)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "Auto" },
     {  0x01, 0x01,  "QPSK" },
     {  0x02, 0x02,  "8PSK" },		// EN 300 468 1.7.1
     {  0x03, 0x03,  "16-QAM" },	// EN 300 468 1.7.1
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}


char *dvbstrRollOffSAT_FLAG (u_int flag)
{
  STR_TABLE  Table[] = {		// EN 300 468 1.7.1
     {  0x00, 0x00,  "Alpha 0.35" },
     {  0x01, 0x01,  "Alpha 0.25" },
     {  0x02, 0x02,  "Alpha 0.20" },
     {  0x03, 0x1F,  "reserved for future use" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}


char *dvbstrModulationCable_FLAG (u_int flag)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "not defined" },
     {  0x01, 0x01,  "16 QAM" },
     {  0x02, 0x02,  "32 QAM" },
     {  0x03, 0x03,  "64 QAM" },
     {  0x04, 0x04,  "128 QAM" },
     {  0x05, 0x05,  "256 QAM" },
     {  0x06, 0xFF,  "reserved for future use" },
     {  0,0, NULL }
  };


  return findTableID (Table, flag);
}



char *dvbstrFECinner_SCHEME (u_int flag)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "not defined" },
     {  0x01, 0x01,  "1/2 conv. code rate" },
     {  0x02, 0x02,  "2/3 conv. code rate" },
     {  0x03, 0x03,  "3/4 conv. code rate" },
     {  0x04, 0x04,  "5/6 conv. code rate" },
     {  0x05, 0x05,  "7/8 conv. code rate" },
     {  0x06, 0x06,  "8/9 conv. code rate" },	// EN 300 468 1.7.1
     {  0x07, 0x07,  "3/5 conv. code rate" },	// ...
     {  0x08, 0x08,  "4/5 conv. code rate" },
     {  0x09, 0x09,  "9/10 conv. code rate"},
     {  0x0A, 0x0E,  "reserved" },
     {  0x0F, 0x0F,  "No conv. coding" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



char *dvbstrFECouter_SCHEME (u_int flag)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "not defined" },
     {  0x01, 0x01,  "no outer FEC coding" },
     {  0x02, 0x02,  "RS(204/188)" },
     {  0x03, 0x0F,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}





/*
  -- Linkage type descriptor
*/

char *dvbstrLinkage_TYPE (u_int flag)

{
  STR_TABLE  Table[] = {
	  /* -- updated 2006-05-28 */
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "information service" },
     {  0x02, 0x02,  "EPG service" },
     {  0x03, 0x03,  "CA replacement service" },
     {  0x04, 0x04,  "TS containing complete Network/Bouquet SI" },
     {  0x05, 0x05,  "service replacement service" },
     {  0x06, 0x06,  "data broadcast service" },
     {  0x07, 0x07,  "RCS Map" },
     {  0x08, 0x08,  "mobile handover service" },
     {  0x09, 0x09,  "system software update service" },
     {  0x0A, 0x0A,  "TS containing SSU BAT or NIT" },
     {  0x0B, 0x0B,  "IP/MAC Notification Table" },
     {  0x0C, 0x0C,  "TS containing INT BAT or NIT" },
     {  0x0D, 0x7F,  "reserved" },

     {  0x80, 0xFE,  "user defined" },
     {  0xFF, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



char *dvbstrHandover_TYPE (u_int flag)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "DVB hand-over to an identical service in a neighbouring country" },
     {  0x02, 0x02,  "DVB hand-over to local variation to same service" },
     {  0x03, 0x03,  "DVB hand-over to an associated service" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



char *dvbstrOrigin_TYPE (u_int flag)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "NIT" },
     {  0x01, 0x01,  "SDT" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



/*
 -- Service Link Descriptor
 -- Updated: EN 300 468 1.7.1
*/ 

char *dvbstrService_TYPE (u_int flag)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "digital television service" },
     {  0x02, 0x02,  "digital radio sound service" },
     {  0x03, 0x03,  "Teletext service" },
     {  0x04, 0x04,  "NVOD reference service" },
     {  0x05, 0x05,  "NVOD time-shifted service" },
     {  0x06, 0x06,  "mosaic service" },
     	// -- 0x07 - 0x0B has been changed in EN 300 468 v1.7.1
     {  0x07, 0x08,  "reserved" },
     {  0x0A, 0x0A,  "advanced codec digital radio sound service" },
     {  0x0B, 0x0B,  "advanced codec mosaic service" },
     {  0x0C, 0x0C,  "data broadcast service" },
     {  0x0D, 0x0D,  "reserved for Common Interface Usage" },
     {  0x0E, 0x0E,  "RCS Map" },
     {  0x0F, 0x0F,  "RCS FLS" },
     {  0x10, 0x10,  "DVB  MHP service" },
     {  0x11, 0x11,  "MPEG-2 HD digital television service" },
     {  0x12, 0x15,  "reserved" },
     {  0x16, 0x16,  "advanced codec SD digital television service" },
     {  0x17, 0x17,  "advanced codec SD NVOD time-shifted service" },
     {  0x18, 0x18,  "advanced codec SD NVOD reference service" },
     {  0x19, 0x19,  "advanced codec HD digital television service" },
     {  0x1A, 0x1A,  "advanced codec HD NVOD time-shifted service" },
     {  0x1B, 0x1B,  "advanced codec HD NVOD reference service" },
     {  0x1C, 0x7F,  "reserved" },
     {  0x80, 0xFE,  "User defined" },
     {  0xFF, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}



/*
 -- Programm Map Table   Stream Type
 -- ISO 13818-1 
 -- 2004-07  updated H.222.0 AMD1
 -- 2004-08  updated H.222.0 AMD3
*/

char *dvbstrStream_TYPE (u_int flag)

{
  STR_TABLE  Table[] = {
	  // -- updated 2003-10-17  from H.220
	  // -- updated 2003-11-04  from ATSC / ISO13818-6AMD1-2000
	  // -- updated 2004-07-26  from ITU-T Rec H.222.0 AMD1
	  // -- updated 2004-08-12  from ITU-T Rec H.222.0 AMD3
     {  0x00, 0x00,  "ITU-T | ISO-IE Reserved" },
     {  0x01, 0x01,  "ISO/IEC 11172 Video" },
     {  0x02, 0x02,  "ITU-T Rec. H.262 | ISO/IEC 13818-2 Video | ISO/IEC 11172-2 constr. parameter video stream" },
     {  0x03, 0x03,  "ISO/IEC 11172 Audio" },
     {  0x04, 0x04,  "ISO/IEC 13818-3 Audio" },
     {  0x05, 0x05,  "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 private sections" },
     {  0x06, 0x06,  "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 PES packets containing private data" },
     {  0x07, 0x07,  "ISO/IEC 13512 MHEG" },
     {  0x08, 0x08,  "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A  DSM CC" },
     {  0x09, 0x09,  "ITU-T Rec. H.222.0 | ISO/IEC 13818-1/11172-1 auxiliary" },
     {  0x0A, 0x0A,  "ISO/IEC 13818-6 Multiprotocol encapsulation" },
     {  0x0B, 0x0B,  "ISO/IEC 13818-6 DSM-CC U-N Messages" },
     {  0x0C, 0x0C,  "ISO/IEC 13818-6 Stream Descriptors" },
     {  0x0D, 0x0D,  "ISO/IEC 13818-6 Sections (any type, including private data)" },
     {  0x0E, 0x0E,  "ISO/IEC 13818-1 auxiliary" },
     {  0x0F, 0x0F,  "ISO/IEC 13818-7 Audio with ADTS transport sytax" },
     {  0x10, 0x10,  "ISO/IEC 14496-2 Visual" },
     {  0x11, 0x11,  "ISO/IEC 14496-3 Audio with LATM transport syntax as def. in ISO/IEC 14496-3/AMD1" },
     {  0x12, 0x12,  "ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in PES packets" },
     {  0x13, 0x13,  "ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in ISO/IEC 14496 sections" },
     {  0x14, 0x14,  "ISO/IEC 13818-6 DSM-CC synchronized download protocol" },
     // Update 2004-07
     {  0x15, 0x15,  "Metadata carried in PES packets using the Metadata Access Unit Wrapper" },
     {  0x16, 0x16,  "Metadata carried in metadata_sections" },
     {  0x17, 0x17,  "Metadata carried in ISO/IEC 13818-6 (DSM-CC) Data Carousel" },
     {  0x18, 0x18,  "Metadata carried in ISO/IEC 13818-6 (DSM-CC) Object Carousel" },
     {  0x19, 0x19,  "Metadata carried in ISO/IEC 13818-6 Synchronized Download Protocol using the Metadata Access Unit Wrapper" },
     {  0x1A, 0x1A,  "IPMP stream (defined in ISO/IEC 13818-11, MPEG-2 IPMP)" },
     {  0x1B, 0x1B,  "AVC video stream as defined in ITU-T Rec. H.264 | ISO/IEC 14496-10 Video" },
     {  0x1C, 0x7E,  "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 reserved" },
     {  0x7F, 0x7F,  "IPMP stream" },

     // $$$ ATSC ID Names could be includes...
     // $$$ TODO  streamtype == 0x90 at MPE_FEC , see EN 301192 v1.4.1 s9.5
     {  0x80, 0xFF,  "User private" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}

/*
 -- Programm Map Table   Stream Type  (Short String ID: ""=Unkown, "S"=Section, "P"=PES)
 -- only important types...
 -- (short string used for spidering PIDs)
*/
char *dvbstrStream_TYPE_SHORT (u_int flag)
{
  // see dvbstrStream_TYPE
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "" },
     {  0x01, 0x04,  "P" },
     {  0x05, 0x05,  "S" },
     {  0x06, 0x06,  "P" },
     {  0x07, 0x07,  "" },
     {  0x08, 0x09,  "P" },
     {  0x0A, 0x0A,  "" },
     {  0x0B, 0x0B,  "S" },
     {  0x0C, 0x0C,  "P" },
     {  0x0D, 0x0D,  "S" },
     {  0x0E, 0x0E,  "P" },
     {  0x0F, 0xFF,  "" },
     {  0x10, 0x10,  "" },
     {  0x11, 0x11,  "" },
     {  0x12, 0x12,  "P" },
     {  0x13, 0x13,  "S" },
     {  0x14, 0x14,  "" },	// $$$ TODO  sect o PES
     {  0x15, 0x15,  "P" },
     {  0x16, 0x16,  "S" },

     {  0x17, 0x7F,  "" },	// ??? $$$ TODO

     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}




/*
 -- Audio Types (descriptor e.g. ISO 639)
 -- Update ISO/IEC 13818-1:2000/Amd.5:2005 (E)
*/

char *dvbstrAudio_TYPE (u_int flag)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "undefined" },
     {  0x01, 0x01,  "clean effects" },
     {  0x02, 0x02,  "hearing impaired" },
     {  0x03, 0x03,  "visual impaired commentary" },
     {  0x04, 0x7F,  "user private" },
     {  0x80, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}





/*
 -- CA-System Identifier  (ETSI ETR 162)
*/

char *dvbstrCASystem_ID (u_int id)

{
  STR_TABLE  Table[] = {
#include "dvb_org/ca_system_id.inc"
     {  0,0, NULL }
  };

  return findTableID (Table, id);
}


/*
 -- Data Broadcast ID
 -- ETR 162
*/ 

char *dvbstrDataBroadcast_ID (u_int flag)

{
  STR_TABLE  Table[] = {
#include "dvb_org/data_broadcast_id.inc"
     {  0,0, NULL }
  };

  return findTableID (Table, flag);
}





/*
 -- Network Identification coding (ETR 162)
*/

char *dvbstrOriginalNetwork_ID (u_int i)
{
  STR_TABLE  Table[] = {
#include "dvb_org/original_network_id.inc"
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


char *dvbstrNetworkIdent_ID (u_int i)

{
  STR_TABLE  Table[] = {
#include "dvb_org/network_id.inc"
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- Teletext type descriptor (ETSI EN 300 468  6.2.38)
*/

char *dvbstrTeletext_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "initial teletext page" },
     {  0x02, 0x02,  "teletext subtitle page" },
     {  0x03, 0x03,  "additional information page" },
     {  0x04, 0x04,  "program schedule page" },
     {  0x05, 0x05,  "teletext subtitle page for hearing impaired people" },
     {  0x06, 0x1F,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- Terrestrial Bandwidth descriptor (ETSI EN 300 468)
 -- see also: EN 300 744
*/

// -- updated: EN 300 468 v1.7.1
char *dvbstrTerrBandwidth_SCHEME (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "8 MHz" },
     {  0x01, 0x01,  "7 MHz" },
     {  0x02, 0x02,  "6 MHz" },
     {  0x03, 0x03,  "5 MHz" },
     {  0x04, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


char *dvbstrTerrConstellation_FLAG (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "QPSK" },
     {  0x01, 0x01,  "16-QAM" },
     {  0x02, 0x02,  "64-QAM" },
     {  0x03, 0x03,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


//  -- updated: EN 300 468 v1.7.1
char *dvbstrTerrHierarchy_FLAG (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00, "non-hierarchical (native interleaver)" },
     {  0x01, 0x01, "alpha=1 (native interleaver)" },
     {  0x02, 0x02, "alpha=2 (native interleaver)" },
     {  0x03, 0x03, "alpha=4 (native interleaver)" },
     {  0x04, 0x04, "non-hierarchical (in-depth interleaver)" },
     {  0x05, 0x05, "alpha=1 (in-depth interleaver)" },
     {  0x06, 0x06, "alpha=2 (in-depth interleaver)" },
     {  0x07, 0x07, "alpha=4 (in-depth interleaver)" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


char *dvbstrTerrCodeRate_FLAG (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "1/2" },
     {  0x01, 0x01,  "2/3" },
     {  0x02, 0x02,  "3/4" },
     {  0x03, 0x03,  "5/6" },
     {  0x04, 0x04,  "7/8" },
     {  0x05, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


//  -- updated: EN 300 468 v1.7.1
char *dvbstrTerrGuardInterval_FLAG (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "1/32" },
     {  0x01, 0x01,  "1/16" },
     {  0x02, 0x02,  "1/8" },
     {  0x03, 0x03,  "1/4" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


// Update EN 300 468 1.6.1.
char *dvbstrTerrTransmissionMode_FLAG (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "2k mode" },
     {  0x01, 0x01,  "8k mode" },
     {  0x02, 0x02,  "4k mode" },
     {  0x03, 0x03,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


// Update EN 300 468 1.6.1.
char *dvbstrTerrPriority (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "LP (low priority)" },
     {  0x01, 0x01,  "HP (high priority) or Non-hierarch." },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}

// Update EN 300 468 1.6.1.
char *dvbstrTerrTimeSlicingIndicator (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "at least one elementary stream uses Time Slicing" },
     {  0x01, 0x01,  "Time Slicing is not used.)" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}

// Update EN 300 468 1.6.1.
char *dvbstrTerrMPE_FEC_Indicator (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "at least one elementary stream uses MPE-FEC" },
     {  0x01, 0x01,  "MPE-FEC is not used.)" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



// EN 300 744 1.5.1   (Annex F.6.2)
char *dvbstrTerr_DVBH_service_indication (u_int i)
{
  STR_TABLE  Table[] = {
     { 0x00, 0x00, "No time slicing, no MPE-FEC" },
     { 0x01, 0x01, "No time slicing, at least one elementary stream use MPE-FEC" },
     { 0x02, 0x02, "Time slicing, no MPE-FEC" },
     { 0x03, 0x03, "Time slicing, at least one elementary stream use MPE-FEC" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- Aspect Ratio  (e.g. Target Background Grid)
 -- ISO 13818-2  Table 6.3
*/

char *dvbstrAspectRatioInfo_FLAG (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "forbidden" },
     {  0x01, 0x01,  " -- " },
     {  0x02, 0x02,  "3:4" },
     {  0x03, 0x03,  "9:16" },
     {  0x04, 0x04,  "1:2.21" },
     {  0x05, 0x0F,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- Hierarchy Type  
 -- ISO 13818-1  Table 2.6.7
*/

char *dvbstrHierarchy_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "ITU-T Rec.H.262 | ISO/IEC 13818-2 Spatial Scalability" },
     {  0x02, 0x02,  "ITU-T Rec.H.262 | ISO/IEC 13818-2 SNR Scalability" },
     {  0x03, 0x03,  "ITU-T Rec.H.262 | ISO/IEC 13818-2 Temporal Scalability" },
     {  0x04, 0x04,  "ITU-T Rec.H.262 | ISO/IEC 13818-2 Data partioning" },
     {  0x05, 0x05,  "ISO/IEC 13818-3 Extension bitstream" },
     {  0x06, 0x06,  "ITU-T Rec.H.222.0 | ISO/IEC 13818-1 Private Stream" },
     {  0x07, 0x0E,  "reserved" },
     {  0x0F, 0x0F,  "Base layer" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- Running Status  (SDT)  
 -- ETSI EN 300 468   5.2.3
*/

char *dvbstrRunningStatus_FLAG (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "undefined" },
     {  0x01, 0x01,  "not running" },
     {  0x02, 0x02,  "starts in a few seconds (e.g. for VCR)" },
     {  0x03, 0x03,  "pausing" },
     {  0x04, 0x04,  "running" },
     {  0x05, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- Data Stream Alignment Type
 -- ISO 13818-1  2.6.11
*/

char *dvbstrDataStreamVIDEOAlignment_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "Slice or video access unit" },
     {  0x02, 0x02,  "video access unit" },
     {  0x03, 0x03,  "GOP or SEQ" },
     {  0x04, 0x04,  "SEQ" },
     {  0x05, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


char *dvbstrDataStreamAUDIOAlignment_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "syncword" },
     {  0x02, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- VBI Data Service ID
  -- ETSI EN 300 468   6.2.43
*/

char *dvbstrDataService_ID (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "EBU teletext" },
     {  0x02, 0x02,  "inverted teletext" },
     {  0x03, 0x03,  "reserved" },
     {  0x04, 0x04,  "VPS (Video Programming System)" },
     {  0x05, 0x05,  "WSS (Wide Screen Signalling)" },
     {  0x06, 0x06,  "CC (Closed Caption)" },
     {  0x07, 0x07,  "monochrome 4:2:2 samples" },
     {  0x08, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}





/*
  -- Stream Content & Component Type
  -- ETSI EN 300 468   6.2.7
  -- updated: EN 300 468 v1.7.1
*/

char *dvbstrStreamContent_Component_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     // streamComponentID << 8    | ComponentID
     {  0x0000, 0x00FF,  "reserved" },

     {  0x0100, 0x0100,  "reserved" },
     {  0x0101, 0x0101,  "MPEG-2 video, 4:3 aspect ratio, 25 Hz" },
     {  0x0102, 0x0102,  "MPEG-2 video, 16:9 aspect ratio with pan vectors, 25 Hz" },
     {  0x0103, 0x0103,  "MPEG-2 video, 16:9 aspect ratio without pan vectors, 25 Hz" },
     {  0x0104, 0x0104,  "MPEG-2 video, >16:9 aspect ratio, 25 Hz" },
     {  0x0105, 0x0105,  "MPEG-2 video, 4:3 aspect ratio, 30 Hz" },
     {  0x0106, 0x0106,  "MPEG-2 video, 16:9 aspect ratio with pan vectors, 30 Hz" },
     {  0x0107, 0x0107,  "MPEG-2 video, 16:9 aspect ratio without pan vectors, 30 Hz" },
     {  0x0108, 0x0108,  "MPEG-2 video, >16:9 aspect ratio, 30 Hz" },

     {  0x0109, 0x0109,  "MPEG-2 high definition video, 4:3 aspect ratio, 25 Hz" },
     {  0x010A, 0x010A,  "MPEG-2 high definition video, 16:9 aspect ratio with pan vectors, 25 Hz" },
     {  0x010B, 0x010B,  "MPEG-2 high definition video, 16:9 aspect ratio without pan vectors, 25 Hz" },
     {  0x010C, 0x010C,  "MPEG-2 high definition video, >16:9 aspect ratio, 25 Hz" },
     {  0x010D, 0x010D,  "MPEG-2 high definition video, 4:3 aspect ratio, 30 Hz" },
     {  0x010E, 0x010E,  "MPEG-2 high definition video, 16:9 aspect ratio with pan vectors, 30 Hz" },
     {  0x010F, 0x010F,  "MPEG-2 high definition video, 16:9 aspect ratio without pan vectors, 30 Hz" },
     {  0x0110, 0x0110,  "MPEG-2 high definition video, >16:9 aspect ratio, 30 Hz" },

     {  0x0111, 0x01AF,  "reserved" },
     {  0x01B0, 0x01FE,  "User defined" },
     {  0x01FF, 0x01FF,  "reserved" },

     {  0x0200, 0x0200,  "reserved" },
     {  0x0201, 0x0201,  "MPEG-1 Layer 2 audio, single mono channel" },
     {  0x0202, 0x0202,  "MPEG-1 Layer 2 audio, dual mono channel" },
     {  0x0203, 0x0203,  "MPEG-1 Layer 2 audio, stereo (2 channels)" },
     {  0x0204, 0x0204,  "MPEG-1 Layer 2 audio, multilingual, multi-channel)" },
     {  0x0205, 0x0205,  "MPEG-1 Layer 2 audio, surround sound" },
     {  0x0206, 0x023F,  "reserved" },
     {  0x0240, 0x0240,  "MPEG-1 Layer 2 audio description for visually impaired" },
     {  0x0241, 0x0241,  "MPEG-1 Layer 2 audio for the hard of hearing" },

     {  0x0242, 0x02AF,  "reserved" },
     {  0x02B0, 0x02FE,  "User defined" },
     {  0x02FF, 0x02FF,  "reserved" },

     {  0x0300, 0x0300,  "reserved" },
     {  0x0301, 0x0301,  "EBU Teletext subtitles" },
     {  0x0302, 0x0302,  "associated EBU Teletext" },
     {  0x0303, 0x0303,  "VBI data" },
     {  0x0304, 0x030F,  "reserved" },

     {  0x0310, 0x0310,  "DVB subtitles (normal) with no monitor aspect ratio critical" },
     {  0x0311, 0x0311,  "DVB subtitles (normal) for display 4:3 aspect ratio monitor" },
     {  0x0312, 0x0312,  "DVB subtitles (normal) for display 16:9 aspect ratio monitor" },
     {  0x0313, 0x0313,  "DVB subtitles (normal) for display 2.21:1 aspect ratio monitor" },
     {  0x0314, 0x031F,  "reserved" },
     {  0x0320, 0x0320,  "DVB subtitles (for the hard hearing) with no monitor aspect ratio critical" },
     {  0x0321, 0x0321,  "DVB subtitles (for the hard hearing) for display 4:3 aspect ratio monitor" },
     {  0x0322, 0x0322,  "DVB subtitles (for the hard hearing) for display 16:9 aspect ratio monitor" },
     {  0x0323, 0x0323,  "DVB subtitles (for the hard hearing) for display 2.21:1 aspect ratio monitor" },
     {  0x0324, 0x03AF,  "reserved" },
     {  0x03B0, 0x03FE,  "User defined" },
     {  0x03FF, 0x03FF,  "reserved" },

     {  0x0400, 0x047F,  "reserved for AC-3 audio modes" },	// $$$ TODO
     {  0x0480, 0x04FF,  "reserved for enhanced AC-3 audio modes" },	// $$$ TODO

     {  0x0500, 0x0500,  "reserved" },
     {  0x0501, 0x0501,  "H.264/AVC standard definition video, 4:3 aspect ratio, 25 Hz" },
     {  0x0502, 0x0502,  "reserved" },
     {  0x0503, 0x0503,  "H.264/AVC standard definition video, 16:9 aspect ratio, 25 Hz" },
     {  0x0504, 0x0504,  "H.264/AVC standard definition video, >16:9 aspect ratio, 25 Hz" },
     {  0x0505, 0x0505,  "H.264/AVC standard definition video, 4:3 aspect ratio, 30 Hz" },
     {  0x0506, 0x0506,  "reserved" },
     {  0x0507, 0x0507,  "H.264/AVC standard definition video, 16:9 aspect ratio, 30 Hz" },
     {  0x0508, 0x0508,  "H.264/AVC standard definition video, >16:9 aspect ratio, 30 Hz" },
     {  0x0509, 0x050A,  "reserved" },
     {  0x050B, 0x050B,  "H.264/AVC high definition video, 16:9 aspect ratio, 25 Hz" },
     {  0x050C, 0x050C,  "H.264/AVC high definition video, >16:9 aspect ratio, 25 Hz" },
     {  0x050D, 0x050E,  "reserved" },
     {  0x050F, 0x050F,  "H.264/AVC high definition video, 16:9 aspect ratio, 30 Hz" },
     {  0x0510, 0x0510,  "H.264/AVC high definition video, >16:9 aspect ratio, 30 Hz" },
     {  0x0511, 0x05AF,  "reserved" },
     {  0x05B0, 0x05FE,  "user defined" },
     {  0x05FF, 0x05FF,  "reserved" },

     {  0x0600, 0x0600,  "reserved" },
     {  0x0601, 0x0601,  "HE-AAC audio, single mono channel" },
     {  0x0602, 0x0602,  "reserved" },
     {  0x0603, 0x0603,  "HE-AAC audio, stereo" },
     {  0x0604, 0x0604,  "reserved" },
     {  0x0605, 0x0605,  "HE-AAC audio, surround sound" },
     {  0x0606, 0x063F,  "reserved" },
     {  0x0640, 0x0640,  "HE-AAC audio description for the visually impaired" },
     {  0x0641, 0x0641,  "HE-AAC audio for the hard of hearing" },
     {  0x0642, 0x0642,  "HE-AAC audio receiver-mixed supplementary audio" },
     {  0x0643, 0x0643,  "HE-AAC v2 audio, stereo" },
     {  0x0644, 0x0644,  "HE-AAC v2 audio description for the visually impaired" },
     {  0x0645, 0x0645,  "HE-AAC v2 audio for the hard of hearing" },
     {  0x0646, 0x0646,  "HE-AAC v2 audio receiver-mixed supplementary audio" },
     {  0x0647, 0x06AF,  "reserved" },
     {  0x06B0, 0x65FE,  "user defined" },
     {  0x06FF, 0x65FF,  "reserved" },

     {  0x0700, 0x77F,  "reserved for DTS audio modes" },	// $$$ TODO
     {  0x0780, 0x7FF,  "reserved" },

     {  0x0800, 0x0BFF,  "reserved" },
     {  0x0C00, 0x0FFF,  "User defined" },

     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- Logical Cell Presentation Info
  -- ETSI EN 300 468   6.2.18
*/

char *dvbstrLogCellPresInfo_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "undefined" },
     {  0x01, 0x01,  "video" },
     {  0x02, 0x02,  "still picture (INTRA coded)" },
     {  0x03, 0x03,  "graphics/text" },
     {  0x04, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- Cell Linkage Info
  -- ETSI EN 300 468   6.2.18
*/

char *dvbstrCellLinkageInfo_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "undefined" },
     {  0x01, 0x01,  "bouquet related" },
     {  0x02, 0x02,  "service related" },
     {  0x03, 0x03,  "other mosaic related" },
     {  0x04, 0x04,  "event related" },
     {  0x05, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- Text Charset Types
  -- ETSI EN 300 468   ANNEX A
*/

char *dvbstrTextCharset_TYPE(u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "Latin/Cyrilic alphabet" },
     {  0x02, 0x02,  "Latin/Arabic alphabet" },
     {  0x03, 0x03,  "Latin/Greek alphabet" },
     {  0x04, 0x04,  "Latin/Hebrew alphabet" },
     {  0x05, 0x05,  "Latin alphabet no. 5" },
     {  0x06, 0x0F,  "reserved" },
     {  0x10, 0x10,  "ISO/IEC 8859  special table " },
     {  0x11, 0x11,  "ISO/IEC 10646-1 2Byte pairs Basic Multilingual Plane" },
     {  0x12, 0x12,  "Korean Charset KSC 5601" },
     {  0x13, 0x1F,  "reserved" },
     {  0x20, 0xFF,  "Latin alphabet" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- Content Nibble Types (Content descriptor)
  -- ETSI EN 300 468   6.2.8
*/

char *dvbstrContentNibble_TYPE(u_int i)

{
  STR_TABLE  Table[] = {
     // ContenNibble_1 << 8    |  ContentNibble_2
     //  4 bit                 |       4 bit
     {  0x0000, 0x000F,  "reserved" },

     // Movie/Drama
     {  0x0100, 0x0100,  "movie/drama (general)" },
     {  0x0101, 0x0101,  "detective/thriller" },
     {  0x0102, 0x0102,  "adventure/western/war" },
     {  0x0103, 0x0103,  "science fiction/fantasy/horror" },
     {  0x0104, 0x0104,  "comedy" },
     {  0x0105, 0x0105,  "soap/melodram/folkloric" },
     {  0x0106, 0x0106,  "romance" },
     {  0x0107, 0x0107,  "serious/classical/religious/historical movie/drama" },
     {  0x0108, 0x0108,  "adult movie/drama" },

     {  0x0109, 0x010E,  "reserved" },
     {  0x010F, 0x010F,  "user defined" },

     // News Current Affairs
     {  0x0200, 0x0200,  "news/current affairs (general)" },
     {  0x0201, 0x0201,  "news/weather report" },
     {  0x0202, 0x0202,  "news magazine" },
     {  0x0203, 0x0203,  "documentary" },
     {  0x0204, 0x0204,  "discussion/interview/debate" },
     {  0x0205, 0x020E,  "reserved" },
     {  0x020F, 0x020F,  "user defined" },

     // Show Games show
     {  0x0300, 0x0300,  "show/game show (general)" },
     {  0x0301, 0x0301,  "game show/quiz/contest" },
     {  0x0302, 0x0302,  "variety show" },
     {  0x0303, 0x0303,  "talk show" },
     {  0x0304, 0x030E,  "reserved" },
     {  0x030F, 0x030F,  "user defined" },

     // Sports
     {  0x0400, 0x0400,  "sports (general)" },
     {  0x0401, 0x0401,  "special events" },
     {  0x0402, 0x0402,  "sports magazine" },
     {  0x0403, 0x0403,  "football/soccer" },
     {  0x0404, 0x0404,  "tennis/squash" },
     {  0x0405, 0x0405,  "team sports" },
     {  0x0406, 0x0406,  "athletics" },
     {  0x0407, 0x0407,  "motor sport" },
     {  0x0408, 0x0408,  "water sport" },
     {  0x0409, 0x0409,  "winter sport" },
     {  0x040A, 0x040A,  "equestrian" },
     {  0x040B, 0x040B,  "martial sports" },
     {  0x040C, 0x040E,  "reserved" },
     {  0x040F, 0x040F,  "user defined" },

     // Children/Youth
     {  0x0500, 0x0500,  "childrens's/youth program (general)" },
     {  0x0501, 0x0501,  "pre-school children's program" },
     {  0x0502, 0x0502,  "entertainment (6-14 year old)" },
     {  0x0503, 0x0503,  "entertainment (10-16 year old)" },
     {  0x0504, 0x0504,  "information/education/school program" },
     {  0x0505, 0x0505,  "cartoon/puppets" },
     {  0x0506, 0x050E,  "reserved" },
     {  0x050F, 0x050F,  "user defined" },

     // Music/Ballet/Dance 
     {  0x0600, 0x0600,  "music/ballet/dance (general)" },
     {  0x0601, 0x0601,  "rock/pop" },
     {  0x0602, 0x0602,  "serious music/classic music" },
     {  0x0603, 0x0603,  "folk/traditional music" },
     {  0x0604, 0x0604,  "jazz" },
     {  0x0605, 0x0605,  "musical/opera" },
     {  0x0606, 0x0606,  "ballet" },
     {  0x0607, 0x060E,  "reserved" },
     {  0x060F, 0x060F,  "user defined" },

     // Arts/Culture
     {  0x0700, 0x0700,  "arts/culture (without music, general)" },
     {  0x0701, 0x0701,  "performing arts" },
     {  0x0702, 0x0702,  "fine arts" },
     {  0x0703, 0x0703,  "religion" },
     {  0x0704, 0x0704,  "popular culture/traditional arts" },
     {  0x0705, 0x0705,  "literature" },
     {  0x0706, 0x0706,  "film/cinema" },
     {  0x0707, 0x0707,  "experimental film/video" },
     {  0x0708, 0x0708,  "broadcasting/press" },
     {  0x0709, 0x0709,  "new media" },
     {  0x070A, 0x070A,  "arts/culture magazine" },
     {  0x070B, 0x070B,  "fashion" },
     {  0x070C, 0x070E,  "reserved" },
     {  0x070F, 0x070F,  "user defined" },

     // Social/Political/Economics
     {  0x0800, 0x0800,  "social/political issues/economics (general)" },
     {  0x0801, 0x0801,  "magazines/reports/documentary" },
     {  0x0802, 0x0802,  "economics/social advisory" },
     {  0x0803, 0x0803,  "remarkable people" },
     {  0x0804, 0x080E,  "reserved" },
     {  0x080F, 0x080F,  "user defined" },

     // Education/Science/...
     {  0x0900, 0x0900,  "education/science/factual topics (general)" },
     {  0x0901, 0x0901,  "nature/animals/environment" },
     {  0x0902, 0x0902,  "technology/natural science" },
     {  0x0903, 0x0903,  "medicine/physiology/psychology" },
     {  0x0904, 0x0904,  "foreign countries/expeditions" },
     {  0x0905, 0x0905,  "social/spiritual science" },
     {  0x0906, 0x0906,  "further education" },
     {  0x0907, 0x0907,  "languages" },
     {  0x0908, 0x090E,  "reserved" },
     {  0x090F, 0x090F,  "user defined" },

     // Leisure hobies
     {  0x0A00, 0x0A00,  "leisure hobbies (general)" },
     {  0x0A01, 0x0A01,  "tourism/travel" },
     {  0x0A02, 0x0A02,  "handicraft" },
     {  0x0A03, 0x0A03,  "motoring" },
     {  0x0A04, 0x0A04,  "fitness & health" },
     {  0x0A05, 0x0A05,  "cooking" },
     {  0x0A06, 0x0A06,  "advertisement/shopping" },
     {  0x0A07, 0x0A07,  "gardening" },
     {  0x0A08, 0x0A0E,  "reserved" },
     {  0x0A0F, 0x0A0F,  "user defined" },

     {  0x0B00, 0x0B00,  "original language" },
     {  0x0B01, 0x0B01,  "black & white" },
     {  0x0B02, 0x0B02,  "unpublished" },
     {  0x0B03, 0x0B03,  "live broadcast" },
     {  0x0B04, 0x0B0E,  "reserved" },
     {  0x0B0F, 0x0B0F,  "user defined" },

     {  0x0C00, 0x0E0F,  "reserved" },
     {  0x0F00, 0x0F0F,  "user defined" },

     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- Parental Rating Info
  -- ETSI EN 300 468   6.2.25
*/

char *dvbstrParentalRating_TYPE (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "undefined" },
     {  0x01, 0x01,  "minimum age: 4 years" },
     {  0x02, 0x02,  "minimum age: 5 years" },
     {  0x03, 0x03,  "minimum age: 6 years" },
     {  0x04, 0x04,  "minimum age: 7 years" },
     {  0x05, 0x05,  "minimum age: 8 years" },
     {  0x06, 0x06,  "minimum age: 9 years" },
     {  0x07, 0x07,  "minimum age: 10 years" },
     {  0x08, 0x08,  "minimum age: 11 years" },
     {  0x09, 0x09,  "minimum age: 12 years" },
     {  0x0A, 0x0A,  "minimum age: 13 years" },
     {  0x0B, 0x0B,  "minimum age: 14 years" },
     {  0x0C, 0x0C,  "minimum age: 15 years" },
     {  0x0D, 0x0D,  "minimum age: 16 years" },
     {  0x0E, 0x0E,  "minimum age: 17 years" },
     {  0x0F, 0x0F,  "minimum age: 18 years" },
     {  0x10, 0xFF,  "defined by broadcaster" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- Delivery System Coding Type
  -- ETSI EN 300 468   6.2.15
*/

char *dvbstrDelivSysCoding_TYPE (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "undefined" },
     {  0x01, 0x01,  "satellite" },
     {  0x02, 0x02,  "cable" },
     {  0x03, 0x03,  "terrestrial" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}






/*
  -- Short Smoothing Buffer Size Type
  -- ETSI EN 300 468   6.2.29
*/

char *dvbstrShortSmoothingBufSize_TYPE (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "1536 Bytes" },
     {  0x02, 0x02,  "reserved" },
     {  0x03, 0x03,  "reserved" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}



char *dvbstrShortSmoothingBufLeakRate_TYPE (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "0.0009 Mbit/s" },
     {  0x02, 0x02,  "0.0018 Mbit/s" },
     {  0x03, 0x03,  "0.0036 Mbit/s" },
     {  0x04, 0x04,  "0.0072 Mbit/s" },
     {  0x05, 0x05,  "0.0108 Mbit/s" },
     {  0x06, 0x06,  "0.0144 Mbit/s" },
     {  0x07, 0x07,  "0.0216 Mbit/s" },
     {  0x08, 0x08,  "0.0288 Mbit/s" },
     {  0x09, 0x09,  "0.075 Mbit/s" },
     {  0x0A, 0x0A,  "0.5 Mbit/s" },
     {  0x0B, 0x0B,  "0.5625 Mbit/s" },
     {  0x0C, 0x0C,  "0.8437 Mbit/s" },
     {  0x0D, 0x0D,  "1.0 Mbit/s" },
     {  0x0E, 0x0E,  "1.1250 Mbit/s" },
     {  0x0F, 0x0F,  "1.5 Mbit/s" },
     {  0x10, 0x10,  "1.6875 Mbit/s" },
     {  0x11, 0x11,  "2.0 Mbit/s" },
     {  0x12, 0x12,  "2.25 Mbit/s" },
     {  0x13, 0x13,  "2.5 Mbit/s" },
     {  0x14, 0x14,  "3.0 Mbit/s" },
     {  0x15, 0x15,  "3.3750 Mbit/s" },
     {  0x16, 0x16,  "3.5 Mbit/s" },
     {  0x17, 0x17,  "4.0 Mbit/s" },
     {  0x18, 0x18,  "4.5 Mbit/s" },
     {  0x19, 0x19,  "5.0 Mbit/s" },
     {  0x1A, 0x1A,  "5.5 Mbit/s" },
     {  0x1B, 0x1B,  "6.0 Mbit/s" },
     {  0x1C, 0x1C,  "6.5 Mbit/s" },
     {  0x1D, 0x1D,  "6.75 Mbit/s" },
     {  0x1E, 0x1E,  "7.0 Mbit/s" },
     {  0x1F, 0x1F,  "7.5 Mbit/s" },
     {  0x20, 0x20,  "8.0 Mbit/s" },
     {  0x21, 0x21,  "9 Mbit/s" },
     {  0x22, 0x22,  "10 Mbit/s" },
     {  0x23, 0x23,  "11 Mbit/s" },
     {  0x24, 0x24,  "12 Mbit/s" },
     {  0x25, 0x25,  "13 Mbit/s" },
     {  0x26, 0x26,  "13.5 Mbit/s" },
     {  0x27, 0x27,  "14.0 Mbit/s" },
     {  0x28, 0x28,  "15 Mbit/s" },
     {  0x29, 0x29,  "16 Mbit/s" },
     {  0x2A, 0x2A,  "17 Mbit/s" },
     {  0x2B, 0x2B,  "18 Mbit/s" },
     {  0x2C, 0x2C,  "20 Mbit/s" },
     {  0x2D, 0x2D,  "22 Mbit/s" },
     {  0x2E, 0x2E,  "24 Mbit/s" },
     {  0x2F, 0x2F,  "26 Mbit/s" },
     {  0x30, 0x30,  "27 Mbit/s" },
     {  0x31, 0x31,  "28 Mbit/s" },
     {  0x32, 0x32,  "30 Mbit/s" },
     {  0x33, 0x33,  "32 Mbit/s" },
     {  0x34, 0x34,  "34 Mbit/s" },
     {  0x35, 0x35,  "36 Mbit/s" },
     {  0x36, 0x36,  "38 Mbit/s" },
     {  0x37, 0x37,  "40 Mbit/s" },
     {  0x38, 0x38,  "44 Mbit/s" },
     {  0x39, 0x39,  "48 Mbit/s" },
     {  0x3A, 0x3A,  "54 Mbit/s" },
     {  0x3B, 0x3B,  "72 Mbit/s" },
     {  0x3C, 0x3C,  "108 Mbit/s" },
     {  0x3D, 0x3F,  "reserved" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}





/*
  -- AC3 Component Type
  -- ETSI EN 300 468, TS 102 114
*/

char *dvbstrDVB_AC3_ComponentType (u_int i)
{
  char *s = "TODO:  $$$ - AC3 Component type";	// $$$ TODO


  return s;
}


/*
  -- AUDIO DTS Sample Rate Code
  -- ETSI EN 300 468, TS 102 114
*/

char *dvbstrDVB_DTS_Audio_SampleRateCode (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "invalid" },
     {  0x01, 0x01,  "8 kHz" },
     {  0x02, 0x02,  "16 kHz" },
     {  0x03, 0x03,  "32 kHz" },
     {  0x04, 0x04,  "64 kHz" },
     {  0x05, 0x05,  "128 kHz" },
     {  0x06, 0x06,  "11.025 kHz" },
     {  0x07, 0x07,  "22.05 kHz" },
     {  0x08, 0x08,  "44.1 kHz" },
     {  0x09, 0x09,  "88.02 kHz" },
     {  0x0A, 0x0A,  "176.4 kHz" },
     {  0x0B, 0x0B,  "18 kHz" },
     {  0x0C, 0x0C,  "24 kHz" },
     {  0x0D, 0x0D,  "48 kHz" },
     {  0x0E, 0x0E,  "96 kHz" },
     {  0x0F, 0x0F,  "192 kHz" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}




/*
  -- AUDIO DTS Bit Rate 
  -- ETSI EN 300 468, TS 102 114
*/

char *dvbstrDVB_DTS_Audio_BitRate (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x05, 0x05,  "128 kbps" },
     {  0x06, 0x06,  "192 kbps" },
     {  0x07, 0x07,  "224 kbps" },
     {  0x08, 0x08,  "256 kbps" },
     {  0x09, 0x09,  "320 kbps" },
     {  0x0A, 0x0A,  "384 kbps" },
     {  0x0B, 0x0B,  "448 kbps" },
     {  0x0C, 0x0C,  "512 kbps" },
     {  0x0D, 0x0D,  "576 kbps" },
     {  0x0E, 0x0E,  "640 kbps" },
     {  0x0F, 0x0F,  "768 kbps" },
     {  0x10, 0x10,  "960 kbps" },
     {  0x11, 0x11,  "1024 kbps" },
     {  0x12, 0x12,  "1152 kbps" },
     {  0x13, 0x13,  "1280 kbps" },
     {  0x14, 0x14,  "1344 kbps" },
     {  0x15, 0x15,  "1408 kbps" },
     {  0x16, 0x16,  "1411.2 kbps" },
     {  0x17, 0x17,  "1472 kbps" },
     {  0x18, 0x18,  "1536 kbps" },
     {  0x19, 0x19,  "1920 kbps" },
     {  0x1A, 0x1A,  "2048 kbps" },
     {  0x1B, 0x1B,  "3072 kbps" },
     {  0x1C, 0x1C,  "3840 kbps" },
     {  0x1D, 0x1D,  "open" },
     {  0x1E, 0x1E,  "variable" },
     {  0x1F, 0x1F,  "lossless" },
     {  0,0, NULL }
  };


  i &= 0x1F;	// ignore bit 6  (En 300 468 v1.7.1 Table G.3)
  return findTableID (Table, i);
}





/*
  -- AUDIO DTS Surround Mode
  -- ETSI EN 300 468, TS 102 114
*/

char *dvbstrDVB_DTS_Audio_SurroundMode (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "1 / mono" },
     {  0x02, 0x02,  "2 / L+R (stereo)" },
     {  0x03, 0x03,  "2 / (L+R)+(L-R)" },
     {  0x04, 0x04,  "2 / LT+RT (left and right total)" },
     {  0x05, 0x05,  "3 / L+R+C" },
     {  0x06, 0x06,  "3 / L+R+S" },
     {  0x07, 0x07,  "4 / C+L+R+S" },
     {  0x08, 0x08,  "4 / L+R+SL+SR" },
     {  0x09, 0x09,  "5 / C+L+R+SL+SR" },
     {  0x0A, 0x0F,  "user defined" },
     {  0x10, 0x1F,  "user defined" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}


/*
  -- AUDIO DTS Extended Surround Mode
  -- ETSI EN 300 468, TS 102 114
*/

char *dvbstrDVB_DTS_Audio_ExtendedSurroundFlag (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "no extended surround" },
     {  0x01, 0x01,  "matrixed extended surround" },
     {  0x02, 0x02,  "discrete extended surround" },
     {  0x03, 0x03,  "undefined" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}





/*
  -- Ancillary Data ID
  -- ETSI EN 300 468   6.2.1
*/

char *dvbstrAncillaryData_ID (u_int i)
{

  // $$$ coded in descriptor

  return NULL;
}



/*
  -- Announcement Type
  -- ETSI EN 300 468   6.2.2
*/

char *dvbstrAnnouncement_TYPE (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "Emergency alarm" },
     {  0x01, 0x01,  "Road Traffic Flash" },
     {  0x02, 0x02,  "Public Transport Flash" },
     {  0x03, 0x03,  "Warning message" },
     {  0x04, 0x04,  "News flash" },
     {  0x05, 0x05,  "Weather flash" },
     {  0x06, 0x06,  "Event announcement" },
     {  0x07, 0x07,  "Personal call" },
     {  0x08, 0x0F,  "reserved" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}



char *dvbstrAnnouncementReference_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "Announcement is broadcast in the usual audio stream of the service" },
     {  0x01, 0x01,  "Announcement is broadcast in the separate audio stream that is part of the service" },
     {  0x02, 0x02,  "Announcement is broadcast by means of a different service within the same transport stream" },
     {  0x03, 0x03,  "Announcement is broadcast by means of a different service within a different transport stream" },
     {  0x04, 0x0F,  "reserved" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}





/*
 ------------------------------------------------------------------------
   Transport Stream  Stuff
 ------------------------------------------------------------------------
*/


/*
  -- Transport Stream PID  Table  ISO 13818-1  2.4.3.2
*/

char *dvbstrTSpid_ID (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x0000, 0x0000,  "Programm Association Table" },
     {  0x0001, 0x0001,  "Conditional Access Table" },
     {  0x0002, 0x000F,  "reserved" },
     {  0x0010, 0x1FFE,  "NIT, PMT or Elementary PID, etc." },
     {  0x1FFF, 0x1FFF,  "Null-packet" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}



/*
  -- Transport Error Indicator [TEI] ISO 13818-1
*/

char *dvbstrTS_TEI (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "packet ok" },
     {  0x01, 0x01,  "Packet has uncorrectable errors" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- PayLoad Unit Start Indicator[PUSI] ISO 13818-1
*/

char *dvbstrTS_PUSI (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "Packet data continues" },
     {  0x01, 0x01,  "Packet data starts" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- Scrambling Control Table  ISO 13818-1
  -- Scrambling Control Table  ETSI ETR 289  5.1,
                               ETSI ETR 154  4.1.4.2.3
*/

char *dvbstrTS_ScramblingCtrl_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "No scrambling of TS packet payload" },
     {  0x01, 0x01,  "Reserved for future DVB use" },
     {  0x02, 0x02,  "TS packet scrambled with Even Key" },
     {  0x03, 0x03,  "TS packet scrambled with Odd Key" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}


/*
  -- Adaptation Field Type  ISO 13818-1  2.4.3.2
*/

char *dvbstrTS_AdaptationField_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "no adaptation_field, payload only" },
     {  0x02, 0x02,  "adaptation_field only, no payload" },
     {  0x03, 0x03,  "adaptation_field followed by payload" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}





/*
 ------------------------------------------------------------------------
  PES   Stuff
 ------------------------------------------------------------------------
*/

char *dvbstrPESH264_NALU_ID (u_int i)
{
  STR_TABLE  Table[] = {
      { 0x00, 0x00,  "unspecified"},
      { 0x01, 0x01,  "slice_non_IDR_picture"},
      { 0x02, 0x02,  "slice_data_partition_a"},
      { 0x03, 0x03,  "slice_data_partition_b"},
      { 0x04, 0x04,  "slice_data_partition_c"},
      { 0x05, 0x05,  "slice_IDR_picture"},
      { 0x06, 0x06,  "SEI"},
      { 0x07, 0x07,  "SPS"},
      { 0x08, 0x08,  "PPS"},
      { 0x09, 0x09,  "AUD"},
      { 0x0A, 0x0A,  "end_of_seq"}, 
      { 0x0B, 0x0B,  "end_of_stream"}, 
      { 0x0C, 0x0C,  "filler_data"},
      { 0x0D, 0x0D,  "SPS_extension"},
      { 0x0E, 0x0E,  "prefix_nal_unit"},
      { 0x0F, 0x0F,  "subset_SPS"},
      { 0x10, 0x12,  "reserved"},
      { 0x13, 0x13,  "slice_auxiliary_coded"}, 
      { 0x14, 0x14,  "slice_scalable_extension"},
      { 0x15, 0x17,  "reserved"},
      { 0x18, 0x1F,  "unspecified"},
      { 0x00, 0x00,  "NULL"} 
  };

  return findTableID (Table, i);
}


char *dvbstrPESH264_Slice_ID (u_int i)
{
  STR_TABLE  Table[] = {
      {0x00, 0x00, "P (P slice)"},
      {0x01, 0x01, "B (B slice)"},
      {0x02, 0x02, "I (I slice)"},
      {0x03, 0x03, "SP (SP slice)"},
      {0x04, 0x04, "SI (SI slice)"},
      {0x05, 0x05, "P (P slice)"},
      {0x06, 0x06, "B (B slice)"},
      {0x07, 0x07, "I (I slice)"},
      {0x08, 0x08, "SP (SP slice)"},
      {0x09, 0x09, "SI (SI slice)"},
      {0x00, 0x00, "NULL"}
  };

  return findTableID (Table, i);
}

char *dvbstrH264_Profile_IDC (u_int i) 
{
  STR_TABLE  Table[] = {
	  {44, 44, "CAVLC 4:4:4 Intra profile"},
      {66, 66, "Baseline profile"},
      {77, 77, "Main profile"},
      {88, 88, "Extended profile"},
      {100, 100, "High 10 Intra profile"},
      {110, 110, "High 10 Intra profile"},
      {122, 122, "High 4:2:2 profile"},
      {244, 244, "High 4:4:4 Predictive profile"},
      {0x00, 0x00, "NULL"}
  };

  return findTableID (Table, i);
}

/*
  -- PES Stream_id  ISO 13818-1  2.4.3.6
  -- PS Stream_id   ISO 13818-2 
*/

char *dvbstrPESstream_ID (u_int i)

{
  STR_TABLE  Table[] = {
	// -- updated 2004-07-26  from ITU-T Rec H.222.0 | ISO/IEC 13818-1:2000/FDAM 1
	// -- updated 2004-08-11  from ITU-T Rec H.222.0 AMD3
	// -- updated 2005-10-22  ISO13818-2 (code 0x00-0xB8)
	//
     // on changes:  adapt dmx_pes.c!!! etc. (search for PESstream_ID)
 
     // streamID 00-B8 (ISO 13818-2)
     {  0x00, 0x00,  "picture_start_code"},
     {  0x01, 0xAF,  "slice_start_code"},
     {  0xB0, 0xB1,  "reserved"},
     {  0xB2, 0xB2,  "user_data_start_code"},
     {  0xB3, 0xB3,  "sequence_header_code"},
     {  0xB4, 0xB4,  "sequence_error_code"},
     {  0xB5, 0xB5,  "extension_start_code"},
     {  0xB6, 0xB6,  "reserved"},
     {  0xB7, 0xB7,  "sequence_end_code"},
     {  0xB8, 0xB8,  "group_start_code"},
     // special PS_stream_IDs (these are not PES stream IDs)
     {  0xB9, 0xB9,  "MPEG_program_stream_end (PS)" },
     {  0xBA, 0xBA,  "MPEG_pack_start (PS)" },
     {  0xBB, 0xBB,  "MPEG_system_header_start (PS)" },
     // PES_stream_IDs
     {  0xBC, 0xBC,  "program_stream_map" },
     {  0xBD, 0xBD,  "private_stream_1" },
     {  0xBE, 0xBE,  "padding_stream" },
     {  0xBF, 0xBF,  "private_stream_2" },
     {  0xC0, 0xDF,  "ISO/IEC 13818-3 or ISO/IEC 11172-3 audio stream" },
     {  0xE0, 0xEF,  "ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2 video stream" },
     {  0xF0, 0xF0,  "ECM_stream" },
     {  0xF1, 0xF1,  "EMM_stream" },
     {  0xF2, 0xF2,  "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex-A or ISO/IEC 13818-6_DSMCC stream" },
     {  0xF3, 0xF3,  "ISO/IEC 13522 stream" },
     {  0xF4, 0xF4,  "ITU-T Rec. H.222.1 type A" },
     {  0xF5, 0xF5,  "ITU-T Rec. H.222.1 type B" },
     {  0xF6, 0xF6,  "ITU-T Rec. H.222.1 type C" },
     {  0xF7, 0xF7,  "ITU-T Rec. H.222.1 type D" },
     {  0xF8, 0xF8,  "ITU-T Rec. H.222.1 type E" },
     {  0xF9, 0xF9,  "ancillary_stream" },
     {  0xFA, 0xFA,  "ISO/IEC14496-1_SL-packetized_stream" },
     {  0xFB, 0xFB,  "ISO/IEC14496-1_FlexMux_stream" },
     {  0xFC, 0xFC,  "metadata stream" },
     {  0xFD, 0xFD,  "extended_stream_id" },
     {  0xFE, 0xFE,  "reserved data stream" },
     {  0xFF, 0xFF,  "program_stream_directory" },
     {  0,0, NULL }

  };


  return findTableID (Table, i);
}


/*
  -- PES Stream_id  H.222.0 AMD2
  -- 2004-08-11  ITU-T Rec H.222.0 AMD2
*/

char *dvbstrPESstream_ID_Extension (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "IPMP Control Information stream" },
     {  0x01, 0x01,  "IPMP stream" },
     {  0x02, 0x7F,  "reserved_data_stream" },
     {  0x80, 0xFF,  "private_stream" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}



/*
  -- PES Scrambling CTRL   ISO 13818-1  2.4.3.7
  --  --> ETR 289  5.1
 */

char *dvbstrPESscrambling_ctrl_TYPE (u_int i)

{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "not scrambled" },
     {  0x01, 0x01,  "Reserved for future DVB use" },
     {  0x02, 0x02,  "PES packet scrambled with Even Key" },
     {  0x03, 0x03,  "PES packet scrambled with Odd Key" },
     {  0,0, NULL }
  };


  return findTableID (Table, i);
}



/*
  -- Private Data Specifier Table  (from dvb.org)
  -- ETR 162
*/

char *dvbstrPrivateDataSpecifier_ID (u_int i)

{
  STR_TABLE  Table[] = {
#include "dvb_org/private_data_spec_id.inc"
	{  0,0, NULL }
  };


  return findTableID (Table, i);
}




/*
  -- Country Code Table  (from dvb.org)
*/

char *dvbstrCountryCode_ID (u_int i)

{
  STR_TABLE  Table[] = {
	{ 0x0004, 0x0004,  "Afghanistan" },
	{ 0x0008, 0x0008,  "Albania" },
	{ 0x000a, 0x000a,  "Antarctica (the territory South of 60 deg S)" },
	{ 0x000c, 0x000c,  "Algeria" },
	{ 0x0010, 0x0010,  "American Samoa" },
	{ 0x0014, 0x0014,  "Andorra" },
	{ 0x0018, 0x0018,  "Angola" },
	{ 0x001c, 0x001c,  "Antigua and Barbuda" },
	{ 0x001f, 0x001f,  "Azerbaijan" },
	{ 0x0020, 0x0020,  "Argentina" },
	{ 0x0024, 0x0024,  "Australia" },
	{ 0x0028, 0x0028,  "Austria" },
	{ 0x002c, 0x002c,  "Bahamas" },
	{ 0x0030, 0x0030,  "Bahrain" },
	{ 0x0032, 0x0032,  "Bangladesh" },
	{ 0x0033, 0x0033,  "Armenia" },
	{ 0x0034, 0x0034,  "Barbados" },
	{ 0x0038, 0x0038,  "Belgium" },
	{ 0x003c, 0x003c,  "Bermuda" },
	{ 0x0040, 0x0040,  "Bhutan" },
	{ 0x0044, 0x0044,  "Bolivia" },
	{ 0x0046, 0x0046,  "Bosnia and Herzegowina [sic]" },
	{ 0x0048, 0x0048,  "Botswana" },
	{ 0x004a, 0x004a,  "Bouvet Island (Bouvetoya)" },
	{ 0x004c, 0x004c,  "Brazil" },
	{ 0x0054, 0x0054,  "Belize" },
	{ 0x0056, 0x0056,  "British Indian Ocean Territory (Chagos Archipelago)" },
	{ 0x005a, 0x005a,  "solomon Islands (was British Solomon Islands)" },
	{ 0x005c, 0x005c,  "British Virgin Islands" },
	{ 0x0060, 0x0060,  "Brunei Darussalam" },
	{ 0x0064, 0x0064,  "Bulgaria" },
	{ 0x0068, 0x0068,  "Myanmar (was Burma)" },
	{ 0x006c, 0x006c,  "Burundi" },
	{ 0x0070, 0x0070,  "Belarus" },
	{ 0x0074, 0x0074,  "Cambodia" },
	{ 0x0078, 0x0078,  "Cameroon" },
	{ 0x007c, 0x007c,  "Canada" },
	{ 0x0084, 0x0084,  "Cape Verde" },
	{ 0x0088, 0x0088,  "Cayman Islands" },
	{ 0x008c, 0x008c,  "Central African Republic" },
	{ 0x0090, 0x0090,  "sri Lanka" },
	{ 0x0094, 0x0094,  "Chad" },
	{ 0x0098, 0x0098,  "Chile" },
	{ 0x009c, 0x009c,  "China" },
	{ 0x009e, 0x009e,  "Taiwan" },
	{ 0x00a2, 0x00a2,  "Christmas Island" },
	{ 0x00a6, 0x00a6,  "Cocos (Keeling) Islands" },
	{ 0x00aa, 0x00aa,  "Colombia" },
	{ 0x00ae, 0x00ae,  "Comoros" },
	{ 0x00af, 0x00af,  "Mayotte" },
	{ 0x00b2, 0x00b2,  "Congo" },
	{ 0x00b4, 0x00b4,  "Congo (was Zaire)" },
	{ 0x00b8, 0x00b8,  "Cook Islands" },
	{ 0x00bc, 0x00bc,  "Costa Rica" },
	{ 0x00bf, 0x00bf,  "Hrvatska (Croatia)" },
	{ 0x00c0, 0x00c0,  "Cuba" },
	{ 0x00c4, 0x00c4,  "Cyprus" },
	{ 0x00cb, 0x00cb,  "Czech Republic" },
	{ 0x00cc, 0x00cc,  "Benin (was Dahomey)" },
	{ 0x00d0, 0x00d0,  "Denmark" },
	{ 0x00d4, 0x00d4,  "Dominica" },
	{ 0x00d6, 0x00d6,  "Dominican Republic" },
	{ 0x00da, 0x00da,  "Ecuador" },
	{ 0x00de, 0x00de,  "El Salvador" },
	{ 0x00e2, 0x00e2,  "Equatorial Guinea" },
	{ 0x00e7, 0x00e7,  "Ethiopia" },
	{ 0x00e8, 0x00e8,  "Eritrea" },
	{ 0x00e9, 0x00e9,  "Estonia" },
	{ 0x00ea, 0x00ea,  "Faeroe Islands" },
	{ 0x00ee, 0x00ee,  "Falkland Islands (Malvinas)" },
	{ 0x00ef, 0x00ef,  "south Georgia and the South Sandwich Islands" },
	{ 0x00f2, 0x00f2,  "Fiji" },
	{ 0x00f6, 0x00f6,  "Finland" },
	{ 0x00fa, 0x00fa,  "France" },
	{ 0x00fe, 0x00fe,  "French Guiana" },
	{ 0x0102, 0x0102,  "French Polynesia" },
	{ 0x0104, 0x0104,  "French Southern Territories" },
	{ 0x0106, 0x0106,  "Djibouti" },
	{ 0x010a, 0x010a,  "Gabon" },
	{ 0x010c, 0x010c,  "Georgia" },
	{ 0x010e, 0x010e,  "Gambia" },
	{ 0x0113, 0x0113,  "Palestinian Territory" },
	{ 0x0114, 0x0114,  "Germany" },
	{ 0x0120, 0x0120,  "Ghana" },
	{ 0x0124, 0x0124,  "Gibraltar" },
	{ 0x0128, 0x0128,  "Kiribati (was Gilbert Islands)" },
	{ 0x012c, 0x012c,  "Greece" },
	{ 0x0130, 0x0130,  "Greenland" },
	{ 0x0134, 0x0134,  "Grenada" },
	{ 0x0138, 0x0138,  "Guadaloupe" },
	{ 0x013c, 0x013c,  "Guam" },
	{ 0x0140, 0x0140,  "Guatemala" },
	{ 0x0144, 0x0144,  "Guinea" },
	{ 0x0148, 0x0148,  "Guyana" },
	{ 0x014c, 0x014c,  "Haiti" },
	{ 0x014e, 0x014e,  "Heard and McDonald Islands" },
	{ 0x0150, 0x0150,  "Holy See (Vatican City State)" },
	{ 0x0154, 0x0154,  "Honduras" },
	{ 0x0158, 0x0158,  "Hong Kong" },
	{ 0x015c, 0x015c,  "Hungary" },
	{ 0x0160, 0x0160,  "Iceland" },
	{ 0x0164, 0x0164,  "India" },
	{ 0x0168, 0x0168,  "Indonesia" },
	{ 0x016c, 0x016c,  "Iran" },
	{ 0x0170, 0x0170,  "Iraq" },
	{ 0x0174, 0x0174,  "Ireland" },
	{ 0x0178, 0x0178,  "Israel" },
	{ 0x017c, 0x017c,  "Italy" },
	{ 0x0180, 0x0180,  "Ivory Coast" },
	{ 0x0184, 0x0184,  "Jamaica" },
	{ 0x0188, 0x0188,  "Japan" },
	{ 0x018e, 0x018e,  "Kazakhstan" },
	{ 0x0190, 0x0190,  "Jordan" },
	{ 0x0194, 0x0194,  "Kenya" },
	{ 0x0198, 0x0198,  "Korea" },
	{ 0x019a, 0x019a,  "Korea" },
	{ 0x019e, 0x019e,  "Kuwait" },
	{ 0x01a1, 0x01a1,  "Kyrgyz Republic" },
	{ 0x01a2, 0x01a2,  "Lao People�s Democratic Republic" },
	{ 0x01a6, 0x01a6,  "Lebanon" },
	{ 0x01aa, 0x01aa,  "Lesotho" },
	{ 0x01ac, 0x01ac,  "Latvia" },
	{ 0x01ae, 0x01ae,  "Liberia" },
	{ 0x01b2, 0x01b2,  "Libyan Arab Jamahiriya" },
	{ 0x01b6, 0x01b6,  "Liechtenstein" },
	{ 0x01b8, 0x01b8,  "Lithuania" },
	{ 0x01ba, 0x01ba,  "Luxembourg" },
	{ 0x01be, 0x01be,  "Macau" },
	{ 0x01c2, 0x01c2,  "Madagascar" },
	{ 0x01c6, 0x01c6,  "Malawi" },
	{ 0x01ca, 0x01ca,  "Malaysia" },
	{ 0x01ce, 0x01ce,  "Maldives" },
	{ 0x01d2, 0x01d2,  "Mali" },
	{ 0x01d6, 0x01d6,  "Malta" },
	{ 0x01da, 0x01da,  "Martinique" },
	{ 0x01de, 0x01de,  "Mauritania" },
	{ 0x01e0, 0x01e0,  "Mauritius" },
	{ 0x01e4, 0x01e4,  "Mexico" },
	{ 0x01ec, 0x01ec,  "Monaco" },
	{ 0x01f0, 0x01f0,  "Mongolia" },
	{ 0x01f2, 0x01f2,  "Moldova" },
	{ 0x01f4, 0x01f4,  "Montserrat" },
	{ 0x01f8, 0x01f8,  "Morocco" },
	{ 0x01fc, 0x01fc,  "Mozambique" },
	{ 0x0200, 0x0200,  "Oman (was Muscat and Oman)" },
	{ 0x0204, 0x0204,  "Namibia" },
	{ 0x0208, 0x0208,  "Nauru" },
	{ 0x020c, 0x020c,  "Nepal" },
	{ 0x0210, 0x0210,  "Netherlands" },
	{ 0x0212, 0x0212,  "Netherlands Antilles" },
	{ 0x0215, 0x0215,  "Aruba" },
	{ 0x021c, 0x021c,  "New Caledonia" },
	{ 0x0224, 0x0224,  "Vanuatu (was New Hebrides)" },
	{ 0x022a, 0x022a,  "New Zealand" },
	{ 0x022e, 0x022e,  "Nicaragua" },
	{ 0x0232, 0x0232,  "Niger" },
	{ 0x0236, 0x0236,  "Nigeria" },
	{ 0x023a, 0x023a,  "Niue" },
	{ 0x023e, 0x023e,  "Norfolk Island" },
	{ 0x0242, 0x0242,  "Norway" },
	{ 0x0244, 0x0244,  "Northern Mariana Islands" },
	{ 0x0245, 0x0245,  "United States Minor Outlying Islands" },
	{ 0x0247, 0x0247,  "Micronesia" },
	{ 0x0248, 0x0248,  "Marshall Islands" },
	{ 0x0249, 0x0249,  "Palau" },
	{ 0x024a, 0x024a,  "Pakistan" },
	{ 0x024f, 0x024f,  "Panama" },
	{ 0x0256, 0x0256,  "Papua New Guinea" },
	{ 0x0258, 0x0258,  "Paraguay" },
	{ 0x025c, 0x025c,  "Peru" },
	{ 0x0260, 0x0260,  "Philippines" },
	{ 0x0264, 0x0264,  "Pitcairn Island" },
	{ 0x0268, 0x0268,  "Poland" },
	{ 0x026c, 0x026c,  "Portugal" },
	{ 0x0270, 0x0270,  "Guinea-Bissau" },
	{ 0x0272, 0x0272,  "East Timor (was Portuguese Timor)" },
	{ 0x0276, 0x0276,  "Puerto Rico" },
	{ 0x027a, 0x027a,  "Qatar" },
	{ 0x027e, 0x027e,  "Reunion" },
	{ 0x0282, 0x0282,  "Romania" },
	{ 0x0283, 0x0283,  "Russian Federation" },
	{ 0x0286, 0x0286,  "Rwanda" },
	{ 0x028e, 0x028e,  "st. Helena" },
	{ 0x0293, 0x0293,  "saint Kitts and Nevis" },
	{ 0x0294, 0x0294,  "Anguilla" },
	{ 0x0296, 0x0296,  "saint Lucia" },
	{ 0x029a, 0x029a,  "st. Pierre and Miquelon" },
	{ 0x029e, 0x029e,  "saint Vincent and the Grenadines" },
	{ 0x02a2, 0x02a2,  "san Marino" },
	{ 0x02a6, 0x02a6,  "sao Tome and Principe" },
	{ 0x02aa, 0x02aa,  "saudi Arabia" },
	{ 0x02ae, 0x02ae,  "senegal" },
	{ 0x02b2, 0x02b2,  "seychelles" },
	{ 0x02b6, 0x02b6,  "sierra Leone" },
	{ 0x02be, 0x02be,  "singapore" },
	{ 0x02bf, 0x02bf,  "slovakia (Slovak Republic)" },
	{ 0x02c0, 0x02c0,  "Viet Nam" },
	{ 0x02c1, 0x02c1,  "slovenia" },
	{ 0x02c2, 0x02c2,  "somalia" },
	{ 0x02c6, 0x02c6,  "south Africa" },
	{ 0x02cc, 0x02cc,  "Zimbabwe (was Southern Rhodesia)" },
	{ 0x02d4, 0x02d4,  "spain" },
	{ 0x02dc, 0x02dc,  "Western Sahara (was Spanish Sahara)" },
	{ 0x02e0, 0x02e0,  "sudan" },
	{ 0x02e4, 0x02e4,  "suriname" },
	{ 0x02e8, 0x02e8,  "svalbard & Jan Mayen Islands" },
	{ 0x02ec, 0x02ec,  "swaziland" },
	{ 0x02f0, 0x02f0,  "sweden" },
	{ 0x02f4, 0x02f4,  "switzerland" },
	{ 0x02f8, 0x02f8,  "syrian Arab Republic" },
	{ 0x02fa, 0x02fa,  "Tajikistan" },
	{ 0x02fc, 0x02fc,  "Thailand" },
	{ 0x0300, 0x0300,  "Togo" },
	{ 0x0304, 0x0304,  "Tokelau (Tokelau Islands)" },
	{ 0x0308, 0x0308,  "Tonga" },
	{ 0x030c, 0x030c,  "Trinidad and Tobago" },
	{ 0x0310, 0x0310,  "United Arab Emirates (was Trucial States)" },
	{ 0x0314, 0x0314,  "Tunisia" },
	{ 0x0318, 0x0318,  "Turkey" },
	{ 0x031b, 0x031b,  "Turkmenistan" },
	{ 0x031c, 0x031c,  "Turks and Caicos Islands" },
	{ 0x031e, 0x031e,  "Tuvalu (was part of Gilbert & Ellice Islands)" },
	{ 0x0320, 0x0320,  "Uganda" },
	{ 0x0324, 0x0324,  "Ukraine" },
	{ 0x0327, 0x0327,  "Macedonia" },
	{ 0x0332, 0x0332,  "Egypt" },
	{ 0x033a, 0x033a,  "United Kingdom of Great Britain & N. Ireland" },
	{ 0x0342, 0x0342,  "Tanzania" },
	{ 0x0348, 0x0348,  "United States of America" },
	{ 0x0352, 0x0352,  "US Virgin Islands" },
	{ 0x0356, 0x0356,  "Burkina Faso (was Upper Volta)" },
	{ 0x035a, 0x035a,  "Uruguay" },
	{ 0x035c, 0x035c,  "Uzbekistan" },
	{ 0x035e, 0x035e,  "Venezuela" },
	{ 0x036c, 0x036c,  "Wallis and Futuna Islands" },
	{ 0x0372, 0x0372,  "samoa" },
	{ 0x0377, 0x0377,  "Yemen" },
	{ 0x037b, 0x037b,  "ex Yugoslavia" },
	{ 0x037e, 0x037e,  "Zambia" },
	{ 0x0384, 0x0384,  "Scandinavia" },
	{ 0x0385, 0x0385,  "North America (Canada, Carribbean,Mexico,United States of America)" },
	{ 0x0386, 0x0386,  "All countries" },
	{ 0x0387, 0x0387,  "South America" },
	{ 0x0388, 0x0388,  "Latin America" },
	{ 0x0389, 0x0389,  "Europe" },
	{ 0x0389, 0x0389,  "Middle East" },
	{ 0x038a, 0x038a,  "North Africa" },
	{ 0x038b, 0x038b,  "Oceania (Australia, New Zealand, Melanesia, Micronesia, Polynesia)" },

     	{  0,0, NULL }
  };


  return findTableID (Table, i);
}




/*
  -- Bouquet ID Table (from dvb.org)
  -- ETR 162
*/

char *dvbstrBouquetTable_ID (u_int i)

{
  STR_TABLE  Table[] = {
#include "dvb_org/bouquet_id.inc"
     	{  0,0, NULL }
  };


  return findTableID (Table, i);
}







/*
  -- Trick Mode Control
  -- ISO 13818-1
*/

char *dvbstrPESTrickModeControl (u_int i)

{
  STR_TABLE  Table[] = {
	{ 0x0, 0x0,   "fast forward" },
	{ 0x1, 0x1,   "slow motion" },
	{ 0x2, 0x2,   "freeze frame" },
	{ 0x3, 0x3,   "fast reverse" },
	{ 0x4, 0x4,   "slow reverse" },
	{ 0x5, 0x7,   "reserved" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- Data Identifier 
  -- ETR 162 and EN 300 472 and EN 301 775).
*/

char *dvbstrPESDataIdentifier (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x0F,   "reserved" },
	{ 0x10, 0x1F,   "EBU data EN 300 472 (teletext)" },
	{ 0x20, 0x20,   "DVB subtitling EN 300 743" },
	{ 0x21, 0x21,   "DVB synchronous data stream" },
	{ 0x22, 0x22,   "DVB synchronized data stream" },
	{ 0x23, 0x7F,   "reserved" },
	{ 0x80, 0x98,   "user defined" },
	{ 0x99, 0x9B,   "EBU teletext/VPS/WSS/closed caption/VBI sample data" }, // EN 301 775
	{ 0x9C, 0xFF,   "user defined" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- dvbstrPES_EBUDataUnitID  (Teletext, VPS, WSS, etc.)
  -- EN 300 472  and EN 301 775.
*/

// $$$ TODO same as data_service_id ??  (EN 300 468)

char *dvbstrPES_EBUDataUnitID (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x01,   "reserved" },
	{ 0x02, 0x02,   "EBU Teletext non-subtitle data" },
	{ 0x03, 0x03,   "EBU Teletext subtitle data" },
	{ 0x04, 0x7F,   "reserved" },
	{ 0x80, 0xBE,   "user defined" },
	{ 0xC0, 0xC0,   "inverted teletext" },
	{ 0xC1, 0xC2,   "reserved" },
	{ 0xC3, 0xC3,   "VPS (Video Programming System)" },
	{ 0xC4, 0xC4,   "WSS (Wide Screen Signalling)" },
	{ 0xC5, 0xC5,   "CC (Closed Caption)" },
	{ 0xC6, 0xC6,   "monochrome 4:2:2 samples" },
	{ 0xC7, 0xFE,   "reserved" },
	{ 0xFF, 0xFF,   "data_unit for stuffing" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- dvbstrTELETEXT_framingcode
  -- EN 300 472  and EN 301 775.
*/

char *dvbstrTELETEXT_framingcode (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0xE4, 0xE4,   "EBU Teletext" },
	{ 0x1B, 0x1B,   "inverted EBU Teletext" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- dvbstrTELETEXT_packetnr
  -- EN 300 472  and EN 301 775.
*/

char *dvbstrTELETEXT_packetnr (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "page header" },
	{ 0x01, 0x19,   "normal packet intended for direct display" },
	{ 0x1A, 0x1F,   "non-displayable packet (see: EN 300 706)" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- dvbstrTELETEXT_lang_code
  -- EN 300 472  and EN 301 775.
*/

char *dvbstrTELETEXT_lang_code (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "English (?)" },
	{ 0x01, 0x01,   "French (?)" },
	{ 0x02, 0x02,   "Swedish/Finnish/Hungarian (?)" },
	{ 0x03, 0x03,   "Czech/Slovak/Turkish (?)" },
	{ 0x04, 0x04,   "German (?)" },
	{ 0x05, 0x05,   "Portuguese/Spanish (?)" },
	{ 0x06, 0x06,   "Italian (?)" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}





/*
  -- dvbstrVPS_pcs_audio
  -- EN 300 231
*/

char *dvbstrVPS_pcs_audio (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "unknown" },
	{ 0x01, 0x01,   "mono" },
	{ 0x02, 0x02,   "stereo" },
	{ 0x03, 0x03,   "dual channel" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- dvbstrVPS_pcs_audio
  -- EN 300 231
*/

char *dvbstrVPS_cni_countrycode (u_int i)
{
  int b_1_4;
  int b_5_8;
  char *s = "";

  // $$$ TODO  check if b_1_4 start really at "1"
  char  *t[6][16] = {
//	  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E      F
/*0*/	{ "",   "",   "",   "",   "",   "",   "",   "",   "",   "",   "",   "",   "",   "",   "",    ""  },
/*1*/	{ "",   "",   "DZ", "AD", "IL", "IT", "BE", "BY", "AZR","AL", "AT", "HU", "MT", "DE", "CNR","EG" },
/*2*/	{ "",   "GR", "CY", "SM", "CH", "JO", "FI", "LU", "BG", "DK", "GI", "IQ", "GB", "LY", "RO", "FR" },
/*3*/	{ "",   "MA", "CZ", "PL", "VA", "",   "SY", "TN", "MA", "LI", "IS", "MC", "",   "",   "ES", "NO" },
/*4*/	{ "",   "",   "IE", "TR", "",   "",   "YU", "UA", "NL", "",   "LB", "",   "",   "",   "SE", ""   },
/*5*/	{ "",   "",   "",   "",   "",   "",   "",   "RU", "PT", "",   "",   "",   "",   "",   "",   ""   }
  };

  b_1_4 = i & 0x0F;
  b_5_8 = (i >> 4) & 0x0F; 

  if (b_1_4 < 5) {
	  s = t[b_1_4][b_5_8];
  }

  return s;
}




/*
  -- VPS PTY Content Nibble Types 
  -- ETSI EN 300 231   
*/

char *dvbstrVPS_pty (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "no information" },
	{ 0x00, 0x0F,   "undefined content" },
	{ 0x10, 0x7F,   "see: ETSI EN 300 231" },	// $$$ TODO
	{ 0x80, 0xFE,   "provider specific" },
	{ 0xFF, 0xFF,   "PTY not used" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- VPS Network/Program Provider 
  -- ETSI EN 300 231   
*/

char *dvbstrVPS_npp (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0xFF,   "see: ETSI TR 101 231" },	// $$$ TODO
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- WSS Aspect Ratio  b0..b3 
  -- Warning!  Bitvalues are reversed due to lsb...msb issue
  -- values includes parity bit!
  -- see: ETSI EN 300 294  
*/

char *dvbstrWSS_aspect_ratio (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x01, 0x01,   "4:3 // full format // pos. not applicable // active lines: 576" },
	{ 0x02, 0x02,   "16:9 // letterbox // top // active lines: 430" },
	{ 0x04, 0x04,   "14:9 // letterbox // top // active lines: 504" },
	{ 0x07, 0x07,   "14:9 // full format // center // active lines: 576" },
	{ 0x08, 0x08,   "14:9 // letterbox // center // active lines: 504" },
	{ 0x0B, 0x0B,   ">16:9 // letterbox // center // active lines: not defined" },
	{ 0x0D, 0x0D,   "16:9 // letterbox // center // active lines: 430" },
	{ 0x0E, 0x0E,   "16:9 // full format (anamorphic) // pos. not applicable // active lines: 576" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- WSS  film bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_film_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "camera mode" },
	{ 0x01, 0x01,   "film mode" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- WSS  color coding bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_color_coding_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "standard coding" },
	{ 0x01, 0x01,   "Motion Adaptive Color Plus" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- WSS  helper bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_helper_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "no helper" },
	{ 0x01, 0x01,   "Modulated helper" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- WSS  subtitles within teletext bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_subtitleTeletext_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "no subtitles within teletext" },
	{ 0x01, 0x01,   "subtitles within Teletext" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- WSS  subtitling mode
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_subtitling_mode (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "no open subtitles" },
	{ 0x01, 0x01,   "subtitles out of active image area" },
	{ 0x02, 0x02,   "subtitles in active image area" },
	{ 0x03, 0x03,   "reserved" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- WSS  surround bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_surround_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "no surround sound information" },
	{ 0x01, 0x01,   "surround sound mode" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- WSS  copyright bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_copyright_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "no copyright asserted or status unknown" },
	{ 0x01, 0x01,   "copyright asserted" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- WSS  copyright generation bit
  -- ETSI EN 300 294  
*/

char *dvbstrWSS_copy_generation_bit (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "copying not restricted" },
	{ 0x01, 0x01,   "copying restricted" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}







/*
  -- Timeslice used bit
  -- ETSI EN 301 192  v1.4.1
*/

char *dvbstrTimeSlice_bit_used (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "not used" },
	{ 0x01, 0x01,   "used" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
  -- MPE_FEC algo
  -- ETSI EN 301 192  v1.4.1
*/

char *dvbstrMPE_FEC_algo (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "MPE-FEC not used" },
	{ 0x01, 0x01,   "MPE-FEC used // Reed-Solomon (255,191,64)" },
	{ 0x02, 0x03,   "reserved" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- MPE_FEC  max burst size
  -- ETSI EN 301 192  v1.4.1
*/

char *dvbstrMPE_FEC_max_burst_size (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "512 kbits" },
	{ 0x01, 0x01,   "1024 kbits" },
	{ 0x02, 0x02,   "1536 kbits" },
	{ 0x03, 0x03,   "2048 kbits" },
	{ 0x04, 0x07,   "reserved" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- MPE_FEC  frame rows
  -- ETSI EN 301 192 v1.4.1
*/

char *dvbstrMPE_FEC_frame_rows (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "256" },
	{ 0x01, 0x01,   "512" },
	{ 0x02, 0x02,   "768" },
	{ 0x03, 0x03,   "1024" },
	{ 0x04, 0x07,   "reserved" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- MPE_FEC  max average rate
  -- ETSI EN 301 192  v1.4.1
*/

char *dvbstrMPE_FEC_max_average_rate (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "16 kbps" },
	{ 0x01, 0x01,   "32 kbps" },
	{ 0x02, 0x02,   "64 kbps" },
	{ 0x03, 0x03,   "128 kbps" },
	{ 0x04, 0x04,   "256 kbps" },
	{ 0x05, 0x05,   "512 kbps" },
	{ 0x06, 0x06,   "1024 kbps" },
	{ 0x07, 0x07,   "2048 kbps" },
	{ 0x08, 0x0F,   "reserved" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
  -- MPE_FEC  table_frame_boundary
  -- ETSI EN 301 192  v1.4.1
*/

char *dvbstrMPE_FEC_table_frame_boundary (u_int i)
{
  STR_TABLE  Table[] = {
	{ 0x00, 0x00,   "" },
	{ 0x01, 0x01,   "last section (current burst or MEC_FEC frame)" },
     	{  0,0, NULL }
  };

  return findTableID (Table, i);
}







/*
 -- Running Status  (TV ANYTIME)
 -- ETSI TS 102 323 v1.1.1  TV ANYTIME
*/

char *dvbstrTVA_RunningStatus(u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "not yet running" },
     {  0x02, 0x02,  "(re-)starts shortly" },
     {  0x03, 0x03,  "paused" },
     {  0x04, 0x04,  "running" },
     {  0x05, 0x05,  "cancelled" },
     {  0x06, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- CRID type  (TV ANYTIME)
 -- ETSI TS 102 323 v1.1.1  TV ANYTIME
*/

char *dvbstrTVA_crid_type (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "not defined" },
     {  0x01, 0x01,  "CRID references the item of content that this event is an instance of" },
     {  0x02, 0x02,  "CRID references a series that this event belongs to" },
     {  0x03, 0x03,  "CRID references a recommendation. This CRID can be a group or a single item of content" },
     {  0x04, 0x1F,  "DVB reserved" },
     {  0x20, 0x3F,  "user defined" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- CRID location (TV ANYTIME)
 -- ETSI TS 102 323 v1.1.1  TV ANYTIME
*/

char *dvbstrTVA_crid_location (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "Carried explicitly within descriptor" },
     {  0x01, 0x01,  "Carried in Content Identifier Table (CIT)" },
     {  0x02, 0x03,  "DVB reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- content id type (TV ANYTIME)
 -- ETSI TS 102 323 v1.1.1  TV ANYTIME
*/

char *dvbstrTVA_content_id_type (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "context_id is a value of bouquet_id" },
     {  0x01, 0x01,  "context_id is a value of original_network_id" },
     {  0x02, 0x02,  "context_id is a value of a value of network_id" },
     {  0x03, 0x7F,  "DVB reserved" },
     {  0x80, 0xFF,  "user defined" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}





//
// H.222.0 AMD1 - AMD3  update
//


/*
 -- metadata_application_format 
 -- H.222.0 AMD1
*/

char *dvbstrMPEG_metadata_application_format (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x0000, 0x00FF,  "reserved" },
     {  0x0100, 0xFFFE,  "User defined" },
     {  0xFFFF, 0xFFFF,  "Defined by the metadata_application_format_identifier" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- Content_time_base_indicator values 
 -- H.222.0 AMD1
*/

char *dvbstrMPEG_Content_time_base_indicator (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "No content time base defined" },
     {  0x01, 0x01,  "Use of STC" },
     {  0x02, 0x02,  "Use of NPT" },
     {  0x03, 0x07,  "reserved" },
     {  0x08, 0x0F,  "private use" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- metadata section_fragmentation_indication
 -- H.222.0 AMD1
*/

char *dvbstrMPEG_metadata_section_frag_indication (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "next metadata section with data from one metadata Access Unit" },
     {  0x01, 0x01,  "last metadata section with data from one metadata Access Unit" },
     {  0x02, 0x02,  "first metadata section with data from one metadata Access Unit" },
     {  0x03, 0x03,  "single metadata section carrying a complete metadata Access Unit" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}






/*
 * ------------------------------------------------------------------------------
 */



/*
 -- frame_rate_code
 -- ISO 13818-2 Table 6.4
*/

char *dvbstrMPEG_FrameRateCode (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "forbidden" },
     {  0x01, 0x01,  "23.976" },
     {  0x02, 0x02,  "24" },
     {  0x03, 0x03,  "25" },
     {  0x04, 0x04,  "29.97" },
     {  0x05, 0x05,  "30" },
     {  0x06, 0x06,  "50" },
     {  0x07, 0x07,  "59.94" },
     {  0x08, 0x08,  "60" },
     {  0x09, 0x0F,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- Picture Coding Type 
 -- ISO 13818-2 
*/

char *dvbstrMPEG_PictureCodingType (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "forbidden" },
     {  0x01, 0x01,  "intra-coded (I)" },
     {  0x02, 0x02,  "predictive-coded (P)" },
     {  0x03, 0x03,  "bidirectionally-predictive-coded (B)" },
     {  0x04, 0x04,  "dc-intra-coded (D) (ISO/IEC 11172-2)" },
     {  0x05, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
 -- MPEG-2 Extension Start Code Identifier
 -- ISO 13818-2 
*/

char *dvbstrMPEG_ExtensionStartCodeIdentifier (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "Sequence Extension ID" },
     {  0x02, 0x02,  "Sequence Display Extension ID" },
     {  0x03, 0x03,  "Quant Matrix Extension ID" },
     {  0x04, 0x04,  "Copyright Extension ID" },
     {  0x05, 0x05,  "Sequence Scalable Extension ID" },
     {  0x06, 0x06,  "reserved" },
     {  0x07, 0x07,  "Picture Display Extension ID" },
     {  0x08, 0x08,  "Picture Coding Extension ID" },
     {  0x09, 0x09,  "Picture Spatial Scalable Extension ID" },
     {  0x0A, 0x0A,  "Picture Temporal Scalable Extension ID" },
     {  0x0B, 0x0F,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




/*
 -- MPEG-2 Profile Indication
 --  profile_and_level_indication
 -- ISO 13818-2 
*/

char *dvbstrMPEG_ProfileIndication (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "High" },
     {  0x02, 0x02,  "Spatially Scalable" },
     {  0x03, 0x03,  "SNR Scalable" },
     {  0x04, 0x04,  "Main" },
     {  0x05, 0x05,  "Simple" },
     {  0x06, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- MPEG-2 Level Indication
 --  profile_and_level_indication
 -- ISO 13818-2 
*/

char *dvbstrMPEG_LevelIndication (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x03,  "reserved" },
     {  0x04, 0x04,  "High" },
     {  0x05, 0x05,  "reserved" },
     {  0x06, 0x06,  "High 1440" },
     {  0x07, 0x07,  "reserved" },
     {  0x08, 0x08,  "Main" },
     {  0x09, 0x09,  "reserved" },
     {  0x0A, 0x0A,  "Low" },
     {  0x0B, 0x0F,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- MPEG Chroma Format
 -- ISO 13818-2 
*/

char *dvbstrMPEG_ChromaFormat (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "4:2:0" },
     {  0x02, 0x02,  "4:2:2" },
     {  0x03, 0x03,  "4:4:4" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- MPEG VideoFormat
 -- ISO 13818-2 
*/

char *dvbstrMPEG_VideoFormat (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "component" },
     {  0x01, 0x01,  "PAL" },
     {  0x02, 0x02,  "NTSC" },
     {  0x03, 0x03,  "SECAM" },
     {  0x04, 0x04,  "MAC" },
     {  0x05, 0x05,  "Unspecified video format" },
     {  0x06, 0x07,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- MPEG Color Primaries
 -- ISO 13818-2 
*/

char *dvbstrMPEG_ColorPrimaries (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "forbidden" },
     {  0x01, 0x01,  "Recommendation ITU-R BT.709" },
     {  0x02, 0x02,  "Unspecified Video" },
     {  0x03, 0x03,  "reserved" },
     {  0x04, 0x04,  "Recommendation ITU-R BT.470-2 System M" },
     {  0x05, 0x05,  "Recommendation ITU-R BT.470-2 System B,G" },
     {  0x06, 0x06,  "SMPTE 170M" },
     {  0x07, 0x07,  "SMPTE 240M (1987)" },
     {  0x08, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- MPEG Transfer Characteristics
 -- ISO 13818-2 
*/

char *dvbstrMPEG_TransferCharacteristics (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "forbidden" },
     {  0x01, 0x01,  "Recommendation ITU-R BT.709" },
     {  0x02, 0x02,  "Unspecified Video" },
     {  0x03, 0x03,  "reserved" },
     {  0x04, 0x04,  "Recommendation ITU-R BT.470-2 System M" },
     {  0x05, 0x05,  "Recommendation ITU-R BT.470-2 System B,G" },
     {  0x06, 0x06,  "SMPTE 170M" },
     {  0x07, 0x07,  "SMPTE 240M (1987)" },
     {  0x08, 0x08,  "Linear transfer characteristics" },
     {  0x09, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
 -- MPEG Matrix Coefficients
 -- ISO 13818-2 
*/

char *dvbstrMPEG_MatrixCoefficients (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "forbidden" },
     {  0x01, 0x01,  "Recommendation ITU-R BT.709" },
     {  0x02, 0x02,  "Unspecified Video" },
     {  0x03, 0x03,  "reserved" },
     {  0x04, 0x04,  "FCC" },
     {  0x05, 0x05,  "Recommendation ITU-R BT.470-2 System B,G" },
     {  0x06, 0x06,  "SMPTE 170M" },
     {  0x07, 0x07,  "SMPTE 240M (1987)" },
     {  0x08, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
 -- MPEG Scalable Mode
 -- ISO 13818-2 
*/

char *dvbstrMPEG_ScalableMode (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "data partitioning" },
     {  0x01, 0x01,  "spatial scalability" },
     {  0x02, 0x02,  "SNR scalability" },
     {  0x03, 0x03,  "temporal scalability" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 -- MPEG Intra DC Precision
 -- ISO 13818-2 
*/

char *dvbstrMPEG_Intra_DC_Precision (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "8 bits" },
     {  0x01, 0x01,  "9 bits" },
     {  0x02, 0x02,  "10 bits" },
     {  0x03, 0x03,  "11 bits" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
 -- MPEG Picture Structure
 -- ISO 13818-2 
*/

char *dvbstrMPEG_PictureStructure (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "reserved" },
     {  0x01, 0x01,  "top field" },
     {  0x02, 0x02,  "bottom field" },
     {  0x03, 0x03,  "frame picture" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
 -- MPEG Copyright Extension  original_or_copy
 -- ISO 13818-2 
*/

char *dvbstrMPEG_Original_Or_Copy (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "copy" },
     {  0x01, 0x01,  "original" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}







/*
 -- TS MIP Synchronization
 -- TS 101 191
*/

char *dvbstrTS_MIP_Syncronization (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "SFN synchronization" },
     {  0x01, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
 * -- MegaFrame Iniialization Packet Functions
 * -- TS 101 191
 */
char *dvbstrTS_MIP_FunctionTag (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "tx_time_offset_function" },
     {  0x01, 0x01,  "tx_frequency_offset_function" },
     {  0x02, 0x02,  "tx_power_function" },
     {  0x03, 0x03,  "private_data_function" },
     {  0x04, 0x04,  "cell_id_function" },
     {  0x05, 0x05,  "enable_function" },
     {  0x06, 0x06,  "bandwidth_function" },
     {  0x07, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}



/*
 * -- MIP, Channel bandwidth
 * -- TS 101 191
 */
char *dvbstrTS_MIP_ChannelBandwidth (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "5 MHz" },
     {  0x01, 0xFF,  "reserved" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}





/* Annotation:

  --- $$$ TODO: store table strings in external text files, to be
  ---           more flexible

*/

/*
 $$$ TODO 

ISO/IEC 13818-1:2000/Amd.5:2005 (E):
  Table 2-62 � MPEG-4_audio_profile_and_level assignment values

  Table Amd.5-2 � MPEG-2_AAC_additional_information field values


*/
