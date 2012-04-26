/*


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



*/


#ifndef __HELPER_H
#define __HELPER_H


u_long outBit_Sx (int verbosity, const char *text, u_char *buf, int startbit, int bitlen);
u_long outBit_Sx_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen);
u_long outBit_S2x_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen, char *(*f)(u_long) );
u_long outBit_S2Tx_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen, const char *text2 );

unsigned long long outBit64_Sx (int verbosity, const char *text, u_char *buf, int startbit, int bitlen);
unsigned long long outBit64_Sx_NL (int verbosity, const char *text, u_char *buf, int startbit, int bitlen);


u_long getBits (u_char *buf, int byte_offset, int startbit, int bitlen);
long long getBits48 (u_char *buf, int byte_offset, int startbit, int bitlen);
unsigned long long getBits64 (u_char *buf, int byte_offset, int startbit, int bitlen);

u_char *getISO639_3 (u_char *str, u_char *buf);

void print_text_468A (int v, const char *s, u_char *b, u_int len);
void print_text_UTF8 (int v, const char *s, u_char *b, u_int len);
void print_std_ascii (int v, const char *s, u_char *b, u_int len);

void print_time_utc (int v, u_long utc);
void print_time_mjd (int v, u_long mjd);
void print_time40 (int verbose, u_long mjd, u_long utc);
void print_timebase90kHz (int v, long long time90kHz);
void print_pcr_time (int v, long long time90kHz, int ext_27MHz);

void print_databytes (int verbose, const char *str, u_char *b, u_int len);
void print_databytes_line  (int v, const char *str, u_char *b, u_int len);
void print_private_data (int verbose, u_char *b, u_int len);

void print_BitMatrix (int v, char *str, u_char *b, int bitoffset,  int matrix_x, int matrix_y);

long str2i (char *s);
int  str2barray  (char *s, u_char *barray, int max_len);

char *str_cell_latitude (long latitude);
char *str_cell_longitude (long longitude);



struct IPv6ADDR {
	u_long  ip[4];		// 32 bit: ip[0] ip[1] ip[2] ip[3]
};

void displ_mac_addr (int v, long mac_H24, long mac_L24);
void displ_IPv4_addr (int v, u_long ip);
struct IPv6ADDR *getIPv6Addr (u_char *b, struct IPv6ADDR *x);
void displ_IPv6_addr (int v, struct IPv6ADDR *ip);



char *str_bit32 (u_long value, int bits);


int lenCheckErrOut (int v, int len);


#endif


