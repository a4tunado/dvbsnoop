/*
$Id: pes_dsmcc.c,v 1.13 2007/02/08 19:17:41 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 -- PES  DSM-CC   ITU H.222.0  Annex B



$Log: pes_dsmcc.c,v $
Revision 1.13  2007/02/08 19:17:41  rasc
Bugfix on PS Program Stream Map  - tnx to "jack" for reporting

Revision 1.12  2006/01/02 18:24:12  rasc
just update copyright and prepare for a new public tar ball

Revision 1.11  2005/11/10 00:05:45  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.10  2004/02/20 22:18:41  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.9  2004/01/17 23:06:10  rasc
minor stuff, some restructs in output

Revision 1.8  2004/01/11 21:01:32  rasc
PES stream directory, PES restructured

Revision 1.7  2004/01/02 22:25:39  rasc
DSM-CC  MODULEs descriptors complete

Revision 1.6  2004/01/02 16:40:38  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.5  2004/01/01 20:09:29  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.4  2003/12/27 22:02:44  rasc
dsmcc INT UNT descriptors started

Revision 1.3  2003/12/27 18:17:18  rasc
dsmcc PES dsmcc_program_stream_descriptorlist

Revision 1.2  2003/12/27 14:35:01  rasc
dvb-t descriptors
DSM-CC: SSU Linkage/DataBroadcast descriptors

Revision 1.1  2003/12/17 23:15:04  rasc
PES DSM-CC  ack and control commands  according ITU H.222.0 Annex B



*/




#include "dvbsnoop.h"
#include "descriptors/descriptor.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"

#include "pes_misc.h"
#include "pes_dsmcc.h"



static  void dsmcc_control (u_char *b, int len);
static  void dsmcc_ack (u_char *b, int len);
static  int  dsmcc_timecode (u_char *b);
static  void dsmcc_program_stream_descriptorlist_loop (u_char *b, int len);





/*
   -- DSM-CC Command stream in a PES Packet!
   -- buffer starts with command_id

*/


void  PES_decodeDSMCC (u_char *b, int len)

{
 /* ITU H.222.0 Annex B */


   int   commandID;	// same as 'dsmcc_discriminator'

   // -- already processed:
   // --- packet_start_code_prefix 	24 bslbf
   // --- stream_id 			 8 uimsbf
   // --- packet_length			16 uimsbf


	commandID = outBit_S2x_NL (4,"Command_ID/dsmcc_discriminator: ",	b,0,8,
			(char *(*)(u_long)) dsmccStr_Command_ID);
	b++;
	len--;

	switch (commandID) {
		case 0x01: dsmcc_control (b,len); break;
		case 0x02: dsmcc_ack (b,len); break;
		case 0x80: dsmcc_program_stream_descriptorlist_loop (b,len); break;

		default:
			out_nl (4," Unknown DSM-CC commandID/dsmcc_discriminator");
			indent (+1);
			printhex_buf (4, b, len);		
			indent (-1);
			break;
		      
   	}


}





static void dsmcc_control (u_char *b, int len)
{
  int   select_flag;
  int   retrieval_flag;
  int   storage_flag;



   out_nl (3,"DSM-CC CONTROL: ");

   select_flag 		= outBit_Sx_NL (4,"select_flag: ",		b,0,1);
   retrieval_flag 	= outBit_Sx_NL (4,"retrieval_flag: ",		b,1,1);
   storage_flag 	= outBit_Sx_NL (4,"storage_flag: ",		b,2,1);

   outBit_Sx_NL (6,"reserved: ",		b,3,12);
   outBit_Sx_NL (4,"marker_bit: ",		b,15,1);

   b += 2;
//   len -= 2;


   if (select_flag) {
	u_long bitstreamID_31_17;
	u_long bitstreamID_16_2;
	u_long bitstreamID_1_0;

	out_nl (4,"SELECT:");
	indent (+1);

   		bitstreamID_31_17 = outBit_Sx_NL (5,"bitstream_id[31..17]: ",	b,0,15);
   				    outBit_Sx_NL (5,"marker_bit: ",		b,15,1);
   		bitstreamID_16_2  = outBit_Sx_NL (5,"bitstream_id[16..2]:  ",	b,16,15);
   				    outBit_Sx_NL (5,"marker_bit: ",		b,31,1);
   		bitstreamID_1_0   = outBit_Sx_NL (5,"bitstream_id[1..0]:   ",	b,32,2);
   		out_SL_NL (4," ==> bitstream_id:   ",
			(bitstreamID_31_17<<17) + (bitstreamID_16_2<<2) + bitstreamID_1_0);

		outBit_S2x_NL (4,"select_mode: ",	b,34,5,
				(char *(*)(u_long))dsmccStr_SelectMode_ID );
		outBit_Sx_NL (4,"marker_bit: ",		b,39,1);

	indent (-1);
	b += 5;
//	len -= 5;
   }


   if (retrieval_flag) {
	int  jump_flag;
	int  play_flag;

	out_nl (4,"RETRIEVE:");
	indent (+1);

	   	jump_flag	= outBit_Sx_NL (4,"jump_flag: ",	b,0,1);
   		play_flag	= outBit_Sx_NL (4,"play_flag: ",	b,1,1);

   		outBit_Sx_NL (4,"pause_mode: ",		b,2,1);
   		outBit_Sx_NL (4,"resume_mode: ",	b,3,1);
   		outBit_Sx_NL (4,"stop_mode: ",		b,4,1);
   		outBit_Sx_NL (6,"reserved: ",		b,5,10);
		outBit_Sx_NL (4,"marker_bit: ",		b,15,1);
		b += 2;
		len -= 2;

		if (jump_flag) {
		   int xlen = 0; 
		   out_nl (4,"JUMP:");
		   indent (+1);
   			outBit_Sx_NL  (6,"reserved: ",		b,0,7);
			outBit_S2x_NL (4,"direction_indicator: ",	b,7,1,
				(char *(*)(u_long)) dsmccStr_DirectionIndicator );
			indent (+1);
				xlen = dsmcc_timecode (b+1);
			b += xlen+1;
//			len -= (xlen+1);
		   indent (-1);
		}

		if (play_flag) {
		   int xlen; 
		   out_nl (4,"PLAY:");
		   indent (+1);
   		   	outBit_Sx_NL  (4,"speed_mode: ",			b,0,1);
   		   	outBit_S2x_NL (4,"direction_indicator: ",	b,1,1,
				(char *(*)(u_long)) dsmccStr_DirectionIndicator );
   		   	outBit_Sx_NL (6,"reserved: ",			b,2,6);
		   	indent (+1);
		   		xlen = dsmcc_timecode (b+1);
		   	b += xlen+1;
//			len -= (xlen+1);
		   indent (-1);
		}

	indent (-1);
   }



   if (storage_flag) {
	int  record_flag;

	out_nl (4,"STORAGE:");
	indent (+1);

		              outBit_Sx_NL (6,"reserved: ",	b,0,6);
		record_flag = outBit_Sx_NL (4,"record_flag: ",	b,6,1);
		              outBit_Sx_NL (4,"stop_mode: ",	b,7,1);
		b++;
//		len--;

		if (record_flag) {
			int  xlen;
			out_nl (4,"RECORD:");
			indent (+1);
			   	xlen = dsmcc_timecode (b);
			   	b += xlen;
//				len -= xlen;
			indent (-1);
		}

	indent (-1);
   }


}





 /* ITU H.222.0 Annex B */

static void dsmcc_ack (u_char *b, int len)
{
   int  select_ack;
   int  retrieval_ack;
   int  storage_ack;
   int  error_ack;
   int  cmd_status;


   out_nl (3,"DSM-CC  Acknowledge: ");

   select_ack 		= outBit_Sx_NL (4,"select_ack: ",	b,0,1);
   retrieval_ack 	= outBit_Sx_NL (4,"retrieval_ack: ",	b,1,1);
   storage_ack 		= outBit_Sx_NL (4,"storage_ack: ",	b,2,1);
   error_ack 		= outBit_Sx_NL (4,"error_ack: ",	b,3,1);
		          outBit_Sx_NL (6,"reserved: ",		b,4,10);
			  outBit_Sx_NL (4,"marker_bit: ",	b,14,1);
   cmd_status 		= outBit_Sx_NL (4,"cmd_status: ",	b,15,1);


   if (cmd_status && (retrieval_ack || storage_ack) ) {
	dsmcc_timecode (b+2);
   }

}






 /* ITU H.222.0 Annex B */

static int  dsmcc_timecode (u_char *b)
{
	int len = 0;
	int infinite_time_flag;

	outBit_Sx_NL (6,"reserved: ",		b,0,7);
	infinite_time_flag = outBit_Sx_NL (4,"infinite_time_flag: ",	b,7,1);
	b++;
	len = 1;

	if (infinite_time_flag == 0) {
		outBit_Sx_NL (6,"reserved: ",	b,0,4);
		print_xTS_field (4,"Time period", b, 4);
		len += 5;
	}

	return len;
}



static void  dsmcc_program_stream_descriptorlist_loop (u_char *b, int len)
{
  int first = 1;

  // dsmcc_discriminator is already displayed for the first pass of the loop


  while (len > 0) {
	  int len2;

	  if (! first) {
		outBit_S2x_NL (4,"dsmcc_discriminator: ",	b,0,8,
			(char *(*)(u_long)) dsmccStr_Command_ID);
		b++;
		len--;
  	  }

	  len2 = descriptor (b, DSMCC_STREAM);
	  b += len2;
	  len -= len2;

	  first = 0;
  }



}



  /* $$$ TODO some mode && cmd_status could be more verbose */


