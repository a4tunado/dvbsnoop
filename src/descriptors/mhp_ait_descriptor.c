/*
$Id: mhp_ait_descriptor.c,v 1.15 2006/02/12 23:17:11 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Private TAG Space  MHP  AIT
 -- TS 102 812  v1.2.1  10.11




$Log: mhp_ait_descriptor.c,v $
Revision 1.15  2006/02/12 23:17:11  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.14  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.13  2004/11/03 21:00:50  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.12  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42

Revision 1.11  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.10  2004/05/24 20:18:17  rasc
bugfix: AIT descriptor transport_protocol_label (reported by Stéphane Esté-Gracias)

Revision 1.9  2004/04/15 03:38:50  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.8  2004/02/21 00:50:40  rasc
bugfix: MHP AIT descriptors

Revision 1.7  2004/02/20 22:18:39  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.6  2004/02/15 01:01:03  rasc
DSM-CC  DDB (DownloadDataBlock Message)
DSM-CC  U-N-Message  started
Carousel Descriptors completed

Revision 1.5  2004/02/12 21:21:20  rasc
MHP AIT descriptors
some smaller changes

Revision 1.4  2004/02/11 20:27:32  rasc
MHP AIT descriptors...

Revision 1.3  2004/02/10 22:57:54  rasc
MHP descriptor, missing DVB descriptor done

Revision 1.2  2004/02/09 21:24:58  rasc
AIT descriptors
minor redesign on output routines

Revision 1.1  2004/02/07 01:28:01  rasc
MHP Application  Information Table
some AIT descriptors






*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "mhp_ait_descriptor.h"
#include "dvb_descriptor.h"
#include "private/userdefs.h"
#include "datacarousel/mhp_misc.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"





/*
  determine descriptor type and print it...
  !!! MHP AIT descriptors are in a private tag space !!!

  return byte length
*/

int  descriptorMHP_AIT (u_char *b)

{
 int len;
 int tag;



  out_NL (4);
  tag = outBit_S2x_NL (4,"MHP_AIT-DescriptorTag: ",		b,   0,  8,
		(char *(*)(u_long))dsmccStrMHP_AIT_DescriptorTAG); 
  len = outBit_Sx_NL  (4,"descriptor_length: ",	 	b,   8,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x00:  descriptorMHP_AIT_application (b); break;
     case 0x01:  descriptorMHP_AIT_application_name (b); break;
     case 0x02:  descriptorMHP_AIT_transport_protocol (b); break;
     case 0x03:  descriptorMHP_AIT_dvb_j_application (b); break;
     case 0x04:  descriptorMHP_AIT_dvb_j_application_location (b); break;
     case 0x05:  descriptorMHP_AIT_external_application_authorisation (b); break;
     // case 0x06: reserved
     // case 0x07: reserved
     case 0x08:  descriptorMHP_AIT_dvb_html_application (b); break;
     case 0x09:  descriptorMHP_AIT_dvb_html_application_location (b); break;
     case 0x0A:  descriptorMHP_AIT_dvb_html_application_boundary (b); break;
     case 0x0B:  descriptorMHP_AIT_application_icons (b); break;
     case 0x0C:  descriptorMHP_AIT_pre_fetch (b); break;
     case 0x0D:  descriptorMHP_AIT_DII_location (b); break;
     case 0x0E:  descriptorMHP_AIT_delegated_application (b); break;
     case 0x0F:  descriptorMHP_AIT_plug_in (b); break;
     case 0x10:  descriptorMHP_AIT_application_storage (b); break;
     case 0x11:  descriptorMHP_AIT_ip_signalling (b); break;

     case 0x5F:  descriptorDVB_PrivateDataSpecifier (b); break;

     default: 
	if (tag < 0x80) {
	    out_nl (0,"  ----> ERROR: unimplemented descriptor (MHP_AIT context), Report!");
	}
	descriptor_PRIVATE (b,MHP_AIT);
	break;
  } 


  return len+2;   // (descriptor total length)
}






//
// Unless otherwise specfied, all fields interpreted as text strings in the AIT
// shall be encoded as UTF8 (see 7.1.5, "Monomedia format for text"on page 54).
// See also 14.5, "Text encoding of application identifiers" on page 222.
//






/*
  0x00 - application
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_application (u_char *b)
{
  int        len;
  int        len2;

  // descriptor_tag	= b[0];
  len		        = b[1];


 len2 = outBit_Sx_NL (4,"application_profile_length: ",	b, 16, 8);
 b += 3;
 len -= 1;

 indent (+1);
 while (len2 > 0) {
	int x;

	out_NL(4);
	x =   mhp_application_profile_version (4, b);

	b += x;
	len -= x;
	len2 -= x;
 }
 out_NL(4);
 indent (-1);


 outBit_Sx_NL (4,"service_bound_flag: ",	b,   0,  1);
 outBit_S2x_NL(4,"visibility: ",		b,   1,  2,
	 	(char *(*)(u_long)) dsmccStrMHP_visibility_state );
 outBit_Sx_NL (4,"reserved: ",			b,   3,  5);
 outBit_Sx_NL (4,"application_priority: ",	b,   8,  8);
 b += 2;
 len -= 2;

 while (len > 0) {
 	outBit_Sx_NL (4,"transport_protocol_label: ",	b,   0, 8);
	b++;
	len--;
 }

}






/*
  0x01 - application name
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_application_name (u_char *b)
{
  int        len;
  u_char     ISO639_language_code[4];


  // descriptor_tag	= b[0];
  len		        = b[1];
  b += 2;

  indent (+1);
  while (len > 0) {
	int len2;

	getISO639_3 (ISO639_language_code, b);
	out_nl (4,"ISO639_language_code:  %3.3s", ISO639_language_code);

 	len2 = outBit_Sx_NL (4,"application_name_length: ",	b, 24, 8);
 	print_text_468A (4, "application_name: ", b+4, len2);

	b += 4 + len2;
	len -= 4 + len2;

	out_NL (4);
  }
  indent (-1);

}








/*
  0x02 - transport_protocol
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_transport_protocol (u_char *b)
{
  int  len;
  int  p_id;	


  // descriptor_tag	= b[0];
  len		        = b[1];

  p_id = outBit_S2x_NL (4,"protocol_id: ",	b, 16, 16,
	 	(char *(*)(u_long)) dsmccStrMHP_protocol_id);
  outBit_Sx_NL (4,"transport_protocol_label: ",	b, 32, 8);
  b += 5;
  len -= 3;


  // -- 0x0001 = Transport via OC
  // -- 0x0002 = Transport via IP
  // -- 0x0003 = Transport via interaction channel
  if (p_id == 0x0001 || p_id == 0x0002) {

	int   remote_conn;


  	remote_conn = outBit_Sx_NL (4,"remote_connection: ",	b,  0, 1);
  	              outBit_Sx_NL (6,"reserved: ",		b,  1, 7);
	b++;
	len--;

	if (remote_conn == 0x01) {
		// $$$ TODO reminder: this code part is used several time
		outBit_S2x_NL (4,"Original_network_id: ",	b,  0, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);
		outBit_Sx_NL  (4,"transport_stream_ID: ",	b, 16, 16);
		outBit_S2Tx_NL(4,"service_ID: ",		b, 32, 16,
			" --> refers to PMT program_number"); 
		b += 6;
		len -= 6;
	}


	if (p_id == 0x0001) {
  		// --  Transport via OC
		outBit_Sx_NL  (4,"component_tag: ",		b,  0,  8);
		b++;
		len--;
	} else {
  		// --  Transport via IP
		outBit_Sx_NL  (4,"alignment_indicator: ",	b,  0,  1);
		outBit_Sx_NL  (6,"reserved: ",			b,  1,  7);
		b++;
		len--;

		while (len > 0) {
			int len2;

			out_NL (4);
			len2 = outBit_Sx_NL (4,"URL_length: ",	b,  0,  8);
	 		print_text_UTF8 (4, "URL: ", b+1, len2);
			b += 1+len2;
			len -= 1+len2;
		}

	}


  } if (p_id == 0x0003) {

	int len2;


	out_NL (4);
	len2 = outBit_Sx_NL (4,"URL_base_length: ",	b,  0,  8);
	print_text_UTF8 (4, "URL_base: ", b+1, len2);
	b += 1+len2;
	len -= 1+len2;


	while (len > 0) {
		int len2;

		out_NL (4);
		len2 = outBit_Sx_NL (4,"URL_extension_length: ", b,  0,  8);
		print_text_UTF8 (4, "URL_extension: ", b+1, len2);
		b += 1+len2;
		len -= 1+len2;
	}

  } else {
	// -- all other
  	print_databytes(4,"selector_bytes:", b, len); 

  }


}







/*
  0x03 -  DVB-J Application
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_dvb_j_application (u_char *b)
{
  int  len;


  // descriptor_tag	= b[0];
  len		        = b[1];
  b += 2;

  indent (+1);
  while  (len > 0) {
	int len2;

  	len2 = outBit_Sx_NL (4,"parameter_length: ",	b, 0, 8);
	print_text_UTF8 (4, "Parameter: ", b+1, len2);

	b += len2+1;
	len -= len2+1;
  }
  indent (-1);
}





/*
  0x04 -  DVB-J Application Location
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_dvb_j_application_location (u_char *b)
{
  int  len;
  int  len2;


  // descriptor_tag	= b[0];
  len		        = b[1];
  b += 2;


  len2 = outBit_Sx_NL (4,"base_directory_length: ",	b, 0, 8);
  print_text_UTF8 (4, "base_directory: ", b+1, len2);
  b += len2+1;
  len -= len2+1;

  len2 = outBit_Sx_NL (4,"classpath_extension_length: ",	b, 0, 8);
  print_text_UTF8 (4, "classpath_extension: ", b+1, len2);
  b += len2+1;
  len -= len2+1;

  print_text_UTF8 (4, "initial_class: ", b, len);

}






/*
  0x05 -  External Application Authorisation
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_external_application_authorisation (u_char *b)
{
  int  len;


  // descriptor_tag	= b[0];
  len		        = b[1];
  b += 2;

  indent(+1);
  while (len > 0) {
	  int x;

	  x = mhp_application_identifier (4, b);
	  b += x;
	  len -= x;

  	  outBit_Sx_NL (4,"application_priority: ",	b, 0, 8);
	  b++;
	  len--;

	  out_NL (4);
  }
  indent(-1);

}






/*
  0x08 -- DVB html application
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_dvb_html_application (u_char *b)
{
  int  len;
  int  len2;


  // descriptor_tag	= b[0];
  len		        = b[1];

  len2 = outBit_Sx_NL (4,"appid_set_length: ",	b+2, 0, 8);
  b += 3;
  len --;

  indent(+1);
  while (len2 > 0) {
  	outBit_Sx_NL (4,"application_id: ",	b, 0, 16);
	b += 2;
	len -= 2;
	len2 -= 2;
  }
  indent(-1);

  print_text_UTF8 (4, "parameter: ", b, len);
}




/*
  0x09 -- DVB html application location
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_dvb_html_application_location (u_char *b)
{
  int  len;
  int  len2;


  // descriptor_tag	= b[0];
  len		        = b[1];

  len2 = outBit_Sx_NL (4,"physical_root_length: ",	b+2, 0, 8);
  print_text_UTF8 (4, "physical_root: ", b+3, len2);

  b += 3 + len2;
  len -= 1 + len2;

  print_text_UTF8 (4, "initial_path: ", b, len);
}





/*
  0x0A -- DVB html application boundary
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_dvb_html_application_boundary (u_char *b)
{
  int  len;
  int  len2;


  // descriptor_tag	= b[0];
  len		        = b[1];

  len2 = outBit_Sx_NL (4,"label_length: ",	b+2, 0, 8);
  print_text_UTF8 (4, "label: ", b+3, len2);

  b += 3 + len2;
  len -= 1 + len2;

  print_text_UTF8 (4, "regular_expression: ", b, len);
}






/*
  0x0B -- Application Icons
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_application_icons (u_char *b)
{
  int  len;
  int  len2;


  // descriptor_tag	= b[0];
  len		        = b[1];

  len2 = outBit_Sx_NL (4,"icon_locator_length: ",	b+2, 0, 8);
  print_text_UTF8 (4, "icon_locator: ", b+3, len2);

  b += 3 + len2;
  len -= 1 + len2;

  outBit_Sx_NL (4,"icon_flags: ",	b, 0, 16);	// $$$ TODO table
  b += 2;
  len -= 2;

  print_databytes(4,"reserved_future_use:", b, len); 
}





/*
  0x0C -- Pre-Fetch descriptor
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_pre_fetch (u_char *b)
{
  int  len;
  int  len2;


  // descriptor_tag	= b[0];
  len		        = b[1];

  outBit_Sx_NL (4,"transport_protcol_label: ",	b+2, 0, 8);
  b += 3;
  len --;

  indent(+1);
  while (len > 0) {
	out_NL (4);
  	len2 = outBit_Sx_NL (4,"label_length: ",	b, 0, 8);
  	print_text_UTF8 (4, "label: ", b+1, len2);
	out_nl (4, "  ==> [= matches DII modul label]");
	b += 1 + len2;
	len -= 1 + len2;

  	outBit_Sx_NL (4,"prefetch_priority: ",	b, 0, 8);
	b++;
	len--;
  }
  indent(-1);

}





/*
  0x0D -- DII location  descriptor
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_DII_location (u_char *b)
{
  int  len;


  // descriptor_tag	= b[0];
  len		        = b[1];

  outBit_Sx_NL (4,"transport_protcol_label: ",	b+2, 0, 8);
  b += 3;
  len --;

  indent(+1);
  while (len > 0) {
	out_NL (4);
  	outBit_Sx_NL   (4,"reserved: ",		b,  0,  1);
  	outBit_S2Tx_NL (4,"DII_identification: ",	b,  1, 15,
	   	        "refers to identification in transaction_id");
  	outBit_Sx_NL   (4,"association_tag: ",	b, 16, 16);
	b += 4;
	len -= 4;
  }
  indent(-1);

}





/*
  0x0E -- Delegated Application descriptor
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_delegated_application (u_char *b)
{
  int  len;


  // descriptor_tag	= b[0];
  len		        = b[1];
  b += 2;

  // indent(+1);
  while (len > 0) {
	out_NL (4);
  	outBit64_Sx_NL (4,"application_identifier: ",	b,  0,  48);
	b += 6;
	len -= 6;
  }
  // indent(-1);
}






/*
  0x0F -- Plug-in descriptor
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_plug_in (u_char *b)
{
  int  len;


  // descriptor_tag	= b[0];
  len		        = b[1];

  outBit_Sx_NL (4,"application_type: ",	b+2,  0,  16);
  b += 4;
  len -= 2;

  indent(+1);
  while (len > 0) {
	int x;

	out_NL(4);
	x =   mhp_application_profile_version (4, b);
	b += x;
	len -= x;
  }
  // indent(-1);
}





/*
  0x10 -- Application Storage descriptor
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_application_storage (u_char *b)
{
  // descriptor_tag	= b[0];
  // len	        = b[1];
  b +=2;

  outBit_S2x_NL(4,"storage_property: ",			b,  0,  8,
		  	(char *(*)(u_long)) dsmccStrMHP_storage_property);
  outBit_Sx_NL (4,"not_launchable_from_broadcast: ",	b,  8,  1);
  outBit_Sx_NL (4,"reserved: ",				b,  9,  7);
  outBit_Sx_NL (4,"version: ",				b, 16, 32);
  outBit_Sx_NL (4,"priority: ",				b, 48,  8);
}





/*
  0x11 -- IP signalling descriptor
  ETSI  TS 102 812
*/

void descriptorMHP_AIT_ip_signalling (u_char *b)
{
  // descriptor_tag	= b[0];
  // len	        = b[1];
  b +=2;

  outBit_S2x_NL (4,"platform_id: ",	b,  0, 24,
		  	(char *(*)(u_long)) dsmccStrPlatform_ID);
}









