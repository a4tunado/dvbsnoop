/*
$Id: pid_mem.h,v 1.2 2006/01/02 18:24:04 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)





$Log: pid_mem.h,v $
Revision 1.2  2006/01/02 18:24:04  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/03/31 21:14:23  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes



*/


#ifndef __PID_MEM
#define __PID_MEM



void init_PidMemory (void);
int  store_PidToMem (int pid);
int  get_UnusedPidFromMem (void);
void mark_PidMem_as_used (int pid);


#endif


