/*
$Id: dsmcc_ddb.c,v 1.4 2006/03/06 20:32:35 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc download Data Block Message



$Log: dsmcc_ddb.c,v $
Revision 1.4  2006/03/06 20:32:35  rasc
DSM-CC Carousel, lots of Bugfixes, BIOP::Message not yet decodable (ddb has to collect Modules)

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
#include "dsmcc_ddb.h"
#include "dsmcc_misc.h"
#include "misc/output.h"
#include "misc/hexprint.h"







/*
 * ISO/IEC 13818-6
 * dsmcc_downloadDataMessage
 * Download Data Block
 */


int dsmcc_DownloadDataMessage (int v, u_char *b, u_int len)
{
   int   	x;
   int   	len_org = len;
   DSMCC_MSG_HD	dmh;




	x = dsmcc_MessageHeader (v, b, len, &dmh);
	b += x;
	len -= x;


	outBit_Sx_NL (v,"moduleId: ",		b,  0, 16);
	outBit_Sx_NL (v,"moduleVersion: ",	b, 16,  8);

	outBit_Sx_NL (v,"reserved: ",		b, 24,  8);
	outBit_Sx_NL (v,"blockNumber: ",	b, 32, 16);

	b += 6;
	len -= 6;

	print_databytes (v, "Block Data: ", b, len);

	// $$$ TODO: Save Blockdata if option set to file
	// a good Test transponder is ASTRA's MHP carousel
	// Beware of multiple BIOPs in a Module! (read below!)


	return len_org;
}





// $$$ TODO


//
// 11.2.4 Transport of BIOP Messages
//
// BIOP messages are transported in Modules of DSM-CC Data Carousels.
// Multiple BIOP messages may be carried in one Module. The Modules of
// the Data Carousel are fragmented into Blocks. These Blocks are
// transported in DownloadDataBlock() messages (described in clause 7).
// Figure 11-3 illustrates the applied encapsulation and fragmentation
// methods.



