/*
$Id: cmdline.c,v 1.51 2006/03/06 00:04:54 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)






$Log: cmdline.c,v $
Revision 1.51  2006/03/06 00:04:54  rasc
More DSM-CC stuff: BIOP::FileMessage, BIOP::DirectoryMessage,
BIOP::Stream::BIOP::StreamEvent, BIOP::ServiceGateway, DSM-TAPs, etc.
this is a preparation for a patch sent in by Richard Case (DSMCC-Save).
Attention: Code is still untested and may considered to be buggy (some teststreams are needed)...

Revision 1.50  2005/12/29 02:43:38  rasc
gcc fixes, man page update

Revision 1.49  2005/10/20 22:25:07  rasc
 - Bugfix: tssubdecode check for PUSI and SI pointer offset
   still losing packets, when multiple sections in one TS packet.
 - Changed: some Code rewrite
 - Changed: obsolete option -nosync, do always packet sync

Revision 1.48  2005/08/12 23:02:35  rasc
New shortcut options: -adapter and -devnr to select dvb cards/adapters or device numbers on a card.
This is a shortcut for -demux -dvr and -frontend...

Revision 1.47  2005/08/11 21:02:16  rasc
minor changes, man page

Revision 1.46  2005/08/10 21:28:18  rasc
New: Program Stream handling  (-s ps)

Revision 1.45  2005/08/02 22:57:46  rasc
Option -N, rewrite offline filters (TS & Section)

Revision 1.44  2005/07/31 21:47:59  rasc
soft CRC for sections...

Revision 1.43  2005/07/11 23:06:47  rasc
Multibyte section filter redesign:  -f 0x4F.22.33.44.55.66 -m 0x.FF.FF.FF etc.
Manpage update

Revision 1.42  2005/06/27 20:28:17  rasc
first version for a man page

Revision 1.41  2005/01/17 19:41:22  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.40  2004/12/07 21:01:42  rasc
Large file support (> 2 GB) for -if cmd option. (tnx to K.Zheng,  Philips.com for reporting)

Revision 1.39  2004/11/16 23:02:50  rasc
cmd option "-tsraw" for full/raw TS read (if supported by hard-/firmware)

Revision 1.38  2004/11/03 21:00:59  rasc
 - New: "premiere.de" private tables and descriptors (tnx to Peter.Pavlov, Premiere)
 - New: cmd option "-privateprovider <provider name>"
 - New: Private provider sections and descriptors decoding
 - Changed: complete restructuring of private descriptors and sections

Revision 1.37  2004/10/12 21:12:05  rasc
no message

Revision 1.36  2004/10/12 20:37:48  rasc
 - Changed: TS pid filtering from file, behavior changed
 - New: new cmdline option -maxdmx <n>  (replaces -f using pidscan)
 - misc. changes

Revision 1.35  2004/09/01 20:20:34  rasc
new cmdline option: -buffersize KB  (set demux buffersize in KBytes)

Revision 1.34  2004/04/15 03:38:50  rasc
new: TransportStream sub-decoding (ts2PES, ts2SEC)  [-tssubdecode]
checks for continuity errors, etc. and decode in TS enclosed sections/pes packets

Revision 1.33  2004/04/01 19:19:06  rasc
cmdline options renamed...

Revision 1.32  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.31  2004/03/21 00:37:47  rasc
Query FrontEnd Info  (option: -s feinfo)

Revision 1.30  2004/03/09 20:59:23  rasc
VPS decoding (someone check the NPP & PTY code output please...)

Revision 1.29  2004/02/28 12:13:03  rasc
minor stuff

Revision 1.28  2004/02/21 00:50:41  rasc
bugfix: MHP AIT descriptors

Revision 1.27  2004/02/20 22:18:40  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.26  2004/02/16 22:45:37  rasc
small bugfix: crc is 32 bit

Revision 1.25  2004/02/15 22:22:28  rasc
cmd option: -hexdumpbuffer -nohexdumpbuffer

Revision 1.24  2004/01/29 22:34:49  rasc
-sync: default now

Revision 1.23  2004/01/22 22:26:35  rasc
pes_pack_header
section read timeout

Revision 1.22  2004/01/06 14:06:09  rasc
no message

Revision 1.21  2004/01/03 15:40:47  rasc
simple frontend signal status query added "-s signal"

Revision 1.20  2004/01/01 20:09:26  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.19  2003/12/28 22:53:41  rasc
some minor changes/cleanup

Revision 1.18  2003/12/28 14:00:26  rasc
bugfix: section read from input file
some changes on packet header output

Revision 1.17  2003/12/28 00:01:14  rasc
some minor changes/adds...

Revision 1.16  2003/12/17 23:57:29  rasc
add. hexdump mode, different layout for some purpose
option:  -ph 4

Revision 1.15  2003/12/15 22:29:27  rasc
pidscan improved, problems with max filters on demux

Revision 1.14  2003/12/15 20:09:49  rasc
no message

Revision 1.13  2003/12/14 23:38:46  rasc
- bandwidth reporting for a PID

Revision 1.12  2003/12/10 20:07:15  rasc
minor stuff

Revision 1.11  2003/12/09 21:02:31  rasc
transponder pid-scan improved (should be sufficient now)

Revision 1.10  2003/12/07 23:36:13  rasc
pidscan on transponder
- experimental(!)

Revision 1.9  2003/12/03 20:06:35  obi
- reduced auto* to minimal required checks, obsoletes acinclude.m4
- added version number to configure.ac, removed it from version.h
  (needed for "make dist" anyway)
- removed autoheader dependency

Revision 1.8  2003/11/26 16:27:46  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.7  2003/11/24 23:52:17  rasc
-sync option, some TS and PES stuff;
dsm_addr inactive, may be wrong - due to missing ISO 13818-6

Revision 1.6  2003/11/01 17:05:46  rasc
no message

Revision 1.5  2003/10/16 20:45:47  rasc
no message

Revision 1.4  2003/10/16 19:02:27  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.3  2003/07/06 05:28:52  obi
compatibility stuff.. now there is only one version for old and new drivers
which selects the api at configure time

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/


#include "dvbsnoop.h"
#include "cmdline.h"
#include "dvb_api/dvb_api.h"
#include "private/userdefs.h"



static void title (void);
static void usage (void);

static char *set_DVB_device (char *str, const char *path_mask, int adapter, int devnr);

// -- GetOptionPtr
static OPTION *opt_ptr = NULL;

// -- mem for dvb devices
static char  strDEV_DEMUX[DVB_MAX_DEV_PATH_LEN];
static char  strDEV_DVR[DVB_MAX_DEV_PATH_LEN];
static char  strDEV_FRONTEND[DVB_MAX_DEV_PATH_LEN];






/*
  -- set default options and decode cmdline
  -- return 0=abort, 1= ok (&opt set)

*/

int  cmdline_options (int argc, char **argv, OPTION *opt)

{
  char  *s;
  int   i;

  /*
    -- init options
  */

  opt->buffer_hexdump = 1;
  opt->printhex = -1;		// see below
  opt->printdecode = -1;	// see below
  opt->binary_out = 0;
  opt->outPidFile = (char *) NULL;
  opt->inpPidFile = (char *) NULL;
  opt->devDemux = (char *) NULL;
  opt->devDvr = (char *) NULL;
  opt->devFE = (char *) NULL;
  opt->dvbAdapterNr = DVB_STD_ADAPTER_NR;	// default
  opt->dvbDeviceNr  = DVB_STD_DEVICE_NR;	// default
  opt->rd_buffer_size = 0L;	// use default read buffersize
  opt->pid = INVALID_PID;
  opt->timeout_ms = 0;		// no timeout (0) or default timeout in ms (SECTIONS)
  opt->max_dmx_filter = 0;	// use module default  (pidscan)
  opt->crc = 0;
  opt->soft_crc = 0;
  opt->spider_pid = 0;
  opt->ts_subdecode = 0;
  opt->rd_all_sections = 0;	// read all section no. for a pid 
  opt->ts_raw_mode = 0;
  opt->rd_packet_count = 0;
  opt->dec_packet_count = 0;
  opt->packet_header_sync = 1;  // $$$ OBSOLETE!
  opt->packet_mode = SECT;
  opt->time_mode = FULL_TIME;
  opt->hide_copyright= 0;
  opt->help = 0;
  opt->privateProviderStr = (char *)NULL;  // decoding known private tables/descriptors, ProviderStr
  opt->dsmcc_save = 0;

  opt->filterLen = 0;
  memset(opt->filter, 0, DMX_FILTER_SIZE);
  memset(opt->mask,   0, DMX_FILTER_SIZE);


  // -- store for getOption 
  opt_ptr = opt;


  /*
   -- Simple parse of cmdline
  */

  i = 0;
  while (++i < argc) {

     if      (!strcmp (argv[i],"-demux")) opt->devDemux = argv[++i];
     else if (!strcmp (argv[i],"-dvr")) opt->devDvr = argv[++i];
     else if (!strcmp (argv[i],"-frontend")) opt->devFE = argv[++i];
     else if (!strcmp (argv[i],"-adapter")) opt->dvbAdapterNr = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-devnr")) opt->dvbDeviceNr  = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-maxdmx")) opt->max_dmx_filter = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-crc")) opt->crc = 1;
     else if (!strcmp (argv[i],"-nocrc")) opt->crc = 0;
     else if (!strcmp (argv[i],"-softcrc")) opt->soft_crc = 1;
     else if (!strcmp (argv[i],"-nosoftcrc")) opt->soft_crc = 0;
     else if (!strcmp (argv[i],"-sync")) opt->packet_header_sync = 1; 
     else if (!strcmp (argv[i],"-nosync")) opt->packet_header_sync = 0;  // -- obsolete
     else if (!strcmp (argv[i],"-n")) opt->rd_packet_count = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-N")) opt->dec_packet_count = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-b")) opt->binary_out = 1;
     else if (!strcmp (argv[i],"-ph")) opt->printhex = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-pd")) opt->printdecode = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-npd")) opt->printdecode = 0;
     else if (!strcmp (argv[i],"-hideproginfo")) opt->hide_copyright= 1;
     else if (!strcmp (argv[i],"-timeout")) opt->timeout_ms = str2i(argv[++i]);
     else if (!strcmp (argv[i],"-buffersize")) opt->rd_buffer_size = str2i(argv[++i]) * 1024;
     else if (!strcmp (argv[i],"-tf")) opt->time_mode = FULL_TIME;
     else if (!strcmp (argv[i],"-td")) opt->time_mode = DELTA_TIME;
     else if (!strcmp (argv[i],"-tn")) opt->time_mode = NO_TIME;
     else if (!strcmp (argv[i],"-hexdumpbuffer")) opt->buffer_hexdump = 1;
     else if (!strcmp (argv[i],"-nohexdumpbuffer")) opt->buffer_hexdump = 0;
     else if (!strcmp (argv[i],"-nph")) opt->buffer_hexdump = 0;  // old option  use -ph and -nhdb/-hdb
     else if (!strcmp (argv[i],"-help")) opt->help = 1;
     else if (!strcmp (argv[i],"-privateprovider")) opt->privateProviderStr = argv[++i];
     else if (!strcmp (argv[i],"-tssubdecode")) opt->ts_subdecode = 1;
     else if (!strcmp (argv[i],"-allsections")) opt->rd_all_sections = 1;
     else if (!strcmp (argv[i],"-dsmccsave")) opt->dsmcc_save = 1;
     else if (!strcmp (argv[i],"-f")) {
	 opt->filterLen = str2barray(argv[++i], opt->filter, DMX_FILTER_SIZE);
     } else if (!strcmp (argv[i],"-m")) {
	 int x = str2barray(argv[++i], opt->mask, DMX_FILTER_SIZE);
	 if (x<0) opt->filterLen = -1;
     } else if (!strcmp (argv[i],"-tsraw")) {
	 opt->ts_raw_mode = 1;
	 opt->pid = DUMMY_PID;			// dummy to avoid usage output
     } else if (!strcmp (argv[i],"-spiderpid")) {
	 opt->spider_pid = 1;
	 opt->rd_packet_count = 1;
     } else if (!strcmp (argv[i],"-of")) {
     	 opt->binary_out = 1;
	 opt->outPidFile = argv[++i];		// binary output filename
	 if (!opt->outPidFile) opt->outPidFile = ""; 
	 if (!strcmp(opt->outPidFile,"-"))  opt->outPidFile = "/dev/stdout"; 
     } else if (!strcmp (argv[i],"-if")) {
	 opt->inpPidFile = argv[++i];		// input filename
	 if (!opt->inpPidFile) opt->inpPidFile = ""; 
	 if (!strcmp(opt->inpPidFile,"-"))  opt->inpPidFile = "/dev/stdin"; 
	 opt->pid = DUMMY_PID;			// dummy to avoid usage output
     } else if (!strcmp (argv[i],"-s")) {
         s = argv[++i];
	 if (!s ) s = ""; 
         if (!strcmp (s,"sec")) opt->packet_mode = SECT;
         else if (!strcmp (s,"ts")) opt->packet_mode = TS;
         else if (!strcmp (s,"pes")) opt->packet_mode = PES;
         else if (!strcmp (s,"ps")) opt->packet_mode = PS;	// ProgramStream
         else if (!strcmp (s,"bandwidth")) opt->packet_mode = PIDBANDWIDTH;
         else if (!strcmp (s,"pidscan")) {
		 	opt->packet_mode = PIDSCAN;
			opt->pid = DUMMY_PID;	// dummy to avoid usage output
	 } else if (!strcmp (s,"signal")) {
		 	opt->packet_mode = SCAN_FE_SIGNAL;
			opt->pid = DUMMY_PID;	// dummy to avoid usage output
	 } else if (!strcmp (s,"feinfo")) {
		 	opt->packet_mode = SCAN_FE_INFO;
			opt->pid = DUMMY_PID;	// dummy to avoid usage output
	 } else opt->help = 1;
     } else if (isdigit (argv[i][0])) {
         opt->pid = str2i(argv[i]); 	// PID
	 if (opt->pid > MAX_PID) opt->help = 1;
     } else {
         opt->help = 1;
         break;
     }

  } // while


  /*
   -- standard if no print decode or printhex given
  */

  if (opt->printhex    < 0) opt->printhex = 4;
  if (opt->printdecode < 0) opt->printdecode = 7;


  if (opt->filterLen < 0) {
    printf("Error: Illegal filter/mask value: use e.g. 0x4F or 0x12.5F.2A. etc...\n");
    return(0); 
  }




  //
  // -- set default DVB devices 
  // -- (e.g. printed by help)
  //

  set_DVB_device (strDEV_DEMUX,    DEMUX_DEVICE_MASK,    DVB_STD_ADAPTER_NR, DVB_STD_DEVICE_NR);
  set_DVB_device (strDEV_DVR,      DVR_DEVICE_MASK,      DVB_STD_ADAPTER_NR, DVB_STD_DEVICE_NR);
  set_DVB_device (strDEV_FRONTEND, FRONTEND_DEVICE_MASK, DVB_STD_ADAPTER_NR, DVB_STD_DEVICE_NR);


 
  //
  //  -- help ?  (and return abort)
  //

  if (opt->help) {
    usage ();
    printf("\nKnown private providers for private sections and descriptors:\n");
    list_PRIVATE_ProviderStrs ();
    return(0); 
  } 


  //
  // -- set private scope id strings (if specified)
  //

  if (opt->privateProviderStr) {
     set_PRIVATE_ProviderStr (opt->privateProviderStr);
  }



  //
  // -- set DVB devices  demux, dvr and frontend
  // -- if not set by cmdline, set by 1.) default, 2.) adapterNr & deviceNr
  //

  if (   opt->dvbAdapterNr < 0 || opt->dvbAdapterNr > 9
      || opt->dvbDeviceNr  < 0 || opt->dvbDeviceNr  > 9)  {
    printf("Error: Illegal DVB adapter/card number or illegal DVB device number. \n");
    return(0); 
  }

  if (!opt->devDemux) {
  	opt->devDemux = set_DVB_device (strDEV_DEMUX, DEMUX_DEVICE_MASK,
  					opt->dvbAdapterNr, opt->dvbDeviceNr);
  }
  if (!opt->devDvr) {
  	opt->devDvr   = set_DVB_device (strDEV_DVR, DVR_DEVICE_MASK,
  					opt->dvbAdapterNr, opt->dvbDeviceNr);
  }
  if (!opt->devFE) {
  	opt->devFE    = set_DVB_device (strDEV_FRONTEND, FRONTEND_DEVICE_MASK,
  					opt->dvbAdapterNr, opt->dvbDeviceNr);
  }



  //
  // -- PID check
  //

  if ((argc==1) || ((opt->pid > MAX_PID) && (opt->pid != DUMMY_PID)) ) {
    title ();
    printf("For help type 'dvbsnoop -help' ...\n");
    return(0); 
  } 


 return 1;
}





//
// -- Get pointer to cmdline Option structure
//
OPTION *getOptionPtr (void)
{
   return opt_ptr;
}





static void title (void)
{
    printf("dvbsnoop  - a dvb/mpeg2 stream analyzer tool\n");
    printf("Version: %s/api-%d  (%s %s)\n",
		    DVBSNOOP_VERSION,DVB_API_VERSION,__DATE__,__TIME__);
    printf("         %s  \n",DVBSNOOP_URL);
    printf("         %s  \n",DVBSNOOP_COPYRIGHT);
    printf("\n");
}



static void usage (void)
{
    title ();

    printf("Usage:   dvbsnoop [opts] pid \n");
    printf("Options:  \n");
    printf("   -s type:    snoop type or mode <type>  [-s sec]\n");
    printf("                   stream type: sec, pes, ps or ts\n");
    printf("                   or special scan type:\n");
    printf("                         pidscan = transponder pid scan,\n");
    printf("                         bandwidth = data rate statistics for pid\n");
    printf("                         signal = signal rate statistics \n");
    printf("                         feinfo = frontend information\n");
    printf("                 stream type or pidscan\n");
    printf("   -demux device: demux device [%s]\n",strDEV_DEMUX);
    printf("   -dvr device:   dvr device [%s]\n",strDEV_DVR);
    printf("   -frontend device: frontend   device [%s]\n",strDEV_FRONTEND);
    printf("   -adapter n:    select dvb adapter/card no. <n> using default path\n");
    printf("   -devnr n:      select device no. <n> using default dvb adapter/card\n");
// $$$ TODO  -of cmd option
//  printf("   -of file:     output file, writes binary <file> (implies -b)\n");
//  printf("                  <file>=\"-\" = /dev/stdout \n");
    printf("   -if file:     input file, reads from binary <file> instead of demux device \n");
    printf("                  <file>=\"-\" = /dev/stdin \n");
    printf("   -timeout ms:  section/signal read timeout in <ms> msec. [-timeout 0]\n");
    printf("   -maxdmx n:    max demux filters <n> to use in pidscan mode (0=max) [-maxdmx 0]\n");
    printf("   -buffersize kb: read buffersize in KBytes  [-buffersize 0]\n");
    printf("                 (0 = use default read buffer size)\n");
    printf("   -f filter:    filtervalue for 'sec' demux [-f 0]\n");
    printf("                 multibyte filter syntax: 0x1A.34.56.7F.01\n");
    printf("   -m mask:      maskvalue for 'sec' demux [-m 0]\n");
    printf("                 multibyte mask syntax: 0x1A.00.F6.55\n");
    printf("   -crc:         CRC check when reading 'sec' [-nocrc]\n");
    printf("   -nocrc:       no CRC check when reading 'sec' [-nocrc]\n");
    printf("   -softcrc:     internal soft CRC check when reading 'sec' [-nosoftcrc]\n");
    printf("   -nosoftcrc:   no internal soft CRC check when reading 'sec' [-nosoftcrc]\n");
    printf("   -sync:        simple packet header sync when reading 'ts' or 'pes' [-snyc]\n");
    printf("   -nosync:      (obsolete option) \n");
    printf("   -n count:     receive/read max. <count> packets (0=no limit) [-n 0]\n");
    printf("   -N count:     decode max. <count> packets (0=no limit) [-N 0]\n");
    printf("                 this will limit -n, e.g. when using soft filters.\n");
    printf("   -spiderpid:   snoop referenced section pids (sets -n 1) \n");
// $$$ TODO
//    printf("   -allsections: read all sections in sequence on pid (limited by -n ..) \n");
    printf("   -tssubdecode: sub-decode sections or pes from ts stream decoding\n");
    printf("   -tsraw:       read raw/full TS in TS snoop mode\n");
    printf("   -b:           binary output of packets (disables other output)\n");
    printf("   -ph mode:     data hex dump mode, modes: [-ph 4]\n");
    printf("                   0=none, 1=hexdump, 2=hex line 3=ascii line 4=hexdump2\n");
    printf("   -hexdumpbuffer:   print hex dump of read buffer [-hexdumpbuffer]\n");
    printf("   -nohexdumpbuffer: don't print hex dump of read buffer [-hexdumpbuffer]\n");
    printf("   -nph:         don't print hex dump of buffer [= -nohexdumpbuffer]\n");
    printf("   -pd verbose:  print stream decode (verbose level 0..9) [-pd 7]\n");
    printf("   -npd:         don't print decoded stream (= -pd 0) \n");
    printf("   -t[n|d|f]:    print timestamp (no, delta, full) [-tf] \n");
    printf("   -privateprovider id: set provider <id> string for decoding private tables and descriptors\n");
// $$$ TODO
//    printf("   -dsmccsave:   Save of Digital Storage Media Command and Control objects, section modes only\n");
//    printf("                 (currently only processing of BIOP Files and Directories is supported)\n");
    printf("   -hideproginfo: hide copyright and program info header at program start\n");
    printf("   -help:        this usage info...\n");
    printf("\n");
    

 return;
}




static char *set_DVB_device (char *str, const char *path_mask, int adapter, int devnr)
{
  sprintf (str, path_mask, adapter, devnr);
  return str;
}






// $$$ TODO  commandline handling needs a redesign 

