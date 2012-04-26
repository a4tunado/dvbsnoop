/*
$Id: mpeg2_video.h,v 1.3 2005/12/27 23:30:29 rasc Exp $

   
 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)



*/

#ifndef __MPEG2_VIDEO__
#define __MPEG2_VIDEO__


void MPEG2_decodeSequenceEnd (int v, u_char *b, int len);
void MPEG2_decodeUserData (int v, u_char *b, int len);
void MPEG2_decodeGroupOfPictures (int v, u_char *b, int len);
void MPEG2_decodeSequenceHeader (int v, u_char *b, int len);
void MPEG2_decodePictureHeader (int v, u_char *b, int len);

void MPEG2_decodeExtension (int v, u_char *b, int len);
void MPEG2_decodeSequenceExtension (int v, u_char *b, int len);
void MPEG2_decodeSequenceDisplayExtension (int v, u_char *b, int len);
void MPEG2_decodeSequenceScalableExtension (int v, u_char *b, int len);
void MPEG2_decodePictureCodingExtension (int v, u_char *b, int len);
void MPEG2_decodeQuantMatrixExtension (int v, u_char *b, int len);
void MPEG2_decodePictureDisplayExtension (int v, u_char *b, int len);
void MPEG2_decodePictureTemporalScalableExtension (int v, u_char *b, int len);
void MPEG2_decodePictureSpatialScalableExtension (int v, u_char *b, int len);
void MPEG2_decodeCopyrightExtension (int v, u_char *b, int len);

void MPEG2_decodeSlice (int v, u_char *b, int len);


#endif

