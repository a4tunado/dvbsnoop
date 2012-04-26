/*
$Id: dvb_descriptor.h,v 1.16 2006/03/06 00:04:52 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- DVB Descriptors  ETSI 300 468



$Log: dvb_descriptor.h,v $
Revision 1.16  2006/03/06 00:04:52  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.15  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.14  2005/12/22 16:21:50  rasc
Update and new descriptors EN 300 468 v1.7.1

Revision 1.13  2005/11/08 23:15:24  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.12  2005/01/17 19:41:22  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.11  2004/07/25 20:12:58  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.10  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.9  2004/04/05 17:32:13  rasc
mass typo fix adaption --> adaptation

Revision 1.8  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.7  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.6  2003/12/27 18:17:17  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.5  2003/11/26 23:54:47  rasc
-- bugfixes on Linkage descriptor

Revision 1.4  2003/11/26 19:55:32  rasc
no message

Revision 1.3  2003/10/25 19:11:49  rasc
no message

Revision 1.2  2003/10/19 21:05:53  rasc
- some datacarousell stuff started

Revision 1.1  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/


#ifndef _DVB_DESCRIPTOR_H
#define _DVB_DESCRIPTOR_H 


int   descriptorDVB (u_char *b);

void  descriptorDVB_NetName (u_char *b);
void  descriptorDVB_ServList (u_char *b);
void  descriptorDVB_Stuffing (u_char *b);
void  descriptorDVB_SatDelivSys (u_char *b);
void  descriptorDVB_CableDelivSys (u_char *b);
void  descriptorDVB_VBI_Data (u_char *b);
void  descriptorDVB_VBI_Teletext (u_char *b);
void  descriptorDVB_BouquetName (u_char *b);
void  descriptorDVB_Service (u_char *b);
void  descriptorDVB_CountryAvail (u_char *b);
void  descriptorDVB_Linkage (u_char *b);
  void sub_descriptorDVB_Linkage0x08 (u_char *b, int len);
  void sub_descriptorDVB_Linkage0x09 (u_char *b, int len);
  void sub_descriptorDVB_Linkage0x0B (u_char *b, int len);
  void sub_descriptorDVB_Linkage0x0C (u_char *b, int len);
void  descriptorDVB_NVOD_Reference (u_char *b);
void  descriptorDVB_TimeShiftedService (u_char *b);
void  descriptorDVB_ShortEvent (u_char *b);
void  descriptorDVB_ExtendedEvent (u_char *b);
void  descriptorDVB_TimeShiftedEvent (u_char *b);
void  descriptorDVB_Component (u_char *b);
void  descriptorDVB_Mosaic (u_char *b);
void  descriptorDVB_StreamIdent (u_char *b);
void  descriptorDVB_CAIdentifier (u_char *b);
void  descriptorDVB_Content(u_char *b);
void  descriptorDVB_ParentalRating(u_char *b);
void  descriptorDVB_Teletext (u_char *b);
void  descriptorDVB_Telephone(u_char *b);
void  descriptorDVB_LocalTimeOffset (u_char *b);
void  descriptorDVB_Subtitling(u_char *b);
void  descriptorDVB_TerrestDelivSys (u_char *b);
void  descriptorDVB_MultilingNetworkName (u_char *b);
void  descriptorDVB_MultilingBouquetName (u_char *b);
void  descriptorDVB_MultilingServiceName (u_char *b);
void  descriptorDVB_MultilingComponent (u_char *b);
void  descriptorDVB_PrivateDataSpecifier (u_char *b);
void  descriptorDVB_ServiceMove (u_char *b);
void  descriptorDVB_FrequencyList (u_char *b);
void  descriptorDVB_ShortSmoothingBuffer(u_char *b);
void  descriptorDVB_PartialTransportStream(u_char *b);
void  descriptorDVB_DataBroadcast (u_char *b);
void  descriptorDVB_Scrambling(u_char *b);
void  descriptorDVB_DataBroadcastID(u_char *b);
void  descriptorDVB_TransportStream(u_char *b);
void  descriptorDVB_DSNG(u_char *b);
void  descriptorDVB_PDC(u_char *b);
void  descriptorDVB_AC3(u_char *b);
void  descriptorDVB_AncillaryData(u_char *b);
void  descriptorDVB_CellList(u_char *b);
void  descriptorDVB_CellFrequencyLink(u_char *b);
void  descriptorDVB_AnnouncementSupport(u_char *b);
void  descriptorDVB_ApplicationSignalling(u_char *b);
void  descriptorDVB_AdaptationFieldData(u_char *b);
void  descriptorDVB_ServiceIdentifier(u_char *b);
void  descriptorDVB_ServiceAvailability(u_char *b);
		 // TV ANYTIME  TS 102 323
void  descriptorDVB_DefaultAuthority (u_char *b);
void  descriptorDVB_RelatedContent(u_char *b);
void  descriptorDVB_TVA_ID(u_char *b);
void  descriptorDVB_ContentIdentifier(u_char *b);
		 // EN 301 192 v1.4.1  MPE_FEC
void  descriptorDVB_TimesliceFecIdentifier(u_char *b);
void  descriptorDVB_ECM_RepetitionRate(u_char *b);
		 // EN 300 468 v1.7.1
void  descriptorDVB_S2SatelliteDeliverySystem(u_char *b);
void  descriptorDVB_Enhanced_AC3(u_char *b);
void  descriptorDVB_DTS_Audio (u_char *b);
void  descriptorDVB_AAC (u_char *b);
void  descriptorDVB_Extension (u_char *b);



#endif

