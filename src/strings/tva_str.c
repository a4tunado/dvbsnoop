/*
$Id: tva_str.c,v 1.2 2006/01/02 18:24:32 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- TV-ANYTIME -Strings



$Log: tva_str.c,v $
Revision 1.2  2006/01/02 18:24:32  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/08/06 22:21:38  rasc
New: TV-Anytime (TS 102 323) RNT descriptors 0x40 - 0x42



*/



#include "dvbsnoop.h"
#include "tva_str.h"
#include "strtable_misc.h"






/*
  -- TVA   RNT Descriptors
 */

char *tvaStrTVA_DescriptorTAG (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x40, 0x40,  "RAR_over_DVB_stream_descriptor" },
     {  0x41, 0x41,  "RAR_over_IP_descriptor" },
     {  0x42, 0x42,  "RNT_scan_descriptor" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}


/*
  -- TVA   RNT scheduling flag
 */

char *tvastr_CRI_DATA_scheduled_flag (u_int i)
{
  STR_TABLE  Table[] = {
     {  0x00, 0x00,  "referenced CRI data is delivered continuously" },
     {  0x01, 0x01,  "referenced CRI data is scheduled" },
     {  0,0, NULL }
  };

  return findTableID (Table, i);
}




