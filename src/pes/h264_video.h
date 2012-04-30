#ifndef __MPEG4_VIDEO__
#define __MPEG4_VIDEO__

#include "dvbsnoop.h"

enum { 	NAL_UNSPECIFIED = 0x00
  , NAL_NONIDR = 0x01
  , NAL_IDR = 0x05
  , NAL_SEI = 0x06
  , NAL_SPS = 0x07
  , NAL_PPS = 0x08
  , NAL_AUD = 0x09
};


void MPEG4_decodeAUD(int v, u_char *b, int len);
void MPEG4_decodeSPS(int v, u_char *b, int len);
void MPEG4_decodePPS(int v, u_char *b, int len);
void MPEG4_decodeSEI(int v, u_char *b, int len);
void MPEG4_decodeSlice(int v, u_char *b, int len);

#endif

