/*
$Id: dsmcc_carousel_descriptor.h,v 1.16 2006/03/06 00:04:52 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  DSM-CC
 -- DSM-CC Carousel Descriptors 



$Log: dsmcc_carousel_descriptor.h,v $
Revision 1.16  2006/03/06 00:04:52  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.15  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.14  2004/02/17 23:54:13  rasc
Bug (not fixed yet): DSM-CC  DII Carousel Descriptor Loop is strange

Revision 1.13  2004/02/15 01:01:03  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed

Revision 1.12  2004/02/07 01:28:01  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.11  2004/01/22 22:58:29  rasc
deleting modul  (again?)
somehow  obsolete module re-appeared??? (or I forgot something)

Revision 1.10  2004/01/11 21:01:31  rasc
PES stream directory, PES restructured

Revision 1.9  2004/01/03 00:30:06  rasc
DSM-CC  STREAM descriptors module (started)

Revision 1.8  2004/01/02 22:25:35  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.7  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.6  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/12/27 18:17:17  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.4  2003/11/26 19:55:32  rasc
no message

Revision 1.3  2003/10/26 23:00:39  rasc
fix

Revision 1.2  2003/10/26 21:36:19  rasc
private DSM-CC descriptor Tags started,
INT-Section completed..

Revision 1.1  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/


#ifndef __DSMCC_CAROUSEL_DESCRIPTOR_H
#define __DSMCC_CAROUSEL_DESCRIPTOR_H 


int  descriptorDSMCC_CAROUSEL (u_char *b);

void descriptorDSMCC_type (u_char *b);
void descriptorDSMCC_name (u_char *b);
void descriptorDSMCC_info (u_char *b);
void descriptorDSMCC_module_link (u_char *b);
void descriptorDSMCC_crc32 (u_char *b);
void descriptorDSMCC_location (u_char *b);
void descriptorDSMCC_est_download_time (u_char *b);
void descriptorDSMCC_group_link (u_char *b);
void descriptorDSMCC_compressed_module (u_char *b);
void descriptorDSMCC_subgroup_association (u_char *b);

void descriptorDSMCC_MHP_label (u_char *b);
void descriptorDSMCC_MHP_caching_priority (u_char *b);
void descriptorDSMCC_MHP_content_type (u_char *b);


#endif


