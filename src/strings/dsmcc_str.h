/*
$Id: dsmcc_str.h,v 1.31 2006/03/06 20:25:38 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- dsmcc strings




$Log: dsmcc_str.h,v $
Revision 1.31  2006/03/06 20:25:38  rasc
DSM-CC Carousell, lots of Bugfixes, BIOP::Message not yet decodable (ddb has to collect Modules)

Revision 1.30  2006/03/06 00:05:03  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.29  2006/01/02 18:24:32  rasc
just update copyright and prepare for a new public tar ball

Revision 1.28  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42

Revision 1.27  2004/07/24 11:44:45  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.26  2004/02/24 23:03:08  rasc
private data of DSMCC::DSI
BIOP::ServiceGatewayInformation()
IOP::IOR()

Revision 1.25  2004/02/20 23:13:17  rasc
BIOP:  TapUse

Revision 1.24  2004/02/15 01:01:05  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed

Revision 1.23  2004/02/14 01:24:45  rasc
DSM-CC started  (DSI/DII, DDB)

Revision 1.22  2004/02/12 21:21:22  rasc
MHP AIT descriptors
some smaller changes

Revision 1.21  2004/02/07 01:28:07  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.20  2004/01/25 21:37:28  rasc
bugfixes, minor changes & enhancments

Revision 1.19  2004/01/17 23:06:10  rasc
minor stuff, some restructs in output

Revision 1.18  2004/01/15 21:27:22  rasc
DSM-CC stream descriptors

Revision 1.17  2004/01/12 22:49:53  rasc
get rid of stream descriptor module

Revision 1.16  2004/01/11 21:01:33  rasc
PES stream directory, PES restructured

Revision 1.15  2004/01/02 22:25:39  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.14  2004/01/02 16:40:43  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.13  2004/01/02 02:18:34  rasc
more DSM-CC  INT/UNT descriptors

Revision 1.12  2004/01/01 20:09:40  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.11  2003/12/27 18:17:18  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.10  2003/12/26 23:27:40  rasc
DSM-CC  UNT section

Revision 1.9  2003/12/17 23:15:05  rasc
PES DSM-CC  ack and control commands  according ITU H.222.0 Annex B

Revision 1.8  2003/11/29 23:11:43  rasc
no message

Revision 1.7  2003/11/26 23:54:49  rasc
-- bugfixes on Linkage descriptor

Revision 1.6  2003/11/26 19:55:34  rasc
no message

Revision 1.5  2003/11/01 21:40:27  rasc
some broadcast/linkage descriptor stuff

Revision 1.4  2003/10/29 20:54:57  rasc
more PES stuff, DSM descriptors, testdata

Revision 1.3  2003/10/26 21:36:20  rasc
private DSM-CC descriptor Tags started,
INT-Section completed..

Revision 1.2  2003/10/25 19:11:50  rasc
no message

Revision 1.1  2003/10/16 19:02:28  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162



*/


#ifndef __DSMCC_STR_H
#define __DSMCC_STR_H 


char *dsmccStrDSMCC_CAROUSEL_DescriptorTAG (u_int i);
char *dsmccStrDSMCC_INT_UNT_DescriptorTAG (u_int i);
char *dsmccStrMHP_AIT_DescriptorTAG (u_int i);


char *dsmccStrMHPOrg (u_int id);
char *dsmccStrAction_Type (u_int id);
char *dsmccStrProcessing_order (u_int id);
char *dsmccStrPayload_scrambling_control (u_int id);
char *dsmccStrAddress_scrambling_control (u_int id);
char *dsmccStrLinkage0CTable_TYPE (u_int i);
char *dsmccStrMultiProtEncapsMACAddrRangeField (u_int i);
char *dsmccStrPlatform_ID (u_int id);
char *dsmccStrCarouselType_ID (u_int id);
char *dsmccStrHigherProtocol_ID (u_int id);
char *dsmccStrUpdateType_ID (u_int id);

char *dsmccStr_Command_ID  (u_int id);
char *dsmccStr_SelectMode_ID  (u_int id);
char *dsmccStr_DirectionIndicator (u_int id);

char *dsmccStr_DescriptorType (u_int id);
char *dsmccStr_SpecifierType (u_int id);
char *dsmccStr_AccessMode (u_int id);

char *dsmccStr_UpdateFlag (u_int id);
char *dsmccStr_UpdateMethod (u_int id);
char *dsmccStr_TimeUnits (u_int id);

char *dsmccStr_GroupModuleLinkPosition (u_int id);
char *dsmccStr_compression_method (u_int id);

char *dsmccStr_streamMode (u_int id);
char *dsmccStr_postDiscontinuityIndicator (u_int id);

char *dsmccStrOUI  (u_int id);
char *dsmccStr_LLC_SNAP_prot (u_int id);



char *dsmccStrMHP_application_type (u_int id);
char *dsmccStrMHP_application_id (u_int id);
char *dsmccStrMHP_application_control_code (u_int id);
char *dsmccStrMHP_visibility_state (u_int id);
char *dsmccStrMHP_protocol_id (u_int id);
char *dsmccStrMHP_storage_property (u_int id);
char *dsmccStrMHP_caching_transparency_level (u_int id);


char *dsmccStr_adaptationType (u_int id);
char *dsmccStr_dsmccType (u_int id);
char *dsmccStr_messageID (u_int id);
char *dsmccStr_transactionID_originator (u_int id);


char *dsmccStrIOP_ProfileID (u_int id);
char *dsmccStrBIOP_TAP_Use (u_int id);
char *dsmccStrBIOP_TAP_SelectorType (u_int id);
char *dsmccStrBIOP_EndianType (u_int id);
char *dsmccStrBIOP_TypeID_Alias (u_int id);
char *dsmccStrBIOP_BindingType (u_int id);
char *dsmccStrBIOP_MAGIC (u_int id);


#endif




