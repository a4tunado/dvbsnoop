/*
$Id: pes_data_sync.c,v 1.3 2006/01/02 18:24:12 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PES Data: Synchronous and synchronized data streaming



$Log: pes_data_sync.c,v $
Revision 1.3  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.1  2004/02/02 23:41:23  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream, restructuring
- some other stuff

Revision 1.1  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured




*/




#include "dvbsnoop.h"
#include "pes_data_sync.h"
#include "strings/dvb_str.h"
#include "misc/helper.h"
#include "misc/hexprint.h"
#include "misc/output.h"





/*
   -- Data Packet Synchronous and synchronized data streaming
   -- EN 301 192  v1.3.1  S. 11
*/

void PES_decodeDATA_SYNC (u_char *b, int len)
{

 typedef struct  _PES_DATA {
        u_int     data_identifier;
        u_int     sub_stream_id;
        u_int     PTS_extension_flag;
        u_int     output_data_rate_flag;
        u_int     reserved;
        u_int     PES_data_packet_header_length;

	// N ... optional data

 } PES_DATA;

 PES_DATA   p;
 int        len2;


   out_nl (4,"Data (synchronous/synchronized):");
   indent (+1);


   p.data_identifier			= getBits (b, 0,  0,  8);
   p.sub_stream_id			= getBits (b, 0,  8,  8);
   p.PTS_extension_flag			= getBits (b, 0, 16,  1);
   p.output_data_rate_flag		= getBits (b, 0, 17,  1);
   p.reserved                           = getBits (b, 0, 18,  2);
   p.PES_data_packet_header_length	= getBits (b, 0, 20,  4);
   b   += 3;
   len -= 3;
   len2 = p.PES_data_packet_header_length;


   out_S2B_NL  (4,"data_identifier: ", p.data_identifier,
		   dvbstrPESDataIdentifier (p.data_identifier) );
   out_SB_NL  (4,"sub_stream_id: ", p.sub_stream_id);
   out_SB_NL  (4,"PTS_extension_flag: ", p.PTS_extension_flag);
   out_SB_NL  (4,"output_data_rate_flag: ", p.output_data_rate_flag);
   out_SB_NL  (6,"reserved_1: ", p.reserved);
   out_SB_NL  (4,"PES_data_packet_header_length: ", p.PES_data_packet_header_length);

   if (p.PTS_extension_flag == 0x01) {
   	out_nl (4,"PTS_extension:");
	indent (+1);
	out_SB_NL  (6,"reserved: ", getBits (b, 0,  0,  7) );
	out_SW_NL  (4,"PTS_extension: ", getBits (b, 0,  7, 9) );
	/* $$$ TODO  PCR extension output in clear text, see ISO 13818-1*/
	b   += 2;
	len -= 2;
	len2 -= 2;
	indent (-1);
   }

   if (p.output_data_rate_flag == 0x01) {
   	out_nl (4,"output_data_rate:");
	indent (+1);
	out_SB_NL  (6,"reserved: ", getBits (b, 0,  0,  4) );
	out_SL_NL  (4,"output_data_rate: ", getBits (b, 0,  4, 28) );
	b   += 4;
	len -= 4;
	len2 -= 4;
	indent (-1);
   }


   print_databytes (4,"PES_data_private_byte:", b, len2);
   b   += len2;
   len -= len2;

   print_databytes (4,"PES_data_byte:", b, len);
   b   += len;
   len -= len;


   indent (-1);
}






