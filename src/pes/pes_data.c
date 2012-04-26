/*
$Id: pes_data.c,v 1.3 2006/01/02 18:24:12 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PES Data   Privat_stream_1
 -- Data Packet Synchronous and synchronized data streaming




$Log: pes_data.c,v $
Revision 1.3  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2004/02/02 23:34:08  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff




*/




#include "dvbsnoop.h"
#include "pes_data.h"
#include "pes_data_ebu.h"
#include "pes_data_sync.h"
#include "strings/dvb_str.h"
#include "misc/helper.h"
#include "misc/hexprint.h"
#include "misc/output.h"





/*
   -- Data Packet Synchronous and synchronized data streaming
   -- Privat_stream_1
*/

void PES_decodeDATA_private_stream_1 (u_char *b, int len)
{
  u_int     data_identifier;


  // -- Data Buffer starts at PES_DATA_BYTES...

  data_identifier		= getBits (b, 0,  0,  8);



	// -- Async Data Streaming will be done as private_stream_2 (pes_std)


  if (data_identifier >= 0x10 && data_identifier <= 0x1F) {

  	// Teletext EBU data (see EN 300 472)
	PES_decodeDATA_EBU_etc (b, len);

  } else if (data_identifier == 0x20) {

	// DVB subtitling (see EN 300 743)

	// $$$ TODO DVB subtitling (see EN 300 743)
	print_databytes (4,"TODO  dvb subtitles:", b, len);


  } else {

  	// default sync. data streams (see EN 301 192)
	PES_decodeDATA_SYNC (b, len);

  }

}


