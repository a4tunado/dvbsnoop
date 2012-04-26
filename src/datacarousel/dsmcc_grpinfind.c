/*
$Id: dsmcc_grpinfind.c,v 1.3 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc GroupInfoIndication()
 -- (e.g. part of DSI private data)



$Log: dsmcc_grpinfind.c,v $
Revision 1.3  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2004/03/06 22:33:11  rasc
no message

Revision 1.1  2004/02/24 23:14:35  rasc
DSI:: DSMCC::GroupInfoIndication






*/




#include "dvbsnoop.h"
#include "dsmcc_grpinfind.h"
#include "dsmcc_misc.h"
#include "misc/output.h"
#include "misc/hexprint.h"





/*
 * ISO/IEC 13818-6
 * EN 301 192
 * dsmcc GroupInfoIndication()
 */


int dsmcc_GroupInfoIndication (int v, u_char *b, u_int len_org)
{
   int   	len = len_org;
   int		n_groups;
   int 		i;
   int		len2;



   	// -- due to some misbehavior of some service providers
   	// -- we do a simple plausi check for group_counts_min_bytes > len
	i = getBits (b, 0, 0, 16);	// group_counts
	i = i * 8  + 2;

	if (i > len_org) {	// this is no  GroupInfo
		print_databytes (v,"Data Bytes (non-standard):", b, len_org);
		return len_org;
	}



	out_nl (v,"GroupInfoIndication:");
	indent (+1);
		n_groups = outBit_Sx_NL (v,"NumberOfGroups: ",	b,  0, 16);
		b += 2;
		len -= 2;

		for (i=0; i < n_groups; i++) {
			out_NL (v);
			if (len <= 0) {
				out_nl (v, "... => strange len <= 0  and still group count > 0  (abort)");
				break;
			}

			out_nl (v, "Group (%d):",i);
			indent (+1);

			outBit_Sx_NL (v,"GroupId: ",	b,  0, 32);
			outBit_Sx_NL (v,"GroupSize: ",	b, 32, 32);
			b += 8;
			len -= 8;

			// GroupCompatibility()
			len2 = dsmcc_CompatibilityDescriptor (b);
			b += len2;
			len -= len2;

			len2 = outBit_Sx_NL (v,"GroupInfoLength: ",	b,  0, 16);
			// print_databytes (v, "GroupInfoBytes: ", b+2, len2);   // $$$ TODO 
			dsmcc_CarouselDescriptor_Loop ("GroupInfo", b+2, len2);
			b += 2+len2;
			len -= 2+len2;


			indent (-1);
		}

		// $$$ passt das hier?
		len2 = outBit_Sx_NL (v,"PrivateDataLength: ",	b,  0, 16);
		print_private_data (v, b+2, len2);   // $$$ What to do here?
		// b += 2+len2;
		// len -= 2+len2;

	indent (-1);
	out_NL (v);

	return len_org;
}



// EN 301 192:
// 8.1.2 DownloadServerInitiate message
// Supergroups in DSI





