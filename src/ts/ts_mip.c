/*
$Id: ts_mip.c,v 1.2 2006/02/13 00:31:01 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



 -- Transport Stream
 -- Mega-Frame Initialization Packet (MIP)
 -- ETSI TS 101 191   


$Log: ts_mip.c,v $
Revision 1.2  2006/02/13 00:31:01  rasc
no message

Revision 1.1  2006/02/12 23:17:13  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Complete implementation  (rasc)

Basic code by (c)
Cedric Delfosse <cedric.delfosse@linbox.com> for TDF-C2R, 2006

*/




#include "dvbsnoop.h"
#include "ts_mip.h"
#include "ts_misc.h"

#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"





//
// -- decode TS MIP packet  (PID: 0x15)
// -- ETSI TS 101 191   
//

void decodeTS_MIP (u_char *b, int len)
{

 int            n;
 u_long         t;
 TSPHD		h;
 int		slen;
 int		ialen;



 //
 // -- decode packet header (32 bit)
 //

 n =  decodeTS_PacketHeader (b, &h);
 len -= n;
 b   += n;


 // transport_packet_header:
 // The transport_packet_header shall comply with ISO/IEC 13818-1 [1], clause 2.4.3.2,
 // tables 3 and 4.
 // The PID value for the Mega-frame initialization Packet (MIP) shall be 0 × 15.
 // The payload_unit_start_indicator is not used by the SFN synchronization
 // function and shall be set to 1.
 //
 // The transport_priority value is not used by the SFN synchronization 
 // function and shall be set to 1.
 // The transport_scrambling_control value shall be set to 00 (not scrambled).
 // The adaptation_field_control value shall be set to 01 (payload only).
 // All other parameters are according to ISO/IEC 13818-1 [1], clause 2.4.3.2.
 // The Transport Packet Header (TPH) is mandatory.




	  outBit_S2x_NL (3,"synchronization_id: ", 		b,  0,  8,
		 	(char *(*)(u_long))dvbstrTS_MIP_Syncronization); 
  slen =  outBit_Sx_NL  (3,"section_length: ", 			b,  8,  8);
          outBit_Sx_NL  (3,"pointer: ", 			b, 16, 16);
          outBit_Sx_NL  (3,"periodic_flag: ", 			b, 32,  1);
          outBit_Sx_NL  (3,"reserved: ", 			b, 33, 15);

    t =   outBit_Sx     (3,"synchronization_time_stamp: ", 	b, 48, 24);
	  out_nl        (3,"  [= %0lu.%04lu ms]", t / 10000, t % 10000) ;
    t =   outBit_Sx     (3,"maximum_delay: ", 			b, 72, 24);
	  out_nl        (3,"  [= %0lu.%04lu ms]", t / 10000, t % 10000) ;


          // outBit_Sx_NL  (3,"tps_mip: ", 			b, 96, 32);
  	  out_nl (3,"tps_mips:");
	  indent (+1);
	    outBit_S2x_NL (3,"constellation: ", 		b, 96+ 0,  2,
		 	  (char *(*)(u_long))dvbstrTerrConstellation_FLAG ); 
	    outBit_S2x_NL (3,"hierarchy: ",	 		b, 96+ 2,  3,
		 	  (char *(*)(u_long))dvbstrTerrHierarchy_FLAG); 
	    outBit_S2x_NL (3,"code_rate: ",	 		b, 96+ 5,  3,
		 	  (char *(*)(u_long))dvbstrTerrCodeRate_FLAG); 
	    outBit_S2x_NL (3,"guard_interval: ",		b, 96+ 8,  2,
		 	  (char *(*)(u_long))dvbstrTerrGuardInterval_FLAG); 
	    outBit_S2x_NL (3,"transmission_mode: ",		b, 96+10,  2,
		 	  (char *(*)(u_long))dvbstrTerrTransmissionMode_FLAG); 
	    outBit_S2x_NL (3,"bandwidth: ",			b, 96+12,  2,
		 	  (char *(*)(u_long))dvbstrTerrBandwidth_SCHEME); 
	    outBit_S2x_NL (3,"priority: ",			b, 96+14,  1,
		 	  (char *(*)(u_long))dvbstrTerrPriority); 
	    outBit_S2x_NL (3,"DVB-H signalling: ",		b, 96+15,  2,
		 	  (char *(*)(u_long))dvbstrTerr_DVBH_service_indication); 
	    outBit_Sx_NL  (3,"reserved: ", 			b, 96+17, 15);
	  indent (-1);


  ialen = outBit_Sx_NL  (3,"individual_addressing_length: ", 	b,128,  8);

  b   += 17;
  len -= 17 + ialen;
  slen-= 15 + ialen;


  //
  //
  //

  if (ialen > 0) {
    out_nl (3,"Transmitter loop:");
    indent (+1);
    while (ialen > 0) {
	  int txi;
	  int fl_len;

          txi    = outBit_Sx  (3,"tx_identifier: ", 		b,  0, 16);
	  if (txi  == 0x0000)  out_nl (3," [= broadcast]");
	  else                 out_NL (3);


          fl_len = outBit_Sx_NL  (3,"function_loop_length: ", 	b, 16,  8);

	  b     += 3;
	  ialen -= 3 + fl_len;

	  out_nl (3,"Function loop:");
	  indent (+1);
	  while (fl_len > 0) {
		  int l;

		  l = MIP_function (b);
		  b      += l;
		  fl_len -= l;
		  out_NL (3);
	  }
	  indent (-1);

    }
    indent (-1);
  } // ialen > 0

  outBit_Sx_NL  (3,"CRC: ", 	b,  0, 32);
  b    += 4;
  len  -= 4;
  slen -= 4;


  if (len > 0) {
	print_databytes(3,"stuffing bytes:", b,len);
  }

  return;
}




//
// -- MIP function dispatcher
//

int  MIP_function (u_char *b)

{
 int   tag;
 int   len;



  tag = outBit_S2x_NL (3,"function_tag: ",		b,   0,  8,
		(char *(*)(u_long))dvbstrTS_MIP_FunctionTag); 
  len = outBit_Sx_NL  (3,"function_length: ",	 	b,   0,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor/function
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x00:  MIP_FUNC_tx_time_offset (b); break;
     case 0x01:  MIP_FUNC_tx_frequency_offset (b); break;
     case 0x02:  MIP_FUNC_tx_power (b); break;
     case 0x03:  MIP_FUNC_private_data (b); break;
     case 0x04:  MIP_FUNC_cell_id (b); break;
     case 0x05:  MIP_FUNC_enable (b); break;
     case 0x06:  MIP_FUNC_bandwidth (b); break;

     default: 
	// reserved
	print_databytes (4,"reserved function data:", b+2, len);
	break;
  } 


  return len+2;  	// (total length)
}





/*
 *  --  MIP functions
 */



void  MIP_FUNC_tx_time_offset (u_char *b)
{
   long   t;

    // tag = b[0];
    // len = b[1];

    t =   outBit_Sx     (3,"time_offset: ", 	b,  16, 16);
	  out_nl        (3,"  [= %0ld.%04lu ms]", t / 10000, t % 10000) ;
}



void  MIP_FUNC_tx_frequency_offset (u_char *b)
{
   long   o;

    // tag = b[0];
    // len = b[1];

    o =   outBit_Sx     (3,"frequency_offset: ", 	b,  16, 24);
	  out_nl        (3,"  [= %0ld.%03lu kHz]", o / 1000, o % 1000) ;
}



void  MIP_FUNC_tx_power (u_char *b)
{
   u_long   p;

    // tag = b[0];
    // len = b[1];

    p =   outBit_Sx     (3,"tx_power: ", 	b,  16, 16);
	  out_nl        (3,"  [= %0lu.%01lu dbm]", p / 10, p % 10) ;
}



void  MIP_FUNC_private_data (u_char *b)
{
   int  len;

    // tag = b[0];
    len = b[1];
    
    print_databytes (4,"private data:", b+2, len);
}



void  MIP_FUNC_cell_id (u_char *b)
{
    // tag = b[0];
    // len = b[1];
    
    outBit_Sx_NL  (3,"cell_id: ",	 	b,  16, 16);
    outBit_Sx_NL  (3,"wait_for_enable_flag: ", 	b,  32,  1);
    outBit_Sx_NL  (3,"reserved: ",	 	b,  33,  7);
}



void  MIP_FUNC_enable (u_char *b)
{
   int  len;

    // tag = b[0];
    len = b[1];
    b += 2;

    while (len > 0) {
	outBit_S2x_NL (3,"enable_function_tag: ",	b,   0,  8,
		(char *(*)(u_long))dvbstrTS_MIP_FunctionTag); 
	b++;
	len --;
    }
    
}



void  MIP_FUNC_bandwidth (u_char *b)
{
    // tag = b[0];
    // len = b[1];

    outBit_S2x_NL (3,"ch_bandwidth: ",		b,  16,  7,
	(char *(*)(u_long))dvbstrTS_MIP_ChannelBandwidth); 
    outBit_Sx_NL  (3,"wait_for_enable_flag: ", 	b,  23,  1);
 
}





