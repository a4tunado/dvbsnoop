/*
$Id: dvb_str.h,v 1.35 2006/02/12 23:17:12 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- dvb strings



$Log: dvb_str.h,v $
Revision 1.35  2006/02/12 23:17:12  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.34  2005/12/27 23:30:30  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.33  2005/12/22 16:21:51  rasc
Update and new descriptors EN 300 468 v1.7.1

Revision 1.32  2005/11/23 23:06:11  rasc
ISO13818-2  MPEG2 sequence header

Revision 1.31  2005/11/08 23:15:26  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.30  2005/09/02 14:11:36  rasc
TS code redesign, xPCR and DTS timestamps decoding

Revision 1.29  2004/08/25 19:51:09  rasc
 - Update: EN 300 468 v1.6.1 Terrestrial delivery system descriptor

Revision 1.28  2004/08/24 21:30:24  rasc
more Metadata

Revision 1.27  2004/08/13 11:05:29  rasc
Metadata_STD_descriptor

Revision 1.26  2004/08/12 22:57:19  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.25  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42

Revision 1.24  2004/07/26 20:58:03  rasc
RNT completed..  (TS 102 323)

Revision 1.23  2004/07/25 20:12:59  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.22  2004/07/24 11:44:45  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.21  2004/04/05 17:32:13  rasc
mass typo fix adaption --> adaptation

Revision 1.20  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.19  2004/03/10 21:05:53  rasc
WSS (Wide Screen Signalling)  data decoding

Revision 1.18  2004/03/09 20:59:23  rasc
VPS decoding (someone check the NPP & PTY code output please...)

Revision 1.17  2004/02/04 22:36:29  rasc
more EBU/teletext stuff

Revision 1.16  2004/02/02 23:34:11  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff

Revision 1.15  2004/01/01 20:09:40  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.14  2003/11/26 19:55:34  rasc
no message

Revision 1.13  2003/11/09 20:48:35  rasc
pes data packet (DSM-CC)

Revision 1.12  2003/10/29 20:54:57  rasc
more PES stuff, DSM descriptors, testdata

Revision 1.11  2003/10/25 19:11:50  rasc
no message

Revision 1.10  2003/10/19 21:05:53  rasc
- some datacarousell stuff started

Revision 1.9  2003/10/17 18:16:54  rasc
- started more work on newer ISO 13818  descriptors
- some reorg work started

Revision 1.8  2003/10/16 19:02:28  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.7  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/



#ifndef __DVB_STR_H
#define __DVB_STR_H 



char *dvbstrPID_assignment (u_int id);
char *dvbstrTableID (u_int id);
char *dvbstrMPEGDescriptorTAG (u_int tag);
char *dvbstrDVBDescriptorTAG (u_int tag);
char *dvbstrCurrentNextIndicator (u_int flag);
char *dvbstrWEST_EAST_FLAG (u_int tag);
char *dvbstrPolarisation_FLAG (u_int tag);
char *dvbstrModulationCable_FLAG(u_int flag);
char *dvbstrModulationSAT_FLAG (u_int tag);
char *dvbstrRollOffSAT_FLAG (u_int flag);
char *dvbstrFECinner_SCHEME (u_int tag);
char *dvbstrFECouter_SCHEME (u_int tag);
char *dvbstrLinkage_TYPE(u_int tag);
char *dvbstrHandover_TYPE(u_int tag);
char *dvbstrOrigin_TYPE(u_int tag);
char *dvbstrService_TYPE(u_int tag);
char *dvbstrStream_TYPE(u_int tag);
char *dvbstrStream_TYPE_SHORT (u_int flag);
char *dvbstrAudio_TYPE(u_int tag);
char *dvbstrCASystem_ID(u_int id);
char *dvbstrDataBroadcast_ID(u_int flag);
char *dvbstrOriginalNetwork_ID (u_int i);
char *dvbstrNetworkIdent_ID(u_int id);
char *dvbstrBroadcast_ID(u_int id);
char *dvbstrTeletext_TYPE(u_int id);
char *dvbstrTerrBandwidth_SCHEME(u_int id);
char *dvbstrTerrConstellation_FLAG(u_int id);
char *dvbstrTerrHierarchy_FLAG(u_int id);
char *dvbstrTerrCodeRate_FLAG(u_int id);
char *dvbstrTerrGuardInterval_FLAG(u_int id);
char *dvbstrTerrTransmissionMode_FLAG(u_int id);
char *dvbstrTerrPriority (u_int i);
char *dvbstrTerrTimeSlicingIndicator (u_int i);
char *dvbstrTerrMPE_FEC_Indicator (u_int i);
char *dvbstrTerr_DVBH_service_indication (u_int i);
char *dvbstrAspectRatioInfo_FLAG(u_int id);
char *dvbstrHierarchy_TYPE(u_int id);
char *dvbstrRunningStatus_FLAG (u_int id);
char *dvbstrDataStreamVIDEOAlignment_TYPE (u_int id);
char *dvbstrDataStreamAUDIOAlignment_TYPE (u_int id);
char *dvbstrDataService_ID (u_int id);
char *dvbstrContent_Component_TYPE (u_int id);
char *dvbstrLogCellPresInfo_TYPE(u_int id);
char *dvbstrCellLinkageInfo_TYPE(u_int id);
char *dvbstrTextCharset_TYPE(u_int id);
char *dvbstrContentNibble_TYPE(u_int id);
char *dvbstrParentalRating_TYPE(u_int id);
char *dvbstrDelivSysCoding_TYPE(u_int id);
char *dvbstrShortSmoothingBufSize_TYPE(u_int id);
char *dvbstrShortSmoothingBufLeakRate_TYPE(u_int id);
char *dvbstrDVB_AC3_ComponentType (u_int i);
char *dvbstrDVB_DTS_Audio_SampleRateCode(u_int i);
char *dvbstrDVB_DTS_Audio_BitRate (u_int i);
char *dvbstrDVB_DTS_Audio_SurroundMode (u_int i);
char *dvbstrDVB_DTS_Audio_ExtendedSurroundFlag (u_int i);
char *dvbstrAncillaryData_ID(u_int id);
char *dvbstrAnnouncement_TYPE(u_int id);
char *dvbstrAnnouncementReference_TYPE(u_int id);


/* -- Transport Stream Stuff */

char *dvbstrTSpid_ID (u_int id);
char *dvbstrTS_AdaptationField_TYPE (u_int id);
char *dvbstrTS_TEI (u_int id);
char *dvbstrTS_PUSI (u_int id);
char *dvbstrTS_ScramblingCtrl_TYPE (u_int id);

/* -- PES stuff */

char *dvbstrPESstream_ID(u_int id);
char *dvbstrPESstream_ID_Extension (u_int i);    // 2004-08-11 H.222.0 AMD2
char *dvbstrPESscrambling_ctrl_TYPE(u_int id);
char *dvbstrPESTrickModeControl (u_int i);
char *dvbstrPESDataIdentifier (u_int i);
char *dvbstrPES_EBUDataUnitID (u_int i);

char *dvbstrTELETEXT_framingcode (u_int i);
char *dvbstrTELETEXT_packetnr (u_int i);
char *dvbstrTELETEXT_lang_code (u_int i);


char *dvbstrVPS_pcs_audio (u_int i);
char *dvbstrVPS_cni_countrycode (u_int i);
char *dvbstrVPS_pty (u_int i);
char *dvbstrVPS_npp (u_int i);

char *dvbstrWSS_aspect_ratio (u_int i);
char *dvbstrWSS_film_bit (u_int i);
char *dvbstrWSS_color_coding_bit (u_int i);
char *dvbstrWSS_helper_bit (u_int i);
char *dvbstrWSS_subtitleTeletext_bit (u_int i);
char *dvbstrWSS_subtitling_mode (u_int i);
char *dvbstrWSS_surround_bit (u_int i);
char *dvbstrWSS_copyright_bit (u_int i);
char *dvbstrWSS_copy_generation_bit (u_int i);


/* -- Div Stuff */

char *dvbstrCountryCode_ID (u_int i);
char *dvbstrPrivateDataSpecifier_ID (u_int i);

char *dvbstrBouquetTable_ID (u_int i);
char *dvbstrStreamContent_Component_TYPE (u_int i);



/* EN 301 192 v1.4.1 updates */

char *dvbstrTimeSlice_bit_used (u_int i);
char *dvbstrMPE_FEC_algo (u_int i);
char *dvbstrMPE_FEC_max_burst_size (u_int i);
char *dvbstrMPE_FEC_frame_rows (u_int i);
char *dvbstrMPE_FEC_max_average_rate (u_int i);
char *dvbstrMPE_FEC_table_frame_boundary (u_int i);


/* TS 102 323 v1.1.1  TV ANYTIME */

char *dvbstrTVA_RunningStatus(u_int i);
char *dvbstrTVA_crid_type (u_int i);
char *dvbstrTVA_crid_location (u_int i);

char *dvbstrTVA_content_id_type (u_int i);



/* H.222.0 AMD1 - AMD3 update */

char *dvbstrMPEG_metadata_application_format (u_int i);
char *dvbstrMPEG_Content_time_base_indicator (u_int i);
char *dvbstrMPEG_metadata_section_frag_indication (u_int i);



/* ISO 13818-2 */

char *dvbstrMPEG_FrameRateCode (u_int i);
char *dvbstrMPEG_PictureCodingType (u_int i);
char *dvbstrMPEG_ExtensionStartCodeIdentifier (u_int i);
char *dvbstrMPEG_ProfileIndication (u_int i);
char *dvbstrMPEG_LevelIndication (u_int i);
char *dvbstrMPEG_ChromaFormat (u_int i);
char *dvbstrMPEG_VideoFormat (u_int i);
char *dvbstrMPEG_ColorPrimaries (u_int i);
char *dvbstrMPEG_TransferCharacteristics (u_int i);
char *dvbstrMPEG_MatrixCoefficients (u_int i);
char *dvbstrMPEG_ScalableMode (u_int i);
char *dvbstrMPEG_Intra_DC_Precision (u_int i);
char *dvbstrMPEG_PictureStructure (u_int i);
char *dvbstrMPEG_Original_Or_Copy (u_int i);


/* TS 101 191 */
char *dvbstrTS_MIP_Syncronization (u_int i);
char *dvbstrTS_MIP_FunctionTag (u_int i);
char *dvbstrTS_MIP_ChannelBandwidth (u_int i);



#endif



