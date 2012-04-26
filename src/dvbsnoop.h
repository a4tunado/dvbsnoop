/*
$Id: dvbsnoop.h,v 1.24 2005/09/09 14:20:29 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2005   Rainer.Scherg@gmx.de








$Log: dvbsnoop.h,v $
Revision 1.24  2005/09/09 14:20:29  rasc
TS continuity sequence check (cc verbose output)

Revision 1.23  2005/01/17 19:41:21  rasc
Bugfix: data broadcast descriptor (tnx to Sergio SAGLIOCCO, SecureLAB)

Revision 1.22  2004/11/16 23:02:50  rasc
cmd option "-tsraw" for full/raw TS read (if supported by hard-/firmware)

Revision 1.21  2004/11/16 09:12:41  obi
increased MAX_PID from 0x1fff to 0x2000 (which means "full transport stream" in linux dvb api terms)

Revision 1.20  2004/07/24 11:44:44  rasc
EN 301 192 update
 - New: ECM_repetition_rate_descriptor (EN 301 192 v1.4.1)
 - New: time_slice_fec_identifier_descriptor (EN 301 192 v1.4.1)
 - New: Section MPE_FEC  EN 301 192 v1.4
 - Bugfixes

Revision 1.19  2004/03/31 21:14:22  rasc
New: Spider section pids  (snoop referenced section pids),
some minor changes

Revision 1.18  2004/01/01 20:09:15  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.17  2003/12/15 20:09:48  rasc
no message

Revision 1.16  2003/12/03 20:06:33  obi
- reduced auto* to minimal required checks, obsoletes acinclude.m4
- added version number to configure.ac, removed it from version.h
  (needed for "make dist" anyway)
- removed autoheader dependency

Revision 1.15  2003/11/26 19:55:31  rasc
no message

Revision 1.14  2003/11/07 16:33:31  rasc
no message

Revision 1.13  2003/11/01 17:05:46  rasc
no message

Revision 1.12  2003/10/24 22:17:13  rasc
code reorg...

Revision 1.11  2003/10/17 19:14:40  rasc
no message

Revision 1.10  2003/10/16 19:02:29  rasc
some updates to dvbsnoop...
- small bugfixes
- tables updates from ETR 162

Revision 1.9  2003/10/13 23:35:35  rasc
Bugfix, verbose < 4 segfaulted, tnx to 'mws'  for reporting.

Revision 1.8  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?

Revision 1.7  2003/07/06 05:28:52  obi
compatibility stuff.. now there is only one version for old and new drivers
which selects the api at configure time

Revision 1.6  2003/06/24 23:51:03  rasc
bugfixes and enhancements

Revision 1.5  2002/11/01 20:38:40  Jolt
Changes for the new API

Revision 1.4  2002/09/13 23:57:04  obi
define NEWSTRUCT to work with current linuxtv cvs

Revision 1.3  2002/08/27 19:00:45  obi
use devfs device names

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/

#ifndef __DVBSNOOP_H
#define __DVBSNOOP_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "version.h"
#include "misc/helper.h"
#include "misc/output.h"



//
// -- some DVB definitions
//

#define MAX_PID      0x1FFF
#define PID_FULL_TS  0x2000	/* special PID for reading full/raw TS */
				/* THIS is defined by Linux DVB-API !! */

#define DUMMY_PID    0xFFFF	/* special if no pid is needed */
#define INVALID_PID  0xFEFE	/* a invalid PID*/




//
// -- BSD style type shortcuts...
// -- may be already defined by system (typedef in linux/types.h)
// -- so we overwrite this via #define to avoid compiler warnings
//

#define u_char  unsigned char
#define u_int   unsigned int
#define u_long  unsigned long


#endif


