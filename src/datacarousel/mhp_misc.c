/*
$Id: mhp_misc.c,v 1.4 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)




$Log: mhp_misc.c,v $
Revision 1.4  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.3  2004/02/15 01:01:01  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed

Revision 1.2  2004/02/12 21:21:19  rasc
MHP AIT descriptors
some smaller changes

Revision 1.1  2004/02/10 22:57:52  rasc
MHP descriptor, missing DVB descriptor done



*/




#include "dvbsnoop.h"
#include "mhp_misc.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/output.h"




/*
 *  used in AIT and in descriptors
 *  ETSI TS 102 812
 */

int  mhp_application_identifier (int  v, u_char *b)
{
 	outBit_Sx_NL  (v,"organisation_id: ",	b,  0, 32);
 	outBit_S2x_NL (v,"appliction_id: ",	b, 32, 16,
			(char *(*)(u_long)) dsmccStrMHP_application_id );
	return 6;
}




/*
 *  used in AIT and in descriptors
 *  ETSI TS 102 812
 */

int  mhp_application_profile_version (int  v, u_char *b)
{
 	outBit_Sx_NL (v,"application_profile: ",	b,   0, 16);
 	outBit_Sx_NL (v,"version.major: ",		b,  16,  8);
 	outBit_Sx_NL (v,"version.minor: ",		b,  24,  8);
 	outBit_Sx_NL (v,"version.micro: ",		b,  32,  8);

	return 5;
}











