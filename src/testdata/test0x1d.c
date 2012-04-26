/*
$Id: test0x1d.c,v 1.10 2006/01/02 18:24:33 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



   -- test data section
   -- DVB test and measurement signalling channel
   -- ETSI TR 101 291



$Log: test0x1d.c,v $
Revision 1.10  2006/01/02 18:24:33  rasc
just update copyright and prepare for a new public tar ball

Revision 1.9  2005/10/20 22:25:19  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.8  2004/10/17 22:20:39  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.7  2004/02/20 22:18:44  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.6  2004/01/01 20:09:42  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/12/28 00:01:15  rasc
some minor changes/adds...

Revision 1.4  2003/12/27 22:02:45  rasc
dsmcc INT UNT descriptors started

Revision 1.3  2003/11/26 20:31:51  rasc
no message

Revision 1.2  2003/11/26 16:27:48  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.1  2003/10/29 21:00:22  rasc
more PES stuff, DSM descriptors, testdata




*/




#include "dvbsnoop.h"
#include "test0x1d.h"
#include "misc/output.h"
#include "misc/hexprint.h"




void section_TESTDATA (u_char *b, int len)
{

 out_nl (3,"TESTDATA-decoding....");

 outBit_Sx_NL (3,"Table_ID: ",			b,  0, 6);
 outBit_Sx_NL (3,"priority_level: ",		b,  6, 2);
 outBit_Sx_NL (3,"section_syntax_indicator: ",	b,  8, 1);


 // $$$ TODO   ...
 print_databytes(5,"Data:",b,len);

}




