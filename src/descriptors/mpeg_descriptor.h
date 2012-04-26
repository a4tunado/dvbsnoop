/*
$Id: mpeg_descriptor.h,v 1.13 2006/01/02 18:23:58 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)

 -- MPEG Descriptors  ISO/IEC 13818-2




$Log: mpeg_descriptor.h,v $
Revision 1.13  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.12  2005/11/10 23:34:37  rasc
Some H.222.1 AMD 4+5 update

Revision 1.11  2004/08/12 22:57:18  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.10  2004/08/01 21:33:08  rasc
minor TVA stuff (TS 102 323)

Revision 1.9  2004/07/25 20:12:58  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.8  2004/01/15 21:27:22  rasc
DSM-CC stream descriptors

Revision 1.7  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.6  2004/01/01 20:09:20  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/11/26 19:55:32  rasc
no message

Revision 1.4  2003/11/26 16:27:45  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.3  2003/10/27 22:43:49  rasc
carousel info descriptor and more

Revision 1.2  2003/10/17 18:16:54  rasc
- started more work on newer ISO 13818  descriptors
- some reorg work started

Revision 1.1  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/

#ifndef _MPEG_DESCRIPTOR_H
#define _MPEG_DESCRIPTOR_H 


int   descriptorMPEG (u_char *b);

void  descriptorMPEG_VideoStream (u_char *b);
void  descriptorMPEG_AudioStream (u_char *b);
void  descriptorMPEG_Hierarchy (u_char *b);
void  descriptorMPEG_Registration (u_char *b);
void  descriptorMPEG_DataStreamAlignment (u_char *b);
void  descriptorMPEG_TargetBackgroundGrid (u_char *b);
void  descriptorMPEG_VideoWindow (u_char *b);
void  descriptorMPEG_CA (u_char *b);
void  descriptorMPEG_ISO639_Lang (u_char *b);
void  descriptorMPEG_SystemClock (u_char *b);
void  descriptorMPEG_MultiplexBufUtil (u_char *b);
void  descriptorMPEG_Copyright (u_char *b);
void  descriptorMPEG_MaxBitrate (u_char *b);
void  descriptorMPEG_PrivateDataIndicator (u_char *b);
void  descriptorMPEG_SmoothingBuf (u_char *b);
void  descriptorMPEG_STD (u_char *b);
void  descriptorMPEG_IBP (u_char *b);
	/* 13818-6 , TR 102 006 */
void  descriptorMPEG_Carousel_Identifier (u_char *b);
void  descriptorMPEG_Association_tag (u_char *b);
void  descriptorMPEG_Deferred_Association_tags (u_char *b);

	/* 13818-6  Stream descriptors */
void descriptorMPEG_NPT_reference (u_char *b);
void descriptorMPEG_NPT_endpoint (u_char *b);
void descriptorMPEG_stream_mode (u_char *b);
void descriptorMPEG_stream_event (u_char *b);

	/* MPEG4 */
void  descriptorMPEG_MPEG4_video (u_char *b);
void  descriptorMPEG_MPEG4_audio (u_char *b);
void  descriptorMPEG_IOD (u_char *b);
void  descriptorMPEG_SL (u_char *b);
void  descriptorMPEG_FMC (u_char *b);
void  descriptorMPEG_External_ES_ID (u_char *b);
void  descriptorMPEG_MuxCode (u_char *b);
void  descriptorMPEG_FMXBufferSize (u_char *b);
void  descriptorMPEG_MultiplexBuffer (u_char *b);
void  descriptorMPEG_ContentLabeling (u_char *b);


     /* TV ANYTIME, TS 102 323 */
void descriptorMPEG_TVA_metadata_pointer (u_char *b);
void descriptorMPEG_TVA_metadata (u_char *b);
void descriptorMPEG_TVA_metadata_STD (u_char *b);

     /* H.222.0 AMD3 */
void descriptorMPEG_AVC_video (u_char *b);
void descriptorMPEG_IPMP (u_char *b);
void descriptorMPEG_AVC_timing_and_HRD (u_char *b);

     /* H.222.0 AMD4 */
void descriptorMPEG_MPEG2_AAC_audio (u_char *b);
void descriptorMPEG_FlexMuxTiming (u_char *b);


#endif

