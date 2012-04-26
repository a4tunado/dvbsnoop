/*
$Id: descriptor_misc.h,v 1.3 2006/03/06 00:04:52 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Descriptors  misc. routines, helpers, etc.


$Log: descriptor_misc.h,v $
Revision 1.3  2006/03/06 00:04:52  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.2  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/01/18 00:30:48  rasc
no message




*/


#ifndef _DESCRIPTOR_MISC_H
#define _DESCRIPTOR_MISC_H 


void  out_nl_calc_NPT (int v, unsigned long long npt);


#endif


