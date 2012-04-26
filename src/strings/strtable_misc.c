/*
$Id: strtable_misc.c,v 1.3 2006/01/15 17:50:31 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de


 -- String table misc.



$Log: strtable_misc.c,v $
Revision 1.3  2006/01/15 17:50:31  rasc
no message

Revision 1.2  2006/01/02 18:24:32  rasc
just update copyright and prepare for a new public tar ball

Revision 1.1  2004/07/24 11:47:08  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes


*/


#include "strtable_misc.h"




/*
  -- match id in range from STR_TABLE
*/

char *findTableID (STR_TABLE *t, u_int id)

{

  while (t->str) {
    if (t->from <= id && t->to >= id)
       return (char *) t->str;
    t++;
  }

  return (char *) ">>ERROR: not (yet) defined... Report!<<";
}





