/*
$Id: mhp_ait_descriptor.h,v 1.7 2006/03/06 00:04:52 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  MHP AIT
 -- MHP AIT Descriptors 



$Log: mhp_ait_descriptor.h,v $
Revision 1.7  2006/03/06 00:04:52  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.6  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.5  2004/02/12 21:21:20  rasc
MHP AIT descriptors
some smaller changes

Revision 1.4  2004/02/11 20:27:32  rasc
MHP AIT descriptors...

Revision 1.3  2004/02/10 22:57:54  rasc
MHP descriptor, missing DVB descriptor done

Revision 1.2  2004/02/09 21:24:58  rasc
AIT descriptors
minor redesign on output routines

Revision 1.1  2004/02/07 01:28:01  rasc
MHP Application  Information Table
some AIT descriptors





*/


#ifndef __MHP_AIT_DESCRIPTOR_H
#define __MHP_AIT_DESCRIPTOR_H 


int  descriptorMHP_AIT (u_char *b);

void descriptorMHP_AIT_application (u_char *b);
void descriptorMHP_AIT_application_name (u_char *b);
void descriptorMHP_AIT_transport_protocol (u_char *b);
void descriptorMHP_AIT_dvb_j_application (u_char *b);
void descriptorMHP_AIT_dvb_j_application_location (u_char *b);
void descriptorMHP_AIT_external_application_authorisation (u_char *b);
void descriptorMHP_AIT_dvb_html_application (u_char *b);
void descriptorMHP_AIT_dvb_html_application_location (u_char *b);
void descriptorMHP_AIT_dvb_html_application_boundary (u_char *b);
void descriptorMHP_AIT_application_icons (u_char *b);
void descriptorMHP_AIT_pre_fetch (u_char *b);
void descriptorMHP_AIT_DII_location (u_char *b);
void descriptorMHP_AIT_delegated_application (u_char *b);
void descriptorMHP_AIT_plug_in (u_char *b);
void descriptorMHP_AIT_application_storage (u_char *b);
void descriptorMHP_AIT_ip_signalling (u_char *b);



#endif


