#include "h264_video.h"

#include <math.h>

#include "dvbsnoop.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/helper.h"
#include "misc/output.h"

#include "bitdata/bitdata_fns.h"
#include "bitdata/bitdata_defns.h"

#define IS_P_SLICE(type) ((type)%0x05 == 0x00)
#define IS_B_SLICE(type) ((type)%0x05 == 0x01)
#define IS_I_SLICE(type) ((type)%0x05 == 0x02)

#define IS_SP_SLICE(type) ((type)%0x05 == 0x03)
#define IS_SI_SLICE(type) ((type)%0x05 == 0x04)

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
  uint32_t pic_height_in_map_units_minus1;
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

  uint8_t nal_unit_type = b[3]&0x1F;

  bitdata data = {0,};
  data.data = (byte*)(b+4);
  data.data_len = remove_0x03(b+4, len-4);
  data.cur_bit = -1;

  read_bits(&data, 3, &aud.primary_pic_type);

  out_SB_NL(v, "primary_pic_type: ", aud.primary_pic_type);
}

void H264_decodeSPS(int v, u_char *b, int len) {

  H264_SPS sps = {0,};
  sps.chroma_format_idc = 1; // default

  uint8_t nal_unit_type = b[3]&0x1F;
  
  bitdata data = {0,};
  data.data = (byte*)(b+4);
  data.data_len = remove_0x03(b+4, len-4);
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
  read_exp_golomb(&data, &sps.pic_height_in_map_units_minus1);
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

  out_nl (v , "pic_height_in_map_units_minus1: %d (0x%02x) [= %d]"
            , sps.pic_height_in_map_units_minus1
            , sps.pic_height_in_map_units_minus1
            , (2 - sps.frame_mbs_only_flag) * (sps.pic_height_in_map_units_minus1 + 1) * 16);

  out_SB_NL(v, "frame_mbs_only_flag: ", sps.frame_mbs_only_flag);
}

void H264_decodePPS(int v, u_char *b, int len) {

  H264_PPS pps = {0,};

  uint8_t nal_unit_type = b[3]&0x1F;

  bitdata data = {0,};
  data.data = (byte*)(b+4);
  data.data_len = remove_0x03(b+4, len-4);
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
  out_SLL_NL(v, "pic_init_qp_minus26: ", pps.pic_init_qp_minus26);
  out_SLL_NL(v, "pic_init_qs_minus26: ", pps.pic_init_qs_minus26);
  out_SLL_NL(v, "chroma_qp_index_offset: ", pps.chroma_qp_index_offset);
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
    uint8_t field_pic_flag;
    uint8_t bottom_field_flag;
    uint32_t idr_pic_id;
    uint32_t pic_order_cnt_lsb;
    int32_t delta_pic_order_cnt_bottom;
    int32_t delta_pic_order_cnt[2];
    uint32_t redundant_pic_cnt;
    uint8_t direct_spatial_mv_pred_flag;
    uint8_t num_ref_idx_active_override_flag;
    uint32_t num_ref_idx_l0_active_minus1;
    uint32_t num_ref_idx_l1_active_minus1;

    // ref_pic_list_reordering    

    uint8_t ref_pic_list_reordering_flag_l0;
    uint8_t ref_pic_list_reordering_flag_l1;
    uint32_t reordering_of_pic_nums_idc;
    uint32_t abs_diff_pic_num_minus1;

    // pred_weight_table

    uint32_t luma_log2_weight_denom;
    uint32_t chroma_log2_weight_denom;
    uint8_t luma_weight_l0_flag;
    //int32_t luma_weight_l0[];
    //int32_t luma_offset_l0[];
    uint8_t chroma_weight_l0_flag;
    //int32_t chroma_weight_l0[][];
    //int32_t chroma_offset_l0[][];
    uint8_t luma_weight_l1_flag;
    //int32_t luma_weight_l1[];
    //int32_t luma_offset_l1[];
    uint8_t chroma_weight_l1_flag;
    //int32_t chroma_weight_l1[][];
    //int32_t chroma_offset_l1[][];

    // dec_ref_pic_marking

    uint8_t no_output_of_prior_pics_flag;
    uint8_t long_term_reference_flag;
    uint8_t adaptive_ref_pic_marking_mode_flag;
    uint32_t memory_management_control_operation;
    uint32_t difference_of_pic_nums_minus1;
    uint32_t long_term_pic_num;
    uint32_t long_term_frame_idx;
    uint32_t max_long_term_frame_idx_plus1;

    uint32_t cabac_init_idc;
    int32_t slice_qp_delta;
    uint8_t sp_for_switch_flag;
    int32_t slice_qs_delta;
    uint32_t disable_deblocking_filter_idc;
    int32_t slice_alpha_c0_offset_div2;
    int32_t slice_beta_offset_div2;
    uint32_t slice_group_change_cycle;
    uint32_t slice_id;
  } H264_SLICE;

  H264_SLICE slice = {0,};

  uint8_t nal_ref_idc = (b[3]&0x60)>>5;
  uint8_t nal_unit_type = b[3]&0x1F;

  bitdata data = {0,};
  data.data = (byte*)(b+4);
  data.data_len = remove_0x03(b+4, len-4);
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

  if (!decoder.sps.frame_mbs_only_flag) {
    read_bit(&data, &slice.field_pic_flag);
    if (slice.field_pic_flag) {
      read_bit(&data, &slice.bottom_field_flag);
    }
  }

  if (nal_unit_type == 5)
    read_exp_golomb(&data, &slice.idr_pic_id);

  if (decoder.sps.pic_order_cnt_type == 0) {
    read_bits(&data, decoder.sps.log2_max_pic_order_cnt_lsb_minus4 + 4, &slice.pic_order_cnt_lsb);
    if (decoder.pps.pic_order_present_flag && !slice.field_pic_flag) {
      read_signed_exp_golomb(&data, &slice.delta_pic_order_cnt_bottom);
    }
  }

  if (decoder.sps.pic_order_cnt_type == 1 
      && !decoder.sps.delta_pic_order_always_zero_flag) {
    read_signed_exp_golomb(&data, &slice.delta_pic_order_cnt[0]);
    if (decoder.pps.pic_order_present_flag && !slice.field_pic_flag) {
      read_signed_exp_golomb(&data, &slice.delta_pic_order_cnt[1]);
    }
  }

  if (decoder.pps.redundant_pic_cnt_present_flag)
    read_exp_golomb(&data, &slice.redundant_pic_cnt);

  if (IS_B_SLICE(slice.slice_type))
    read_bit(&data, &slice.direct_spatial_mv_pred_flag);

  if (IS_P_SLICE(slice.slice_type) 
      || IS_SP_SLICE(slice.slice_type) 
      || IS_B_SLICE(slice.slice_type) ) {
    read_bit(&data, &slice.num_ref_idx_active_override_flag);
    if (slice.num_ref_idx_active_override_flag) {
      read_exp_golomb(&data, &slice.num_ref_idx_l0_active_minus1);
      if (IS_B_SLICE(slice.slice_type))
        read_exp_golomb(&data, &slice.num_ref_idx_l1_active_minus1);
    }
  }

  // ref_pic_list_reordering

  if(slice.slice_type % 5 != 2 && slice.slice_type % 5 != 4) {
    read_bit(&data, &slice.ref_pic_list_reordering_flag_l0);
    if(slice.ref_pic_list_reordering_flag_l0) {
      do {
        read_exp_golomb(&data, &slice.reordering_of_pic_nums_idc);
        if (slice.reordering_of_pic_nums_idc == 0
            || slice.reordering_of_pic_nums_idc == 1)
          read_exp_golomb(&data, &slice.abs_diff_pic_num_minus1);
        else if (slice.reordering_of_pic_nums_idc == 2)
          read_exp_golomb(&data, &slice.long_term_pic_num);
      } while( slice.reordering_of_pic_nums_idc != 3 );
    }
  }

  if(slice.slice_type % 5 == 1) {
    read_bit(&data, &slice.ref_pic_list_reordering_flag_l1);
    if(slice.ref_pic_list_reordering_flag_l1) {
      do {
        read_exp_golomb(&data, &slice.reordering_of_pic_nums_idc);
        if (slice.reordering_of_pic_nums_idc == 0
            || slice.reordering_of_pic_nums_idc == 1)
          read_exp_golomb(&data, &slice.abs_diff_pic_num_minus1);
        else if (slice.reordering_of_pic_nums_idc == 2)
          read_exp_golomb(&data, &slice.long_term_pic_num);
      } while( slice.reordering_of_pic_nums_idc != 3 );
    }
  }


  // pred_weight_table

  uint32_t ChromaArrayType = 0;
  if (decoder.sps.separate_colour_plane_flag == 0)
    ChromaArrayType = decoder.sps.chroma_format_idc;

  if ( (decoder.pps.weighted_pred_flag && (IS_P_SLICE(slice.slice_type) || IS_SP_SLICE(slice.slice_type))) 
      || (decoder.pps.weighted_bipred_idc == 1 && IS_B_SLICE(slice.slice_type)) ) {
    int32_t i,j;

    int32_t luma_weight_l0;
    int32_t luma_offset_l0;
    int32_t chroma_weight_l0;
    int32_t chroma_offset_l0;
    int32_t luma_weight_l1;
    int32_t luma_offset_l1;
    int32_t chroma_weight_l1;
    int32_t chroma_offset_l1;

    read_exp_golomb(&data, &slice.luma_log2_weight_denom);

    if (ChromaArrayType != 0)
      read_exp_golomb(&data, &slice.chroma_log2_weight_denom);

    for ( i = 0; i <= slice.num_ref_idx_l0_active_minus1; i++ ) {
      read_bit(&data, &slice.luma_weight_l0_flag);
      if (slice.luma_weight_l0_flag ) {
        read_signed_exp_golomb(&data, &luma_weight_l0);
        read_signed_exp_golomb(&data, &luma_offset_l0);
      }
      if ( ChromaArrayType != 0 ) {
        read_bit(&data, &slice.chroma_weight_l0_flag);
        if (slice.chroma_weight_l0_flag) {
          for (j = 0; j < 2; j++) {
            read_signed_exp_golomb(&data, &chroma_weight_l0);
            read_signed_exp_golomb(&data, &chroma_offset_l0);
          }
        }
      }
    }

    if (slice.slice_type % 5 == 1) {
      for( i = 0; i <= slice.num_ref_idx_l1_active_minus1; i++ ) {
        read_bit(&data, &slice.luma_weight_l1_flag);
        if (slice.luma_weight_l1_flag ) { 
          read_signed_exp_golomb(&data, &luma_weight_l1);
          read_signed_exp_golomb(&data, &luma_offset_l1);
        } 
        if ( ChromaArrayType != 0 ) { 
          read_bit(&data, &slice.chroma_weight_l1_flag);
          if (slice.chroma_weight_l1_flag) { 
            for (j = 0; j < 2; j++) { 
              read_signed_exp_golomb(&data, &chroma_weight_l1);
              read_signed_exp_golomb(&data, &chroma_offset_l1);
            } 
          } 
        }
      }
    }

  }

  // dec_ref_pic_marking

  if (nal_ref_idc != 0) {
    if (nal_unit_type == 5) { // IDR
      read_bit(&data, &slice.no_output_of_prior_pics_flag);
      read_bit(&data, &slice.long_term_reference_flag);
    }
    else {
      read_bit(&data, &slice.adaptive_ref_pic_marking_mode_flag);
      if (slice.adaptive_ref_pic_marking_mode_flag) {
        do {
          read_exp_golomb(&data, &slice.memory_management_control_operation);
          if(slice.memory_management_control_operation == 1 || 
            slice.memory_management_control_operation == 3) {
            read_exp_golomb(&data, &slice.difference_of_pic_nums_minus1);
          } 
          if(slice.memory_management_control_operation == 2) {
            read_exp_golomb(&data, &slice.long_term_pic_num);
          }
          if (slice.memory_management_control_operation == 3
              || slice.memory_management_control_operation == 6 ) {
            read_exp_golomb(&data, &slice.long_term_frame_idx);
          }
          if ( slice.memory_management_control_operation == 4 ) {
            read_exp_golomb(&data, &slice.max_long_term_frame_idx_plus1);
          }
        } while (slice.memory_management_control_operation != 0);
      }
    }
  }

  if (decoder.pps.entropy_coding_mode_flag 
      && !IS_I_SLICE(slice.slice_type) 
      && !IS_SI_SLICE(slice.slice_type)) {
    read_exp_golomb(&data, &slice.cabac_init_idc);
  }

  read_signed_exp_golomb(&data, &slice.slice_qp_delta);

  if (IS_SP_SLICE(slice.slice_type) || IS_SI_SLICE(slice.slice_type)) {
    if(IS_SP_SLICE(slice.slice_type)) {
      read_bit(&data, &slice.sp_for_switch_flag);
    }
    read_signed_exp_golomb(&data, &slice.slice_qs_delta);
  }

  if (decoder.pps.deblocking_filter_control_present_flag) {
    read_exp_golomb(&data, &slice.disable_deblocking_filter_idc);
    if (slice.disable_deblocking_filter_idc != 1) {
      read_signed_exp_golomb(&data, &slice.slice_alpha_c0_offset_div2);
      read_signed_exp_golomb(&data, &slice.slice_beta_offset_div2);
    }
  }

  if (decoder.pps.num_slice_groups_minus1 > 0
      && decoder.pps.slice_group_map_type >= 3 
      && decoder.pps.slice_group_map_type <= 5) {

    uint32_t PicWidthInMbs = decoder.sps.pic_width_in_mbs_minus1 + 1;
    uint32_t PicHeightInMapUnits = decoder.sps.pic_height_in_map_units_minus1 + 1;
    uint32_t PicSizeInMapUnits = PicWidthInMbs * PicHeightInMapUnits;
    uint32_t SliceGroupChangeRate = decoder.pps.slice_group_change_rate_minus1 + 1;

    uint32_t len = log2( PicSizeInMapUnits / SliceGroupChangeRate + 1 );
   
    read_bits(&data, len, &slice.slice_group_change_cycle);

  }

  read_exp_golomb(&data, &slice.slice_id);



  out_SB_NL(v, "first_mb_in_slice: ", slice.first_mb_in_slice);
  out_S2B_NL(v, "slice_type: ", slice.slice_type, dvbstrPESH264_Slice_ID(slice.slice_type));
  out_SB_NL(v, "pic_parameter_set_id: ", slice.pic_parameter_set_id);
  if (decoder.sps.separate_colour_plane_flag == 1) {
    out_SB_NL(v, "colour_plane_id: ", slice.colour_plane_id);
  }
  out_SB_NL(v, "frame_num: ", slice.frame_num);


  if (!decoder.sps.frame_mbs_only_flag) {
    out_SB_NL(v, "field_pic_flag: ", slice.field_pic_flag);
    if (slice.field_pic_flag) {
      out_SB_NL(v, "bottom_field_flag: ", slice.bottom_field_flag);
    }
  }

  if (nal_unit_type == 5)
    out_SB_NL(v, "idr_pic_id: ", slice.idr_pic_id);

  if (decoder.sps.pic_order_cnt_type == 0) {
    out_SB_NL(v, "pic_order_cnt_lsb: ", slice.pic_order_cnt_lsb);
    if (decoder.pps.pic_order_present_flag && !slice.field_pic_flag) {
      out_SB_NL(v, "delta_pic_order_cnt_bottom: ", slice.delta_pic_order_cnt_bottom);
    }
  }

  if (decoder.sps.pic_order_cnt_type == 1
      && !decoder.sps.delta_pic_order_always_zero_flag) {
    out_SB_NL(v, "delta_pic_order_cnt[0]: ", slice.delta_pic_order_cnt[0]);
    if (decoder.pps.pic_order_present_flag && !slice.field_pic_flag) {
      out_SB_NL(v, "delta_pic_order_cnt[1]: ", slice.delta_pic_order_cnt[1]);
    }
  }

  if (decoder.pps.redundant_pic_cnt_present_flag)
    out_SB_NL(v, "redundant_pic_cnt: ", slice.redundant_pic_cnt);

  if (IS_B_SLICE(slice.slice_type))
    out_SB_NL(v, "direct_spatial_mv_pred_flag: ", slice.direct_spatial_mv_pred_flag);

  if (IS_P_SLICE(slice.slice_type)
      || IS_SP_SLICE(slice.slice_type)
      || IS_B_SLICE(slice.slice_type) ) {
    out_SB_NL(v, "num_ref_idx_active_override_flag: ", slice.num_ref_idx_active_override_flag);
    if (slice.num_ref_idx_active_override_flag) {
      out_SB_NL(v, "num_ref_idx_l0_active_minus1: ", slice.num_ref_idx_l0_active_minus1);
      if (IS_B_SLICE(slice.slice_type))
        out_SB_NL(v, "num_ref_idx_l1_active_minus1: ", slice.num_ref_idx_l1_active_minus1);
    }
  }

  // ref_pic_list_reordering

  if( (slice.slice_type % 5) != 2 && (slice.slice_type % 5) != 4 ) {
    out_SB_NL(v, "ref_pic_list_reordering_flag_l0: ", slice.ref_pic_list_reordering_flag_l0);
  }

  if( (slice.slice_type % 5) == 1 ) {
    out_SB_NL(v, "ref_pic_list_reordering_flag_l1: ", slice.ref_pic_list_reordering_flag_l1);
  }

  // pred_weight_table

  if ( (decoder.pps.weighted_pred_flag && (IS_P_SLICE(slice.slice_type) || IS_SP_SLICE(slice.slice_type)))
      || (decoder.pps.weighted_bipred_idc == 1 && IS_B_SLICE(slice.slice_type)) ) {
     out_SB_NL(v, "luma_log2_weight_denom: ", slice.luma_log2_weight_denom);
     if( ChromaArrayType != 0 )
       out_SB_NL(v, "chroma_log2_weight_denom: ", slice.chroma_log2_weight_denom);
  }

  // dec_ref_pic_marking

  if ( nal_ref_idc != 0 ) {
    if (nal_unit_type == 5) { // IDR
      out_SB_NL(v, "no_output_of_prior_pics_flag: ", slice.no_output_of_prior_pics_flag);
      out_SB_NL(v, "long_term_reference_flag: ", slice.long_term_reference_flag);
    }
    else {
      out_SB_NL(v, "adaptive_ref_pic_marking_mode_flag: ", slice.adaptive_ref_pic_marking_mode_flag);
      if (slice.adaptive_ref_pic_marking_mode_flag) {
        out_SB_NL(v, "memory_management_control_operation: ", slice.memory_management_control_operation);
        if(slice.memory_management_control_operation == 1 ||
          slice.memory_management_control_operation == 3) {
          out_SB_NL(v, "difference_of_pic_nums_minus1: ", slice.difference_of_pic_nums_minus1);
        }
        if(slice.memory_management_control_operation == 2) {
          out_SB_NL(v, "long_term_pic_num: ", slice.long_term_pic_num);
        }
        if (slice.memory_management_control_operation == 3
            || slice.memory_management_control_operation == 6 ) {
          out_SB_NL(v, "long_term_frame_idx: ", slice.long_term_frame_idx);
        }
        if ( slice.memory_management_control_operation == 4 ) {
          out_SB_NL(v, "max_long_term_frame_idx_plus1: ", slice.max_long_term_frame_idx_plus1);
        }
      }
    }
  }


  if (decoder.pps.entropy_coding_mode_flag
      && !IS_I_SLICE(slice.slice_type)
      && !IS_SI_SLICE(slice.slice_type)) {
    out_SB_NL(v, "cabac_init_idc: ", slice.cabac_init_idc);
  }

  out_SLL_NL(v, "slice_qp_delta: ", slice.slice_qp_delta);

  if (IS_SP_SLICE(slice.slice_type) || IS_SI_SLICE(slice.slice_type)) {
    if(IS_SP_SLICE(slice.slice_type)) {
      out_SB_NL(v, "sp_for_switch_flag: ", slice.sp_for_switch_flag);
    }
    out_SLL_NL(v, "slice_qs_delta: ", slice.slice_qs_delta);
  }

  if (decoder.pps.deblocking_filter_control_present_flag) {
    out_SB_NL(v, "disable_deblocking_filter_idc: ", slice.disable_deblocking_filter_idc);
    if (slice.disable_deblocking_filter_idc != 1) {
      out_SLL_NL(v, "slice_alpha_c0_offset_div2: ", slice.slice_alpha_c0_offset_div2);
      out_SLL_NL(v, "slice_beta_offset_div2: ", slice.slice_beta_offset_div2);
    }
  }

  if (decoder.pps.num_slice_groups_minus1 > 0
      && decoder.pps.slice_group_map_type >= 3
      && decoder.pps.slice_group_map_type <= 5) {
    out_SB_NL(v, "slice_group_change_cycle: ", slice.slice_group_change_cycle);
  }


  out_SB_NL(v, "slice_id: ", slice.slice_id);

}
