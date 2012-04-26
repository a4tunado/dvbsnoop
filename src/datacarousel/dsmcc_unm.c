/*
$Id: dsmcc_unm.c,v 1.3 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc User Network  Message
 -- ISO/IEC 13818-6:2000   7. User-Network Download



$Log: dsmcc_unm.c,v $
Revision 1.3  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2004/02/15 18:58:27  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.1  2004/02/15 01:02:10  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed





*/




#include "dvbsnoop.h"
#include "dsmcc_unm.h"
#include "dsmcc_unm_dsi.h"
#include "dsmcc_unm_dii.h"
#include "dsmcc_unm_dlcancel.h"
#include "dsmcc_misc.h"
#include "misc/output.h"
#include "misc/hexprint.h"






/*
 * ISO/IEC 13818-6
 * user Network Message
 */


int dsmcc_UserNetworkMessage (int v, u_char *b, int len)
{
   int		x;
   int   	len_org = len;
   DSMCC_MSG_HD	dmh;



	x = dsmcc_MessageHeader (v, b, len, &dmh);
	b += x;
	len -= x;

	switch (dmh.messageId) {
		case DownloadInfoIndication:
			dsmcc_DownloadInfoIndication (v, b, len);
			break;

		case DownloadServerInitiate:
			dsmcc_DownloadServerInitiate (v, b, len);
			break;

		case DownloadCancel:
			dsmcc_DownloadCancel (v, b, len);
			break;

		default:
			out_nl (v,"unsupported messageId (please report!)");
			print_databytes (v, "Data bytes: ", b, len);
			break;
	}


	return len_org;
}








