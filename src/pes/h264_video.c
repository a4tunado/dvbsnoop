#include "h264_video.h"

#include <math.h>

#include "dvbsnoop.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"

#include "bitdata/bitdata_fns.h"
#include "bitdata/bitdata_defns.h"

typedef struct _H264_AUD {
  uint32_t primary_pic_type;
} H264_AUD;

typedef struct _H264_SPS {
  uint8_t profile_idc;
  uint8_t constraint_set0_flag;
  uint8_t constraint_set1_flag;
  uint8_t constraint_set2_flag;
  uint8_t constraint_set3_flag;
  uint8_t reserved_zero_4bits;
  uint8_t level_idc;
  uint32_t seq_parameter_set_id;
  uint32_t chroma_format_idc;
  uint8_t separate_colour_plane_flag;
  uint32_t bit_depth_luma_minus8;
  uint32_t bit_depth_chroma_minus8;
  uint8_t qpprime_y_zero_transform_bypass_flag;
  uint8_t seq_scaling_matrix_present_flag;
  //uint8_t seq_scaling_list_present_flag[ ];
  uint32_t log2_max_frame_num_minus4;
  uint32_t pic_order_cnt_type;
  uint32_t log2_max_pic_order_cnt_lsb_minus4;
  uint8_t delta_pic_order_always_zero_flag;
  uint32_t offset_for_non_ref_pic;
  uint32_t offset_for_top_to_bottom_field;
  uint32_t num_ref_frames_in_pic_order_cnt_cycle;
  //uint32_t offset_for_ref_frame[ ];
  uint32_t num_ref_frames;
  uint8_t gaps_in_frame_num_value_allowed_flag;
  uint32_t pic_width_in_mbs_minus1;
  uint32_t pic_height_in_map_minus1;
  uint8_t frame_mbs_only_flag;
} H264_SPS;

typedef struct _H264_PPS {
  uint32_t pic_parameter_set_id;
  uint32_t seq_parameter_set_id;
  uint8_t entropy_coding_mode_flag;
  uint8_t pic_order_present_flag;
  uint32_t num_slice_groups_minus1;
  uint32_t slice_group_map_type;
  uint8_t slice_group_change_direction_flag;
  uint32_t slice_group_change_rate_minus1;
  uint32_t pic_size_in_map_units_minus1;
  uint32_t num_ref_idx_l0_active_minus1;
  uint32_t num_ref_idx_l1_active_minus1;
  uint8_t weighted_pred_flag;
  uint32_t weighted_bipred_idc;
  int32_t pic_init_qp_minus26;
  int32_t pic_init_qs_minus26;
  int32_t chroma_qp_index_offset;
  uint8_t deblocking_filter_control_present_flag;
  uint8_t constrained_intra_pred_flag;
  uint8_t redundant_pic_cnt_present_flag;
} H264_PPS;

typedef struct _H264_DECODER {
  H264_SPS sps;
  H264_PPS pps;
} H264_DECODER;

static H264_DECODER decoder = {0,};

static u_int remove_0x03(u_char *b, u_int len) {
  u_int i = 0;
  while (i + 2 < len) {
    if (b[0] == 0 && b[1] == 0 && b[2] == 3) {
      b += 2; i += 2; --len;
      memmove(b, b + 1, len - i);
    } else { ++b; ++i; }
  }
  return len;
}

void H264_decodeAUD(int v, u_char *b, int len) {

  H264_AUD aud = {0,};

  bitdata data = {0,};

  data.data = (byte*)(b);
  data.data_len = remove_0x03(b, len);
  data.cur_bit = -1;

  read_bits(&data, 3, &aud.primary_pic_type);

  out_SB_NL(v, "primary_pic_type: ", aud.primary_pic_type);
}

void H264_decodeSPS(int v, u_char *b, int len) {

  H264_SPS sps = {0,};
  
  bitdata data = {0,};

  data.data = (byte*)(b);
  data.data_len = remove_0x03(b, len);
  data.cur_bit = -1;

  read_bits_into_byte(&data, 8, &sps.profile_idc);
  read_bit(&data, &sps.constraint_set0_flag);
  read_bit(&data, &sps.constraint_set1_flag);
  read_bit(&data, &sps.constraint_set2_flag);
  read_bit(&data, &sps.constraint_set3_flag);
  read_bits_into_byte(&data, 4, &sps.reserved_zero_4bits);
  read_bits_into_byte(&data, 8, &sps.level_idc);
  read_exp_golomb(&data, &sps.seq_parameter_set_id); 

  if (sps.profile_idc == 100 || sps.profile_idc == 110
      || sps.profile_idc == 122 || sps.profile_idc == 144) {
    
    read_exp_golomb(&data, &sps.chroma_format_idc);
    if (sps.chroma_format_idc == 3) {
      read_bit(&data, &sps.separate_colour_plane_flag);
    }
    
    read_exp_golomb(&data, &sps.bit_depth_luma_minus8);
    read_exp_golomb(&data, &sps.bit_depth_chroma_minus8);
    read_bit(&data, &sps.qpprime_y_zero_transform_bypass_flag);
    read_bit(&data, &sps.seq_scaling_matrix_present_flag);
    
    if (sps.seq_scaling_matrix_present_flag) {
      uint32_t i;
      for (i = 0; i < ((sps.chroma_format_idc != 3) ? 8 : 12); ++i) {
        uint8_t seq_scaling_list_present_flag;
        read_bit(&data, &seq_scaling_list_present_flag);
        if(seq_scaling_list_present_flag) {
          uint32_t j, last_scale = 8, next_scale = 8;
          for(j = 0; j < ((i < 6) ? 16 : 64); ++j) {
            if(next_scale != 0) {
               int32_t delta_scale;
               read_signed_exp_golomb(&data, &delta_scale);
               next_scale = (last_scale + delta_scale + 256) % 256;
            }
            last_scale = (next_scale == 0) ? last_scale : next_scale;
          }
        }
      }
    } // if (sps.seq_scaling_matrix_present_flag)

  }

  read_exp_golomb(&data, &sps.log2_max_frame_num_minus4);
  
  read_exp_golomb(&data, &sps.pic_order_cnt_type);
  if (sps.pic_order_cnt_type == 0) {
    read_exp_golomb(&data, &sps.log2_max_pic_order_cnt_lsb_minus4);
  } else if (sps.pic_order_cnt_type == 1) {
    uint32_t i;
    read_bit(&data, &sps.delta_pic_order_always_zero_flag);
    read_exp_golomb(&data, &sps.offset_for_non_ref_pic);
    read_exp_golomb(&data, &sps.offset_for_top_to_bottom_field);
    read_exp_golomb(&data, &sps.num_ref_frames_in_pic_order_cnt_cycle);
    for (i = 0; i < sps.num_ref_frames_in_pic_order_cnt_cycle; ++i) {
      uint32_t offset_for_ref_frame;
      read_exp_golomb(&data, &offset_for_ref_frame);
    }
  } // if (sps.pic_order_cnt_type == 1)

  read_exp_golomb(&data, &sps.num_ref_frames);
  read_bit(&data, &sps.gaps_in_frame_num_value_allowed_flag);
  read_exp_golomb(&data, &sps.pic_width_in_mbs_minus1);
  read_exp_golomb(&data, &sps.pic_height_in_map_minus1);
  read_bit(&data, &sps.frame_mbs_only_flag);

  decoder.sps = sps;

  out_S2B_NL(v, "profile_idc: ", sps.profile_idc, dvbstrH264_Profile_IDC(sps.profile_idc));
  out_SB_NL(v, "constraint_set0_flag: ", sps.constraint_set0_flag);
  out_SB_NL(v, "constraint_set1_flag: ", sps.constraint_set1_flag);
  out_SB_NL(v, "constraint_set2_flag: ", sps.constraint_set2_flag);
  out_SB_NL(v, "constraint_set3_flag: ", sps.constraint_set3_flag);
  out_SB_NL(v, "reserved_zero_4bits: ", sps.reserved_zero_4bits);
  out_SB_NL(v, "level_idc: ", sps.level_idc);
  out_SB_NL(v, "seq_parameter_set_id: ", sps.seq_parameter_set_id);
  
  if (sps.profile_idc == 100 || sps.profile_idc == 110
      || sps.profile_idc == 122 || sps.profile_idc == 144) {

    out_SB_NL(v, "chroma_format_idc: ", sps.chroma_format_idc);
    if (sps.chroma_format_idc == 3) {
      out_SB_NL(v, "separate_colour_plane_flag: ", sps.separate_colour_plane_flag);
    }
    out_SB_NL(v, "bit_depth_luma_minus8: ", sps.bit_depth_luma_minus8);
    out_SB_NL(v, "bit_depth_chroma_minus8: ", sps.bit_depth_chroma_minus8);
    out_SB_NL(v, "qpprime_y_zero_transform_bypass_flag: ", sps.qpprime_y_zero_transform_bypass_flag);
    out_SB_NL(v, "seq_scaling_matrix_present_flag: ", sps.seq_scaling_matrix_present_flag);
  }

  out_SB_NL(v, "log2_max_frame_num_minus4: ", sps.log2_max_frame_num_minus4);
  out_SB_NL(v, "pic_order_cnt_type: ", sps.pic_order_cnt_type);
  if (sps.pic_order_cnt_type == 0) {
    out_SB_NL(v, "log2_max_pic_order_cnt_lsb_minus4: ", sps.log2_max_pic_order_cnt_lsb_minus4);
  } else if (sps.pic_order_cnt_type == 1) {
    out_SB_NL(v, "delta_pic_order_always_zero_flag: ", sps.delta_pic_order_always_zero_flag);
    out_SB_NL(v, "offset_for_non_ref_pic: ", sps.offset_for_non_ref_pic);
    out_SB_NL(v, "offset_for_top_to_bottom_field: ", sps.offset_for_top_to_bottom_field);
    out_SB_NL(v, "num_ref_frames_in_pic_order_cnt_cycle: ", sps.num_ref_frames_in_pic_order_cnt_cycle);
  }

  out_SB_NL(v, "num_ref_frames: ", sps.num_ref_frames);
  out_SB_NL(v, "gaps_in_frame_num_value_allowed_flag: ", sps.gaps_in_frame_num_value_allowed_flag);

  out_nl (v , "pic_width_in_mbs_minus1: %d (0x%02x) [= %d]"
            , sps.pic_width_in_mbs_minus1
            , sps.pic_width_in_mbs_minus1
            , 16 * (sps.pic_width_in_mbs_minus1 + 1));

  out_nl (v , "pic_height_in_map_minus1: %d (0x%02x) [= %d]"
            , sps.pic_height_in_map_minus1
            , sps.pic_height_in_map_minus1
            , (2 - sps.frame_mbs_only_flag) * (sps.pic_height_in_map_minus1 + 1) * 16);

  out_SB_NL(v, "frame_mbs_only_flag: ", sps.frame_mbs_only_flag);
}

void H264_decodePPS(int v, u_char *b, int len) {

  H264_PPS pps = {0,};

  bitdata data = {0,};

  data.data = (byte*)(b);
  data.data_len = remove_0x03(b, len);
  data.cur_bit = -1;

  read_exp_golomb(&data, &pps.pic_parameter_set_id);
  read_exp_golomb(&data, &pps.seq_parameter_set_id);
  read_bit(&data, &pps.entropy_coding_mode_flag);
  read_bit(&data, &pps.pic_order_present_flag);
  
  read_exp_golomb(&data, &pps.num_slice_groups_minus1);
  if (pps.num_slice_groups_minus1 > 0) {

    read_exp_golomb(&data, &pps.slice_group_map_type);
    switch (pps.slice_group_map_type) {
      case 0: {
        uint32_t i;
        for (i = 0; i <= pps.num_slice_groups_minus1; ++i) {
          uint32_t run_length_minus1;
          read_exp_golomb(&data, &run_length_minus1);
        }
      } break;
      case 2: {
        uint32_t i;
        for (i = 0; i < pps.num_slice_groups_minus1; ++i) {
          uint32_t top_left, bottom_right;
          read_exp_golomb(&data, &top_left);
          read_exp_golomb(&data, &bottom_right);
        }
      } break;
      case 3:
      case 4:
      case 5: {
        read_bit(&data, &pps.slice_group_change_direction_flag);
        read_exp_golomb(&data, &pps.slice_group_change_rate_minus1);
      } break;
      case 6: {
        uint32_t i, size = (uint32_t)ceil(log2(pps.num_slice_groups_minus1+1));
        read_exp_golomb(&data, &pps.pic_size_in_map_units_minus1);
        for (i = 0; i <= pps.pic_size_in_map_units_minus1; ++i) {
          uint32_t slice_group_id;
          read_bits(&data, size, &slice_group_id);
        }
      } break;
    } // switch (pps.slice_group_map_type)

  } // if (pps.num_slice_groups_minus1 > 0)

  read_exp_golomb(&data, &pps.num_ref_idx_l0_active_minus1);
  read_exp_golomb(&data, &pps.num_ref_idx_l1_active_minus1);
  read_bit(&data, &pps.weighted_pred_flag);
  read_bits(&data, 2, &pps.weighted_bipred_idc);
  read_signed_exp_golomb(&data, &pps.pic_init_qp_minus26);
  read_signed_exp_golomb(&data, &pps.pic_init_qs_minus26);
  read_signed_exp_golomb(&data, &pps.chroma_qp_index_offset);
  read_bit(&data, &pps.deblocking_filter_control_present_flag);
  read_bit(&data, &pps.constrained_intra_pred_flag);
  read_bit(&data, &pps.redundant_pic_cnt_present_flag);

  decoder.pps = pps;

  out_SB_NL(v, "pic_parameter_set_id: ", pps.pic_parameter_set_id);
  out_SB_NL(v, "seq_parameter_set_id: ", pps.seq_parameter_set_id);
  out_SB_NL(v, "entropy_coding_mode_flag: ", pps.entropy_coding_mode_flag);
  out_SB_NL(v, "pic_order_present_flag: ", pps.pic_order_present_flag);

  out_SB_NL(v, "num_slice_groups_minus1: ", pps.num_slice_groups_minus1);
  if (pps.num_slice_groups_minus1 > 0) {
    out_SB_NL(v, "slice_group_map_type: ", pps.slice_group_map_type);
    switch (pps.slice_group_map_type) {
      case 3:
      case 4:
      case 5:
        out_SB_NL(v, "slice_group_change_direction_flag: ", pps.slice_group_change_direction_flag);
        out_SB_NL(v, "slice_group_change_rate_minus1: ", pps.slice_group_change_rate_minus1);
        break;
      case 6:
        out_SB_NL(v, "pic_size_in_map_units_minus1: ", pps.pic_size_in_map_units_minus1);
        break;
    }
  }

  out_SB_NL(v, "num_ref_idx_l0_active_minus1: ", pps.num_ref_idx_l0_active_minus1);
  out_SB_NL(v, "num_ref_idx_l1_active_minus1: ", pps.num_ref_idx_l1_active_minus1);
  out_SB_NL(v, "weighted_pred_flag: ", pps.weighted_pred_flag);
  out_SB_NL(v, "weighted_bipred_idc: ", pps.weighted_bipred_idc);
  out_SB_NL(v, "pic_init_qp_minus26: ", pps.pic_init_qp_minus26);
  out_SB_NL(v, "pic_init_qs_minus26: ", pps.pic_init_qs_minus26);
  out_SB_NL(v, "chroma_qp_index_offset: ", pps.chroma_qp_index_offset);
  out_SB_NL(v, "deblocking_filter_control_present_flag: ", pps.deblocking_filter_control_present_flag);
  out_SB_NL(v, "constrained_intra_pred_flag: ", pps.constrained_intra_pred_flag);
  out_SB_NL(v, "redundant_pic_cnt_present_flag: ", pps.redundant_pic_cnt_present_flag);
}

void H264_decodeSEI(int v, u_char *b, int len) {
  //print_databytes (v, "Bytes (incl. sync + id):", b, len);
}

void H264_decodeSlice(int v, u_char *b, int len) {

  typedef struct _H264_SLICE {
    uint32_t first_mb_in_slice;
    uint32_t slice_type;
    uint32_t pic_parameter_set_id;
    uint32_t colour_plane_id;
    uint32_t frame_num;
  } H264_SLICE;

  H264_SLICE slice = {0,};

  bitdata data = {0,};

  data.data = (byte*)(b);
  data.data_len = remove_0x03(b, len);
  data.cur_bit = -1;

  read_exp_golomb(&data, &slice.first_mb_in_slice);
  read_exp_golomb(&data, &slice.slice_type);
  read_exp_golomb(&data, &slice.pic_parameter_set_id);

  if (slice.pic_parameter_set_id != decoder.pps.pic_parameter_set_id 
      || decoder.pps.seq_parameter_set_id != decoder.sps.seq_parameter_set_id) {
    out_nl (3," !!! Invalid pps reference %d\n!!!", slice.pic_parameter_set_id);
  }

  if (decoder.sps.separate_colour_plane_flag == 1) {
    read_bits(&data, 2, &slice.colour_plane_id);
  }

  read_bits(&data, decoder.sps.log2_max_frame_num_minus4 + 4, &slice.frame_num);

  out_SB_NL(v, "first_mb_in_slice: ", slice.first_mb_in_slice);
  out_S2B_NL(v, "slice_type: ", slice.slice_type, dvbstrPESH264_Slice_ID(slice.slice_type));
  out_SB_NL(v, "pic_parameter_set_id: ", slice.pic_parameter_set_id);
  if (decoder.sps.separate_colour_plane_flag == 1) {
    out_SB_NL(v, "colour_plane_id: ", slice.colour_plane_id);
  }
  out_SB_NL(v, "frame_num: ", slice.frame_num);
}
