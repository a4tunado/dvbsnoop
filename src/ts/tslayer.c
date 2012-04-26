/*
$Id: tslayer.c,v 1.28 2006/07/19 22:49:24 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



 -- Transport Stream Decode/Table section

   


$Log: tslayer.c,v $
Revision 1.28  2006/07/19 22:49:24  rasc
no message

Revision 1.27  2006/07/19 20:05:46  rasc
Special handling for null packets

Revision 1.26  2006/02/12 23:17:13  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.25  2006/01/02 18:24:34  rasc
just update copyright and prepare for a new public tar ball

Revision 1.24  2005/10/20 22:25:31  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.23  2005/09/09 14:20:31  rasc
TS continuity sequence check (cc verbose output)

Revision 1.22  2005/09/02 14:11:36  rasc
TS code redesign, xPCR and DTS timestamps decoding

Revision 1.21  2005/08/02 22:57:47  rasc
Option -N, rewrite offline filters (TS & Section)

Revision 1.20  2004/10/12 20:37:48  rasc
 - Changed: TS pid filtering from file, behavior changed
 - New: new cmdline option -maxdmx <n>  (replaces -f using pidscan)
 - misc. changes

Revision 1.19  2004/04/15 22:29:23  rasc
PMT: some brainded section check
TS: filter single pids from multi-pid ts-input-file
minor enhancements

Revision 1.18  2004/04/15 03:38:51  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.17  2004/04/05 17:32:14  rasc
mass typo fix adaption --> adaptation

Revision 1.16  2004/01/06 20:06:36  rasc
revert a change for -s signal + small adaptions
(frontend.h uses enums instead of #defines, so committ didn't work...)

Revision 1.15  2004/01/06 14:06:11  rasc
no message

Revision 1.14  2004/01/06 03:13:26  rasc
TS prints PES/Section ID on payload_start

Revision 1.13  2004/01/02 16:40:44  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.12  2004/01/02 02:45:33  rasc
no message

Revision 1.11  2004/01/02 00:00:42  rasc
error output for buffer overflow

Revision 1.10  2004/01/01 20:09:43  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.9  2003/12/17 23:21:35  rasc
PES DSM-CC  ack and control commands  according ITU H.222.0 Annex B

Revision 1.8  2003/12/17 23:15:06  rasc
PES DSM-CC  ack and control commands  according ITU H.222.0 Annex B

Revision 1.7  2003/12/07 23:36:13  rasc
pidscan on transponder
- experimental(!)

Revision 1.6  2003/11/26 16:27:48  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.5  2003/11/24 23:52:18  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.4  2003/10/24 22:17:24  rasc
code reorg...

Revision 1.3  2002/08/17 20:36:12  obi
no more compiler warnings

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/




#include "dvbsnoop.h"
#include "tslayer.h"
#include "ts2secpes.h"
#include "ts_mip.h"
#include "ts_misc.h"

#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"
#include "misc/print_header.h"
#include "misc/cmdline.h"





//
// -- process TS packet (in sync) 
// -- hexdump, subdecode processing, decoding
//

void processTS_packet (u_int pid, long pkt_nr, u_char *b, int len)
{

  OPTION *opt  = getOptionPtr();


       // -- subdecode prev. collected TS data
       // -- push new data
       if (opt->printdecode && opt->ts_subdecode) {
	       ts2SecPes_subdecode (b, len, pid);
       }


       // -- new packet, output header
       indent (0);
       print_packet_header (opt, "TS", opt->pid, pkt_nr, len);


       // hex output (also on wrong packets)
       if (opt->buffer_hexdump) {
           printhex_buf (0, b, len);
           out_NL(0);
       }


       // -- decode protocol (if ts packet)
       if (opt->printdecode) {
          decodeTS_packet (b, len);
          out_nl (3,"==========================================================");
          out_NL (3);
          if (opt->ts_subdecode) {
             // -- check if stored packet(s) length is sufficient for output
	     ts2SecPes_checkAndDo_PacketSubdecode_Output();
          }

       }

}




//
// -- Dispatch TS packet 
// --- Standard Transport Stream
// --- Special Transport Streams...
//

void decodeTS_packet (u_char *b, int len)
{
  int  pid;


  pid = getBits (b, 0,11,13);
  // -- see also ts_misc.c-> special pids!!
  switch (pid) {

	case 0x15:		// MIP, TS 101 191
		decodeTS_MIP (b, len);
		break;

	case 0x1FFF:		// NULL PACKET (ISO 13818-1)
		decodeTS_NullPacket (b, len);
		break;


	default: 		// ISO 13818-1
		decodeTS_iso13818 (b, len);
		break;
  }

}





//
// -- Decode TS packet content
// -- Standard TS packet ISO 13818
//

void decodeTS_iso13818 (u_char *b, int len)
{
 /* ISO 13818-1  2.4.3.2  */

 int            n;
 TSPHD		h;


 //
 // -- decode packet header (32 bit)
 //

 n =  decodeTS_PacketHeader (b, &h);
 len -= n;
 b   += n;


 if (h.afc & 0x2) {
    indent (+1);
    out_nl (3,"Adaptation_field: ");
    	indent (+1);
    	n = ts_adaptation_field (b);
    	b   += n;
    	len -= n;
    	indent (-1);
    indent (-1);
 }

 
 if (h.afc & 0x1) {

    indent (+1);
    out_nl (3,"Payload: (len: %d)",len);

	// -- if payload_start, check PES/SECTION
	if (h.pusi && ! (h.tsc || h.tei) ) {
	    indent (+1);
	    if (b[0]==0x00 && b[1]==0x00 && b[2]==0x01) {
		// -- PES
		outBit_S2x_NL (4,"==> PES-stream: ",	b+3, 0,8,
			(char *(*)(u_long))dvbstrPESstream_ID );
	    } else {
		// -- section (eval pointer field)
		int pointer = b[0]+1;
		outBit_Sx_NL  (4,"==> pointer_field: ",	b, 0,8);
		outBit_S2x_NL (4,"==> Section table: ",	b+pointer, 0,8,
			(char *(*)(u_long))dvbstrTableID );
	    }
	    indent (-1);
	}

    	print_databytes (5, "Data-Bytes:", b,len); 

    indent (-1);

 }


 if (h.afc == 0x00) {
    // -- ISO/IEC reserved...
    print_databytes (5, "Data-Bytes:", b,len); 
 }

}





//
// -- Decode TS packet content
// -- Standard TS Null Packet 0x1FFF
//

void decodeTS_NullPacket (u_char *b, int len)
{
 /* ISO 13818-1  2.4.3.2  */

 int            n;
 TSPHD		h;


 //
 // -- decode packet header (32 bit)
 //

 n =  decodeTS_PacketHeader (b, &h);
 len -= n;
 b   += n;


 // Null Packet may contain any data
 print_databytes (5, "Data-Bytes:", b,len); 

}








int ts_adaptation_field (u_char  *b)

{
 int    len;
 int    af_len;
 int    pcr_flag;
 int    opcr_flag;
 int    sp_flag;
 int    tpd_flag;
 int    afe_flag;



 af_len 	= outBit_Sx_NL  (3,"adaptation_field_length: ",  b, 0, 8);

 b  += 1;
 len = af_len;
 if (af_len == 0) return 1;


  		outBit_Sx_NL  (3,"discontinuity_indicator: ", 			b, 0, 1);
  		outBit_Sx_NL  (3,"random_access_indicator: ", 			b, 1, 1);
 // $$$ TODO discontinuity signalling check
  		outBit_Sx_NL  (3,"elementary_stream_priotity_indicator: ", 	b, 2, 1);
 pcr_flag =  	outBit_Sx_NL  (3,"PCR_flag: ", 					b, 3, 1);
 opcr_flag =  	outBit_Sx_NL  (3,"OPCR_flag: ", 				b, 4, 1);
 sp_flag = 	outBit_Sx_NL  (3,"splicing_point_flag: ", 			b, 5, 1);
 tpd_flag = 	outBit_Sx_NL  (3,"transport_private_data_flag: ", 		b, 6, 1);
 afe_flag = 	outBit_Sx_NL  (3,"adaptation_field_extension_flag: ", 		b, 7, 1);


 b   += 1;
 len -= 1;


  if (pcr_flag) {
     int n = print_PCR_field (3, "program_clock_reference", b, 0); 
     b   += n;
     len -= n;
  }


  if (opcr_flag) {
     int n = print_PCR_field (3, "original_program_clock_reference", b, 0); 
     b   += n;
     len -= n;
  }


  if (sp_flag) {
     outBit_Sx_NL  (3,"splice_countdown: ", 	b, 0, 8);
     b   += 1;
     len -= 1;
  }


  if (tpd_flag) {
     int len1;
     int n;

     len1 = outBit_Sx_NL  (3,"transport_private_data_length: ", b, 0, 8);
     print_databytes (3,"Transport_private_data:",b+1,len1);

     n    = 1 + len1;
     b   += n;
     len -= n;
  }


   // Extension

  if (afe_flag) {
      int n;

      indent (+1);
      n    = ts_adaptation_field_extension (b);
      b   += n;
      len -= n;
      indent (-1);
  }


   // Stuffing bytes

   if (len > 0) {
     out_nl (3,"(Stuffing_bytes length: %d) ",len);
     print_databytes (3,"Stuffing bytes:",b,len);
   }


 return (af_len + 1);
}






int ts_adaptation_field_extension (u_char  *b)

{
  int    len;
  int    afe_len;
  int    ltw_flag;
  int    pr_flag;
  int    ss_flag;



  afe_len = outBit_Sx_NL  (3,"adaptation_field_extension_length: ", b, 0, 8);
  b  += 1;
  len = afe_len;
  if (afe_len == 0) return 1;



  ltw_flag =   outBit_Sx_NL  (3,"ltw_flag: ", 			b, 0, 1);
  pr_flag =    outBit_Sx_NL  (3,"piecewise_rate_flag: ", 	b, 1, 1);
  ss_flag =    outBit_Sx_NL  (3,"seamless_splice_flag: ", 	b, 2, 1);
               outBit_Sx_NL  (3,"reserved: ",		 	b, 3, 5);
  b   += 1;
  len -= 1;



  if (ltw_flag) {
     outBit_Sx_NL  (3,"ltw_valid_flag: ",	 	b, 0,  1);
     outBit_Sx_NL  (3,"ltw_offset: ",		 	b, 1, 15);

     b   += 2;
     len -= 2;
  }


  if (pr_flag) {
     outBit_Sx_NL  (3,"reserved: ",		 	b, 0,  2);
     outBit_Sx_NL  (3,"piecewise_rate: ",	 	b, 2, 22);

     b   += 3;
     len -= 3;
  }


  if (ss_flag) {

     outBit_Sx_NL  (3,"splice_type: ",		 	b, 0,  4);

     {		// $$$ TODO: this is basically the same as for PES
      long long   xTS_32_30;
      long long   xTS_29_15;
      long long   xTS_14_0;
      long long   ull;

      xTS_32_30 = outBit_Sx_NL (3,"DTS_next_AU[32..30]: ",	b,  4,  3);
                  outBit_Sx_NL (3,"marker_bit: ",		b,  7,  1);
      xTS_29_15 = outBit_Sx_NL (3,"DTS_next_AU[29..15]: ",	b,  8, 15);
                  outBit_Sx_NL (3,"marker_bit: ",		b, 23,  1);
      xTS_14_0  = outBit_Sx_NL (3,"DTS_next_AU[14..0]: ",	b, 24, 15);
                  outBit_Sx_NL (3,"marker_bit: ",		b, 39,  1);

      ull = (xTS_32_30<<30) + (xTS_29_15<<15) + xTS_14_0;
      out (3," ==> DTS_next_AU: ");
      print_timebase90kHz (3, ull);
      out_NL (3);
     }

     b   += 5;
     len -= 5;
  }


  if (len > 0) {
     out_nl (3,"(Reserved Bytes length: %d) ",len);
     print_databytes (3,"Reserved bytes:",b,len);
  }


 return afe_len + 1;
}





/*
 *  PCR
 *  Len is 6 bytes fixed
 */

int  print_PCR_field (int v, const char *str, u_char *b, int bit_offset) 
{
  long long   pcr_H, pcr_L, pcr_Ext;
  long long   ull;
  int         bo = bit_offset;
  int         v1 = v+1;


  out_nl (v,"%s:",str);
  indent (+1);

    pcr_H    = outBit_Sx_NL (v1,"baseH: ",	b, bo+ 0,  1);
    pcr_L    = outBit_Sx_NL (v1,"baseL: ",	b, bo+ 1, 32);
               outBit_Sx_NL (v1,"reserved: ",	b, bo+33,  6);
    pcr_Ext  = outBit_Sx_NL (v1,"extension: ",	b, bo+39,  9);

    ull = (pcr_H << 32) + pcr_L;

    out (v," ==> %s: ", str);
    // print_timebase90kHz (v, ull);
    print_pcr_time (v, ull,pcr_Ext);
    out_NL (v);

  indent (-1);

  return 6;
}




