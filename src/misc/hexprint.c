/*
$Id: hexprint.c,v 1.9 2006/01/02 18:24:04 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)




$Log: hexprint.c,v $
Revision 1.9  2006/01/02 18:24:04  rasc
just update copyright and prepare for a new public tar ball

Revision 1.8  2005/09/12 20:56:16  rasc
Make dvbsnoop compile on Cygwin / Windows

Revision 1.7  2004/03/09 20:59:23  rasc
VPS decoding (someone check the NPP & PTY code output please...)

Revision 1.6  2004/02/20 22:18:40  rasc
DII complete (hopefully)
BIOP::ModuleInfo  (damned, who is spreading infos over several standards???)
maybe someone give me a hint on the selector_byte info!!!
some minor changes...

Revision 1.5  2004/01/01 20:09:26  rasc
DSM-CC INT/UNT descriptors
PES-sync changed, TS sync changed,
descriptor scope
other changes

Revision 1.4  2003/12/17 23:57:29  rasc
add. hexdump mode, different layout for some purpose
option:  -ph 4

Revision 1.3  2003/11/26 16:27:46  rasc
- mpeg4 descriptors
- simplified bit decoding and output function

Revision 1.2  2001/10/06 18:19:18  Toerli
Steuerzeichen entfernt. rasc wuerdest du mal bitte nen gescheiten unix-konformen Editor verwenden... windows editoren sind ungeeignet

Revision 1.1  2001/09/30 13:05:20  rasc
dvbsnoop v0.7  -- Commit to CVS


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#include "dvbsnoop.h"
#include "hexprint.h"
#include "output.h"



/*
 -- global static data

*/


int HexPrintmode = 0;



static void printhexdump_buf (int verbose, u_char *buf, int len);
static void printhexdump2_buf (int verbose, u_char *buf, int len);





/*
   -- print-modus setzen
*/

void setHexPrintMode (int i)

{
  HexPrintmode = i;
}






/*
  - print buffer as Hex Printout
*/

void printhex_buf (int verbose, u_char *buf, int n)

{

   switch (HexPrintmode) {

      case 0:
	return;
	break;

      case 1:
	printhexdump_buf (verbose,buf,n);
	break;

      case 2:
	printhexline_buf (verbose,buf,n);
	break;

      case 3:
	printasciiline_buf (verbose,buf,n);
	break;

      case 4:
	printhexdump2_buf (verbose,buf,n);
	break;


      default:
	printhexdump_buf (verbose,buf,n);
	break;
   }

   return;
}




/*
 -- multi line dump HEX+ASCII
  0000:  42 f1 59 04 41 f1 00 00 00 01 ff 2e e3 ff 80 1f 
  0000:   B  .  Y  .  A  .  .  .  .  .  .  .  .  .  .  . 

*/
static void printhexdump_buf (int verbose, u_char *buf, int n)
{
 int i, j;
 u_char c;
 int WID=16;

j = 0;
while (j*WID < n) {

 out (verbose,"  %04x:  ",j*WID);
 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose,"%02x ",(int)c);
 }
 out_NL (verbose);

 out (verbose,"  %04x:  ",j*WID);
 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose," %c ",isprint((int)c) ?c:'.');
 }
 out_NL (verbose);
 
 j++;

}


}




/*
 -- single line dump HEX
   42 f1 59 04 41 f1 00 00 00 01 ff 2e e3 ff 80 1f 4
*/
void printhexline_buf (int verbose, u_char *buf, int n)
{
 int i;

 for (i=0; i<n; i++) {
   out (verbose,"%02x ",(int)buf[i]);
 }
 out_NL (verbose);
}




/*
 -- single line ascii
    B.Y.A...........H...RTL World...RTL. Television.
*/
void printasciiline_buf (int verbose, u_char *buf, int n)
{
 int    i;
 u_char c;

 for (i=0; i<n; i++) {
   c = buf[i];
   out (verbose,"%c",isprint((int)c) ?c:'.');
 }
 out_NL (verbose);
}



/*
 -- single line dump HEX+ASCII
*/
static void printhexdump2_buf (int verbose, u_char *buf, int n)
{
 int    i, j;
 int    k;
 u_char c;
 int    WID=16;

j = 0;
while (j*WID < n) {

 out (verbose,"  %04x:  ",j*WID);

 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose,"%02x ",(int)c);
   if ((i+1)%8 == 0) out (verbose," ");
 }

 for (k=i; k<WID; k++) {
   out (verbose, "   ");   // filler
   if ((k+1)%8 == 0) out (verbose," ");
 }

 out (verbose," ");

 for (i=0; i<WID; i++) {
   if ( (i+j*WID) >= n) break;
   c = buf[i+j*WID];
   out (verbose,"%c",isprint((int)c) ?c:'.');
 }
 out_NL (verbose);

 
 j++;

}


}




