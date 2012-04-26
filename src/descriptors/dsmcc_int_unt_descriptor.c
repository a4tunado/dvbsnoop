/*
$Id: dsmcc_int_unt_descriptor.c,v 1.22 2006/02/12 23:17:11 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- Private TAG Space  DSM-CC INT UNT
 -- DSM-CC Descriptors  ISO 13818-6  // EN 301 192 // TS 102 006




$Log: dsmcc_int_unt_descriptor.c,v $
Revision 1.22  2006/02/12 23:17:11  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.21  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.20  2004/11/03 21:00:50  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.19  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42

Revision 1.18  2004/08/04 21:58:41  rasc
BugFix: IPv6 (INT) descriptor display, got wrong values

Revision 1.17  2004/04/15 03:38:50  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.16  2004/02/20 22:18:39  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.15  2004/02/09 21:24:57  rasc
AIT descriptors
minor redesign on output routines

Revision 1.14  2004/01/03 00:30:06  rasc
DSM-CC  STREAM descriptors module (started)

Revision 1.13  2004/01/02 22:59:59  rasc
DSM-CC  modules renaming...

Revision 1.12  2004/01/02 22:25:35  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.11  2004/01/02 16:40:34  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.10  2004/01/02 02:18:34  rasc
more DSM-CC  INT/UNT descriptors

Revision 1.9  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.8  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.7  2003/12/29 22:14:53  rasc
more dsm-cc INT UNT descriptors

Revision 1.6  2003/12/28 00:01:14  rasc
some minor changes/adds...

Revision 1.5  2003/12/27 22:02:43  rasc
dsmcc INT UNT descriptors started

Revision 1.4  2003/12/27 18:17:17  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.3  2003/12/27 14:35:00  rasc
dvb-t descriptors
DSM-CC: SSU Linkage/DataBroadcast descriptors

Revision 1.2  2003/11/01 21:40:27  rasc
some broadcast/linkage descriptor stuff

Revision 1.1  2003/10/29 20:56:18  rasc
more PES stuff, DSM descriptors, testdata




*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "dsmcc_int_unt_descriptor.h"
#include "dvb_descriptor.h"
#include "private/userdefs.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"
#include "misc/helper.h"
#include "misc/pkt_time.h"






/*
  determine descriptor type and print it...
  !!! DSMCC INT/UNT descriptors are in a private tag space !!!

  EN 301 192:
  Descriptors from the DVB SI range (0x40 - 0x7F) shall have their standard
  semantics as defined in EN 300 468 [2].
  Equally MPEG descriptors in the range 0x00 - 0x3F can not be used in the
  INT.  Note that descriptor tags from 0x00 to 0x3F share a common descriptor
  name space with UNT descriptors (see TS 102 006 [19]).
  All descriptors may appear more than once in the INT sub-table at the
  locations indicated above. In the case of name_descriptors multiple
  occurrences require different ISO 639 language codes.


  return byte length
*/

int  descriptorDSMCC_INT_UNT  (u_char *b)

{
 int len;
 int tag;



  out_NL (4);
  tag = outBit_S2x_NL (4,"DSM_CC-INT-UNT-DescriptorTag: ",	b,   0,  8,
		(char *(*)(u_long))dsmccStrDSMCC_INT_UNT_DescriptorTAG); 
  len = outBit_Sx_NL  (4,"descriptor_length: ",	 		b,   8,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x01:  descriptorDSMCC_scheduling (b); break;
     case 0x02:  descriptorDSMCC_update (b); break;
     case 0x03:  descriptorDSMCC_ssu_location (b); break;
     case 0x04:  descriptorDSMCC_message (b); break;
     case 0x05:  descriptorDSMCC_ssu_event_name (b); break;
     case 0x06:  descriptorDSMCC_target_smartcard (b); break;
     case 0x07:  descriptorDSMCC_target_MAC_address (b); break;
     case 0x08:  descriptorDSMCC_target_serial_number (b); break;
     case 0x09:  descriptorDSMCC_target_IP_address (b); break;
     case 0x0A:  descriptorDSMCC_target_IPv6_address (b); break;
     case 0x0B:  descriptorDSMCC_ssu_subgroup_association (b); break;
     case 0x0C:  descriptorDSMCC_IP_MAC_platform_name (b); break;
     case 0x0D:  descriptorDSMCC_IP_MAC_platform_provider_name (b); break;
     case 0x0E:  descriptorDSMCC_target_MAC_address_range (b); break;
     case 0x0F:  descriptorDSMCC_target_IP_slash (b); break;
     case 0x10:  descriptorDSMCC_target_IP_source_slash (b); break;
     case 0x11:  descriptorDSMCC_target_IPv6_slash (b); break;
     case 0x12:  descriptorDSMCC_target_IPv6_source_slash (b); break;
     case 0x13:  descriptorDSMCC_IP_MAC_StreamLocation (b); break;
     case 0x14:  descriptorDSMCC_ISP_access_mode (b); break;
     // DVB SI scope...
     case 0x57:  descriptorDVB_Telephone (b);  break;
     case 0x5F:  descriptorDVB_PrivateDataSpecifier (b);  break;

     default: 
	if (tag < 0x80) {
	    out_nl (0,"  ----> ERROR: unimplemented descriptor (DSM-CC INT/UNT context), Report!");
	}
	descriptor_PRIVATE (b,DSMCC_INT_UNT);
	break;
  } 


  return len+2;   // (descriptor total length)
}








/*
 * EN 301 192  / TR 102 006
 * private DSM-CC INT UNT descriptors
 */




/*
  0x01 - scheduling
  ETSI TS 102 006  (ISO 13818-6)
*/

void descriptorDSMCC_scheduling (u_char *b)
{
 int        len;
 int        x;
 u_long     UTC_time_MJD;
 u_long     UTC_time_UTC;



  // descriptor_tag	= b[0];
  len			= b[1];

  UTC_time_MJD			 = getBits (b, 0, 16, 16);
  UTC_time_UTC			 = getBits (b, 0, 32, 24);
  out (4,"start_date_time: ");
  print_time40 (4, UTC_time_MJD,UTC_time_UTC);
  out_NL (4);

  UTC_time_MJD			 = getBits (b, 0, 56, 16);
  UTC_time_UTC			 = getBits (b, 0, 72, 24);
  out (4,"end_date_time: ");
  print_time40 (4, UTC_time_MJD,UTC_time_UTC);
  out_NL (4);


  x = outBit_Sx     (4,"final_availability: ",	  b,96, 1);
  	if (x == 1) out_nl (4,"  [= final schedule]");
	else out_NL (4);
	 
  x = outBit_Sx     (4,"periodicity_flag: ",	  b,97, 1);
  	if (x == 1) out_nl (4,"  [= only available between start/end time]");
	else out_NL (4);
 
  outBit_S2x_NL (4,"period_unit: ",	  	b, 98, 2,
                        (char *(*)(u_long)) dsmccStr_TimeUnits);     
  outBit_S2x_NL (4,"duration_unit: ",	  	b,100, 2,
                        (char *(*)(u_long)) dsmccStr_TimeUnits);     
  outBit_S2x_NL (4,"estimated_cycle_time_unit: ",b,102, 2,
                        (char *(*)(u_long)) dsmccStr_TimeUnits);     

  outBit_Sx_NL (4,"period: ",			b,104, 8);
  outBit_Sx_NL (4,"duration: ",	  		b,112, 8);
  outBit_Sx_NL (4,"estimated_cycle_time: ",	b,120, 8);

  print_private_data (4,b+16,len-14);

}










/*
  0x02 - update
  ETSI TS 102 006  (ISO 13818-6)
*/

void descriptorDSMCC_update (u_char *b)
{
 int len;

 // descriptor_tag	= b[0];
 len			= b[1];

 outBit_S2x_NL (4,"update_flag: ",	  b,16, 2,
                        (char *(*)(u_long)) dsmccStr_UpdateFlag );     
 outBit_S2x_NL (4,"update_method: ",	  b,18, 4,
                        (char *(*)(u_long)) dsmccStr_UpdateMethod );     
 outBit_S2Tx_NL (4,"update_priority: ",	  b,22, 2, "0=highest");
 
 print_private_data (4,b+3,len-1);
}






/*
  0x03 - ssu_location
  ETSI TS 102 006  (ISO 13818-6)
*/

void descriptorDSMCC_ssu_location (u_char *b)
{
 int len;
 int id;

 // descriptor_tag	= b[0];
 len			= b[1];

 id = outBit_S2x_NL (4,"data_broadcast_id: ",	  b,16, 16,
                        (char *(*)(u_long)) dvbstrDataBroadcast_ID );

 if (id == 0x000A) {
 	outBit_Sx_NL (4,"association_tag: ",	  b,32, 16);
	len -= 2;
	b += 2;
 }

 print_private_data (4,b+4,len-2);
}






/*
  0x04 - message
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_message(u_char *b)
{
  int        len;
  u_char     ISO639_language_code[4];


  // descriptor_tag	= b[0];
  len		        = b[1];

  outBit_Sx_NL (4,"descriptor_number: ",  	b,16, 4);
  outBit_Sx_NL (4,"last_descriptor_number: ",  	b,20, 4);


  getISO639_3 (ISO639_language_code, b+3);
  out_nl (4,"  ISO639_language_code:  %3.3s", ISO639_language_code);
  print_text_468A (4, "Text: ", b+6, len-4);
}







/*
  0x05 - ssu_event_name
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_ssu_event_name (u_char *b)
{
  int        len;
  u_char     ISO639_language_code[4];

  // descriptor_tag		 = b[0];
  // len		       	 = b[1];


  getISO639_3 (ISO639_language_code, b+2);
  out_nl (4,"  ISO639_language_code:  %3.3s", ISO639_language_code);

  len = outBit_Sx_NL (4,"name_length: ",	  b,40, 8);
  print_std_ascii (4, "SSU_event_name: ", b+6, len);
  b += 6+len;
  
  len = outBit_Sx_NL (4,"text_length: ",	  b, 0, 8);
  print_text_468A (4, "MessageText: ", b+1, len);

}






/*
  0x06 - target_smartcard 
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_smartcard (u_char *b)
{
 int len;

 // descriptor_tag	= b[0];
 len			= b[1];

 outBit_Sx_NL (4,"Super_CA_system_id: ",  b,16,32);  // $$$ TODO ? TS 101 197

 print_private_data (4,b+6,len-4);
}





/*
  0x07 - MAC_address
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_MAC_address (u_char *b)
{
 int  len;
 long mac_H, mac_L;

 // descriptor_tag	= b[0];
 len			= b[1];

 mac_H 		= getBits (b, 0,  16, 24);
 mac_L 		= getBits (b, 0,  40, 24);
 out (4,"Mac_addr_mask: %06lx%06lx [= ",mac_H, mac_L);
  	displ_mac_addr (4, mac_H, mac_L);
	out_nl (4,"]");
 b += 8;
 len -= 6;

 while (len > 0) {
 	mac_H 		= getBits (b, 0,   0, 24);
 	mac_L 		= getBits (b, 0,  24, 24);
 	out (4,"Mac_addr: %06lx%06lx [= ",mac_H, mac_L);
  		displ_mac_addr (4, mac_H, mac_L);
		out_nl (4,"]");
 	b += 6;
	len -= 6;
 }

}




/*
  0x08 - target_serial_number 
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_serial_number (u_char *b)
{
 int len;

 // descriptor_tag	= b[0];
 len			= b[1];

 print_databytes (4,"Serial Data Bytes:", b+2,len);
}





/*
  0x09 - IP_address
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_IP_address (u_char *b)
{
 int    len;
 u_long ip;

 // descriptor_tag	= b[0];
 len			= b[1];

 ip = getBits (b, 0,  16, 32);
 out (4,"IPv4_addr_mask: %08lx [= ",ip);
  	displ_IPv4_addr (4, ip);
	out_nl (4,"]");
 b += 6;
 len -= 4;

 while (len > 0) {
 	ip  = getBits (b, 0,   0, 32);
 	out (4,"IPv4_addr: %08lx [= ",ip);
  		displ_IPv4_addr (4, ip);
		out_nl (4,"]");
 	b += 4;
	len -= 4;
 }

}





/*
  0x0A - IPv6_address
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_IPv6_address (u_char *b)
{
 int    len;
 struct IPv6ADDR  x;

 // descriptor_tag	= b[0];
 len			= b[1];

 getIPv6Addr (b+2, &x);
 out (4,"IPv6_addr_mask: %08lx%08lx%08lx%08lx [= ",
		 x.ip[0], x.ip[1], x.ip[2], x.ip[3] );
  	displ_IPv6_addr (4, &x);
	out_nl (4,"]");
 b += 18;
 len -= 16;

 while (len > 0) {
 	getIPv6Addr (b, &x);
	out (4,"IPv6_addr_mask: %08lx%08lx%08lx%08lx [= ",
		 	x.ip[0], x.ip[1], x.ip[2], x.ip[3] );
	  	displ_IPv6_addr (4, &x);
		out_nl (4,"]");
 	b += 16;
	len -= 16;
 }

}






/*
  0x0B - ssu_subgroup_association
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_ssu_subgroup_association (u_char *b)
{

 // descriptor_tag	= b[0];
 // len			= b[1];

  outBit_Sx    (4,"subgroup_tag: ",		b, 16, 24);
  outBit_Sx_NL (4," ",				b, 40, 16);

 // TS 102 006:
 // subgroup_tag (40 bit): the least significant 16 bits of this field shall
 // contain the same value as the subgroup_association_descriptor in
 // the GroupInfoBytes in the GroupInfoIndication structure of the
 // DSI message. This is a unique value under the defining authority
 // of the holder of the OUI conveyed in the field's most significant
 // 24 bits.
 // Note that no relationship between this OUI and any other OUI
 // in the system is implied.


}





/*
  0x0C - IP/MAC_platform_name
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_IP_MAC_platform_name (u_char *b)
{
  int        len;
  u_char     ISO639_language_code[4];

  // descriptor_tag		 = b[0];
  len			       	 = b[1];


  getISO639_3 (ISO639_language_code, b+2);
  out_nl (4,"  ISO639_language_code:  %3.3s", ISO639_language_code);
  print_text_468A (4, "Text: ", b+2+3, len-3);
}


/*
  0x0D - IP/MAC_platform_provider_name
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_IP_MAC_platform_provider_name (u_char *b)
{
  descriptorDSMCC_IP_MAC_platform_name (b); // same encoding...
}




/*
  0x0E - target_MAC_address_range
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_MAC_address_range (u_char *b)
{
 int  len;
 long mac_H, mac_L;

 // descriptor_tag	= b[0];
 len			= b[1];
 b += 2;

 while (len > 0) {
 	mac_H 		= getBits (b, 0,   0, 24);
 	mac_L 		= getBits (b, 0,  24, 24);
 	out (4,"Mac_addr_low: %06lx%06lx [= ",mac_H, mac_L);
  		displ_mac_addr (4, mac_H, mac_L);
		out_nl (4,"]");

 	mac_H 		= getBits (b, 0,  48, 24);
 	mac_L 		= getBits (b, 0,  72, 24);
 	out (4,"Mac_addr_high: %06lx%06lx [= ",mac_H, mac_L);
  		displ_mac_addr (4, mac_H, mac_L);
		out_nl (4,"]");

 	b += 12;
	len -= 12;
 }

}






/*
  0x0F - IP_slash
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_IP_slash (u_char *b)
{
 int    len;

 // descriptor_tag	= b[0];
 len			= b[1];
 b += 2;

 while (len > 0) {
 	u_long ip;
	int    mask;

	ip   = outBit_Sx_NL (4,"IPv4_addr: ",        b, 0,32);
	mask = outBit_Sx_NL (4,"IPv4_slash_mask: ",  b,32, 8);
 	out (4,"  [= ");
		displ_IPv4_addr (4, ip);
		out_nl (4,"/%d]",mask);

 	b += 5;
	len -= 5;
 }

}






/*
  0x10 - IP_source_slash
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_IP_source_slash (u_char *b)
{
 int    len;

 // descriptor_tag	= b[0];
 len			= b[1];
 b += 2;

 while (len > 0) {
 	u_long ip;
	int    mask;

	ip   = outBit_Sx_NL (4,"IPv4_source_addr: ",        b, 0,32);
	mask = outBit_Sx_NL (4,"IPv4_source_slash_mask: ",  b,32, 8);
 	out (4,"  [= ");
		displ_IPv4_addr (4, ip);
		out_nl (4,"/%d]",mask);

	ip   = outBit_Sx_NL (4,"IPv4_dest_addr: ",          b,40,32);
	mask = outBit_Sx_NL (4,"IPv4_dest_slash_mask: ",    b,72, 8);
 	out (4,"  [= ");
		displ_IPv4_addr (4, ip);
		out_nl (4,"/%d]",mask);

 	b += 10;
	len -= 10;
 }

}






/*
  0x11 - IPv6_slash
  ETSI EN 301 192  (ISO 13818-6)
*/


void descriptorDSMCC_target_IPv6_slash (u_char *b)
{
 int    len;

 // descriptor_tag	= b[0];
 len			= b[1];
 b += 2;

 while (len > 0) {
 	struct IPv6ADDR  x;
	int    mask;

 	getIPv6Addr (b, &x);
	out_nl (4,"IPv6_addr_mask: %08lx%08lx%08lx%08lx",
		 	x.ip[0], x.ip[1], x.ip[2], x.ip[3] );

	mask = outBit_Sx_NL (4,"IPv6_slash_mask: ",  b,128, 8);
 	out (4,"  [= ");
		displ_IPv6_addr (4, &x);
		out_nl (4,"/%d]",mask);

 	b += 17;
	len -= 17;
 }

}





/*
  0x12 - IPv6_source_slash
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_target_IPv6_source_slash (u_char *b)
{
 int    len;

 // descriptor_tag	= b[0];
 len			= b[1];
 b += 2;

 while (len > 0) {
 	struct IPv6ADDR  x;
	int    mask;

 	getIPv6Addr (b, &x);
	out_nl (4,"IPv6_source_addr: %08lx%08lx%08lx%08lx",
		 	x.ip[0], x.ip[1], x.ip[2], x.ip[3] );

	mask = outBit_Sx_NL (4,"IPv6_source_slash_mask: ",  b,128, 8);
 	out (4,"  [= ");
		displ_IPv6_addr (4, &x);
		out_nl (4,"/%d]",mask);

 	b += 17;
	len -= 17;


 	getIPv6Addr (b, &x);
	out_nl (4,"IPv6_dest_addr: %08lx%08lx%08lx%08lx",
		 	x.ip[0], x.ip[1], x.ip[2], x.ip[3] );

	mask = outBit_Sx_NL (4,"IPv6_dest_slash_mask: ",  b,128, 8);
 	out (4,"  [= ");
		displ_IPv6_addr (4, &x);
		out_nl (4,"/%d]",mask);

 	b += 17;
	len -= 17;

 }

}






/*
  0x13 - IP_MAC_StreamLocation
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_IP_MAC_StreamLocation (u_char *b)
{

 // descriptor_tag	= b[0];
 // len			= b[1];


  outBit_S2x_NL (4,"Network_id: ",		b, 16, 16,
			(char *(*)(u_long)) dvbstrNetworkIdent_ID);
  outBit_S2x_NL (4,"Original_network_id: ",	b, 32, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);
  outBit_Sx_NL  (4,"transport_stream_ID: ",	b, 48, 16);
  outBit_Sx     (4,"service_ID: ",		b, 64, 16);
		out_nl (4," --> refers to PMT program_number"); 
  outBit_Sx_NL  (4,"component_tag: ",		b, 80,  8);

}





/*
  0x14 - ISP_access_mode
  ETSI EN 301 192  (ISO 13818-6)
*/

void descriptorDSMCC_ISP_access_mode (u_char *b)
{

 // descriptor_tag	= b[0];
 // len			= b[1];

  outBit_S2x_NL (4,"Access_mode: ",		b, 16, 8,
			(char *(*)(u_long)) dsmccStr_AccessMode );

}






