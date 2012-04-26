/*
$Id: dvb_descriptor_premiere.c,v 1.4 2006/04/04 17:16:54 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 -- Private DVB Descriptors  Premiere.de



$Log: dvb_descriptor_premiere.c,v $
Revision 1.4  2006/04/04 17:16:54  rasc
finally fix typo in premiere descriptor name

Revision 1.3  2006/01/02 18:24:16  rasc
just update copyright and prepare for a new public tar ball

Revision 1.2  2004/11/04 19:21:11  rasc
Fixes and changes on "premiere.de" private sections
Cleaning up "premiere.de" private descriptors (should be final now)

Revision 1.1  2004/11/03 21:01:02  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections


*/


#include "dvbsnoop.h"
#include "dvb_descriptor_premiere.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"




/*
 *
 * Private DVB descriptors
 * User Space: Premiere privat (www.premiere.de)
 *
 * basic code snipset provided by  Peter.Pavlov, Premiere 2004-10
 *  
 */





/*
   0xF0  Content Order Descriptor
   PTS 60 04 101    v 1.0.1 17.06.2004
*/

void descriptor_PRIVATE_PremiereDE_ContentOrder (u_char *b)
{
 int  tag, len;

  tag		 = b[0];
  len       	 = b[1];
 
  out_nl (4,"--> Premiere Content Order descriptor ");

  b+=2;
  out_SB_NL (5,"Order_number_length: ", *b);
  print_text_468A (4, "Order_number: ", b+1, *b);
 
  b += *b + 1;
  out_SB_NL (5,"Order_price_length: ", *b);
  print_text_468A (4, "Order_price: ", b+1, *b);
 
  b += *b + 1;
  out_SB_NL (5,"Order_phone_number_length: ", *b);
  print_text_468A (4, "Order_phone_number: ", b+1, *b);
 
  b += *b + 1;
  out_SB_NL (5,"SMS_order_information_length: ", *b);
  print_text_468A (4, "SMS_order_information: ", b+1, *b);
 
  b += *b + 1;
  out_SB_NL (5,"URL_order_information_length: ", *b);
  print_text_468A (4, "URL_order_information: ", b+1, *b);

}
 



 
/*
 	Premiere privat
   0xF1  Parent Information Descriptor
   PTS 60 04 101    v 1.0.1 17.06.2004
*/
 
void descriptor_PRIVATE_PremiereDE_ParentalInformation (u_char *b)
{
  int  tag, len;
 
  tag		 = b[0];
  len       	 = b[1];
 
  out_nl (4,"--> Premiere Parental Information descriptor ");

  b += 2;
  out_SB_NL (5,"rating: ", *b);
  out_nl    (4,"Controll_time_t1: %02x:%02x:%02x", b[1], b[2], b[3]);
  out_nl    (4,"Controll_time_t2: %02x:%02x:%02x", b[4], b[5], b[6]);
 
  b += 7;
  out_SB_NL (5,"Parental_information_length: ", *b);
  print_text_468A (4, "Parental_information: ", b+1, *b);
 
}
 


/*
 	Premiere privat
   0xF2  Content Transmission Descriptor
   PTS 60 04 101    v 1.0.1 17.06.2004
*/

 
void descriptor_PRIVATE_PremiereDE_ContentTransmission (u_char *b)
{
  int  len, str_tim_len;
  u_int time_MJD, time_UTC;

 
  // tag	 = b[0];
  len       	 = b[1];


  out_nl (4,"--> Premiere Content Transmission descriptor ");


  outBit_Sx_NL  (4,"transport_stream_ID: ",	b,  16, 16);
  outBit_S2x_NL (4,"original_network_id: ",	b,  32, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);
  outBit_S2Tx_NL(4,"service_ID: ",		b,  48, 16,
			" --> refers to PMT program_number"); 
 
 
  b += 8;
  len -= 6;

  out_NL(4);
  while (len>0) {

	out (4,"Start_date: ");
  	time_MJD = getBits (b, 0, 0, 16);
	print_time_mjd (4, time_MJD);
	out_NL (4);

  	str_tim_len = outBit_Sx_NL (5,"start_time_loop_length: ", b,  16, 8);

	b += 3;
 	len -= 3;

	indent (+1);
 	for(; str_tim_len>0; str_tim_len-=3) {
  		out (4,"Start_time: ");
  		time_UTC = getBits (b, 0, 0, 24);
  		print_time_utc (4, time_UTC);
  		out_NL (4);

		b   += 3;
		len -= 3;
 	}
	out_NL (4);
	indent (-1);
  }

}



