/*
$Id: sig_abort.c,v 1.2 2006/01/02 18:24:04 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 -- Handle Kill/Interrupt Signals from User/OS
 -- (e.g. Kill -1)



$Log: sig_abort.c,v $
Revision 1.2  2006/01/02 18:24:04  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2005/09/06 23:39:04  rasc
catch OS signals (kill ...) for smooth program termination



*/


#include <signal.h>
#include <stdlib.h>


#include "sig_abort.h"


//
// -- Module Global Vars
//


static void SmoothHandler (int sig_nr);
static void AbortHandler  (int sig_nr);
static void NullHandler   (int sig_nr);



// catch these signals 
static struct {
   	int 	sig;
   	void	(*new_handler)();
   	void	(*org_handler)();
} signalList[] = {
	{ SIGHUP,  SmoothHandler,   NullHandler }, // -1  terminate smoothly
	{ SIGQUIT, SmoothHandler,   NullHandler }, // -3  terminate smoothly
	{ SIGABRT, AbortHandler,    NullHandler }, // -6  terminate at once
	{ SIGTERM, SmoothHandler,   NullHandler }  // -15 terminate smoothly
};


#define  SignalListSize (sizeof(signalList) / sizeof(signalList[0]))


static int  hasSignal = 0;	// no Signal by default received


//
// -- init OS  Signal Handler
// -- Set Signals to catch and handler functions
//

void initOSSigHandler (void)
{
  int i;

  for (i=0; i < SignalListSize; i++) {

      signalList[i].org_handler = signal(signalList[i].sig, signalList[i].new_handler);

  }

  hasSignal = 0;

}



//
// -- restore OS  Signal Handler
// -- Set Signals and handler functions prior to dvbsnoop execution
//

void restoreOSSigHandler (void)
{
  int i;

  for (i=0; i < SignalListSize; i++) {

      if (signalList[i].org_handler != SIG_ERR) {
        signal(signalList[i].sig, signalList[i].org_handler);
      }

  }

}



//
// -- check if Abort is Signaled to Program
//
int  isSigAbort (void)
{
  return hasSignal;
}



//
// -- The Signal Handler Routines
//


//
// -- to be checked via isSigAbort()
//
static void SmoothHandler (int sig_nr)
{
  hasSignal = sig_nr;
}


//
// -- Abort NOW by program... 
// -- exit () should flush buffers
//
static void AbortHandler (int sig_nr)
{

  hasSignal = sig_nr;
  restoreOSSigHandler();

  exit (sig_nr);
}


//
// -- dummy
//
static void NullHandler (int sig_nr)
{
  return;
}



