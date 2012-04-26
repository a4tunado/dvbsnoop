/*
$Id: dvb_api.h,v 1.10 2006/01/02 18:23:59 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)




$Log: dvb_api.h,v $
Revision 1.10  2006/01/02 18:23:59  rasc
just update copyright and prepare for a new public tar ball

Revision 1.9  2005/10/23 20:58:14  rasc
subdecode multiple SI packets with TS packet using -tssubdecode

Revision 1.8  2005/09/13 18:41:15  rasc
... revert cygwin stuff

Revision 1.7  2005/09/12 20:56:16  rasc
Make dvbsnoop compile on Cygwin / Windows

Revision 1.6  2005/08/12 23:02:33  rasc
New shortcut options: -adapter and -devnr to select dvb cards/adapters or device numbers on a card.
This is a shortcut for -demux -dvr and -frontend...


*/



#ifndef __DVB_API_H
#define __DVB_API_H


#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>




//
// -- Cygwin(??) environment
// -- uncomment the following lines...
// --- no IOCTLs or __types
// --- Only offline analyze mode available
//

//#ifndef ioctl
//
//#warning "----"
//#warning "IOCTL not defined (needed for dvb-api), using dummy!"
//#warning "dvbsnoop only will support offline mode..."
//#warning "----"
//
//#define ioctl(...)  	dummyFunc()
//#define _IOR(...)  	dummyFunc()
//static int dummyFunc (void) {return 0;}
//#endif
//
//#ifndef __u64
//#define __s64   long long
//#define __u64   unsigned long long
//
//#endif






#if defined(HAVE_LINUX_DVB_DMX_H)


// API 3
#define DVB_API_VERSION 3

#include <linux/dvb/dmx.h>
#define DEMUX_DEVICE_MASK    "/dev/dvb/adapter%d/demux%d"
#define DVR_DEVICE_MASK      "/dev/dvb/adapter%d/dvr%d"
#include <linux/dvb/frontend.h> 
#define FRONTEND_DEVICE_MASK "/dev/dvb/adapter%d/frontend%d"

// adapter[0-4]/device[0-4]
#define DVB_STD_ADAPTER_NR	0
#define DVB_STD_DEVICE_NR	0
#define DVB_MAX_DEV_PATH_LEN	64


#elif defined(HAVE_OST_DMX_H)


// API 1
#define DVB_API_VERSION 1

#include <ost/dmx.h>
#define DEMUX_DEVICE_MASK   "/dev/dvb/card0/demux0"
#define DVR_DEVICE_MASK     "/dev/dvb/card0/dvr0"
#define dmx_pes_filter_params dmxPesFilterParams
#define dmx_sct_filter_params dmxSctFilterParams
#define pes_type pesType
#include <ost/frontend.h> 
#define FRONTEND_DEVICE_MASK "/dev/dvb/card0/frontend0"
#define fe_status_t FrontendStatus

// card[0-4]/device[0-4]   card = adapter
#define DVB_STD_ADAPTER_NR	0
#define DVB_STD_DEVICE_NR	0
#define DVB_MAX_DEV_PATH_LEN	64


#endif



#endif

