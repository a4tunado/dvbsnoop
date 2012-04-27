#include "dvbsnoop.h"
#include "h264_video.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"

void H264_decodeAUD(int v, u_char *b, int len) {
  print_databytes (v, "H264 AUD (incl. sync + id):", b, len);
}

void H264_decodeSPS(int v, u_char *b, int len) {
  print_databytes (v, "H264 SPS (incl. sync + id):", b, len);
}

void H264_decodePPS(int v, u_char *b, int len) {
  print_databytes (v, "H264 PPS (incl. sync + id):", b, len);
}

void H264_decodeSEI(int v, u_char *b, int len) {
  print_databytes (v, "H264 SEI (incl. sync + id):", b, len);
}

void H264_decodeSlice(int v, u_char *b, int len) {
  print_databytes (v, "H264 Slice (incl. sync + id):", b, len);
}

