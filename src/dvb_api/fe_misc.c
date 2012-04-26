/*
$Id: fe_misc.c,v 1.10 2006/03/03 01:51:13 obi Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- FrontEnd routines...
 --  DVB-API 3 (3.1)




$Log: fe_misc.c,v $
Revision 1.10  2006/03/03 01:51:13  obi
use same unit for frequency tolerance as for min, max and stepsize

Revision 1.9  2006/01/02 18:23:59  rasc
just update copyright and prepare for a new public tar ball

Revision 1.8  2005/08/22 22:37:59  rasc
ATSC frontend info

Revision 1.7  2005/08/13 00:06:56  rasc
no message

Revision 1.6  2004/08/22 22:11:57  rasc
no message

Revision 1.5  2004/08/22 22:07:48  rasc
- Fix: nit.h got lost in Makefile
  ifdefs for special DVB-API parameters 

Revision 1.4  2004/04/01 23:02:10  rasc
clear structures in cases these are not completly filled...

Revision 1.3  2004/03/27 22:34:03  rasc
- frontend info  current parameters

Revision 1.2  2004/03/21 18:02:45  rasc
corrections

Revision 1.1  2004/03/21 13:20:07  rasc
more -feinfo, some restructs on FE code



*/


#include <stdint.h>
#include <sys/time.h>
#include <errno.h>


#include "dvbsnoop.h"
#include "fe_misc.h"
#include "misc/output.h"

#include "dmx_error.h"
#include "dvb_api.h"






/*
 * check capability of device function
 * return: 0/1 (has_capability)
 */

int capability_Check (int f, int cap)
{
  u_long  dummy;

  if (ioctl(f,cap,&dummy) < 0) {
	if (errno == ENOSYS)  return 0;
  }

  return 1;
}




/*
 * -- read signal strength parameter 
 */

int read_Signal(int f, FE_SIGNAL *s, FE_SIG_CAP *cap)
{
  int err = 0;

  s->strength = 0;
  s->ber = 0xFFFFFFFF;
  s->snr = 0;
  s->status = 0;
  s->ublocks = 0;


  if (cap->strength) {
  	err = ioctl(f,FE_READ_SIGNAL_STRENGTH,&s->strength);
  }

  if (cap->ber && ! err) {
  	err = ioctl(f,FE_READ_BER,&s->ber);
  }

  if (cap->snr && ! err) {
  	err = ioctl(f,FE_READ_SNR,&s->snr);
  }

  if (cap->status && ! err) {
  	err = ioctl(f,FE_READ_STATUS,&s->status);
  }

  if (cap->ublocks && ! err) {
  	err = ioctl(f,FE_READ_UNCORRECTED_BLOCKS,&s->ublocks);
  }


  if (err < 0) {
//  	if (errno == ENOSIGNAL)  return -2;
	IO_error ("frontend ioctl");
  	return -1;
  }
  return 0;
}




/*
  -- DVI-API Frontend Status Flags -> verbose
  -- we do this API independent per flag...
  -- see history of dvb_api docs
 */

void out_status_detail (int v,fe_status_t s)
{
        out (v,"[");
#if DVB_API_VERSION == 1
        if (s & FE_HAS_SIGNAL)  out (v,"SIG ");
        if (s & FE_HAS_LOCK)    out (v,"LOCK ");
        if (s & FE_SPECTRUM_INV)out (v,"INV ");
#else
        if (s & FE_HAS_SIGNAL)  out (v,"SIG ");
        if (s & FE_HAS_CARRIER) out (v,"CARR ");
        if (s & FE_HAS_VITERBI) out (v,"VIT ");
        if (s & FE_HAS_SYNC)    out (v,"SYNC ");
        if (s & FE_HAS_LOCK)    out (v,"LOCK ");
        if (s & FE_TIMEDOUT)    out (v,"TIMOUT ");
        if (s & FE_REINIT)      out (v,"REINIT ");
#endif
	
        out (v,"]");
}



// Annotation:
//
// DVB_API 3:
// FE_HAS_SIGNAL = 0x01, /* found something above the noise level
// FE_HAS_CARRIER = 0x02, /* found a DVB signal */
// FE_HAS_VITERBI = 0x04, /* FEC is stable */
// FE_HAS_SYNC = 0x08, /* found sync bytes */
// FE_HAS_LOCK = 0x10, /* everything's working... */
// FE_TIMEDOUT = 0x20, /* no lock within the last 2 seconds
// FE_REINIT = 0x40 /* frontend was reinitialized, */
//
// DVB_API: 1
// FE_HAS_POWER = 0x01    the frontend is powered up and is ready to be used
// FE_HAS_SIGNAL = 0x02   the frontend detects a signal above the normal noise level
// FE_SPECTRUM_INV = 0x04 spectrum inversion is enabled/was necessary for lock
// FE_HAS_LOCK = 0x08 	  frontend successfully locked to a DVB signal
// TUNER_HAS_LOCK = 0x80 the tuner has a frequency lock






#if DVB_API_VERSION != 1


/*
 * -- print_FE_BasicCapabilities
 */

int  print_FE_BasicCapabilities (int v, int fd_fe)
{
  int        err;
  u_long     d;
  struct dvb_frontend_info fi;




   out_nl (v,"Basic capabilities:");
   indent(+1);

   err = read_FEInfo(fd_fe, &fi);
   if (err) return 1;
 


   fi.name[127] = '\0';		// be save...
   out_nl (v,"Name: \"%s\"",fi.name);


   {
     char   *s;
     char   *sf;

     s  = "";
     sf = "";
     switch (fi.type) {
	case FE_QPSK:   s = "QPSK (DVB-S)"; sf = "MHz";  break;
	case FE_QAM:	s = "QAM (DVB-C)";  sf = "kHz";  break;
	case FE_OFDM:	s = "OFDM (DVB-T)"; sf = "kHz";  break;
#ifdef FE_ATSC			// API 3.1
	case FE_ATSC:   s = " VSB/QAM (ATSC)"; sf = "khz"; break;	// (QAM | VSB) -> VSB_param
#endif
	default:	s = "unkonwn"; break;
     }
     out_nl (v,"Frontend-type:       %s", s);

     out_nl (v,"Frequency (min):     %d.%03d %s", fi.frequency_min / 1000, fi.frequency_min % 1000, sf);
     out_nl (v,"Frequency (max):     %d.%03d %s", fi.frequency_max / 1000, fi.frequency_max % 1000, sf);
     out_nl (v,"Frequency stepsiz:   %d.%03d %s", fi.frequency_stepsize / 1000, fi.frequency_stepsize % 1000, sf);
     out_nl (v,"Frequency tolerance: %d.%03d %s", fi.frequency_tolerance / 1000, fi.frequency_tolerance % 1000, sf);

   }


   d = 1000000L;
   out_nl (v,"Symbol rate (min):     %d.%06d MSym/s", fi.symbol_rate_min / d, fi.symbol_rate_min % d);
   out_nl (v,"Symbol rate (max):     %d.%06d MSym/s", fi.symbol_rate_max / d, fi.symbol_rate_max % d);
   out_nl (v,"Symbol rate tolerance: %d ppm", fi.symbol_rate_tolerance);
   

   out_nl (v,"Notifier delay: %d ms", fi.notifier_delay);



   out_nl (v,"Frontend capabilities:");
      indent (+1);
      if (fi.caps == FE_IS_STUPID)  		out_nl (v,"stupid FE");
      if (fi.caps &  FE_CAN_INVERSION_AUTO)  	out_nl (v,"auto inversion");
      if (fi.caps &  FE_CAN_FEC_1_2)  		out_nl (v,"FEC 1/2");
      if (fi.caps &  FE_CAN_FEC_2_3)  		out_nl (v,"FEC 2/3");
      if (fi.caps &  FE_CAN_FEC_3_4)  		out_nl (v,"FEC 3/4");
      if (fi.caps &  FE_CAN_FEC_4_5)  		out_nl (v,"FEC 4/5");
      if (fi.caps &  FE_CAN_FEC_5_6)  		out_nl (v,"FEC 5/6");
      if (fi.caps &  FE_CAN_FEC_6_7)  		out_nl (v,"FEC 6/7");
      if (fi.caps &  FE_CAN_FEC_7_8)  		out_nl (v,"FEC 7/8");
      if (fi.caps &  FE_CAN_FEC_AUTO)	  	out_nl (v,"FEC AUTO");
      if (fi.caps &  FE_CAN_QPSK)	  	out_nl (v,"QPSK");
      if (fi.caps &  FE_CAN_QAM_16)	  	out_nl (v,"QAM 16");
      if (fi.caps &  FE_CAN_QAM_32)	  	out_nl (v,"QAM 32");
      if (fi.caps &  FE_CAN_QAM_64)	  	out_nl (v,"QAM 64");
      if (fi.caps &  FE_CAN_QAM_128)	  	out_nl (v,"QAM 128");
      if (fi.caps &  FE_CAN_QAM_256)	  	out_nl (v,"QAM 256");
      if (fi.caps &  FE_CAN_QAM_AUTO)	  	out_nl (v,"QAM AUTO");
      if (fi.caps &  FE_CAN_TRANSMISSION_MODE_AUTO)	out_nl (v,"auto transmission mode");
      if (fi.caps &  FE_CAN_BANDWIDTH_AUTO)		out_nl (v,"auto bandwidth");
      if (fi.caps &  FE_CAN_GUARD_INTERVAL_AUTO)	out_nl (v,"auto guard interval");
      if (fi.caps &  FE_CAN_HIERARCHY_AUTO)	out_nl (v,"auto hierarchy");

#ifdef FE_CAN_CLEAN_SETUP
      if (fi.caps &  FE_CAN_CLEAN_SETUP)	out_nl (v,"clean setup");
#endif
#ifdef FE_CAN_16VSB
      if (fi.caps &  FE_CAN_8VSB)		out_nl (v,"FE_CAN_8VSB");
      if (fi.caps &  FE_CAN_16VSB)		out_nl (v,"FE_CAN_16VSB");
#endif
#ifdef FE_NEEDS_BENDING
      if (fi.caps &  FE_NEEDS_BENDING)		out_nl (v,"FE_NEEDS_BENDING");
#endif
#ifdef FE_CAN_RECOVER
      if (fi.caps &  FE_CAN_RECOVER)		out_nl (v,"FE_CAN_RECOVER");
#endif
#ifdef FE_CAN_MUTE_TS
      if (fi.caps &  FE_CAN_MUTE_TS)		out_nl (v,"FE_CAN_MUTE_TS");
#endif

      indent (-1);
      out_NL(v);


   indent (-1);
   return 0;
}



/*
 * -- print_FE_CurrentParameters
 */

int  print_FE_CurrentParameters (int v, int fd_fe)
{
  int        err;
  struct dvb_frontend_parameters p;
  fe_type_t  fe_typ;
  char       *s;



   out_nl (v,"Current parameters:");
   indent(+1);


   fe_typ = read_FEType(fd_fe);
   err = read_FEParam(fd_fe, &p);
   if (err) return 1;
 




   out_nl (v,"Frequency:  %d.%03d %s", p.frequency / 1000, p.frequency % 1000,
					(fe_typ == QPSK) ? "MHz" : "kHz");

   s = "unknown";
   switch (p.inversion) {
	   case INVERSION_OFF:	s = "OFF"; break;
	   case INVERSION_ON:	s = "ON"; break;
	   case INVERSION_AUTO:	s = "AUTO"; break;
   }
   out_nl (v,"Inversion:  %s", s);


   switch (fe_typ) {
	   case FE_QPSK:  print_FE_QPSK_param (v,p.u.qpsk); break;
	   case FE_QAM:   print_FE_QAM_param  (v,p.u.qam);  break;
	   case FE_OFDM:  print_FE_OFDM_param (v,p.u.ofdm); break;
#ifdef FE_ATSC
	   case FE_ATSC:  print_FE_VSB_param  (v,p.u.vsb);  break;  // also for ATSC QAM
#endif
   }

   indent(-1);
   out_NL(v);

   return 0;
}




/*
 * -- print_FE QPSK parameters
 */

void print_FE_QPSK_param (int v, struct dvb_qpsk_parameters qp)
{
  u_long  d;

   d = 1000000L;
   out_nl (v,"Symbol rate:  %d.%06d MSym/s", qp.symbol_rate / d, qp.symbol_rate % d);
   out_nl (v,"FEC:  %s", festr_FE_code_rate (qp.fec_inner));
}



/*
 * -- print_FE QAM parameters
 */

void print_FE_QAM_param (int v, struct dvb_qam_parameters qp)
{
  u_long  d;

   d = 1000000L;
   out_nl (v,"Symbol rate:  %d.%06d MSym/s", qp.symbol_rate / d, qp.symbol_rate % d);
   out_nl (v,"FEC:  %s", festr_FE_code_rate (qp.fec_inner));
   out_nl (v,"Modulation:  %s", festr_FE_modulation (qp.modulation));
}



/*
 * -- print_FE OFDM parameters
 */

void print_FE_OFDM_param (int v, struct dvb_ofdm_parameters op)
{

   out_nl (v,"Bandwidth:  %s", festr_FE_bandwidth (op.bandwidth));
   out_nl (v,"Stream code rate (hi prio):  %s", festr_FE_code_rate (op.code_rate_HP));
   out_nl (v,"Stream code rate (lo prio):  %s", festr_FE_code_rate (op.code_rate_LP));
   out_nl (v,"Modulation:  %s", festr_FE_modulation (op.constellation));

   out_nl (v,"Transmission mode:  %s", festr_FE_transmit_mode (op.transmission_mode));
   out_nl (v,"Guard interval:  %s", festr_FE_guard_interval (op.guard_interval));
   out_nl (v,"Hierarchy:  %s", festr_FE_hierarchy (op.hierarchy_information));
}


/*
 * -- print_FE vsb parameters
 */

#ifdef FE_ATSC
void print_FE_VSB_param (int v, struct dvb_vsb_parameters vsb)
{

   out_nl (v,"Modulation:  %s", festr_FE_modulation (vsb.modulation));
}
#endif






//
// ----------------------------------------------------------------------
//



/*
 * -- get_FEType
 * -- returns: fe_type_t  (FE_QPSK, FE_QAM, FE_OFDM)
 */

fe_type_t  read_FEType(int f)
{
  struct dvb_frontend_info fi;

  memset (&fi, 0, sizeof(struct dvb_frontend_info));
  read_FEInfo(f, &fi);
  return fi.type;
}



/*
 * -- read frontend info
 */

int read_FEInfo(int f, struct dvb_frontend_info *fi)
{
  int err = 0;


  memset (fi, 0, sizeof(struct dvb_frontend_info));
  err = ioctl(f, FE_GET_INFO, fi);
  if (err < 0) {
	IO_error ("frontend ioctl");
  	return -1;
  }
  return 0;
}



/*
 * -- read effective frontend params
 */

int read_FEParam(int f, struct dvb_frontend_parameters *p)
{
  int err = 0;


  memset (p, 0, sizeof(struct dvb_frontend_parameters));
  err = ioctl(f, FE_GET_FRONTEND, p);
  if (err < 0) {
	IO_error ("frontend ioctl");
  	return -1;
  }
  return 0;
}





//
// ----------------------------------------------------------------------
//


/*
 * -- FE strings...
 */

const char *festr_FE_code_rate (fe_code_rate_t fec)
{
  const char *s = "";

  switch (fec) {
	  case FEC_NONE: s = "none"; break;
	  case FEC_1_2:  s = "FEC 1/2"; break;
	  case FEC_2_3:  s = "FEC 2/3"; break;
	  case FEC_3_4:  s = "FEC 3/4"; break;
	  case FEC_4_5:  s = "FEC 4/5"; break;
	  case FEC_5_6:  s = "FEC 5/6"; break;
	  case FEC_6_7:  s = "FEC 6/7"; break;
	  case FEC_7_8:  s = "FEC 7/8"; break;
	  case FEC_8_9:  s = "FEC 8/9"; break;
	  case FEC_AUTO: s = "FEC AUTO"; break;
  }

  return s;
}



const char *festr_FE_modulation (fe_modulation_t modulation)
{
  const char *s = "";

  switch (modulation) {
	  case QPSK:     s = "QPSK"; break;
	  case QAM_16:   s = "QAM 16"; break;
	  case QAM_32:   s = "QAM 32"; break;
	  case QAM_64:   s = "QAM 64"; break;
	  case QAM_128:  s = "QAM 128"; break;
	  case QAM_256:  s = "QAM 256"; break;
	  case QAM_AUTO: s = "QAM AUTO"; break;
#ifdef VSB_16
	  case VSB_8:    s = "VSB 8"; break;
	  case VSB_16:   s = "VSB 16"; break;
#endif
  }

  return s;
}



const char *festr_FE_bandwidth (fe_bandwidth_t bandwidth)
{
  const char *s = "";

  switch (bandwidth) {
	  case BANDWIDTH_8_MHZ:     s = "8 MHz"; break;
	  case BANDWIDTH_7_MHZ:     s = "7 MHz"; break;
	  case BANDWIDTH_6_MHZ:     s = "6 MHz"; break;
	  case BANDWIDTH_AUTO:      s = "AUTO"; break;
  }

  return s;
}


const char *festr_FE_transmit_mode (fe_transmit_mode_t transmit_mode)
{
  const char *s = "";

  switch (transmit_mode) {
	  case TRANSMISSION_MODE_2K:     s = "2k mode"; break;
	  case TRANSMISSION_MODE_8K:     s = "8k mode"; break;
	  case TRANSMISSION_MODE_AUTO:   s = "auto"; break;
  }

  return s;
}



const char *festr_FE_guard_interval (fe_guard_interval_t guard_interval)
{
  const char *s = "";

  switch (guard_interval) {
	  case GUARD_INTERVAL_1_32:  s = "1/32"; break;
	  case GUARD_INTERVAL_1_16:  s = "1/16"; break;
	  case GUARD_INTERVAL_1_8:   s = "1/8"; break;
	  case GUARD_INTERVAL_1_4:   s = "1/4"; break;
	  case GUARD_INTERVAL_AUTO:  s = "auto"; break;
  }

  return s;
}




const char *festr_FE_hierarchy (fe_hierarchy_t hierarchy)
{
  const char *s = "";

  switch (hierarchy) {
	  case HIERARCHY_NONE:  s = "none"; break;
	  case HIERARCHY_1:     s = "1"; break;
	  case HIERARCHY_2:     s = "2"; break;
	  case HIERARCHY_4:     s = "4"; break;
	  case HIERARCHY_AUTO:  s = "auto"; break;
  }

  return s;
}





#endif




