/*
$Id: dsmcc_unm_dii.c,v 1.6 2006/01/02 18:23:47 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

 -- dsmcc Download Info Indication
 -- to be called from U-N-Message



$Log: dsmcc_unm_dii.c,v $
Revision 1.6  2006/01/02 18:23:47  rasc
just update copyright and prepare for a new public tar ball

Revision 1.5  2004/02/24 23:03:04  rasc
private data of DSMCC::DSI
BIOP::ServiceGatewayInformation()
IOP::IOR()

Revision 1.4  2004/02/20 22:18:38  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.3  2004/02/17 23:54:12  rasc
Bug (not fixed yet): DSM-CC  DII Carousel Descriptor Loop is strange

Revision 1.2  2004/02/15 20:46:09  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)

Revision 1.1  2004/02/15 18:58:27  rasc
DSM-CC  data/object carousell continued   (DSI, DII, DDB, DCancel)





*/




#include "dvbsnoop.h"
#include "dsmcc_unm_dii.h"
#include "dsmcc_misc.h"
#include "biop_modinfo.h"
#include "misc/output.h"
#include "misc/hexprint.h"





/*
 * ISO/IEC 13818-6
 * dsmcc  Download Info Indication
 */


int dsmcc_DownloadInfoIndication (int v, u_char *b, u_int len)
{
   int   	len_org = len;
   int		n_modules;
   int 		len2;
   int		i, x;



	// already read  dsmcc_MessageHeader (v, b, len, &dmh);

	outBit_Sx_NL (v,"downloadId: ",		b   ,  0, 32);
	outBit_Sx_NL (v,"blockSize: ",		b+ 4,  0, 16);
	outBit_Sx_NL (v,"windowSize: ",		b+ 6,  0,  8);
	outBit_Sx_NL (v,"ackPeriod: ",		b+ 7,  0,  8);
	outBit_Sx_NL (v,"tCDownloadWindow: ",	b+ 8,  0, 32);
	outBit_Sx_NL (v,"tCDownloadScenario: ",	b+12,  0, 32);
	b += 16;
	len -= 16;

	x = dsmcc_CompatibilityDescriptor (b);
	b += x;
	len -= x;

	n_modules = outBit_Sx_NL (v,"numberOfModules: ",	b,  0, 16);
	b += 2;
	len -= 2;

	for (i=0; i < n_modules; i++) {
		u_int    mId;

		out_NL (v);
		out_nl (v, "Module (%d):",i);
		indent (+1);

		mId = outBit_Sx (v,"moduleId: ",	b,  0, 16);
		      out_nl (4, "%s", (mId < 0xFFF0) ? "" : "  [= DAVIC application]");
		outBit_Sx_NL (v,"moduleSize: "	,	b, 16, 32);
		outBit_Sx_NL (v,"moduleVersion: ",	b, 48,  8);
		len2 = outBit_Sx_NL (v,"moduleInfoLength: ",	b, 56,  8);
		b += 8;
		len -= 8;


		// moduleInfoByte: these fields shall convey a list of descriptors
		// which each define one or more attributes of the described module,
		// except when the moduleId is within the range of 0xFFF0-0xFFFF. In
		// this case, the moduleInfoByte structure contains the ModuleInfo
		// structure as defined by DAVIC with the privateDataByte field of that
		// structure as a loop of descriptors.
		// ISO 13818-6:2000  11.3.3.2

		if (mId < 0xFFF0) {
			BIOP_ModuleInfo (v, b, len2);
		} else {
			print_databytes (v, "moduleInfoBytes: ", b, len2);  // $$$ TODO Davic
		}
		b += len2;
		len -= len2;

		indent (-1);
	}
	out_NL (v);
	indent (-1);


	len2 = outBit_Sx_NL (v,"privateDataLength: ",	b,  0, 16);
	print_databytes (v, "privat Data: ", b+2, len2);   // $$$ TODO ???
	// b += 2 + len2;
	// len -= 2 + len2;


	return len_org;
}








// EN 301 192
// 8.1.3 DownloadInfoIndication message
//
// The DownloadInfoIndication message contains the description of the
// modules within a group as well as some general parameters of the
// data carousel (such as downloadId and blockSize). Each module is
// described by a number of attributes. The attributes moduleId,
// moduleSize, and moduleVersion are defined as fields in the
// DownloadInfoIndication message by DSM-CC (see ISO/IEC 13818-6 [5]).
// Other module attributes shall be carried as descriptors as defined
// below. The moduleId range of 0xFFF0-0xFFFF is reserved for DAVIC
// compliant applications.  The semantics of the DownloadInfoIndication
// message for DVB data carousels are as follows:
//
// compatibilityDescriptor(): this structure shall only contain the
// compatibilityDescriptorLength field of the compatibilityDescriptor()
// as defined in DSM-CC (see ISO/IEC 13818-6 [5]). It shall be set to
// the value of 0x0000.
//
// moduleInfoLength: this field defines the length in bytes of the
// moduleInfo field for the described module.
//
// !! moduleInfoByte: these fields shall convey a list of descriptors
// !! which each define one or more attributes of the described module,
// !! except when the moduleId is within the range of 0xFFF0-0xFFFF. In
// !! this case, the _moduleInfoByte structure_ contains the ModuleInfo
// !! structure as defined by DAVIC with the privateDataByte field of that
// !! structure as a loop of descriptors.
//
// privateDataLength: this field defines the length in bytes of the
// privateDataByte field.
//
// privateDataByte: these fields are user defined.

