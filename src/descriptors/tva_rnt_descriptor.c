/*
$Id: tva_rnt_descriptor.c,v 1.6 2006/02/12 23:17:11 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- Private TAG Space  TS 102 323  TV-Anytime 
 -- RNT Descriptors




$Log: tva_rnt_descriptor.c,v $
Revision 1.6  2006/02/12 23:17:11  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.5  2006/01/02 18:23:58  rasc
just update copyright and prepare for a new public tar ball

Revision 1.4  2004/11/03 21:00:58  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.3  2004/09/01 20:20:34  rasc
new cmdline option: -buffersize KB  (set demux buffersize in KBytes)

Revision 1.2  2004/08/27 23:25:52  rasc
 - Update: changes due to  EN 300 468 v1.6.1
 - Bugfix: Multilingual component descriptor  (tnx to Karsten Siebert)

Revision 1.1  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42




*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "tva_rnt_descriptor.h"
#include "dvb_descriptor.h"
#include "private/userdefs.h"
#include "strings/dvb_str.h"
#include "strings/tva_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"
#include "misc/helper.h"
#include "misc/pkt_time.h"






/*
  determine descriptor type and print it...
  !!! TVA RNT descriptors seems to have  a private tag space !!!
  !!! (descriptor tag collission with DVB descriptors)
*/

int  descriptorTVA  (u_char *b)

{
 int len;
 int tag;



  out_NL (4);
  tag = outBit_S2x_NL (4,"TVA-DescriptorTag: ",		b,   0,  8,
		(char *(*)(u_long))tvaStrTVA_DescriptorTAG); 
  len = outBit_Sx_NL  (4,"descriptor_length: ",	 	b,   8,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x41:  descriptorTVA_RAR_over_DVB_stream (b); break;
     case 0x42:  descriptorTVA_RAR_over_IP_stream (b); break;
     case 0x43:  descriptorTVA_RNT_scan (b); break;

     default: 
	if (tag < 0x80) {
	    out_nl (0,"  ----> ERROR: unimplemented descriptor (TVA context), Report!");
	}
	descriptor_PRIVATE (b, TVA_RNT);
	break;
  } 


  return len+2;   // (descriptor total length)
}








/*
 * TS 102 323  TV-ANYTIME
 * RNT descriptors
 */



static int _valid_dates_block (u_char *b);


/*
  0x41 - RAR_over_DVB_stream
*/

void descriptorTVA_RAR_over_DVB_stream (u_char *b)
{
 int        sf;
 int	    x;
 u_long     date_MJD, date_UTC;



  // descriptor_tag	= b[0];
  // len		= b[1];


  _valid_dates_block (b+2);

  
  outBit_Sx_NL    (4,"weighting: ",		b,  96, 6);
  x = outBit_Sx   (4,"complete_flag: ",		b, 102, 1);
    	if (x == 1) out_nl (4,"  [= referenced CRI data is complete]");
	else out_NL (4);

  sf = outBit_S2x_NL (4,"scheduled_flag: ",	b, 103, 1,
			(char *(*)(u_long)) tvastr_CRI_DATA_scheduled_flag);




  // $$$ TODO this part is re-usable
  outBit_S2x_NL (4,"network_id: ",		b, 104, 16,
			(char *(*)(u_long)) dvbstrNetworkIdent_ID);
  outBit_S2x_NL (4,"original_network_id: ",	b, 120, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);
  outBit_Sx_NL  (4,"transport_stream_ID: ",	b, 132, 16);
  outBit_S2Tx_NL(4,"service_ID: ",		b, 148, 16,
			" --> refers to PMT program_number"); 
  outBit_Sx_NL  (4,"component_tag: ",		b, 164,  8);
  //  ---


  if (sf) {
  	date_MJD		= getBits (b, 0, 172, 16);
  	date_UTC		= getBits (b, 0, 188, 24);
	out (4,"download_start_time: ");
	print_time40 (4, date_MJD,date_UTC);
	out_NL (4);

  	x = outBit_Sx  (4,"download_period_duration: ",	b, 212,  8); 
		out_nl (4," [= %d minutes]",x*6); 
  	outBit_S2Tx_NL (4,"download_cycle_time: ",	b, 220,  8, "minutes");
  }


}





/*
  0x42 - RAR_over_IP_stream
*/

void descriptorTVA_RAR_over_IP_stream (u_char *b)
{
 int	    x;


  // descriptor_tag	= b[0];
  // len		= b[1];


  _valid_dates_block (b+2);

  
  outBit_Sx_NL    (4,"weighting: ",		b,  96, 6);
  x = outBit_Sx   (4,"complete_flag: ",		b, 102, 1);
    	if (x == 1) out_nl (4,"  [= referenced CRI data is complete]");
	else out_NL (4);

  outBit_Sx_NL    (6,"reserved: ",		b, 103, 1);


  x = outBit_Sx_NL(4,"URL_length: ",		b, 104, 8);
  print_text_UTF8 (4,"URL: ", b+14, x);

}






/*
 * valid_date_weighting_complete_flag - Block
 * subroutine for identical stuctures reusage
 * return: len in bytes = 10;
 */
static int _valid_dates_block (u_char *b)
{
  u_long     date_MJD, date_UTC;


  date_MJD		= getBits (b, 0,  0, 16);
  date_UTC		= getBits (b, 0, 16, 24);
  out (4,"first_valid_date: ");
  print_time40 (4, date_MJD,date_UTC);
  out_NL (4);

  date_MJD		= getBits (b, 0, 40, 16);
  date_UTC		= getBits (b, 0, 56, 24);
  out (4,"last_valid_date: ");
  print_time40 (4, date_MJD,date_UTC);
  out_NL (4);

  return 10;
}






/*
  0x43 - RNT_scan
*/

void descriptorTVA_RNT_scan (u_char *b)
{
 int        len;


  // descriptor_tag	= b[0];
  len			= b[1];


  while (len > 0) {

	outBit_S2x_NL (4,"network_id: ",		b,   0, 16,
			(char *(*)(u_long)) dvbstrNetworkIdent_ID);
	outBit_S2x_NL (4,"original_network_id: ",	b,  16, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);


	outBit_Sx_NL    (4,"scan_weighting: ",		b,  32, 8);

	b   += 5;
	len -= 5;
	out_NL (4);
  }
  
}





