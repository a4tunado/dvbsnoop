/*
$Id: sectables.c,v 1.35 2005/12/29 02:43:39 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- For more information please see: ISO 13818 (-1) and ETSI 300 468



$Log: sectables.c,v $
Revision 1.35  2005/12/29 02:43:39  rasc
gcc fixes, man page update

Revision 1.34  2005/11/08 23:15:26  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.33  2005/10/20 22:25:08  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.32  2005/07/31 21:48:03  rasc
soft CRC for sections...

Revision 1.31  2005/07/18 21:11:40  rasc
TVA Content Section

Revision 1.30  2004/11/03 21:01:03  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.29  2004/10/17 22:20:36  rasc
section decoding functions renamed due to preparation of private structures

Revision 1.28  2004/08/22 18:36:45  rasc
 - Bugfix: multilang service descriptor fix  (tnx to Karsten Siebert)
 - New: MetaData Section  (Basic) (H.222.0 AMD1)

Revision 1.27  2004/08/13 01:15:54  rasc
small change in PID assignment display

Revision 1.26  2004/08/12 22:57:18  rasc
 - New: MPEG Content Labeling descriptor  (H.222.0 AMD1)
 - New: PES update ITU-T H.222.0 AMD2
H.222.0 AMD3 updates started

Revision 1.25  2004/08/04 19:54:39  rasc
Bugfix: UNT/INT table mixup  (reported by  Karsten Siebert)

Revision 1.24  2004/08/01 21:33:09  rasc
minor TVA stuff (TS 102 323)

Revision 1.23  2004/07/25 20:12:59  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.22  2004/07/24 11:44:45  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.21  2004/02/20 22:18:42  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.20  2004/02/07 01:28:04  rasc
MHP Application  Information Table
some AIT descriptors

Revision 1.19  2004/01/04 22:03:22  rasc
time for a version leap

Revision 1.18  2004/01/01 20:09:31  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.17  2003/12/27 00:21:16  rasc
dsmcc section tables

Revision 1.16  2003/12/26 23:27:40  rasc
DSM-CC  UNT section

Revision 1.15  2003/11/26 23:54:48  rasc
-- bugfixes on Linkage descriptor

Revision 1.14  2003/11/26 19:55:34  rasc
no message

Revision 1.13  2003/11/24 23:52:17  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.12  2003/11/09 22:54:16  rasc
no message

Revision 1.11  2003/10/29 20:54:57  rasc
more PES stuff, DSM descriptors, testdata

Revision 1.10  2003/10/26 23:00:43  rasc
fix

Revision 1.9  2003/10/24 22:17:21  rasc
code reorg...

Revision 1.8  2003/10/21 20:12:51  rasc
no message

Revision 1.7  2003/10/21 19:54:43  rasc
no message

Revision 1.6  2003/10/19 22:22:57  rasc
- some datacarousell stuff started

Revision 1.5  2003/10/19 13:54:25  rasc
-more table decoding

Revision 1.4  2003/10/17 18:16:54  rasc
- started more work on newer ISO 13818  descriptors
- some reorg work started

Revision 1.3  2003/07/06 05:49:25  obi
CAMT fix and indentation

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/


#include "dvbsnoop.h"
#include "sectables.h"

#include "pat.h"
#include "cat.h"
#include "pmt.h"
#include "tsdt.h"
#include "nit.h"
#include "sdt.h"
#include "st.h"
#include "bat.h"
#include "tdt.h"
#include "tot.h"
#include "rst.h"
#include "dit.h"
#include "sit.h"
#include "eit.h"
#include "mdt.h"
#include "emm_ecm.h"

#include "datacarousel/ait.h"
#include "datacarousel/dsmcc.h"
#include "datacarousel/datagram.h"
#include "datacarousel/ints.h"
#include "datacarousel/unts.h"
#include "datacarousel/mpe_fec.h"

#include "tvanytime/rnt.h"
#include "tvanytime/cs.h"

#include "private/userdefs.h"

#include "testdata/test0x1d.h"

#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"
#include "misc/cmdline.h"
#include "misc/crc32.h"
#include "misc/print_header.h"



void  guess_table (u_char *buf, int len, u_int pid);




//
// -- process SI packet (Sections)
// -- hexdump, decoding
//

void processSI_packet (u_int pid, long pkt_nr, u_char *buf, int len)
{
	
  OPTION *opt  = getOptionPtr();


       indent (0);
       print_packet_header (opt, "SECT", opt->pid, pkt_nr, len);


       if (opt->buffer_hexdump) {
           printhex_buf (0,buf, len);
           out_NL(0);
       }


       // -- decode protocol
       if (opt->printdecode) {
          decodeSI_packet (buf,len ,opt->pid);
          out_nl (3,"==========================================================");
          out_NL (3);
       }

}





/* 
 -- decode Sections buffer by identifying the table IDs
 -- siehe EN 300 468 S.14 
*/

void decodeSI_packet (u_char *buf, int len, u_int pid)

{
  OPTION *opt;
  int    softcrc_fail;


  // nothing to output ?  
  if (getVerboseLevel() < 2) return;


  if (pid != DUMMY_PID) {
	char *s;

  	out (2,"PID:  %u (0x%04x)",pid,pid);

  	s =  dvbstrPID_assignment(pid);
	if (*s) out (2,"  [= assigned for: %s]", s);
	out_NL (2);
	out_NL (2);
  }


  //
  // -- do a soft crc check
  // -- if soft crc fails, ignore packet
  //
  opt = getOptionPtr();
  softcrc_fail = 0;

  if (opt->soft_crc) {
    u_long crc = crc32 ((char *)buf,len);
    if (crc) {
	softcrc_fail = 1;
    }
  }


  if (! softcrc_fail) {

	switch (pid) {

		case  0x01D:	/* Measurement */
			section_TESTDATA  (buf, len);
			break; 

        	default:	// multiple PIDs possible
                	guess_table (buf, len, pid);
			break;

	}

  } else {
	printhex_buf (5,buf,len);
	out_nl (2, "Packet soft CRC failed, skipping packet..."); 
  }


  fflush (stdout);

}







/*
  -- content of packet can not be determined via PID,
  -- so gess from first byte of packet header
*/




typedef struct _TABLE_IF_FUNC {
    u_int    from;          /* e.g. from id 1  */
    u_int    to;            /*      to   id 3  */
    void     (*func)();     /*      function for table decoding */
} TABLE_ID_FUNC;


/*
 * -- Decode mapping table  (TableID --> decode function)
 * -- Crosscheck this with dvb_str, when changing!!!
 */

static TABLE_ID_FUNC table_id_func[] = {

     {  0x00, 0x00,  section_PAT	},
     {  0x01, 0x01,  section_CAT	},
     {  0x02, 0x02,  section_PMT	},
     {  0x03, 0x03,  section_TSDT },
// $$$ TODO     {  0x04, 0x04,  section_14496_SCT },
// $$$ TODO     {  0x05, 0x05,  section_14496_OCT },
     {  0x06, 0x06,  section_MDT },	// Metadata section
// $$$ TODO     {  0x07, 0x07,  section_IPMP_CIT },	// IPMP_Control_Information_section (defined in ISO/IEC13818-11)
     /* res. */
     {  0x3a, 0x3d,  section_DSMCC	},
     {  0x3e, 0x3e,  section_DSMCC_DATAGRAM },
     {  0x40, 0x41,  section_NIT	},
     {  0x42, 0x42,  section_SDT	},
     /* res. */
     {  0x46, 0x46,  section_SDT	},
     /* res. */
     {  0x4A, 0x4A,  section_BAT	},
     {  0x4B, 0x4B,  section_DSMCC_UNT },
     {  0x4C, 0x4C,  section_DSMCC_INT },
     {  0x4E, 0x6E,  section_EIT	},  /*  4 different types */
     {  0x70, 0x70,  section_TDT },
     {  0x71, 0x71,  section_RST },
     {  0x72, 0x72,  section_ST  },
     {  0x73, 0x73,  section_TOT },
     {  0x74, 0x74,  section_MHP_AIT },

     {  0x75, 0x75,  section_TVA_CS },		// TS 102 323
// $$$ TODO
// 0x76 related content section (TS 102 323 [36])
// 0x77 content identifier section (TS 102 323 [36])  (CIT)

     {  0x78, 0x78,  section_MPE_FEC },		// EN 301 192 v1.4.1
     {  0x79, 0x79,  section_TVA_RNT },		// TS 102 323

     /* res. */
     {  0x7E, 0x7E,  section_DIT },
     {  0x7F, 0x7F,  section_SIT },
     {  0x80, 0x8F,  section_EMM_ECM },   /* $$$ Conditional Access Message Section */

     {  0x90, 0xFE,  section_PRIVATE },	 /* opps!? DSM-CC or other stuff?! */
     {  0,0, NULL }
  };






void  guess_table (u_char *buf, int len, u_int pid)

{

  TABLE_ID_FUNC *t = table_id_func;
  u_int		table_id;



  /* -- scan id table for decode function */

  table_id =  (u_int) buf[0];
  while (t->func) {
    if (t->from <= table_id && t->to >= table_id)
       break;
    t++;
  }



  out_nl (2,"Guess table from table id...");

  if (t->func == NULL) {
   	out_SB_NL (2,"Unknown, reserved or not (yet) implemented - TableID: ",table_id);
	out_nl    (2,"--> %s",dvbstrTableID (table_id));
	printhex_buf (5,buf,len);
	return;
  }


  (*(t->func))(buf,len);		/* exec decode function */
  return;
}










