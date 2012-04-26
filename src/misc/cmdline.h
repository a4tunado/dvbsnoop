/*
$Id: cmdline.h,v 1.33 2006/03/06 00:04:54 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



*/



#ifndef __CMDLINE_H
#define __CMDLINE_H 

#include "dvb_api/dvb_api.h"


/*
 -- defs...
*/

enum PACKET_MODE  {SECT, TS, PES, PS,
			PIDSCAN, PIDBANDWIDTH,
			SCAN_FE_SIGNAL, SCAN_FE_INFO};
enum TIME_MODE    {NO_TIME, FULL_TIME, DELTA_TIME};

typedef struct _OPTIONS {
  int         packet_mode;
  int         packet_header_sync;	// Try to do a softsync of packet sync bytes -- $$$ OBSOLETE!!!
  int         buffer_hexdump;		// 0/1: print hexdump prior to decoding
  int         printhex;			// hexdump mode
  int         printdecode;		// decode verbose mode
  int         binary_out;		// binary output?
  char        *outPidFile;		// write to file (implies binary_out)
  char        *inpPidFile;		// read from file instead of dmux if not NULL
  char        *devDemux;		// input device DMX
  char        *devDvr;			// input device DVR
  char        *devFE;			// input device Frontend
  int         dvbAdapterNr;		// /dev/dvb/adapterN/... (Api3)
  int         dvbDeviceNr;		// z.B. /dev/dvb/.../demuxN
  long        rd_buffer_size;		// read buffer size in (0L = default)
  u_int       pid;			// decode PID
  int         filterLen;		// bytelength of section filter
  u_char      filter[DMX_FILTER_SIZE];	// section byte filter
  u_char      mask[DMX_FILTER_SIZE];	// section byte mask
  int         crc;			// section CRC check?
  int         soft_crc;			// section CRC soft check?
  int         max_dmx_filter;		// max dmx filter use? (pidscan)
  long        timeout_ms;		// read timeout in ms
  long        rd_packet_count;		// read max. n packets
  long        dec_packet_count;		// decode max. n packets
  int         rd_all_sections;		// read all sections no. for a pid
  int         spider_pid;		// Section PID spider mode
  int         ts_subdecode;		// sub decode PES or SEC in TS stream
  int         ts_raw_mode;		// Read full TS in TS stream mode (if hardware supported)
  int         time_mode;		// time print mode
  char        *privateProviderStr;	// Private Provider ID str (usedef tables, descr)
  int         dsmcc_save;		// save modules from DSM-CC to file
  int         hide_copyright;  		// suppress message at prog start
  int         help;
} OPTION;


/*
 -- prototypes
*/

int    cmdline_options (int argc, char **argv, OPTION *opt);
OPTION *getOptionPtr (void);

#endif


