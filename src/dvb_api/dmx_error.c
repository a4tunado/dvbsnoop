/*
$Id: dmx_error.c,v 1.3 2005/12/27 23:30:27 rasc Exp $


 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


 -- simple error output for DMX & file I/O




$Log: dmx_error.c,v $
Revision 1.3  2005/12/27 23:30:27  rasc
PS MPEG-2 Extension data packets, MPEG-2 decoding

Revision 1.2  2004/01/25 22:36:52  rasc
minor changes & enhancments

Revision 1.1  2004/01/02 00:00:37  rasc
error output for buffer overflow



*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



int  IO_error (char *str)
{
   char *s;
   int  err;
  

   s = (str) ? str : "";
   err = errno;

   switch (err) {

	case EOVERFLOW:
		fprintf (stderr,
			"Error(%d): %s: Buffer overflow, stream bandwidth to high\n",
			err,s);
		break;

	default:
		fprintf (stderr,"Error(%d): ",err);
		perror(s);
		break;

   }

   return err;

}


