/*
$Id: pes_misc.c,v 1.11 2005/12/27 23:30:29 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)



 -- PS misc.
 -- PES misc.





$Log: pes_misc.c,v $
Revision 1.11  2005/12/27 23:30:29  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.10  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.9  2005/08/10 21:28:18  rasc
New: Program Stream handling  (-s ps)

Revision 1.8  2004/08/12 22:57:18  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.7  2004/02/20 22:18:41  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.6  2004/02/05 10:30:57  rasc
no message

Revision 1.5  2004/02/04 23:54:37  rasc
Bugfix:  PTS wrongly displayed!!!

Revision 1.4  2004/02/02 23:34:08  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff

Revision 1.3  2004/01/25 21:37:28  rasc
bugfixes, minor changes & enhancments

Revision 1.2  2004/01/22 22:26:35  rasc
pes_pack_header
section read timeout

Revision 1.1  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured




*/




#include "dvbsnoop.h"
#include "pes_misc.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"




/*
 *  PTS //  DTS
 *  Len is 36 bits fixed
 */

void  print_xTS_field (int v, const char *str, u_char *b, int bit_offset) 
{
  long long   xTS_32_30;
  long long   xTS_29_15;
  long long   xTS_14_0;
  long long   ull;
  int         bo = bit_offset;
  int         v1 = v+1;


  out_nl (v,"%s:",str);
  indent (+1);

    xTS_32_30 = outBit_Sx_NL (v1,"bit[32..30]: ",	b, bo+0,  3);
                outBit_Sx_NL (v1,"marker_bit: ",	b, bo+3,  1);
    xTS_29_15 = outBit_Sx_NL (v1,"bit[29..15]: ",	b, bo+4, 15);
                outBit_Sx_NL (v1,"marker_bit: ",	b, bo+19, 1);
    xTS_14_0  = outBit_Sx_NL (v1,"bit[14..0]: ",	b, bo+20,15);
                outBit_Sx_NL (v1,"marker_bit: ",	b, bo+35, 1);

    ull = (xTS_32_30<<30) + (xTS_29_15<<15) + xTS_14_0;
    out (v," ==> %s: ", str);
    print_timebase90kHz (v, ull);
    out_NL (v);

  indent (-1);
}







