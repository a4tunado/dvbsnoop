/*
$Id: dvb_descriptor.c,v 1.50 2006/02/12 23:17:11 rasc Exp $ 


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



 -- DVB Descriptors  ETSI 300 468
 -- EN/ISO/TR document references in comments may habe been changed
 -- during updates of documents by ETSI.



$Log: dvb_descriptor.c,v $
Revision 1.50  2006/02/12 23:17:11  rasc
TS 101 191 MIP - Mega-Frame Initialization Packet for DVB-T/H  (TS Pid 0x15)

Revision 1.49  2005/12/29 02:43:38  rasc
gcc fixes, man page update

Revision 1.48  2005/12/22 16:21:50  rasc
Update and new descriptors EN 300 468 v1.7.1

Revision 1.47  2005/11/23 23:06:08  rasc
ISO13818-2  MPEG2 sequence header

Revision 1.46  2005/11/16 20:12:18  rasc
bugfix

Revision 1.45  2005/11/10 00:05:44  rasc
 - New: PS MPEG2 UserData + GOP, DVB-S2 fix

Revision 1.44  2005/11/08 23:15:24  rasc
 - New: DVB-S2 Descriptor and DVB-S2 changes (tnx to Axel Katzur)
 - Bugfix: PES packet stuffing
 - New:  PS/PES read redesign and some code changes

Revision 1.43  2005/10/25 18:41:40  rasc
minor code rewrite

Revision 1.42  2005/10/20 22:25:05  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.41  2005/01/17 19:41:22  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.40  2004/11/03 21:00:50  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.39  2004/08/27 23:25:52  rasc
 - Update: changes due to  EN 300 468 v1.6.1
 - Bugfix: Multilingual component descriptor  (tnx to Karsten Siebert)

Revision 1.38  2004/08/25 19:51:09  rasc
 - Update: EN 300 468 v1.6.1 Terrestrial delivery system descriptor

Revision 1.37  2004/08/24 21:30:22  rasc
more Metadata

Revision 1.36  2004/08/22 18:36:45  rasc
 - Bugfix: multilang service descriptor fix  (tnx to Karsten Siebert)
 - New: MetaData Section  (Basic) (H.222.0 AMD1)

Revision 1.35  2004/08/07 22:10:00  rasc
Bugfix: NIT cable frequency display (reported by Karsten Siebert )

Revision 1.34  2004/08/01 21:33:08  rasc
minor TVA stuff (TS 102 323)

Revision 1.33  2004/07/25 20:12:58  rasc
 - New: content_identifier_descriptor (TS 102 323)
 - New: TVA_id_descriptor (TS 102 323)
 - New: related_content_descriptor (TS 102 323)
 - New: default_authority_descriptor (TS 102 323)

Revision 1.32  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.31  2004/04/15 03:38:50  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.30  2004/04/05 17:32:13  rasc
mass typo fix adaption --> adaptation

Revision 1.29  2004/02/10 22:57:54  rasc
MHP descriptor, missing DVB descriptor done

Revision 1.28  2004/02/09 22:56:59  rasc
Bugfix VBI Data descriptor

Revision 1.27  2004/02/09 21:24:57  rasc
AIT descriptors
minor redesign on output routines

Revision 1.26  2004/01/02 16:40:34  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.25  2004/01/01 20:35:26  rasc
PES program stream map, minor descriptor cleanup

Revision 1.24  2004/01/01 20:31:22  rasc
PES program stream map, minor descriptor cleanup

Revision 1.23  2004/01/01 20:09:19  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.22  2003/12/27 22:02:43  rasc
dsmcc INT UNT descriptors started

Revision 1.21  2003/12/27 14:35:00  rasc
dvb-t descriptors
DSM-CC: SSU Linkage/DataBroadcast descriptors

Revision 1.20  2003/12/26 23:27:39  rasc
DSM-CC  UNT section

Revision 1.19  2003/11/26 23:54:47  rasc
-- bugfixes on Linkage descriptor

Revision 1.18  2003/11/26 16:27:45  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.17  2003/11/24 23:52:16  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.16  2003/11/09 20:48:34  rasc
pes data packet (DSM-CC)

Revision 1.15  2003/11/07 16:33:32  rasc
no message

Revision 1.14  2003/11/01 21:40:27  rasc
some broadcast/linkage descriptor stuff

Revision 1.13  2003/10/29 20:54:56  rasc
more PES stuff, DSM descriptors, testdata

Revision 1.12  2003/10/26 21:36:19  rasc
private DSM-CC descriptor Tags started,
INT-Section completed..

Revision 1.11  2003/10/26 19:06:27  rasc
no message

Revision 1.10  2003/10/25 19:11:49  rasc
no message

Revision 1.9  2003/10/24 22:45:04  rasc
code reorg...

Revision 1.8  2003/10/24 22:17:17  rasc
code reorg...

Revision 1.7  2003/10/21 21:31:29  rasc
no message

Revision 1.6  2003/10/21 19:54:43  rasc
no message

Revision 1.5  2003/10/19 22:31:38  rasc
- some datacarousell stuff started

Revision 1.4  2003/10/19 22:22:57  rasc
- some datacarousell stuff started

Revision 1.3  2003/10/19 21:05:53  rasc
- some datacarousell stuff started

Revision 1.2  2003/10/16 19:02:28  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.1  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?



*/


#include "dvbsnoop.h"
#include "descriptor.h"
#include "dvb_descriptor.h"
#include "private/userdefs.h"
#include "strings/dvb_str.h"
#include "strings/dsmcc_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"






/*
  determine descriptor type and print it...

  EN 300 468:
  descriptor_tag: The descriptor tag is an 8-bit field which identifies
  each descriptor. Those values with MPEG-2 normative meaning are described
  in ISO/IEC 13818-1 [1].

  return byte length
*/

int  descriptorDVB  (u_char *b)

{
 int len;
 int tag;



  out_NL (4);
  tag = outBit_S2x_NL (4,"DVB-DescriptorTag: ",		b,   0,  8,
		(char *(*)(u_long))dvbstrDVBDescriptorTAG); 
  len = outBit_Sx_NL  (4,"descriptor_length: ",	 	b,   8,  8);


  // empty ??
  if (len == 0) return len;

  // print hex buf of descriptor
  printhex_buf (9, b,len+2);



  switch (tag) {

     case 0x40:  descriptorDVB_NetName (b);  break;
     case 0x41:  descriptorDVB_ServList (b);  break;
     case 0x42:  descriptorDVB_Stuffing (b);  break;
     case 0x43:  descriptorDVB_SatDelivSys (b);  break;
     case 0x44:  descriptorDVB_CableDelivSys (b);  break;
     case 0x45:  descriptorDVB_VBI_Data (b);  break;
     case 0x46:  descriptorDVB_VBI_Teletext (b);  break;
     case 0x47:  descriptorDVB_BouquetName (b);  break;
     case 0x48:  descriptorDVB_Service (b);  break;
     case 0x49:  descriptorDVB_CountryAvail (b);  break;
     case 0x4A:  descriptorDVB_Linkage (b);  break;
     case 0x4B:  descriptorDVB_NVOD_Reference (b);  break;
     case 0x4C:  descriptorDVB_TimeShiftedService (b);  break;
     case 0x4D:  descriptorDVB_ShortEvent (b);  break;
     case 0x4E:  descriptorDVB_ExtendedEvent (b);  break;
     case 0x4F:  descriptorDVB_TimeShiftedEvent(b);  break;
     case 0x50:  descriptorDVB_Component(b);  break;
     case 0x51:  descriptorDVB_Mosaic(b);  break;
     case 0x52:  descriptorDVB_StreamIdent (b);  break;
     case 0x53:  descriptorDVB_CAIdentifier (b);  break;
     case 0x54:  descriptorDVB_Content (b);  break;
     case 0x55:  descriptorDVB_ParentalRating(b);  break;
     case 0x56:  descriptorDVB_Teletext (b);  break;
     case 0x57:  descriptorDVB_Telephone (b);  break;
     case 0x58:  descriptorDVB_LocalTimeOffset (b);  break;
     case 0x59:  descriptorDVB_Subtitling (b);  break;
     case 0x5A:  descriptorDVB_TerrestDelivSys (b);  break;
     case 0x5B:  descriptorDVB_MultilingNetworkName (b);  break;
     case 0x5C:  descriptorDVB_MultilingBouquetName (b);  break;
     case 0x5D:  descriptorDVB_MultilingServiceName (b);  break;
     case 0x5E:  descriptorDVB_MultilingComponent (b);  break;
     case 0x5F:  descriptorDVB_PrivateDataSpecifier (b);  break;
     case 0x60:  descriptorDVB_ServiceMove (b);  break;
     case 0x61:  descriptorDVB_ShortSmoothingBuffer (b);  break;
     case 0x62:  descriptorDVB_FrequencyList (b);  break;
     case 0x63:  descriptorDVB_PartialTransportStream(b);  break;
     case 0x64:  descriptorDVB_DataBroadcast(b);  break;
     case 0x65:  descriptorDVB_Scrambling(b);  break;
     case 0x66:  descriptorDVB_DataBroadcastID(b);  break;
     case 0x67:  descriptorDVB_TransportStream(b);  break;
     case 0x68:  descriptorDVB_DSNG(b);  break;
     case 0x69:  descriptorDVB_PDC(b);  break;
     case 0x6A:  descriptorDVB_AC3(b);  break;
     case 0x6B:  descriptorDVB_AncillaryData(b);  break;
     case 0x6C:  descriptorDVB_CellList(b);  break;
     case 0x6D:  descriptorDVB_CellFrequencyLink(b);  break;
     case 0x6E:  descriptorDVB_AnnouncementSupport(b);  break;
     case 0x6F:  descriptorDVB_ApplicationSignalling(b);  break;
     case 0x70:  descriptorDVB_AdaptationFieldData(b);  break;
     case 0x71:  descriptorDVB_ServiceIdentifier(b);  break;
     case 0x72:  descriptorDVB_ServiceAvailability(b);  break;
		 // TV ANYTIME  TS 102 323
     case 0x73:  descriptorDVB_DefaultAuthority(b);  break;
     case 0x74:  descriptorDVB_RelatedContent(b);  break;
     case 0x75:  descriptorDVB_TVA_ID(b);  break;
     case 0x76:  descriptorDVB_ContentIdentifier(b);  break;
		 // EN 301 192 v1.4.1  MPE_FEC
     case 0x77:  descriptorDVB_TimesliceFecIdentifier(b);  break;
     case 0x78:  descriptorDVB_ECM_RepetitionRate(b);  break;
		 // EN 300 468 v1.7.1
     case 0x79:  descriptorDVB_S2SatelliteDeliverySystem(b);  break;
     case 0x7A:  descriptorDVB_Enhanced_AC3(b);  break;
     case 0x7B:  descriptorDVB_DTS_Audio(b);  break;
     case 0x7C:  descriptorDVB_AAC(b);  break;
     case 0x7D:  descriptor_any(b);  break;	// $$$ TODO: currently reserved
     case 0x7E:  descriptor_any(b);  break;	// $$$ TODO: currently reserved
     case 0x7F:  descriptorDVB_Extension(b);  break;

     default: 
	if (tag < 0x80) {
	    out_nl (0,"  ----> ERROR: unimplemented descriptor (dvb context), Report!");
	}
	descriptor_PRIVATE (b, DVB_SI);
	break;
  } 


  return len+2;   // (descriptor total length)
}











/* --------------------------------------------------------------- 
  well known DVB descriptors
   --------------------------------------------------------------- */



/*
  0x40 NetName  descriptor  (network name descriptor)
  EN 300 468
  -- checked v1.6.1
*/

void descriptorDVB_NetName (u_char *b)
{
  int  len;

  // tag	 = b[0];
  len       	 = b[1];

  print_text_468A (4, "Network_name: ", b+2,len);
}




/*
  0x41 Service List Descriptor 
  EN 300 468
  -- adapted v1.6.1
*/

void descriptorDVB_ServList (u_char *b)
{
 int    len;


 // tag 	= b[0];
 len 		= b[1];

 b   += 2;

 indent (+1);
 while (len > 0) {
   int	stype;

   stype = b[2];   // prefetch service_type == (b, 16,8)

   outBit_Sx (4,"service_ID: ", 	b,  0,  16);
   if (stype != 0x04) {    // 0x04 = NVOD
	out (4,	"[ --> refers to PMT program_number]");
   }
   out_NL (4);

   outBit_S2x_NL  (4,"service_type: ", 	b, 16,  8,
		 (char *(*)(u_long)) dvbstrService_TYPE );

   b   += 3;
   len -= 3;
   out_NL (4);

 }
 indent (-1);

}





/*
  0x42  Stuffing descriptor 
  ETSI EN 300 468  
*/

void descriptorDVB_Stuffing (u_char *b)

{
  descriptor_any (b);
}





/*
  0x43 SatDelivSys  descriptor  (Satellite delivery system descriptor)
  EN 300 468
  -- adapted v1.6.1
  -- adapted v1.7.1  
*/

void descriptorDVB_SatDelivSys (u_char *b)
{
    u_long     frequency;
    u_int      orbital_position;
    u_int      west_east_flag;
    u_int      polarisation;
    // u_int      modulation;   	// v1.6.1
    u_int      roll_off;		// v1.7.1 replaces mod.
    u_int      modulation_system;	// v1.7.1 replaces mod.
    u_int      modulation_type;		// v1.7.1 replaces mod.
    u_long     symbol_rate;
    u_int      FEC_inner;
    char       *s;




  // tag 	= b[0];
  // len	= b[1];


  frequency			 = getBits (b, 0, 16, 32);
  orbital_position		 = getBits (b, 0, 48, 16);
  west_east_flag		 = getBits (b, 0, 64, 1);
  polarisation			 = getBits (b, 0, 65, 2);
  roll_off			 = getBits (b, 0, 67, 2);
  modulation_system		 = getBits (b, 0, 69, 1);
  modulation_type		 = getBits (b, 0, 70, 2);
  symbol_rate			 = getBits (b, 0, 72, 28);
  FEC_inner			 = getBits (b, 0, 100, 4);


  out_nl (4,"Frequency: %lu (= %3lx.%05lx GHz)",frequency,
	 frequency >> 20, frequency & 0x000FFFFF );
  out_nl (4,"Orbital_position: %u (= %3x.%01x)",orbital_position,
	 orbital_position >> 4, orbital_position & 0x000F);

  out_S2B_NL (4,"West_East_flag: ",west_east_flag,
	 dvbstrWEST_EAST_FLAG(west_east_flag));

  out_S2B_NL (4,"Polarisation: ",polarisation,
	 dvbstrPolarisation_FLAG(polarisation));


  s = (modulation_system == 0) ? "DVB-S" : "DVB-S2";
  out_S2B_NL (4,"Kind: ", modulation_system, s);
  if (modulation_system) {
	out_S2B_NL (4,"Roll Off Faktor: ", roll_off,
		dvbstrRollOffSAT_FLAG(roll_off));
  } else {
 	out_SB_NL (4,"fixed ('00'): ",roll_off);
  }


  out_S2B_NL (4,"Modulation_type: ",modulation_type,
	dvbstrModulationSAT_FLAG(modulation_type));


  out_nl (4,"Symbol_rate: %u (= %3x.%04x)",symbol_rate,
	 symbol_rate >> 16, symbol_rate & 0x0000FFFF );

  out_S2B_NL (4,"FEC_inner: ",FEC_inner,
	 dvbstrFECinner_SCHEME (FEC_inner));

}





/*
  0x44 CableDelivSys  descriptor  (Cable delivery system descriptor)
  EN 300 468
  -- adapted v1.6.1
*/

void descriptorDVB_CableDelivSys (u_char *b)

{
 /* ETSI 300 468    6.2.xx */

 typedef struct  _descCDS {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_long     frequency;
    u_int      FEC_outer;
    u_int      reserved_1;
    u_int      modulation;
    u_long     symbol_rate;
    u_int      FEC_inner;

 } descCDS;

 descCDS  d;
 //int      i;




 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 d.frequency			 = getBits (b, 0, 16, 32);
 d.reserved_1			 = getBits (b, 0, 48, 12);
 d.FEC_outer			 = getBits (b, 0, 60, 4);
 d.modulation			 = getBits (b, 0, 64, 8);
 d.symbol_rate			 = getBits (b, 0, 72, 28);
 d.FEC_inner			 = getBits (b, 0, 100, 4);


 out_nl (4,"Frequency: %lu (= %3lx.%04lx MHz)",d.frequency,
	 d.frequency >> 16, d.frequency & 0x0000FFFF );

 out_S2B_NL (4,"FEC_outer: ",d.FEC_outer,
	 dvbstrFECouter_SCHEME (d.FEC_outer));

 out_SB_NL (6,"reserved_1: ",d.reserved_1);


 out_S2B_NL (4,"Modulation (Cable): ",d.modulation,
	 dvbstrModulationCable_FLAG(d.modulation));

 out_nl (4,"  Symbol_rate: %u (= %4x.%04x)",d.symbol_rate,
	 d.symbol_rate >> 16, d.symbol_rate & 0x0000FFFF );

 out_S2B_NL (4,"FEC_inner: ",d.FEC_inner,
	 dvbstrFECinner_SCHEME (d.FEC_inner));

}






/*
  0x45  VBI Data  descriptor 
  ETSI EN 300 468  2.2.42
  -- checked v1.6.1
*/

void descriptorDVB_VBI_Data  (u_char *b)

{
 int           len1;


 // dtag	 = b[0];
 len1       	 = b[1];
 b += 2;


 indent (+1);
 while (len1 > 0) {
	int  ds_id;
	int  len2;

    	out_NL (4); 
	ds_id =	outBit_S2x_NL (4,"Data_service_id: ",			b,  0,  8,
			(char *(*)(u_long)) dvbstrDataService_ID);
	len2 = outBit_Sx_NL   (4,"Data_service_descriptor_length: ",	b,  8,  8);

	b    += 2;
	len1 -= 2;

	if ((ds_id >= 1 && ds_id <= 7) && (ds_id != 3) ) {

		indent (+1);
		while (len2 > 0) {
           		out_NL (4);
			outBit_Sx_NL   (6,"reserved_1: ",	b,  0,  2);
			outBit_Sx_NL   (4,"field_parity: ",	b,  2,  1);
			outBit_Sx_NL   (4,"line_offset: ",	b,  3,  5);

			b++;
	   		len2--;
			len1--;
		} 
		indent (-1);

	} else {

		print_databytes (6,"Reserved Data:", b,len2);
		b += len2;
		len1 -= len2;


	}

 }
 indent (-1);


}






/*
  0x46  VBI teletext descriptor 
  ETSI EN 300 468   6.2.xx
*/

void descriptorDVB_VBI_Teletext (u_char *b)

{
  descriptorDVB_Teletext (b);
}






/*
  0x47  Bouquet Name  descriptor 
  ETSI EN 300 468    6.2.xx
*/

void descriptorDVB_BouquetName  (u_char *b)

{
  int len;

  // tag	 = b[0];
  len       	 = b[1];

  print_text_468A (4, "BouquetName: ", b+2,len);
}







/*
  0x48  Service  descriptor 
  ETSI EN 300 468   6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_Service  (u_char *b)

{
  int   len2;


  // tag	= b[0];
  // len = 	= b[1];


  outBit_S2x_NL(4,"service_type: ",  	b,  16,  8,
		 (char *(*)(u_long)) dvbstrService_TYPE );

  len2 = outBit_Sx_NL (4,"service_provider_name_length: ",  	b,  24,  8);
  b += 4;
  print_text_468A     (4,"service_provider_name: ", b,len2);
  b += len2;


  len2 = outBit_Sx_NL (4,"service_name_length: ",  		b,   0,  8);
  b += 1;
  print_text_468A (4, "Service_name: ", b,len2);

}





/*
  0x49  Country Availibility  descriptor 
  ETSI EN 300 468   6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_CountryAvail  (u_char *b)

{
 int     len;


 // tag 	= b[0];
 len		= b[1];

 outBit_Sx_NL (4,"country_availability_flag: ",  	b,  16,  1);
 outBit_Sx_NL (6,"reserved: ", 			 	b,  17,  7);

 b   += 3;
 len -= 1;

 indent (+1);
 while (len > 0) {
    u_char  country_code[4];

    strncpy ((char *)country_code, (char *)b, 3);	// 24 bit
    *(country_code+3) = '\0';
    b   += 3;
    len -= 3;

    out_nl (4,"country_code:  %3.3s",country_code);
 }
 indent (-1);

}







/*
  0x4A  Linkage  descriptor  
*/

void descriptorDVB_Linkage (u_char *b)

{
 /* ETSI 300 468   6.2.xx */

 typedef struct  _descLinkage {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      transport_stream_id;
    u_int      original_network_id;
    u_int      service_id;
    u_int      linkage_type;
 } descLinkage;


 descLinkage  d;
 int          len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.transport_stream_id		 = getBits (b, 0, 16, 16);
 d.original_network_id		 = getBits (b, 0, 32, 16);
 d.service_id			 = getBits (b, 0, 48, 16);
 d.linkage_type			 = getBits (b, 0, 64, 8);


 out_SW_NL  (4,"transport_stream_ID: ",d.transport_stream_id);
 out_S2W_NL (4,"original_network_ID: ",d.original_network_id,
	dvbstrOriginalNetwork_ID(d.original_network_id));
 out_S2W_NL (4,"service_ID: ",d.service_id,
      " --> refers to PMT program_number");
 out_S2B_NL (4,"linkage_type: ",d.linkage_type,
	dvbstrLinkage_TYPE (d.linkage_type));

 len = d.descriptor_length - 7;
 b  += 7 + 2;

 indent (+1);

    if (d.linkage_type == 0x08) {		/* EN 300 468 */
        sub_descriptorDVB_Linkage0x08 (b, len);
    } else if (d.linkage_type == 0x09) {	/* TR 102 006  DSM-CC */
        sub_descriptorDVB_Linkage0x09 (b, len);
    } else if (d.linkage_type == 0x0A) {	/* TR 102 006  DSM-CC */
	/* SSU SCAN Linkage */
	outBit_S2x_NL (4,"Table_type: ",  	b, 0, 8,
		   (char *(*)(u_long))dsmccStrLinkage0CTable_TYPE );
    } else if (d.linkage_type == 0x0B) {	/* EN 301 192  DSM-CC */
        sub_descriptorDVB_Linkage0x0B (b, len);
    } else if (d.linkage_type == 0x0C) {	/* EN 301 192  DSM-CC */
        sub_descriptorDVB_Linkage0x0C (b, len);
    } else {
    	print_private_data (4, b,len);
    }

 indent (-1);

}


/*
 * DVB Linkage Subdescriptor  0x08
 */

void sub_descriptorDVB_Linkage0x08 (u_char *b, int len)
{
 /* ETSI 300 468   6.2.xx */

 typedef struct  _descLinkage0x08 {
    u_int      handover_type;
    u_int      reserved_1; 
    u_int      origin_type;
    u_int      network_id;
    u_int      initial_service_id;

 } descLinkage0x08;


 descLinkage0x08  d;



    d.handover_type		= getBits (b, 0, 0, 4);
    d.reserved_1		= getBits (b, 0, 4, 3);
    d.origin_type		= getBits (b, 0, 7, 1);
    b   += 1;
    len -= 1;
    
    out_S2B_NL (4,"Handover_type: ",d.handover_type,
	dvbstrHandover_TYPE(d.handover_type));

    out_SB_NL (6,"reserved_1: ",d.reserved_1);

    out_S2B_NL (4,"Origin_type: ",d.origin_type,
	dvbstrOrigin_TYPE(d.origin_type));

    if (   d.handover_type == 0x01
        || d.handover_type == 0x02
        || d.handover_type == 0x03) {
        d.network_id		= getBits (b, 0, 0, 16);
        out_S2W_NL (4,"Network_ID: ",d.network_id,
		dvbstrNetworkIdent_ID(d.network_id));
        b   += 1;
        len -= 1;
    } 
    if (d.origin_type == 0x00) {
        d.initial_service_id	= getBits (b, 0, 0, 16);
        out_SW_NL (4,"Initial_service_ID: ",d.initial_service_id);
        b   += 1;
        len -= 1;
    }

    if (len > 0) {
       print_private_data (4, b,len);
    }

}



/*
 * DVB Linkage Subdescriptor  0x09
 */

void sub_descriptorDVB_Linkage0x09 (u_char *b, int len)
{
 /* ETSI TR 102 006   6.1 */

    int      OUI_data_length;
    u_long   OUI;
    int      selector_length;


    OUI_data_length = outBit_Sx_NL (4,"OUI_data_length: ", b,0,8);
    b++;
    len --;

    while (OUI_data_length > 0) {
    	OUI             = outBit_S2x_NL (4,"OUI: ", 		b, 0,24,
				   (char *(*)(u_long))dsmccStrOUI );
	b += 3;
	OUI_data_length -= 3;
	len -= 3;

	// the following is special to Premiere DSM-CC to prevent segfaults
	// Premiere seems to set short OUI_data_length
	if (OUI_data_length <= 0) continue;

    	selector_length = outBit_Sx_NL (4,"selector_length: ",  b, 0, 8);
       	print_databytes (4,"Selector Bytes:", b+1,selector_length);
		b 		+= (selector_length +1);	// +1 = length byte
		OUI_data_length -= (selector_length +1);
		len 		-= (selector_length +1);
    }

    if (len > 0) {
	print_private_data (4, b,len);
    }

}



/*
 * -- as defined as private data for DSM-CC  
 * -- in EN 301 192
 */

void sub_descriptorDVB_Linkage0x0B (u_char *b, int len)			 /* $$$ TODO */
{

 typedef struct  _descLinkage0x0B {
    u_int      platform_id_data_length;		

        // inner Loop 1
    	u_long     platform_id;		
	u_int      platform_name_loop_length;		

        // inner Loop 2
    	u_char     ISO639_2_language_code[4];
    	u_int      platform_name_length;

 } descLinkage0x0B;



 descLinkage0x0B  d;
 int		  len_loop1;



 d.platform_id_data_length     	 = b[0];
 out_SB_NL  (4,"Platform_ID_data_length: ",d.platform_id_data_length);

 len_loop1 = d.platform_id_data_length;
 b++;
 len--;

 indent (+1);
 while (len_loop1 > 0) {

	int		 len_loop2;

        d.platform_id 	 		= getBits (b, 0,  0, 24);
        d.platform_name_loop_length  	= getBits (b, 0, 24,  8);
	b += 4;
	len -= 4;

        out_S2T_NL  (4,"Platform_id: ",d.platform_id,
			dsmccStrPlatform_ID (d.platform_id));
        out_SB_NL  (4,"Platform_name_loop_length: ",d.platform_name_loop_length);

	len_loop1 -= 4;
        len_loop2 = d.platform_name_loop_length;

	indent (+1);
	while (len_loop2 > 0) {

	 	getISO639_3 (d.ISO639_2_language_code, b);	
 		out_nl (4,"  ISO639_language_code:  %3.3s", d.ISO639_2_language_code);
        	d.platform_name_length  = getBits (b, 0, 24,  8);
 		print_text_468A (4, "Platform_name: ", b+4,d.platform_name_length);

		b +=  d.platform_name_length + 4;
		len -= d.platform_name_length + 4;
		len_loop2 -= d.platform_name_length + 4;

		out_NL (4);
	}
	indent (-1);

        len_loop1 -= d.platform_name_loop_length;

 }
 indent (-1);


 print_private_data (4, b,len);


}



void sub_descriptorDVB_Linkage0x0C (u_char *b, int len)
{

  u_int      table_id;		
  u_int      bouquet_id;



 table_id				= getBits (b, 0,  0, 8);
 out_S2W_NL  (4,"Table_id: ",table_id, dsmccStrLinkage0CTable_TYPE(table_id));

 if (table_id == 2) {
	bouquet_id			= getBits (b, 0,  8, 16);
 	out_S2W_NL  (4,"Bouquet_id: ",bouquet_id, dvbstrBouquetTable_ID (bouquet_id));
 }

}
















/*
  0x4B  NVOD Reference  descriptor 
  ETSI EN 300 468  6.2.xx
  --- checked v1.6.1
*/

void descriptorDVB_NVOD_Reference  (u_char *b)
{
 int          len;


 // tag 	= b[0];
 len		= b[1];

 b  += 2;

 indent (+1);
 while (len > 0) {
    // $$$ TODO this part is re-usable
    outBit_Sx_NL  (4,"transport_stream_ID: ",	b,   0, 16);
    outBit_S2x_NL (4,"original_network_id: ",	b,  16, 16,
			(char *(*)(u_long)) dvbstrOriginalNetwork_ID);
    outBit_S2Tx_NL(4,"service_ID: ",		b,  32, 16,
			" --> refers to PMT program_number"); 

    len -= 6;
    b   += 6;
    out_NL (4);
 }
 indent (-1);

}







/*
  0x4C  Time Shifted Service   descriptor 
  ETSI EN 300 468     6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_TimeShiftedService  (u_char *b)
{
  // tag		= b[0];
  // len		= b[1];

  outBit_Sx_NL  (4,"reference_service_ID: ",	b,   16, 16);

}







/*
  0x4D  Short Event  descriptor 
  ETSI EN 300 468     6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_ShortEvent  (u_char *b)
{
  int      len2;
  u_char   ISO639_2_language_code[4];


  // tag	= b[0];
  // len	= b[1];

 getISO639_3 (ISO639_2_language_code, b+2);
 out_nl (4,"  ISO639_2_language_code:  %3.3s", ISO639_2_language_code);
 b+= 5;


 len2 =  outBit_Sx_NL  (4,"event_name_length: ", b,  0, 8);
 b += 1;
 print_text_468A (4, "event_name: ", b,len2);
 b += len2;


 len2 =  outBit_Sx_NL  (4,"text_length: ", b,  0, 8);
 b += 1;
 print_text_468A (4, "text_char: ", b,len2);

}






/*
  0x4E  Extended Event  descriptor 
  ETSI EN 300 468     6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_ExtendedEvent  (u_char *b)
{

 typedef struct  _descExtendedEvent {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      descriptor_number;
    u_int      last_descriptor_number;
    u_char     ISO639_2_language_code[4];
    u_int      length_of_items;

    // N   Ext. Events List

    u_int      text_length;
    // N4  char  text char
 } descExtendedEvent;


 typedef struct  _descExtendedEvent2 {
    u_int      item_description_length;
    //  N2   descriptors
    u_int      item_length;
    //  N3   chars
 } descExtendedEvent2;


 descExtendedEvent    d;
 descExtendedEvent2   d2;
 int                  len1, lenB;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.descriptor_number		 = getBits (b, 0, 16, 4);
 d.last_descriptor_number	 = getBits (b, 0, 20, 4);
 getISO639_3 (d.ISO639_2_language_code, b+3);	
 d.length_of_items		 = getBits (b, 0, 48, 8);


 out_SB_NL (4,"descriptor_number: ",d.descriptor_number);
 out_SB_NL (4,"last_descriptor_number: ",d.last_descriptor_number);
 out_nl    (4,"ISO639_2_language_code:  %3.3s", d.ISO639_2_language_code);
 out_SB_NL (5,"length_of_items: ",d.length_of_items);


 b   += 7;
 lenB = d.descriptor_length - 5;
 len1 = d.length_of_items;

 indent (+1);
 while (len1 > 0) {
 
   d2.item_description_length	 = getBits (b, 0, 0, 8);
   out_NL (4);
   out_SB_NL (5,"item_description_length: ",d2.item_description_length);
   print_text_468A (4, "item_description: ", b+1, d2.item_description_length);

   b += 1 + d2.item_description_length;
   

   d2.item_length	 	 = getBits (b, 0, 0, 8);
   out_SB_NL (5,"item_length: ",d2.item_length);
   print_text_468A (4, "item: ", b+1, d2.item_length);

   b += 1 + d2.item_length;

   len1 -= (2 + d2.item_description_length + d2.item_length);
   lenB -= (2 + d2.item_description_length + d2.item_length);

 }
 out_NL (4);
 indent (-1);



   d.text_length		 = getBits (b, 0, 0, 8);
   b += 1;
   lenB -= 1;


   out_SB_NL (5,"text_length: ",d.text_length);
   print_text_468A (4, "text: ", b,d.text_length);

}







/*
  0x4F  Time Shifted Event  descriptor 
  ETSI EN 300 468     6.2.xx
  --- checked v1.6.1
*/

void descriptorDVB_TimeShiftedEvent  (u_char *b)
{

  // tag	= b[0];
  // len	= b[1];

  outBit_Sx_NL  (4,"reference_service_id: ", b,  16, 16);
  outBit_Sx_NL  (4,"reference_event_id: ",   b,  32, 16);
 
}







/*
  0x50  Component descriptor 
  ETSI EN 300 468     6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_Component  (u_char *b)
{

 typedef struct  _descComponent {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_int      stream_content;
    u_int      component_type;
    u_int      component_tag;
    u_char     ISO639_2_language_code[4];

    // N2  char Text

 } descComponent;


 descComponent d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 4);
 d.stream_content		 = getBits (b, 0, 20, 4);
 d.component_type		 = getBits (b, 0, 24, 8);
 d.component_tag		 = getBits (b, 0, 32, 8);
 getISO639_3 (d.ISO639_2_language_code, b+5);	

 
 out_SB_NL (6,"reserved: ",d.reserved_1);
 out_SB_NL (4,"stream_content: ",d.stream_content);
 out_SB_NL (4,"component_type: ",d.component_type);
 out_nl    (4,"   == Content&Component: (= %s)",
      dvbstrStreamContent_Component_TYPE(
	(d.stream_content << 8) | d.component_type ) );

 out_SB_NL (4,"component_tag: ",d.component_tag);
 out_nl    (4,"ISO639_language_code:  %3.3s", d.ISO639_2_language_code);

 print_text_468A (4, "component-description: ", b+8,d.descriptor_length - 6);

}








/*
  0x51  Mosaic  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_Mosaic  (u_char *b)

{

 typedef struct  _descMosaic {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      mosaic_entry_point;
    u_int      number_of_horizontal_elementary_cells;
    u_int      reserved_1;
    u_int      number_of_vertical_elementary_cells;

    // N    desc Mosaic2

 } descMosaic;

 typedef struct  _descMosaic2 {
    u_int      logical_cell_id;
    u_int      reserved_1;
    u_int      logical_cell_presentation_info;
    u_int      elementary_cell_field_length;

    // N2   desc Mosaic3

    u_int      cell_linkage_info;
    //  conditional data !! (cell_linkage_info)
    u_int   bouquet_id;
    u_int   original_network_id;
    u_int   transport_stream_id;
    u_int   service_id;
    u_int   event_id;
 } descMosaic2;

 typedef struct  _descMosaic3 {
    u_int      reserved_1;
    u_int      elementary_cell_id;
 } descMosaic3;




 descMosaic    d;
 descMosaic2   d2;
 descMosaic3   d3;
 int           len1,len2;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.mosaic_entry_point                    = getBits (b, 0, 16,  1);
 d.number_of_horizontal_elementary_cells = getBits (b, 0, 17,  3);
 d.reserved_1                            = getBits (b, 0, 20,  1);
 d.number_of_vertical_elementary_cells   = getBits (b, 0, 21,  3);

 
 out_SB_NL (4,"Mosaic_entry_point: ",d.mosaic_entry_point);
 out_nl    (4,"Number_of_horizontal_elementary_cells: %u  (= %d cells)",
	d.number_of_horizontal_elementary_cells,
	d.number_of_horizontal_elementary_cells + 1);
 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_nl    (4,"  Number_of_vertical_elementary_cells: %u  (= %d cells)",
	d.number_of_vertical_elementary_cells,
	d.number_of_vertical_elementary_cells + 1);

 len1 = d.descriptor_length - 1;
 b   += 3;

 indent(+1);
 while (len1 > 0) {

    d2.logical_cell_id                       = getBits (b, 0,  0,  6);
    d2.reserved_1                            = getBits (b, 0,  6,  7);
    d2.logical_cell_presentation_info        = getBits (b, 0, 13,  3);
    d2.elementary_cell_field_length          = getBits (b, 0, 16,  8);


    out_NL (4);
    out_SB_NL  (4,"Logical_cell_ID: ",d2.logical_cell_id);
    out_SB_NL  (6,"reserved_1: ",d2.reserved_1);
    out_S2B_NL (4,"Logical_cell_presentation_info: ",
	d2.logical_cell_presentation_info,
	dvbstrLogCellPresInfo_TYPE(d2.logical_cell_presentation_info) );
    out_SB_NL (5,"Elementary_cell_field_length: ",
	d2.elementary_cell_field_length);

    b    += 3;
    len2  = d2.elementary_cell_field_length;
    len1 -= (len2 + 3);

    indent (+1);
    while (len2 > 0) {
       d3.reserved_1                         = getBits (b, 0,  0,  2);
       d3.elementary_cell_id                 = getBits (b, 0,  2,  6);

       len2 -= 1;
       b    += 1;

       out_NL (4);	
       out_SB_NL (6,"reserved_1: ",d3.reserved_1);
       out_SB_NL (4,"Elementary_cell_ID: ",d3.elementary_cell_id);

    }  //len2
    indent (-1);


    d2.cell_linkage_info                     = getBits (b, 0,  0,  8);
    b    += 1;
    len1 -= 1;
    out_S2B_NL (4,"Cell_linkage_info: ",
		d2.cell_linkage_info,
		dvbstrCellLinkageInfo_TYPE (d2.cell_linkage_info));


    /*   conditional fields!! */

    switch (d2.cell_linkage_info) {

      case 0x01:
	d2.bouquet_id		 = getBits (b, 0, 0, 16);
	b    += 2;
	len1 -= 2;
	out_S2W_NL (4,"bouquet_ID: ",d2.bouquet_id,dvbstrBouquetTable_ID(d2.bouquet_id));
	break;

      case 0x02:
      case 0x03:
      case 0x04:
 	d2.transport_stream_id		 = getBits (b, 0, 0, 16);
	d2.original_network_id		 = getBits (b, 0, 16, 16);
	d2.service_id			 = getBits (b, 0, 32, 16);
	b    += 6;
	len1 -= 6;

 	out_SW_NL  (4,"transport_stream_ID: ",d2.transport_stream_id);
	out_S2W_NL (4,"original_network_ID: ",d2.original_network_id,
	    dvbstrOriginalNetwork_ID(d2.original_network_id));
	out_S2W_NL (4,"service_ID: ",d2.service_id,
          " --> refers to PMT program_number");


	if (d2.cell_linkage_info == 0x03)
		out_nl (4,"  --> Service referce to mosaic service");

	if (d2.cell_linkage_info == 0x04) {
		out_nl (4,"  --> Service referce to event");

 		d2.event_id	 = getBits (b, 0, 0, 16);
		b    += 2;
		len1 -= 2;
 		out_SW_NL (4,"Event_ID: ",d2.event_id);
	}

	break;

    } // switch
    

 } // while len1
 indent(-1);

}









/*
  0x52  Stream Identifier descriptor
  ETSI EN 300 468  6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_StreamIdent (u_char *b)
{

  // tag	= b[0];
  // len	= b[1];

  outBit_Sx_NL  (4,"component_tag: ",   b,  16, 8);

}








/*
  0x53  CA Identifier  descriptor 
  ETSI EN 300 468   6.2.xx
  -- checked v1.6.1
*/

void descriptorDVB_CAIdentifier  (u_char *b)
{
 int         len;

 // tag		= b[0];
 len 		= b[1];

 b  += 2;

 indent (+1);
 while (len > 0) {

   outBit_S2x_NL (4,"CA_system_ID: ",	b,  0, 16,
			(char *(*)(u_long)) dvbstrCASystem_ID );

   b   += 2;
   len -= 2;
 }
 indent (-1);

}









/*
  0x54  Content  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_Content  (u_char *b)

{

 typedef struct  _descContent {
    u_int      descriptor_tag;
    u_int      descriptor_length;		
 } descContent;

 typedef struct  _descContent2 {
    u_int      content_nibble_level_1;
    u_int      content_nibble_level_2;
    u_int      user_nibble_1;
    u_int      user_nibble_2;
 } descContent2;


 descContent   d;
 descContent2  d2;
 int           len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 len = d.descriptor_length;
 b  += 2;
 
 indent (+1);
 while ( len > 0) {
    d2.content_nibble_level_1	 = getBits (b,0, 0,4);
    d2.content_nibble_level_2	 = getBits (b,0, 4,4);
    d2.user_nibble_1		 = getBits (b,0, 8,4);
    d2.user_nibble_2		 = getBits (b,0,12,4);

    b   += 2;
    len -= 2;
 
    out_SB_NL (4,"Content_nibble_level_1: ", d2.content_nibble_level_1);
    out_SB_NL (4,"Content_nibble_level_2: ", d2.content_nibble_level_2);
    out_nl    (4,"   [= %s]", dvbstrContentNibble_TYPE (
	(d2.content_nibble_level_1 << 8) | d2.content_nibble_level_2) );

    out_SB_NL (4,"User_nibble_1: ", d2.user_nibble_1);
    out_SB_NL (4,"User_nibble_2: ", d2.user_nibble_2);
    out_NL (4);
 }
 indent (-1);

}











/*
  0x55  Parental Rating  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_ParentalRating (u_char *b)

{

 typedef struct  _descParentalRating {
    u_int      descriptor_tag;
    u_int      descriptor_length;		
 } descParentalRating;

 typedef struct  _descParentalRating2 {
    char       country_code[4];
    u_int      rating;		
 } descParentalRating2;



 descParentalRating   d;
 descParentalRating2  d2;
 int                  len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 len = d.descriptor_length;
 b  += 2;

 indent (+1);
 while (len > 0) {
    strncpy (d2.country_code, (char *)b, 3);	
    d2.rating			 = getBits (b,0,24,8);

    b += 4;
    len -= 4;

    out_nl     (4,"Country_code:  %3.3s", d2.country_code);
    out_S2B_NL (4,"Rating:  ", d2.rating,
	dvbstrParentalRating_TYPE (d2.rating));
    out_NL (4);

 }
 indent (-1);
 
}









/*
  -- 0x56 Teletext descriptor
*/

void descriptorDVB_Teletext (u_char *b)

{
 /* ETSI EN 300 468   6.2.xx */

 typedef struct  _descTeletext {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    // N TeleTextList desc

 } descTeletext;

 typedef struct  _descTeletextList {
    u_char     ISO_639_language_code[4];
    u_int      teletext_type;
    u_int      teletext_magazine_number;
    u_int      teletext_page_number;
 } descTeletextList;


 descTeletext      d;
 descTeletextList  d2;
 int               len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 len = d.descriptor_length;
 b  += 2;

 indent (+1);
 while ( len > 0) {
    getISO639_3 (d2.ISO_639_language_code, b);	
    d2.teletext_type		= getBits (b,0,24,5);
    d2.teletext_magazine_number	= getBits (b,0,29,3);
    d2.teletext_page_number	= getBits (b,0,32,8);

    b += 5;
    len -= 5;

    out_nl     (4,"ISO639_language_code:  %3.3s", d2.ISO_639_language_code);
    out_S2B_NL (4,"Teletext_type: ", d2.teletext_type,
	dvbstrTeletext_TYPE (d2.teletext_type));

    out_SB_NL (4,"Teletext_magazine_number: ",d2.teletext_magazine_number);
    out_SB_NL (4,"Teletext_page_number: ",d2.teletext_page_number);
    out_NL (4);
 }
 indent (-1);

}





/*
  0x57  Telephone  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_Telephone  (u_char *b)

{
  u_int      country_prefix_len;
  u_int      internat_area_code_len;
  u_int      operator_code_len;
  u_int      national_area_code_len;
  u_int      core_number_len;



  // descriptor_tag		 = b[0];
  // len		       	 = b[1];

  outBit_Sx_NL (6,"reserved_1: ",		b, 16, 2);
  outBit_Sx_NL (4,"foreign_availability: ",	b, 18, 1);
  outBit_Sx_NL (4,"connection_type: ",		b, 19, 5);
  outBit_Sx_NL (6,"reserved_2: ",		b, 24, 1);

  country_prefix_len 	= outBit_Sx_NL (4,"country_prefix_length: ",	b, 25, 2);
  internat_area_code_len= outBit_Sx_NL (4,"international_area_code_length: ",	b, 27, 3);
  operator_code_len	= outBit_Sx_NL (4,"operator_code_length: ",	b, 30, 2);
  			  outBit_Sx_NL (6,"reserved_3: ",		b, 32, 1);
  national_area_code_len= outBit_Sx_NL (4,"national_area_code_length: ",b, 33, 3);
  core_number_len	= outBit_Sx_NL (4,"core_number_length: ",	b, 36, 4);
  b += 5;

  out (4,"country_prefix: "); printasciiline_buf (4, b, country_prefix_len);
  b += country_prefix_len;

  out (4,"international_area_code_prefix: "); printasciiline_buf (4, b, internat_area_code_len);
  b += internat_area_code_len;

  out (4,"operator_code: "); printasciiline_buf (4, b, operator_code_len);
  b += operator_code_len;

  out (4,"national_area_code: "); printasciiline_buf (4, b, national_area_code_len);
  b += national_area_code_len;

  out (4,"core_number: "); printasciiline_buf (4, b, core_number_len);
  b += core_number_len;

}








/*
  0x58  Local Time Offset  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_LocalTimeOffset  (u_char *b)

{

 typedef struct  _descLocalTimeOffset {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    // N  Descriptor
 } descLocalTimeOffset;

 typedef struct  _descLocalTimeOffset2 {
   char          country_code[4];
   u_int         country_region_id;
   u_int         reserved_1;
   u_int         local_time_offset_polarity;
   u_int         local_time_offset;
   u_int         time_of_change_MJD;
   u_int         time_of_change_UTC;
   u_int         next_time_offset;
 } descLocalTimeOffset2;


 descLocalTimeOffset   d;
 descLocalTimeOffset2  d2;
 int                   len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 len = d.descriptor_length;
 b  += 2;
 
 indent (+1);
 while (len > 0) {

    strncpy (d2.country_code, (char *)b, 3);	
    d2.country_region_id	 = getBits (b, 0, 24,  6);
    d2.reserved_1		 = getBits (b, 0, 30,  1);
    d2.local_time_offset_polarity = getBits (b, 0, 31,  1);
    d2.local_time_offset	 = getBits (b, 0, 32, 16);
    d2.time_of_change_MJD	 = getBits (b, 0, 48, 16);
    d2.time_of_change_UTC	 = getBits (b, 0, 64, 24);
    d2.next_time_offset		 = getBits (b, 0, 88, 16);

    len -= 13;
    b   += 13;

    out_nl    (4,"Country_code:  %3.3s", d2.country_code);
    out_SB_NL (4,"Country_region_ID: ",d2.country_region_id);
    out_SB_NL (6,"reserved_1: ",d2.reserved_1);

    out_nl    (4,"local_time_offset_polarity: %u  [= %s to UTC]",
	d2.local_time_offset_polarity,
	(d2.local_time_offset_polarity) ? "minus" : "plus");

    out_nl    (4,"Local_time_offset: %02x:%02x",
	d2.local_time_offset >> 8, d2.local_time_offset & 0xFF);

    out       (4,"Time_of_change: ");
      print_time40 (4, d2.time_of_change_MJD,d2.time_of_change_UTC);
      out_NL (4);

    out_nl    (4,"Next_time_offset: %02x:%02x ",
	d2.next_time_offset >> 8, d2.next_time_offset & 0xFF);

    out_NL(4);

 }
 indent (-1);


}






/*
  0x59  Subtitling  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_Subtitling  (u_char *b)

{

 typedef struct  _descSubTitling {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

 } descSubTitling;

 typedef struct  _descSubTitling2 {
    u_char     ISO_639_language_code[4];
    u_int      subtitling_type;
    u_int      composition_page_id;
    u_int      ancillary_page_id;
 } descSubTitling2;


 descSubTitling   d;
 descSubTitling2  d2;
 int              len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 len = d.descriptor_length;
 b  += 2;

 indent (+1);
 while ( len > 0) {
    getISO639_3 (d2.ISO_639_language_code, b);	
    d2.subtitling_type		= getBits (b,0,24, 8);
    d2.composition_page_id	= getBits (b,0,32,16);
    d2.ancillary_page_id	= getBits (b,0,48,16);

    b   += 8;
    len -= 8;

    out_nl  (4,"  ISO639_language_code:  %3.3s", d2.ISO_639_language_code);
    out_S2B_NL (4,"Subtitling_type: ", d2.subtitling_type,
	dvbstrStreamContent_Component_TYPE (
	    (0x03 << 8) | d2.subtitling_type));

    out_SW_NL (4,"Composition_page_id: ",d2.composition_page_id);
    out_SW_NL (4,"Ancillary_page_id: ",d2.ancillary_page_id);
    out_NL (4);
 }
 indent (-1);

}








/*
  0x5A TerrestDelivSys  descriptor  (Terrestrial delivery system descriptor)
  ETSI 300 468    6.2.xx 
  -- 2004-08-28 update auf EN 300 468 1.6.1 (routine rewritten)
*/

void descriptorDVB_TerrestDelivSys (u_char *b)

{
  u_long  cfreq;


  // tag	 = b[0];
  // len       	 = b[1];

  cfreq				 = getBits (b, 0, 16, 32);
  // frequency is in 10 Hz steps == * 10
  out_nl (4,"Center frequency: 0x%08x (= %lu.%03lu kHz)",cfreq,
		 cfreq / 100, cfreq % 100 );

  outBit_S2x_NL  (4,"Bandwidth: ",  		b, 48,  3,
		 	(char *(*)(u_long)) dvbstrTerrBandwidth_SCHEME );
  outBit_S2x_NL (4,"priority: ",  		b, 51,  1,
		 	(char *(*)(u_long)) dvbstrTerrPriority );
  outBit_S2x_NL (4,"Time_Slicing_indicator: ",	b, 52,  1,
		 	(char *(*)(u_long)) dvbstrTerrTimeSlicingIndicator );
  outBit_S2x_NL (4,"MPE-FEC_indicator: ",	b, 53,  1,
		 	(char *(*)(u_long)) dvbstrTerrMPE_FEC_Indicator );
  outBit_Sx_NL  (6,"reserved_1: ",  		b, 54,  2);
  outBit_S2x_NL (4,"Constellation: ",  		b, 56,  2,
		 	(char *(*)(u_long)) dvbstrTerrConstellation_FLAG );
  outBit_S2x_NL (4,"Hierarchy information: ", 	b, 58,  3,
		 	(char *(*)(u_long)) dvbstrTerrHierarchy_FLAG );
  outBit_S2x_NL (4,"Code_rate_HP_stream: ", 	b, 61,  3,
		 	(char *(*)(u_long)) dvbstrTerrCodeRate_FLAG );
  outBit_S2x_NL (4,"Code_rate_LP_stream: ", 	b, 64,  3,
		 	(char *(*)(u_long)) dvbstrTerrCodeRate_FLAG );
  outBit_S2x_NL (4,"Guard_interval: ", 		b, 67,  2,
		 	(char *(*)(u_long)) dvbstrTerrGuardInterval_FLAG );
  outBit_S2x_NL (4,"Transmission_mode: ", 	b, 69,  2,
		 	(char *(*)(u_long)) dvbstrTerrTransmissionMode_FLAG );
  outBit_Sx_NL  (4,"Other_frequency_flag: ", 	b, 71,  1);
  outBit_Sx_NL  (6,"reserved_2: ", 		b, 72, 32);

}







/*
  0x5B  Multilingual Network Name  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_MultilingNetworkName (u_char *b)

{

 typedef struct  _descMultiNetName {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    //  N .. List2

 } descMultiNetName;

 typedef struct  _descMultiNetName2 {
    u_char     ISO639_2_language_code[4];
    u_int      network_name_length;

    //  N2 ..  char

 } descMultiNetName2;



 descMultiNetName   d;
 descMultiNetName2  d2;
 int                len1;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 b += 2;
 len1 = d.descriptor_length;

 indent (+1);
 while (len1 > 0 ) {

    getISO639_3 (d2.ISO639_2_language_code, b);
    d2.network_name_length	 = getBits (b, 0, 24, 8);

    out_nl    (4,"ISO639_2_language_code:  %3.3s", d2.ISO639_2_language_code);
    out_SB_NL (5,"Network_name_length: ",d2.network_name_length);
    print_text_468A (4, "Network_name: ", b+4,d2.network_name_length);

    len1 -= (4 + d2.network_name_length);
    b    +=  4 + d2.network_name_length;

    out_NL (4);
 }
 indent (-1);

}








/*
  0x5C  Multilingual Bouquet Name  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_MultilingBouquetName (u_char *b)

{

 typedef struct  _descMultiBouqName {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    //  N .. List2

 } descMultiBouqName;

 typedef struct  _descMultiBouqName2 {
    u_char     ISO639_2_language_code[4];
    u_int      bouquet_name_length;

    //  N2 ..  char

 } descMultiBouqName2;



 descMultiBouqName   d;
 descMultiBouqName2  d2;
 int                 len1;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 b += 2;
 len1 = d.descriptor_length;

 indent (+1);
 while (len1 > 0 ) {

    getISO639_3 (d2.ISO639_2_language_code, b);
    d2.bouquet_name_length	 = getBits (b, 0, 24, 8);

    out_nl    (4,"ISO639_2_language_code:  %3.3s", d2.ISO639_2_language_code);
    out_SB_NL (5,"Bouquet_name_length: ",d2.bouquet_name_length);
    print_text_468A (4, "Bouquet_name: ", b+4,d2.bouquet_name_length);

    len1 -= (4 + d2.bouquet_name_length);
    b    +=  4 + d2.bouquet_name_length;

    out_NL (4);
 }
 indent (-1);

}






/*
  0x5D  Multilingual Service Name  descriptor 
  ETSI EN 300 468     6.2.xx
  -- 2004-08-22 Bugfix, rewrite
*/

void descriptorDVB_MultilingServiceName (u_char *b)

{
 int   len;


 // tag		= b[0];
 len 		= b[1];
 b += 2;


 indent (+1);
 while (len > 0 ) {
    int    len2;
    u_char ISO639_2_language_code[4];


    getISO639_3 (ISO639_2_language_code, b);
    out_nl    (4,"ISO639_2_language_code:  %3.3s", ISO639_2_language_code);

    len2 = outBit_Sx_NL  (5,"Service_provider_name_length: ",	b, 24, 8);
    print_text_468A (4, "Service_provider_name: ", b+4,len2);
    b   += 4 + len2;
    len -= 4 + len2;


    len2 = outBit_Sx_NL  (5,"Service_name_length: ",	b, 0, 8);
    print_text_468A      (4, "Service_name: ", 		b+1,len2);
    b   += 1 + len2;
    len -= 1 + len2;

    out_NL (4);

 }
 indent (-1);

}







/*
  0x5E  Multilingual Component  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_MultilingComponent (u_char *b)

{

 typedef struct  _descMultiComponent {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      component_tag;

    //  N .. List2

 } descMultiComponent;

 typedef struct  _descMultiComponent2 {
    u_char     ISO639_2_language_code[4];
    u_int      text_description_length;

    //  N2 ..  char

 } descMultiComponent2;



 descMultiComponent   d;
 descMultiComponent2  d2;
 int                  len1;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];


 d.component_tag 		 = b[2];

 out_SB_NL (4,"Component_tag: ",d.component_tag);

 b += 3;
 len1 = d.descriptor_length - 1;

 indent (+1);
 while (len1 > 0 ) {

    getISO639_3 (d2.ISO639_2_language_code, b);
    d2.text_description_length	 = getBits (b, 0, 24, 8);

    out_nl    (4,"ISO639_2_language_code:  %3.3s", d2.ISO639_2_language_code);
    out_SB_NL (5,"Text_description_length: ",d2.text_description_length);
    print_text_468A (4, "Text_description: ", b+4,d2.text_description_length);

    len1 -= (4 + d2.text_description_length);
    b    +=  4 + d2.text_description_length;

    out_NL (4);
 }
 indent (-1);

}








/*
  0x5F  Private Data Specifier  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_PrivateDataSpecifier (u_char *b)

{

 typedef struct  _descPrivDataSpec {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_long     private_data_specifier;

 } descPrivDataSpec;


 descPrivDataSpec d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.private_data_specifier	 = getBits (b, 0, 16, 32);

 out_S2L_NL (4,"PrivateDataSpecifier: ",d.private_data_specifier,
	dvbstrPrivateDataSpecifier_ID( d.private_data_specifier) );

}







/*
  0x60  Service Move  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_ServiceMove  (u_char *b)

{

  // tag	= b[0];
  // len	= b[1];

  outBit_S2x_NL (4,"New_original_network_ID: ",		b, 16, 16,
	 	(char *(*)(u_long)) dvbstrOriginalNetwork_ID );
  outBit_Sx_NL  (4,"New_transport_stream_ID: ",		b, 32, 16);
  outBit_Sx_NL  (4,"Service_ID: ",			b, 48, 16);
}








/*
  0x61  Short Smoothing Buffer  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_ShortSmoothingBuffer  (u_char *b)

{

  u_int   len;


  // tag 	= b[0];
  len 		= b[1];

 
  outBit_S2x_NL (4,"sb_size: ", 		b, 16, 2,
	 	(char *(*)(u_long)) dvbstrShortSmoothingBufSize_TYPE );
  outBit_S2x_NL (4,"sb_leak_rate: ", 	b, 18, 6,
	 	(char *(*)(u_long)) dvbstrShortSmoothingBufLeakRate_TYPE );

  print_databytes (6,"reserved:", b+3, len-1);
}










/*
  0x62  Frequency List descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_FrequencyList  (u_char *b)

{

 typedef struct  _descFreqList {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_int      coding_type;
 } descFreqList;

 typedef struct  _descFreqList2 {
    u_long     centre_frequency;
 } descFreqList2;


 descFreqList   d;
 descFreqList2  d2;
 int            len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 6);
 d.coding_type			 = getBits (b, 0, 22, 2);

 

 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_S2B_NL (4,"coding_type: ",d.coding_type,
	dvbstrDelivSysCoding_TYPE(d.coding_type));


 b += 3;
 len = d.descriptor_length - 1;
 indent (+1);
 while (len > 0) {

    d2.centre_frequency		 = getBits (b, 0, 0, 32);

    out (4,"Centre_frequency: %08lx  ",d2.centre_frequency);
    switch (d.coding_type) {
	case 0x01:
 	  out_nl (4,"(= %3lx.%05lx GHz)",
	    d2.centre_frequency >> 20, d2.centre_frequency & 0x000FFFFF );
	  break;

	case 0x02:
 	  out_nl (4,"(= %3lx.%04lx MHz)",
	    d2.centre_frequency >> 16, d2.centre_frequency & 0x0000FFFF );
	  break;

	case 0x03:
 	  // frequency is in 10 Hz steps == * 10
	  out_nl (4,"(= %lu.%03lu kHz)",
			  d2.centre_frequency / 100, d2.centre_frequency % 100 );
	  break;
    }

    len -= 4;
    b   += 4;
 }
 indent (-1);


}







/*
  0x63  Partial Transport Stream Descriptor
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_PartialTransportStream  (u_char *b)

{

 typedef struct  _descPartTranspStream {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      reserved_1;
    u_long     peak_rate;
    u_int      reserved_2;
    u_long     minimum_overall_smoothing_rate;
    u_int      reserved_3;
    u_int      maximum_overall_smoothing_buffer;

 } descPartTranspStream;


 descPartTranspStream   d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.reserved_1			 = getBits (b, 0, 16, 2);
 d.peak_rate			 = getBits (b, 0, 18, 22);
 d.reserved_2			 = getBits (b, 0, 40, 2);
 d.minimum_overall_smoothing_rate= getBits (b, 0, 42, 22);
 d.reserved_3			 = getBits (b, 0, 64, 2);
 d.maximum_overall_smoothing_buffer= getBits (b, 0, 66, 14);

 

 out_SB_NL (6,"reserved_1: ",d.reserved_1);
 out_nl    (4,"peak_rate: 0x%06lx  (= %lu bits/sec)",
	d.peak_rate,d.peak_rate/400);

 out_SB_NL (6,"reserved_2: ",d.reserved_2);
 out_nl    (4,"minimum_overall_smoothing_rate: 0x%06lx  (= %lu bits/sec)",
	d.minimum_overall_smoothing_rate,
	d.minimum_overall_smoothing_rate/400);

 out_SB_NL (6,"reserved_3: ",d.reserved_3);
 out_nl    (4,"maximum_overall_smoothing_buffer: 0x%04x  (= %lu bits/sec)",
	d.maximum_overall_smoothing_buffer,
	d.maximum_overall_smoothing_buffer/400);


}









/*
  0x64  DataBroadcast  descriptor 
  ETSI EN 300 468    6.2.xx
*/

void descriptorDVB_DataBroadcast (u_char *b)

{

 typedef struct  _descDataBroadcast {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      data_broadcast_id;
    u_int      component_tag;
    int        selector_length;

    // N   bytes

    u_char     ISO639_2_language_code[4];
    u_int      text_length;

    // N2  char 

 } descDataBroadcast;


 descDataBroadcast d;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.data_broadcast_id		 = getBits (b, 0, 16, 16);
 d.component_tag		 = getBits (b, 0, 32, 8);
 d.selector_length		 = getBits (b, 0, 40, 8);
 b  += 6;

 
 out_S2W_NL (4,"Data_broadcast_ID: ",d.data_broadcast_id,
	dvbstrDataBroadcast_ID(d.data_broadcast_id));

 out_SB_NL (4,"Component_tag: ",d.component_tag);
 out_SB_NL (5,"Selector_length: ",d.selector_length);


 indent (+1);
 if (d.data_broadcast_id == 0x0005) {
	 /* -- EN 301 192 Multi-protocol-encapsulation! */

 		typedef struct  _descMultiProtEncaps {
			u_int	MAC_address_range;
			u_int	MAC_ip_mapping_flag;
			u_int	alignment_indicator;
			u_int   reserved;
			u_int   max_sections_per_datagram;
 		} descMultiProtEncaps;


		descMultiProtEncaps e;

 		out_nl    (4,"Multi_Protocol_Encapsulation [EN 301 192]:");
 		e.MAC_address_range	 = getBits (b, 0,  0,  3);
 		e.MAC_ip_mapping_flag	 = getBits (b, 0,  3,  1);
 		e.alignment_indicator	 = getBits (b, 0,  4,  1);
 		e.reserved		 = getBits (b, 0,  5,  3);
 		e.max_sections_per_datagram = getBits (b, 0,  8,  8);

 		out_S2B_NL (5,"MAC_address_range: ",e.MAC_address_range,
			dsmccStrMultiProtEncapsMACAddrRangeField (e.MAC_address_range) );
 		out_SB_NL (5,"MAC_ip_mapping_flag: ",e.MAC_ip_mapping_flag);
 		out_S2B_NL (5,"alignment_indicator: ",e.alignment_indicator,
					(e.alignment_indicator) ?"32 bit": "8 bit");
 		out_SB_NL (6,"reserved: ",e.reserved);
 		out_SB_NL (5,"max_sections_per_datagram: ",e.max_sections_per_datagram);

 } else if (d.data_broadcast_id == 0x0006) {
	 /* --  EN 301 192 8.3.1 */

 		typedef struct  _descDATA_CAROUSEL_INFO {
			u_int	carousel_type_id;
			u_int	reserved_1;
			u_long	transaction_id;
			u_long  timeout_value_DSI;
			u_long  timeout_value_DII;
			u_int	reserved_2;
			u_long	leak_rate;
 		} descDATA_CAROUSEL_INFO;


		descDATA_CAROUSEL_INFO c;


 		out_nl    (4,"Data_Carousel_info:");
 		c.carousel_type_id		= getBits (b, 0,  0,  2);
 		c.reserved_1			= getBits (b, 0,  2,  6);
 		c.transaction_id		= getBits (b, 0,  8, 32);
 		c.timeout_value_DSI		= getBits (b, 0, 40, 32);
 		c.timeout_value_DII		= getBits (b, 0, 72, 32);
 		c.reserved_2			= getBits (b, 0,104,  2);
 		c.leak_rate			= getBits (b, 0,106, 22);

 		out_S2B_NL (5,"carousel_type_id: ",c.carousel_type_id,
			dsmccStrCarouselType_ID (c.carousel_type_id) );
 		out_SB_NL (6,"reserved_1: ",c.reserved_1);
 		out_SL_NL (5,"transaction_id: ",c.transaction_id);
 		out_SL_NL (5,"timeout_value_DSI: ",c.timeout_value_DSI);
 		out_SL_NL (5,"timeout_value_DII: ",c.timeout_value_DII);
 		out_SB_NL (6,"reserved_2: ",c.reserved_2);
 		out_SL_NL (5,"leak_rate: ",c.leak_rate);

 } else if (d.data_broadcast_id == 0x0007) {
	 /* -- EN 301 192 9.3.2 */

 		typedef struct  _descOBJECT_CAROUSEL_INFO {
			u_int	carousel_type_id;
			u_int	reserved_1;
			u_long	transaction_id;
			u_long  timeout_value_DSI;
			u_long  timeout_value_DII;
			u_int	reserved_2;
			u_long	leak_rate;
			// --
 		} descOBJECT_CAROUSEL_INFO;


		descOBJECT_CAROUSEL_INFO c;
		u_char                   *b1; 
		int                      len1;


		out_nl    (4,"Object_Carousel_Info:");
 		c.carousel_type_id		= getBits (b, 0,  0,  2);
 		c.reserved_1			= getBits (b, 0,  2,  6);
 		c.transaction_id		= getBits (b, 0,  8, 32);
 		c.timeout_value_DSI		= getBits (b, 0, 40, 32);
 		c.timeout_value_DII		= getBits (b, 0, 72, 32);
 		c.reserved_2			= getBits (b, 0,104,  2);
 		c.leak_rate			= getBits (b, 0,106, 22);

 		out_S2B_NL (5,"carousel_type_id: ",c.carousel_type_id,
			dsmccStrCarouselType_ID (c.carousel_type_id) );
 		out_SB_NL (6,"reserved_1: ",c.reserved_1);
 		out_SL_NL (5,"transaction_id: ",c.transaction_id);
 		out_SL_NL (5,"timeout_value_DSI: ",c.timeout_value_DSI);
 		out_SL_NL (5,"timeout_value_DII: ",c.timeout_value_DII);
 		out_SB_NL (6,"reserved_2: ",c.reserved_2);
 		out_SL_NL (5,"leak_rate: ",c.leak_rate);

		b1 = b + 16;
		len1 = d.selector_length - 16;

		while (len1 > 0) {
    			u_char     ISO639_2_language_code[4];
			int        object_name_length;

 			getISO639_3 (ISO639_2_language_code, b1);
			object_name_length		 = getBits (b1, 0, 24, 8);

			out_nl    (5,"ISO639_2_language_code:  %3.3s", ISO639_2_language_code);
			out_SB_NL (5,"object_name_length: ",object_name_length);
			print_text_468A (5, "object_name: ", b1+4,object_name_length);

			b1   += (4 + object_name_length);
			len1 -= (4 + object_name_length);
		}

/* $$$ TODO  what is 0x0008 */

 } else if (d.data_broadcast_id == 0x0009) {
	 /* --  EN 301 192 10.2.1 */

 		typedef struct  _descHIGH_PROT_ASYNC_DATA_INFO {
			u_int	higher_protocol_id;
			u_int	reserved;
			// private data
 		} descHIGH_PROT_ASYNC_DATA_INFO;


		descHIGH_PROT_ASYNC_DATA_INFO  c;


		out_nl    (4,"higher_protocol_asynchronous_data_info:");
 		c.higher_protocol_id 		= getBits (b, 0,  0,  4);
 		c.reserved			= getBits (b, 0,  4,  4);

 		out_S2B_NL (5,"higher_protocol_id: ",c.higher_protocol_id,
			dsmccStrHigherProtocol_ID (c.higher_protocol_id) );
 		out_SB_NL (6,"reserved: ",c.reserved);
		print_private_data (5, b+1, d.selector_length-1);

 } else if (d.data_broadcast_id == 0x000A) {
	 /* TR 102 006 */

 		typedef struct  _descSUI {
    		   int      OUI_data_length;
		   u_long   OUI;
		   u_int    updt_type;
		   int      selector_length2;
		} descSUI;

		descSUI  s;
		int      len2;


		out_nl    (4,"Software_update_info:");
		s.OUI_data_length = outBit_Sx_NL (4,"OUI_data_length: ", b,0,8);
    		b++;

   		while (s.OUI_data_length > 0) {
    		   outBit_S2x_NL (4,"OUI: ", 			b,0,24,
				   (char *(*)(u_long))dsmccStrOUI);
    		   outBit_Sx_NL (6,"reserved: ", 		b,24, 4);
    		   s.updt_type = outBit_S2x_NL (4,"update_type: ",b,28, 4,
				   (char *(*)(u_long))dsmccStrUpdateType_ID);
    		   outBit_Sx_NL (6,"reserved: ", 		b,32, 2);
    		   outBit_Sx_NL (4,"update_versioning_flag: ", 	b,34, 1);
    		   outBit_Sx    (4,"update_version: ", 		b,35, 5);
		   	if (s.updt_type == 0x02 || s.updt_type == 0x03) {
		   		out (4, "  [--> refers to UNT version number]");
		   	}
		   	out_NL (4);


		   s.selector_length2 = outBit_Sx_NL (4,"selector_length: ", b,40, 8);
		   b += 6;
		   s.OUI_data_length -= 6;
        	   print_databytes (4,"Selector bytes:", b,s.selector_length2);
			b += s.selector_length2;
			s.OUI_data_length -= s.selector_length2;
    		}

		len2 = d.selector_length - s.OUI_data_length -1;
    		if (len2 > 0) {
		   print_private_data (4, b,len2);
    		}

 } else {
	// 0x0002 == asynchronous Data Streaming
	// 0x0003 == indicate a synchronous data stream
	// 0x0004 == synchronised data streams
	// ...
 	print_databytes (4,"Selector bytes:",  b, d.selector_length);
 }
 indent (-1);


 b += d.selector_length;
 getISO639_3 (d.ISO639_2_language_code, b);
 d.text_length			 = getBits (b, 0, 24, 8);

 out_nl    (4,"ISO639_2_language_code:  %3.3s", d.ISO639_2_language_code);
 out_SB_NL (5,"Text_length: ",d.text_length);
 print_text_468A (4, "Text: ", b+4,d.text_length);

}








/*
  0x65  Scrambling descriptor 
  ETSI EN 300 468     
  -- updated 1.7.1 (maybe prior) 
*/

void descriptorDVB_Scrambling (u_char *b)

{

  // tag = b[0];
  // len = b[1];

  outBit_Sx_NL (4,"scrambling_mode: ",	b,  16, 8);
}






/*
  0x66  Data Broadcast ID  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_DataBroadcastID  (u_char *b)

{

 typedef struct  _descDataBroadcastID {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      data_broadcast_id;

    //  N ... id_selector bytes
 } descDataBroadcastID;


 descDataBroadcastID   d;
 int 		       len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.data_broadcast_id		 = getBits (b, 0, 16, 16);
 b+=4;
 len = d.descriptor_length -2;

 
 out_S2W_NL (4,"Data_broadcast_ID: ",d.data_broadcast_id,
	dvbstrDataBroadcast_ID(d.data_broadcast_id));

 // $$$ ID selector bytes may depend on databroadcast_id
 // $$$ do further more selection here
 // $$$ EN 301 192 Stuff TODO


 if (d.data_broadcast_id == 0x000A) {

	// TR 102 006  Software update  S.12
	int  OUI_data_len;
	int  i;


	out_nl    (4,"system_software_update_info [TR 102 006]:");
 	OUI_data_len = outBit_Sx_NL (4,"OUI_data_length: ",	b, 0, 8);
	b++;
	len--;

	i = OUI_data_len;
	while (i > 0) {
		int len2;

		out_NL (5);
		indent (+1);

	    	outBit_S2x_NL(5,"OUI: ", 		b, 0,24,
				   (char *(*)(u_long))dsmccStrOUI );
 		outBit_Sx_NL (6,"reserved_1: ",		b,24, 4);
 		outBit_S2x_NL(5,"update_type: ",	b,28, 4,
				   (char *(*)(u_long)) dsmccStrUpdateType_ID );
 		outBit_Sx_NL (6,"reserved_2: ",		b,32, 2);
 		outBit_Sx_NL (5,"update_versioning_flag: ",	b,34, 1);
 		outBit_Sx_NL (5,"update_version: ",	b,35, 5);

 		len2 = outBit_Sx_NL (5,"selector_length: ",	b,40, 8);
		b += 6;
		len -= 6;
		i   -= 6;

	     	print_databytes (5,"Selector bytes:", b, len2);
		b += len2;
		len -= len2;
		i   -= len2;

		indent (-1);
	}

	print_private_data (5, b, len);


 } else if (d.data_broadcast_id == 0x000B) {
	 // -- EN 301 192 PSI Signalling IP/MAC Notification Table

	 {
 		typedef struct  _descIPMAC_NOTIF_TABLE {
			int	platform_id_data_length;
			// inner loop
			u_long	platform_id;
			u_int	action_type;
			u_int	reserved;
			u_int	INT_versioning_flag;
			u_int	INT_version;
 		} descIPMAC_NOTIF_TABLE;


		descIPMAC_NOTIF_TABLE   d;
		int 		 	len2;


 		out_nl    (4,"IP/MAC Notification [EN 301 192]:");

 		d.platform_id_data_length = getBits (b, 0,  0,  8);
 		out_SW_NL (5,"Platform_id_data_length: ",d.platform_id_data_length);
		b++;
		len--;
		len2 = d.platform_id_data_length;

		indent (+1);
		while (len2 > 0) {
		   out_NL (5);
        	   d.platform_id  		= getBits (b, 0,  0, 24);
        	   d.action_type		= getBits (b, 0, 24,  8);
        	   d.reserved			= getBits (b, 0, 32,  2);
        	   d.INT_versioning_flag	= getBits (b, 0, 34,  1);
        	   d.INT_version		= getBits (b, 0, 35,  5);
		   b += 5;
		   len -= 5;
		   len2 -= 5;

 		   out_S2T_NL  (5,"Platform_id: ",d.platform_id,
				   dsmccStrPlatform_ID (d.platform_id));
 		   out_S2B_NL  (5,"Action_type: ",d.action_type,
				   dsmccStrAction_Type(d.action_type));
 		   out_SB_NL  (5,"reserved: ",d.reserved);
 		   out_SB_NL  (5,"INT_versioning_flag: ",d.INT_versioning_flag);
 		   out_SB_NL  (5,"INT_version: ",d.INT_version);

		}
		indent (-1);
 	
     		print_private_data (5, b, len);


	 }
	
 } else {

     	print_databytes(4,"ID_selector_bytes:", b, len);

 }

}





/*
  0x67  Transport Stream  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_TransportStream  (u_char *b)

{
  u_int    len;


  // tag	= b[0];
  len 		= b[1];
 
  print_databytes (4,"transport_stream_bytes:", b+2, len);
}








/*
  0x68  DSNG  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_DSNG  (u_char *b)

{
  u_int   len;


  // tag	= b[0];
  len 		= b[1];

  print_databytes (4,"DSNG_bytes:", b+2, len);
}



/*
  0x69  PDC  descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_PDC  (u_char *b)

{
    u_long     programme_identification_label;
    // ... splits in
    u_int     day;
    u_int     month;
    u_int     hour;
    u_int     minute;



 // tag		 = b[0];
 // lenh       	 = b[1];

 outBit_Sx_NL (6,"reserved: ",   	b,  16,  4);

 programme_identification_label = getBits (b, 0, 20, 20);
    day     = getBits (b,0,20,5);
    month   = getBits (b,0,25,4);
    hour    = getBits (b,0,29,5);
    minute  = getBits (b,0,34,6);

 out (4,"Programme_identification_label: 0x%05lx ", programme_identification_label);
 out (4,"[= month=%d  day=%d   hour=%d  min=%d]", month, day, hour, minute);
 out_NL (4);
}





/*
  0x6A  AC-3  descriptor 
  ETSI EN 300 468    ANNEX E 
  -- updated
*/

void descriptorDVB_AC3  (u_char *b)

{

   u_int      len;
   u_int      comp_type_flag;
   u_int      bsid_flag;
   u_int      mainid_flag;
   u_int      asvc_flag;


  // tag 	= b[0];
  len 		= b[1];

  comp_type_flag= outBit_Sx_NL (4,"component_type_flag: ",b,16,  1);
  bsid_flag     = outBit_Sx_NL (4,"bsid_flag: ",   	b,  17,  1);
  mainid_flag   = outBit_Sx_NL (4,"mainid_flag: ",   	b,  18,  1);
  asvc_flag     = outBit_Sx_NL (4,"asvc_flag: ",   	b,  19,  1);
                  outBit_Sx_NL (4,"reserved: ",   	b,  20,  4);

  b   += 3;
  len -= 1;


 if (comp_type_flag) {
     outBit_S2x_NL (4,"component_type: ", b++,  0, 8,
	 	(char *(*)(u_long)) dvbstrDVB_AC3_ComponentType );
     len--;
 }

 if (bsid_flag) {
     outBit_Sx_NL (4,"bsid: ",		b++,  0, 8);
     len--;
 }

 if (mainid_flag) {
     outBit_Sx_NL (4,"mainid: ",	b++,  0, 8);
     len--;
 }

 if (asvc_flag) {
     outBit_Sx_NL (4,"asvc: ",		b++,  0, 8);
     len--;
 }

 print_databytes (4,"Additional_info:", b, len);

}





/*
  0x6B  Ancillary Data  descriptor 
  ETSI EN 300 468 v1.6.1
  -- updated EN 300 468 v1.7.1
*/

void descriptorDVB_AncillaryData  (u_char *b)
{
  u_int  adi;


  // tag	 = b[0];
  // len       	 = b[1];


  adi = outBit_Sx_NL (4,"Ancillary_data_identifier: ",   b,  16,  8);

  // $$$  the following should normally in dvbStrAncillaryData...()
  indent (+1);
   if (adi & 0x01) out_nl (4,"[= DVD-Video Ancillary Data]");
   if (adi & 0x02) out_nl (4,"[= Extended Ancillary Data]");
   if (adi & 0x04) out_nl (4,"[= Announcement Switching Data]");
   if (adi & 0x08) out_nl (4,"[= DAB Ancillary Data]");
   if (adi & 0x10) out_nl (4,"[= Scale Factor Error Check]");
   if (adi & 0x20) out_nl (4,"[= MPEG-4 ancillary data]");
   if (adi & 0x40) out_nl (4,"[= RDS via UECP]");
   if (adi & 0x80) out_nl (4,"[= reserved ]");
  indent (-1);

}




/*
  0x6C  Cell List descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_CellList  (u_char *b)
{
 int len;

 // descriptor_tag		 = b[0];
 len       	 = b[1];
 b += 2;
 len -= 0;

 while (len > 0) {
	int len2;

	out_nl (4,"Cell:");

	indent (+1);
		outBit_Sx_NL  (4,"cell_id: ",  		b, 0,16);
		outBit_S2x_NL (4,"cell_latitude: ",  	b,16,16,
				   (char *(*)(u_long)) str_cell_latitude);
		outBit_S2x_NL (4,"cell_longitude: ",  	b,32,16,
				   (char *(*)(u_long)) str_cell_longitude);
		outBit_S2x_NL (4,"cell_extend_of_latitude: ",  	b,48,12,
				   (char *(*)(u_long)) str_cell_latitude);
		outBit_S2x_NL (4,"cell_extend_of_longitude: ",  	b,60,12,
				   (char *(*)(u_long)) str_cell_longitude);

		len2 = outBit_Sx_NL (4,"subcell_info_loop_length: ",  	b,72, 8);
		b += 10;
		len -= 10;

		while ( len2 > 0) {
			out_nl (4,"Sub-Cell:");
			indent (+1);
				outBit_Sx_NL (4,"cell_id_extension: ", 		b, 0, 8);
				outBit_S2x_NL (4,"sub_cell_latitude: ",  	b, 8,16,
				   (char *(*)(u_long)) str_cell_latitude);
				outBit_S2x_NL (4,"sub_cell_longitude: ",  	b,24,16,
				   (char *(*)(u_long)) str_cell_longitude);
				outBit_S2x_NL (4,"sub_cell_extend_of_latitude: ",b,40,12,
				   (char *(*)(u_long)) str_cell_latitude);
				outBit_S2x_NL (4,"cell_extend_of_longitude: ", 	b,52,12,
				   (char *(*)(u_long)) str_cell_longitude);
			indent (-1);
			b += 8;
			len -= 8;
			len2 -= 8;
		}

	indent (-1);
 }

}




/*
  0x6D  Cell Frequency Link descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_CellFrequencyLink  (u_char *b)
{
 int len;

 // descriptor_tag		 = b[0];
 len       	 = b[1];
 b += 2;
 len -= 0;

 while (len > 0) {
	int    len2;
	u_long frequency;

	out_nl (4,"Cell:");

	indent (+1);
		outBit_Sx_NL  (4,"cell_id: ",  		b, 0,16);

		frequency = getBits (b, 0, 16, 32);
 		// frequency is in 10 Hz steps == * 10
		out_nl (4,"Center frequency: 0x%08x (= %lu.%03lu kHz)",
			frequency, frequency / 100, frequency % 100 );

		len2 = outBit_Sx_NL (4,"subcell_info_loop_length: ",  	b,48, 8);
		b += 7;
		len -= 7;

		while (len2 > 0) {
			u_long frequency2;

			out_nl (4,"Sub-Cell:");
			indent (+1);
				outBit_Sx_NL (4,"cell_id_extension: ", 		b, 0, 8);
				frequency2 = getBits (b, 0,  8, 32);
		 		// frequency is in 10 Hz steps == * 10
				out_nl (4,"Transposer frequency: 0x%08x (= %lu.%03lu kHz)",
					frequency2,
					frequency2 / 100, frequency2 % 100 );

				b += 5;
				len -= 5;
				len2 -= 5;

			indent (-1);
		}


	indent (-1);
 }

}





/*
  0x6E  Announcement Support descriptor 
  ETSI EN 300 468     6.2.xx
*/

void descriptorDVB_AnnouncementSupport (u_char *b)
{

 typedef struct  _descAnnouncementSupport {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      announcement_support_indicator;
    // N .. Announcement 2

 } descAnnouncementSupport;

 typedef struct  _descAnnouncementSupport2 {
    u_int      announcement_type;
    u_int      reserved_1;
    u_int      reference_type;
    // conditional data
    u_int      original_network_id;
    u_int      transport_stream_id;
    u_int      service_id;
    u_int      component_tag;


 } descAnnouncementSupport2;



 descAnnouncementSupport   d;
 descAnnouncementSupport2  d2;
 int                       len;
 int                       i;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.announcement_support_indicator = getBits (b, 0, 16, 16);
 b   += 4;
 len = d.descriptor_length - 4;


 out_SW_NL (4,"Announcement_support_indicator: ",
	d.announcement_support_indicator);

    i = d.announcement_support_indicator;
    // $$$ should be in dvbstr...()
    indent (+1);
      if (i & 0x01) out_nl (4,"[= Emergency alarm]");
      if (i & 0x02) out_nl (4,"[= Road Traffic Flash]");
      if (i & 0x04) out_nl (4,"[= Public Transport Flash]");
      if (i & 0x08) out_nl (4,"[= Warning message]");
      if (i & 0x10) out_nl (4,"[= News flash]");
      if (i & 0x20) out_nl (4,"[= Weather flash]");
      if (i & 0x40) out_nl (4,"[= Event announcement]");
      if (i & 0x80) out_nl (4,"[= Personal call]");
      if (i & 0xFF00) out_nl (4,"[= reserved ]");
    indent (-1);
    out_NL (4);

    

 indent (+1);
 while (len > 0) {
    d2.announcement_type	 = getBits (b, 0,  0,  4);
    d2.reserved_1		 = getBits (b, 0,  4,  1);
    d2.reference_type		 = getBits (b, 0,  5,  3);

    b   += 1;
    len -= 1;

    out_S2B_NL (4,"Announcement_type: ",d2.announcement_type,
	dvbstrAnnouncement_TYPE (d2.announcement_type) );
    out_SB_NL  (6,"reserved_1: ",d2.reserved_1);
    out_S2B_NL (4,"reference_type: ",d2.reference_type,
	dvbstrAnnouncementReference_TYPE (d2.reference_type) );


    i = d2.reference_type;
    if (i == 1 || i == 2 || i == 3) {
       d2.original_network_id	 = getBits (b, 0,  0, 16);
       d2.transport_stream_id	 = getBits (b, 0, 16, 16);
       d2.service_id		 = getBits (b, 0, 32, 16);
       d2.component_tag		 = getBits (b, 0, 48,  8);

       b   += 7;
       len -= 7;

       out_S2W_NL (4,"original_network_ID: ",d2.original_network_id,
           dvbstrOriginalNetwork_ID(d2.original_network_id));
       out_SW_NL  (4,"transport_stream_ID: ",d2.transport_stream_id);
       out_SW_NL  (4,"service_ID: ",d2.service_id);
       out_SB_NL  (4,"component_tag: ",d2.component_tag);

    } // if


 } // while
 indent (-1); 

}





/*
  0x6F  Application Signalling descriptor 
  ETSI EN 300 468     6.2.x
*/

void descriptorDVB_ApplicationSignalling (u_char *b)
{

 typedef struct  _descApplSignalling {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    // N  AppSignalling2

 } descApplSignalling;

 typedef struct  _descApplSignalling2 {
    u_int      application_type;	// 16
    u_int      reserved;		// 3
    u_int      AIT_version_nr;		// 5
 } descApplSignalling2;



 descApplSignalling        d;
 descApplSignalling2       d2;
 int                       len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 b   += 2;
 len = d.descriptor_length - 0;

 while ( len > 0) {
    d2.application_type          = getBits (b, 0, 0, 16);
    d2.reserved                  = getBits (b, 0,16,  3);
    d2.AIT_version_nr            = getBits (b, 0,19,  5);

    out_SW_NL (4,"Application type: ",d2.application_type);	// $$$ TODO Application type text
    out_SB_NL (6,"reserved: ",d2.reserved);
    out_SB_NL (4,"AIT version nr.: ",d2.AIT_version_nr);

    b += 3;
    len -= 3;
 }

}




/*
  0x70  Adaptation Field Data descriptor 
  ETSI EN 300 468     6.2.x
*/

void descriptorDVB_AdaptationFieldData (u_char *b)
{

 typedef struct  _descAdaptationFieldData {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      adaptationFieldDataIdentifier;

    // ? .. 

 } descAdaptationFieldData;



 descAdaptationFieldData     d;
 int                       len;
 int                       i;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.adaptationFieldDataIdentifier   = getBits (b, 0, 16, 8);

 b   += 3;
 len = d.descriptor_length - 1;


 out_SB_NL (4,"Adaptation field data identifier: ",
        d.adaptationFieldDataIdentifier);
  indent (+1);
   i = d.adaptationFieldDataIdentifier;
   if (i & 0x01) out_nl (4,"[= announcement switching data field]");
   if (i & 0xFE) out_nl (4,"[= reserved]");
 indent (-1);

}





/*
  0x71  Service Identifier descriptor 
  ETSI EN 300 468     6.2.x
  ETSI TS 102 812  v1.2.1  10.12
*/

void descriptorDVB_ServiceIdentifier (u_char *b)
{
 int  len;

 // tag		 = b[0];
 len       	 = b[1];

 print_text_468A (4, "textual_service_identifier: ", b+2, len);

}



/*
  0x72  Service Availability descriptor 
  ETSI EN 300 468     6.2.x
*/

void descriptorDVB_ServiceAvailability (u_char *b)
{

 typedef struct  _descServiceAvailability {
    u_int      descriptor_tag;
    u_int      descriptor_length;		

    u_int      availability_flag_1;
    u_int      reserved_7;

    //  0..N cell_ids 

 } descServiceAvailability;



 descServiceAvailability   d;
 int                       len;



 d.descriptor_tag		 = b[0];
 d.descriptor_length       	 = b[1];

 d.availability_flag_1           = getBits (b, 0, 16, 1);
 d.reserved_7                    = getBits (b, 0, 16, 7);

 b   += 3;
 len = d.descriptor_length - 1;

 out_SB_NL (4,"Availability flag: ", d.availability_flag_1);
 out_SB_NL (6,"reserved_1: ",d.reserved_7);


 indent (+1);
 while ( len > 0) {
    u_int cellid                 = getBits (b, 0, 0, 16);

    b += 2;
    len -= 2;

    out_S2B_NL (4,"Cell-ID: ",cellid, "[identifies terrestrial cell]");
 }
 indent (-1);

}






/*
  0x73 Default Authority descriptor 
  ETSI TS 102 323 
*/

void descriptorDVB_DefaultAuthority (u_char *b)
{
  int len;

  // tag	 = b[0];
  len       	 = b[1];

  print_databytes (4, "Default_authority: ", b+2, len);  // a DNS name
}




/*
  0x74 Related Content descriptor 
  ETSI TS 102 323 
*/

void descriptorDVB_RelatedContent (u_char *b)
{
  // -- related content descriptor seems to be empty 
  // -- (TS 102 323  v1.1.1, p10.3)
  descriptor_any (b);   
}





/*
  0x75 TVA ID descriptor 
  ETSI TS 102 323 
*/

void descriptorDVB_TVA_ID (u_char *b)
{
  int len;

  // tag	 = b[0];
  len       	 = b[1];


  b += 2;
  while (len > 0) {
  	outBit_Sx_NL  (4,"TVA_id: ",		b,  0, 16);
  	outBit_Sx_NL  (6,"reserved: ",		b, 16,  5);
  	outBit_S2x_NL (4,"running_status: ", 	b, 21,  3,
		 	(char *(*)(u_long)) dvbstrTVA_RunningStatus );
	b   += 3;
	len -= 3;
	out_NL (4);
  }

}





/*
  0x76 Content Identifier descriptor 
  ETSI TS 102 323 
*/

void descriptorDVB_ContentIdentifier (u_char *b)
{
  int len;

  // tag	 = b[0];
  len       	 = b[1];


  b += 2;
  while (len > 0) {
	int cloc;

  	outBit_S2x_NL      (4,"crid_type: ",		b,  0,  6,
		 	(char *(*)(u_long)) dvbstrTVA_crid_type );
  	cloc = outBit_S2x_NL (4,"crid_location: ",	b,  6,  2,
		 	(char *(*)(u_long)) dvbstrTVA_crid_location );

	b++;
	len--;

	if (cloc == 0x00) {
		int clen;

  		clen = outBit_Sx_NL (4,"crid_len: ",	b,  0,  8);
  		print_databytes (4, "crid_bytes: ", 	b+1, clen);
		b   += clen+1;
		len -= clen+1;
	}

	if (cloc == 0x01) {
  		outBit_Sx_NL  (4,"crid_ref: ",		b,  0,  16);
		b   += 2;
		len -= 2;
	}

	out_NL (4);
  }

}




/*
  0x77 time_slice_fec_identifier descriptor 
  ETSI EN 301 192  1.4.1
*/

void descriptorDVB_TimesliceFecIdentifier (u_char *b)
{
  int 	len;
  int   tslice, mpe_fec;
  int	frame_size;
  int   mbd, tslice_fec_id;


  // tag	 = b[0];
  len       	 = b[1];




  // -- prefetch value
  tslice_fec_id = getBits (b, 0, 36, 4);



  tslice  = outBit_S2x_NL (4,"time_slicing: ", 	b,16, 1,
		 	(char *(*)(u_long)) dvbstrTimeSlice_bit_used );
  mpe_fec = outBit_S2x_NL (4,"mpe_fec: ",	b,17, 2,
		 	(char *(*)(u_long)) dvbstrMPE_FEC_algo );

  outBit_Sx_NL  (6,"reserved: ",	  	b,19, 2);


  frame_size = outBit_Sx_NL  (4,"frame_size: ",	b,21, 3);
  if (tslice_fec_id == 0) {
     if (tslice)  out_nl (4,"  ==> max burst size: %s",
		  	dvbstrMPE_FEC_max_burst_size (frame_size) );
     if (mpe_fec) out_nl (4,"  ==> MPE-FEC frame rows: %s", 
			dvbstrMPE_FEC_frame_rows (frame_size) );
  } else {
     out_nl  (4,"  ==> not defined ");
  }



  mbd = outBit_Sx (4,"max_burst_duration: ",	b,24,8);
  if (tslice_fec_id == 0) {
  	if (tslice)  out_nl  (4," [= %ld msec]",(mbd+1)*20);
  	else         out_nl  (4," [= reserved]");
  } else {
     out_nl  (4," [not defined]");
  }



  if (tslice_fec_id == 0) {
	  outBit_S2x_NL  (4,"max_average_rate: ",	b,32, 4,
		 	(char *(*)(u_long)) dvbstrMPE_FEC_max_average_rate );
  } else {
	  outBit_Sx      (4,"max_average_rate: ",	b,32, 4);
  	  out_nl         (4," [= not defined]");
  }


  outBit_Sx_NL  (4,"time_slice_fec_id: ",	b,36, 4);
  b   += 5;
  len -= 3;
  print_databytes (4,"id_selector_bytes:", b,len);
}




/*
  0x78 ECM RepetitionRate descriptor 
  ETSI EN 301 192  1.4.1
*/

void descriptorDVB_ECM_RepetitionRate (u_char *b)
{
  int len;

  // tag	 = b[0];
  len       	 = b[1];


 outBit_S2x_NL  (4,"CA_systemID: ",  		b,16,16,
		 	(char *(*)(u_long)) dvbstrCASystem_ID );
 outBit_S2Tx_NL (4,"ECM_repetition_rate: ",  	b,32,16,"msec.");

 b   += 6;
 len -= 4;
 print_private_data (4, b, len);

}




/*
  0x79 S2 Satellite Delivery System Descriptor 
  ETSI EN 301 192  1.7.1
*/

void  descriptorDVB_S2SatelliteDeliverySystem(u_char *b)
{

  u_int   sss;
  u_int   misf;


  // tag	 = b[0];
  // len       	 = b[1];
  b +=2;


  sss =  outBit_Sx_NL (4,"scrambling_sequence_selector: ", 	b,  0, 1);
  misf = outBit_Sx_NL (4,"multiple_input_stream_flag: ",	b,  1, 1);
         outBit_Sx_NL (4,"backwards_compatibility_indicator: ", b,  2, 1);
         outBit_Sx_NL (4,"reserved_future_use: ",		b,  3, 5);
  b +=1;

  if (sss) {
      outBit_Sx_NL (4,"reserved: ",			b,  0, 6);
      outBit_Sx_NL (4,"scrambling_sequence_index: ",	b,  6,18); // $$$ TODO
      b += 3;
  }

  if (misf) {
      outBit_Sx_NL (4,"input_stream_identifier: ",	b,  0, 8);  // $$$TODO EN 302 307
      b += 1;
  }

}





/*
  0x7A  Enhanced AC-3  descriptor 
  ETSI EN 300 468 v.1.7.1   ANNEX D 
*/

void descriptorDVB_Enhanced_AC3  (u_char *b)
{

   u_int      len;
   u_int      comp_type_flag;
   u_int      bsid_flag;
   u_int      mainid_flag;
   u_int      asvc_flag;
   u_int      substream1_flag;
   u_int      substream2_flag;
   u_int      substream3_flag;


  // tag 	= b[0];
  len 		= b[1];

  comp_type_flag  = outBit_Sx_NL (4,"component_type_flag: ",	b,  16,  1);
  bsid_flag       = outBit_Sx_NL (4,"bsid_flag: ",   		b,  17,  1);
  mainid_flag     = outBit_Sx_NL (4,"mainid_flag: ",   		b,  18,  1);
  asvc_flag       = outBit_Sx_NL (4,"asvc_flag: ",  	 	b,  19,  1);
                    outBit_Sx_NL (4,"mixinfoexists: ", 		b,  20,  1);
  substream1_flag = outBit_Sx_NL (4,"substream1_flag: ", 	b,  21,  1);
  substream2_flag = outBit_Sx_NL (4,"substream2_flag: ", 	b,  22,  1);
  substream3_flag = outBit_Sx_NL (4,"substream3_flag: ", 	b,  23,  1);

  b   += 3;
  len -= 1;


 if (comp_type_flag) {
     outBit_S2x_NL (4,"component_type: ",b++,  0, 8,
	 	(char *(*)(u_long)) dvbstrDVB_AC3_ComponentType );
     len--;
 }

 if (bsid_flag) {
     outBit_Sx_NL (4,"bsid: ",		b++,  0, 8);
     len--;
 }

 if (mainid_flag) {
     outBit_Sx_NL (4,"mainid: ",	b++,  0, 8);
     len--;
 }

 if (asvc_flag) {
     outBit_Sx_NL (4,"asvc: ",		b++,  0, 8);
     len--;
 }

 if (substream1_flag) {
     outBit_Sx_NL (4,"substream1: ",	b++,  0, 8);	// $$$ TODO
     len--;
 }

 if (substream2_flag) {
     outBit_Sx_NL (4,"substream2: ",	b++,  0, 8);	// $$$ TODO
     len--;
 }

 if (substream3_flag) {
     outBit_Sx_NL (4,"substream3: ",	b++,  0, 8);	// $$$ TODO
     len--;
 }

 print_databytes (4,"additional_info:", b, len);

}





/*
  0x7B  DTS_Audio  descriptor 
  ETSI EN 300 468 v.1.7.1   ANNEX G 
*/

void descriptorDVB_DTS_Audio (u_char *b)
{

   u_int      len;


  // tag 	= b[0];
  len 		= b[1];

  outBit_S2x_NL(4,"sample_rate_code: ", 		b,  16,  4,
	 	(char *(*)(u_long)) dvbstrDVB_DTS_Audio_SampleRateCode );
  outBit_S2x_NL(4,"bit_rate_code: ",	 		b,  20,  6,
	 	(char *(*)(u_long)) dvbstrDVB_DTS_Audio_BitRate );
  outBit_Sx_NL (4,"nblks: ",		 		b,  26,  7);
  outBit_Sx_NL (4,"fsize: ",		 		b,  33, 14);
  outBit_S2x_NL(4,"surround_mode: ",	 		b,  47,  6,
	 	(char *(*)(u_long)) dvbstrDVB_DTS_Audio_SurroundMode );
  outBit_Sx_NL (4,"lfe_flag: ",		 		b,  53,  1);
  outBit_S2x_NL(4,"extended_surround_flag: ",		b,  54,  2,
	 	(char *(*)(u_long)) dvbstrDVB_DTS_Audio_ExtendedSurroundFlag );

  print_databytes (4,"additional_info:", b+7, len-6);
}





/*
  0x7C  AAC  descriptor 
  ETSI EN 300 468 v.1.7.1   ANNEX H 
*/

void descriptorDVB_AAC (u_char *b)
{

   u_int      len;
   u_int      atf;


  // tag 	= b[0];
  len 		= b[1];

        outBit_Sx_NL (4,"profile_and_level: ",		b,  16,  8); 
  atf = outBit_Sx_NL (4,"AAC_type_flag: ", 		b,  24,  1);
        outBit_Sx_NL (4,"reserved: ",			b,  25,  7);

  b   += 4;
  len -= 2;

  if (atf) {
        outBit_Sx_NL (4,"AAC_type: ", 			b,   0,  8);
	b++;
	len--;
  }

  print_databytes (4,"additional_info:", b, len);
}





// 0x7D -- reserved

// 0x7E -- reserved




/*
  0x7F  Extension  descriptor 
  ETSI EN 300 468 v.1.7.1 
*/

void descriptorDVB_Extension (u_char *b)
{

   u_int      len;
   u_int      ext_tag;


  // tag 	= b[0];
  len 		= b[1];

  ext_tag = outBit_Sx_NL (4,"descriptor_tag_extension: ",	b,  16,  8); 

  switch (ext_tag) {

//    case  xx:
//	    break;

    default: 
  	print_databytes (4,"selector_bytes:", b+3, len-1);
	break;
  }

}




