/*
$Id: ts_misc.c,v 1.2 2006/07/19 20:05:46 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



 -- Transport Stream misc routines

   


$Log: ts_misc.c,v $
Revision 1.2  2006/07/19 20:05:46  rasc
Special handling for null packets

Revision 1.1  2006/02/12 23:17:13  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)



*/




#include "dvbsnoop.h"
#include "ts_misc.h"
#include "ts_cc_check.h"

#include "strings/dvb_str.h"
#include "misc/output.h"





//
// -- Decode TS packet header content (4 Bytes len)
// -- Print CC errors
// -- Return: Transport Stream Packet Header Data (ptr)
// -- Return: len in bytes (== 4)
//

int decodeTS_PacketHeader (u_char *b, TSPHD *h)

{
 /* IS13818-1  2.4.3.2  */


 h->sync   = outBit_Sx_NL  (3,"Sync-Byte 0x47: ", 		b,  0, 8);
 h->tei    = outBit_S2x_NL (3,"Transport_error_indicator: ", 	b,  8, 1,
		 	(char *(*)(u_long))dvbstrTS_TEI ); 
 h->pusi   = outBit_S2x_NL (3,"Payload_unit_start_indicator: ", b,  9, 1,
			(char *(*)(u_long))dvbstrTS_PUSI ); 
 h->tprio  = outBit_Sx_NL  (3,"transport_priority: ",		b, 10, 1);
 h->pid    = outBit_S2x_NL (3,"PID: ",			 	b, 11,13,
			// (char *(*)(u_long))dvbstrTSpid_ID ); 
			(char *(*)(u_long))dvbstrPID_assignment ); 
           ts_cc_SetPid (h->pid); // set this here for ts_cc_check...

 h->tsc	   = outBit_S2x_NL (3,"transport_scrambling_control: ", b, 24, 2,
			(char *(*)(u_long))dvbstrTS_ScramblingCtrl_TYPE ); 
 h->afc	   = outBit_S2x_NL (3,"adaptation_field_control: ", 	b, 26, 2,
			(char *(*)(u_long))dvbstrTS_AdaptationField_TYPE ); 
 h->cc	   = outBit_S2x_NL (3,"continuity_counter: ", 		b, 28, 4,
			  (char *(*)(u_long))ts_cc_StatusStr );


 return 4;
}



//
// -- Check if PID is a special TS
// -- Return: 0 = Standard TS containing PES or SECTION
// --         1  = Special TS handling needed (and no subdecoding)
//

int check_TS_PID_special (u_int pid)
{
  // see also TS pid dispatch
  switch (pid) {
	  case 0x15:   return 1;	// MIP
	  case 0x1FFF: return 1;	// NULL PACKET
  }

  return  0;
}
