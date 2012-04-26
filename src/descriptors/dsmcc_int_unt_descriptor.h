/*
$Id: dsmcc_int_unt_descriptor.h,v 1.14 2006/03/06 00:04:52 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  DSM-CC   INT, UNT, ...
 -- DSM-CC INT/UNT Descriptors



$Log: dsmcc_int_unt_descriptor.h,v $
Revision 1.14  2006/03/06 00:04:52  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.13  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.12  2005/01/17 19:41:22  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.11  2004/01/03 00:30:06  rasc
DSM-CC  STREAM descriptors module (started)

Revision 1.10  2004/01/02 22:25:35  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.9  2004/01/02 02:18:34  rasc
more DSM-CC  INT/UNT descriptors

Revision 1.8  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.7  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.6  2003/12/29 22:14:53  rasc
more dsm-cc INT UNT descriptors

Revision 1.5  2003/12/28 00:01:14  rasc
some minor changes/adds...

Revision 1.4  2003/12/27 22:02:43  rasc
dsmcc INT UNT descriptors started

Revision 1.3  2003/12/27 18:17:17  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.2  2003/11/26 19:55:32  rasc
no message

Revision 1.1  2003/10/29 20:56:18  rasc
more PES stuff, DSM descriptors, testdata



*/


#ifndef __DSM_INT_UNT_DESCRIPTOR_H
#define __DSM_INT_UNT_DESCRIPTOR_H 


int  descriptorDSMCC_INT_UNT (u_char *b);

void descriptorDSMCC_scheduling (u_char *b);
void descriptorDSMCC_update (u_char *b);
void descriptorDSMCC_ssu_location (u_char *b);
void descriptorDSMCC_message(u_char *b);
void descriptorDSMCC_ssu_event_name (u_char *b);
void descriptorDSMCC_target_smartcard (u_char *b);
void descriptorDSMCC_target_MAC_address (u_char *b);
void descriptorDSMCC_target_serial_number (u_char *b);
void descriptorDSMCC_target_IP_address (u_char *b);
void descriptorDSMCC_target_IPv6_address (u_char *b);
void descriptorDSMCC_ssu_subgroup_association (u_char *b);
void descriptorDSMCC_IP_MAC_platform_name (u_char *b);
void descriptorDSMCC_IP_MAC_platform_provider_name (u_char *b);
void descriptorDSMCC_target_MAC_address_range (u_char *b);
void descriptorDSMCC_target_IP_slash (u_char *b);
void descriptorDSMCC_target_IP_source_slash (u_char *b);
void descriptorDSMCC_target_IPv6_slash (u_char *b);
void descriptorDSMCC_target_IPv6_source_slash (u_char *b);
void descriptorDSMCC_IP_MAC_StreamLocation (u_char *b);
void descriptorDSMCC_ISP_access_mode (u_char *b);


#endif


