#include "dvbsnoop.h"
#include "h264_video.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"

#include "bitdata/bitdata_fns.h"
#include "bitdata/bitdata_defns.h"

void H264_decodeAUD(int v, u_char *b, int len) {
  //print_databytes (v, "Bytes (incl. sync + id):", b, len);
}

void H264_decodeSPS(int v, u_char *b, int len) {
  //print_databytes (v, "Bytes (incl. sync + id):", b, len);
}

void H264_decodePPS(int v, u_char *b, int len) {
  //print_databytes (v, "Bytes (incl. sync + id):", b, len);
}

void H264_decodeSEI(int v, u_char *b, int len) {
  //print_databytes (v, "Bytes (incl. sync + id):", b, len);
}

void H264_decodeSlice(int v, u_char *b, int len) {
  bitdata data = {0};
  data.data = (byte*)(b+4);
  data.data_len = len;
  data.cur_bit = -1;

  uint32_t first_mb_in_slice = 0;
  uint32_t slice_type = 0;

  read_exp_golomb(&data, &first_mb_in_slice);
  read_exp_golomb(&data, &slice_type);

  out_SB_NL(v, "first_mb_in_slice: ", first_mb_in_slice);
  out_S2B_NL(v, "slice_type: ", slice_type, dvbstrPESH264_Slice_ID(slice_type));

  //print_databytes (v, "(incl. sync + id):", b, len);
}

