/*
$Id: dsmcc_unm_dlcancel.c,v 1.2 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc download Cancel
 -- to be called from U-N-Message



$Log: dsmcc_unm_dlcancel.c,v $
Revision 1.2  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/02/15 18:58:28  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)





*/




#include "dvbsnoop.h"
#include "dsmcc_unm_dlcancel.h"
#include "dsmcc_misc.h"
#include "misc/output.h"
#include "misc/hexprint.h"





/*
 * ISO/IEC 13818-6
 * dsmcc_DownloadCancel
 */


int dsmcc_DownloadCancel (int v, u_char *b, u_int len)
{
   int   	len_org = len;
   int		len2;




	// already read  dsmcc_MessageHeader (v, b, len, &dmh);

	outBit_Sx_NL (v,"downloadId: ",			b,  0, 32);
	outBit_Sx_NL (v,"moduleId: ",			b, 32, 16);
	outBit_Sx_NL (v,"blockNumber: ",		b, 48, 16);
	outBit_Sx_NL (v,"downloadCancelReason: ",	b, 64,  8);
	outBit_Sx_NL (v,"reserved: ",			b, 72,  8);

	len2 = outBit_Sx_NL (v,"privateDataLength: ",	b, 80,  16);

	b += 12;
	len -= 12;

	print_databytes (v, "private data: ", b, len);

	return len_org;
}





