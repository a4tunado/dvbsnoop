/*
$Id: llc_snap.c,v 1.6 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)




$Log: llc_snap.c,v $
Revision 1.6  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.5  2004/01/25 21:37:27  rasc
bugfixes, minor changes & enhancments

Revision 1.4  2004/01/01 20:09:16  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.3  2003/12/26 23:27:39  rasc
DSM-CC  UNT section

Revision 1.2  2003/11/26 20:31:50  rasc
no message

Revision 1.1  2003/11/26 20:02:31  rasc
LLC-SNAP



*/


#include "dvbsnoop.h"
#include "llc_snap.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"






/*
  -- decode LLC/SNAP
  -- ISO 8802, RFC 1042
  -- return: len
 */


int  llc_snap (int v, u_char *b)

{
  int dsap, ssap, ctrl;
  int oui, prot;

  out_nl (v,"LLC/SNAP:");
  indent (+1);

  out_nl (v,"LLC:");
  dsap = outBit_Sx_NL (v," DSAP: ",  		b, 0, 8);
  ssap = outBit_Sx_NL (v," SSAP: ",  		b, 8, 8);
  ctrl = outBit_Sx_NL (v," Control: ",	 	b,16, 8);
  
  out_nl (v,"SNAP:");
  oui   = outBit_S2x_NL (v," Org. Unique ID: ", 	b,24,24,
	  	(char *(*)(u_long))dsmccStrOUI );
  prot  = outBit_S2x_NL (v," Protocol Identifier: ", 	b,48,16,
	  	(char *(*)(u_long))dsmccStr_LLC_SNAP_prot );

  indent (-1);
  return 8;

}

/*
 *
 * $$$ TODO  LLC-Snap
 *
 LLCSNAP() -- This structure shall contain the datagram according to the ISO/IEC 8802-2 Logical Link Control
(LLC) and ISO/IEC 8802-1a SubNetwork Attachment Point (SNAP) specifications. In LLC Type 1 operation,
unacknowledged connectionless mode, the LLC header is three bytes long and consists of a one byte
Destination Service Access Point (DSAP) field, a one byte Source Service Access Point (SSAP) field, a one
byte Control field. The values 0xAA in the LLC header's DSAP and SSAP fields indicate that an IEEE 802.2
SNAP header follows. The Control value of 0x03 specifies an Unnumbered Information Command PDU. The
SNAP header is five bytes long and consists of a three byte Organizationally Unique Identifier (OUI) field and a
two byte Protocol Identifier. The SNAP OUI value 0x00-00-00 specifies the Protocol Identifier as an EtherType
or routed non-OSI protocol. The SNAP OUI of 0x00-80-C2 indicates a Bridged Protocol. When the OUI is set
to 0x00-00-00 then the SNAP Protocol Identifier for IP is 0x08-00. For Internet Protocol datagrams, the
complete LLC/SNAP header is 0xAA-AA-03-00-00-00-08-00.


*/

