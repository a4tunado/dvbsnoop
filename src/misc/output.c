/*
$Id: output.c,v 1.11 2006/01/02 18:24:04 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


 --  Output Module




$Log: output.c,v $
Revision 1.11  2006/01/02 18:24:04  rasc
just update copyright and prepare for a new public tar ball

Revision 1.10  2005/09/12 20:56:16  rasc
Make dvbsnoop compile on Cygwin / Windows

Revision 1.9  2005/09/02 14:11:35  rasc
TS code redesign, xPCR and DTS timestamps decoding

Revision 1.8  2004/02/02 23:34:07  rasc
- output indent changed to avoid \r  (which sucks on logged output)
- EBU PES data started (teletext, vps, wss, ...)
- bugfix: PES synch. data stream
- some other stuff

Revision 1.7  2004/01/02 16:40:37  rasc
DSM-CC  INT/UNT descriptors complete
minor changes and fixes

Revision 1.6  2004/01/01 20:09:26  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.5  2003/11/26 23:54:48  rasc
-- bugfixes on Linkage descriptor

Revision 1.4  2003/11/26 16:27:46  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.3  2003/07/08 19:59:50  rasc
restructuring... some new, some fixes,
trying to include DSM-CC, Well someone a ISO13818-6 and latest version of ISO 18313-1 to spare?


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>


#include "dvbsnoop.h"
#include "output.h"


/*
  -- Module Global Vars
*/

static int  verbose_level = 0;
static int  col0 = 0;		//2

static int  indent_level = 0;
int   table_indent [] = {0,4,8,12,15,18,21,24,27,30};

#define MAX_INDENT_LEVEL  ( (sizeof(table_indent)/sizeof(int)) - 1)






/*
   -- set indent-level
   -- and sends a '\r' to reset indent prints
   - +1 = indent plus one level
   - -1 = unindent one level
   -  0 = reset to Level 0 
*/

void indent (int v)

{
  if (v == 0) indent_level  = 0;
  else        indent_level += v;

  if (indent_level < 0)
     indent_level = 0;
  if (indent_level >= MAX_INDENT_LEVEL)
     indent_level = MAX_INDENT_LEVEL;

//2  fputc ('\r',stdout);
//2  print_indent();
//    out_nl2 (0);
}



/*
 -- set verbosity level
 -- 0 = highest, 9 = lowest level
 -- print message upto (including) this verbosity level
*/

void setVerboseLevel (int v)
{
  verbose_level = v;
}

int getVerboseLevel ()
{
 return verbose_level;
}




/*
  -- output special printf
  -- out_nl will append \n at the end of the output
*/

void out(int verbose, const char *msgfmt,...)
{
  va_list args;

  if (verbose <= verbose_level) {
     print_indent(); //2
     va_start (args,msgfmt);
     vfprintf (stdout, msgfmt, args);
     va_end   (args);
  }
}


void out_nl(int verbose, const char *msgfmt,...)
{
  va_list args;

  if (verbose <= verbose_level) {
     print_indent();  //2
     va_start (args,msgfmt);
     vfprintf (stdout, msgfmt, args);
     va_end   (args);

     out_nl2(verbose);
  }
}


/*
  -- just print a NL
*/

void  out_nl2 (int verbose)
{
  if (verbose <= verbose_level) {
     fputc ('\n',stdout);
     col0 = 1; //2
//2     print_indent();
  }

}


void print_indent (void)

{
 int i;

 if (! col0)  return; //2

 for (i=0; i<table_indent[indent_level]; i++) {
   fputc (' ',stdout);
 }

 col0 = 0; //2
}



