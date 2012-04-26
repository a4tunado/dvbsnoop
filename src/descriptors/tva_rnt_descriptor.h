/*
$Id: tva_rnt_descriptor.h,v 1.2 2006/01/02 18:23:58 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  TS 102 323  TV-Anytime 
 -- RNT Descriptors



$Log: tva_rnt_descriptor.h,v $
Revision 1.2  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42




*/


#ifndef __TVA_RNT_DESCRIPTOR_H
#define __TVA_RNT_DESCRIPTOR_H


int  descriptorTVA (u_char *b);

void descriptorTVA_RAR_over_DVB_stream (u_char *b);
void descriptorTVA_RAR_over_IP_stream (u_char *b);
void descriptorTVA_RNT_scan (u_char *b);


#endif


