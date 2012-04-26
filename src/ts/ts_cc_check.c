/*
$Id: ts_cc_check.c,v 1.2 2006/01/02 18:24:34 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de



 -- Transport Stream  continuity counter check

   


$Log: ts_cc_check.c,v $
Revision 1.2  2006/01/02 18:24:34  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2005/09/09 14:21:12  rasc
TS continuity sequence check (cc verbose output)



*/




#include "dvbsnoop.h"
#include "ts_cc_check.h"
#include "misc/output.h"




typedef struct _TS_CC {
	char    last_continuity_counter;	// 0..15 + special values
} TS_CC;

enum  { CC_DISCONTINUED=127 };

static  TS_CC  tscc[MAX_PID+2];
static  int    current_pid;			// reminder for current pid




//------------------------------------------------------------ 

//
// -- init TS sub decoding buffer
// -- return: < 0: fail
//
void ts_cc_init (void)
{
  int i; 
  int n = (sizeof(tscc) / sizeof(tscc[0]));
 
  for (i=0; i < n; i++) {
	  tscc[i].last_continuity_counter = CC_DISCONTINUED;
  }
}

void ts_cc_free (void)
{
  return;
}



//
// -- set current PID for checking CC
// -- (this is workaround, because we can only deliver 1 param to
// --  string routine using out_S2x...)
//

void ts_cc_SetPid (int pid)
{
  current_pid = pid;
}


//
// -- TS Continuity status check
// -- (has to be compatible to dvbStr... routines!)
// -- Return status string for display
//
char * ts_cc_StatusStr (int cc)
{
  char *s = "(sequence ok)";
  int  pid = current_pid;


  // -- first time or discontinuity signalled

  if (tscc[pid].last_continuity_counter == CC_DISCONTINUED) {
      tscc[pid].last_continuity_counter = cc;
      return s;
  }

  // -- duplicate packet (same cc for pid)
  // -- check continuity counter

  if (tscc[pid].last_continuity_counter == cc) {
	  s = "(duplicate packet)";
  } else if (cc != ((tscc[pid].last_continuity_counter+1) % 16) ) {
	  s = "(continuity error!)";
  }

  tscc[pid].last_continuity_counter = cc;
  return s;
}


