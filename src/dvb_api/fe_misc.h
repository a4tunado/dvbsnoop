/*
$Id: fe_misc.h,v 1.5 2006/01/02 18:23:59 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)

*/

#ifndef __FE_MISC_H
#define __FE_MISC_H

#include "dvb_api.h"



typedef struct _fe_signal {
	int16_t   strength;
	int16_t   snr;
	uint32_t  ber;
	uint32_t  ublocks;
	fe_status_t status;
} FE_SIGNAL;

typedef struct _fe_signal_cap {
	int  ber;
	int  snr;
	int  strength;
	int  status;
	int  ublocks;
} FE_SIG_CAP;



int capability_Check (int f, int cap);
int read_Signal(int f, FE_SIGNAL *s, FE_SIG_CAP *cap);
void out_status_detail (int v, fe_status_t s);



#if DVB_API_VERSION != 1

// -- only > API3

int  print_FE_BasicCapabilities (int v, int f);
int  print_FE_CurrentParameters (int v, int f);

void print_FE_QPSK_param (int v, struct dvb_qpsk_parameters qp);
void print_FE_QAM_param  (int v, struct dvb_qam_parameters qp);
void print_FE_OFDM_param (int v, struct dvb_ofdm_parameters op);
#ifdef FE_ATSC			// API 3.1
void print_FE_VSB_param  (int v, struct dvb_vsb_parameters vsb);
#endif


fe_type_t  read_FEType(int f);
int read_FEInfo(int f, struct dvb_frontend_info *fi);
int read_FEParam(int f, struct dvb_frontend_parameters *p);


const char *festr_FE_code_rate (fe_code_rate_t fec);
const char *festr_FE_modulation (fe_modulation_t modulation);
const char *festr_FE_bandwidth (fe_bandwidth_t bandwidth);
const char *festr_FE_transmit_mode (fe_transmit_mode_t transmit_mode);
const char *festr_FE_guard_interval (fe_guard_interval_t guard_interval);
const char *festr_FE_hierarchy (fe_hierarchy_t hierarchy);



#endif








#endif


