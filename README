
dvbsnoop   - an open source DVB/MPEG stream analyzer
====================================================


http://dvbsnoop.sourceforge.net/
http://cvs.tuxbox.org/



dvbsnoop is a DVB/MPEG stream analyzer program.
The program can be used to sniff, monitor, debug, dump
or view DVB/MPEG/DSM-CC/MHP stream information (digital
television or data broadcasts) sent via satellite, cable
or terrestrial.

The program was mainly written to learn and understand the DVB 
protocol structures and streams. dvbsnoop is currently part of
the tuxbox project, bringing Linux based TV software to some
set top boxes (digital satellite/cable receivers).


Documentation and example outputs can be found at:

	http://dvbsnoop.sourceforge.net



Disclaimer:
===========
  You are using this program at your own risk!
  This program may not be used to hack pay tv or encrypted dvb services
  in any way.



License: 
========

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA




Basic requirements:
===================

  - a DVB card (not needed for offline decoding of recorded files)
  - Linux DVB API version 1 or 3 installed (see www.linuxtv.org)
 or
  - a Linux based set top box (using DVB API version 1 or 3)
    (e.g. 'dbox2' or 'dreambox')



Installation:
=============
  - install the DVB API driver from http://www.linuxtv.org
    (linux kernel 2.6.x and above are already providing the DVB API)

  - Prerequistes of other software:
    To compile dvbsnoop you may need:
     - autoconf >= 2.57a
     - automake >= 1.8
     - libtool >= 1.4.2
     - make >= 3.79
     - tar
     - bunzip2 (bzip2)
     - gunzip (gzip)
     - gcc 2.95 or >= 3.0


  - download the latest source from http://dvbsnoop.sourceforge.net
    (download a tarball or checkout from cvs)

  - unzip and untar the archive (if needed)
      gzip -d  dvbsnoop-<version>.tar.gz
     or
      bzip2 -d  dvbsnoop-<version>.tar.bz2

      tar xvf  dvbsnoop-<version>.tar
      cd dvbsnoop-<version>

  - configure the source
      ./autogen.sh	# e.g. on "dbox2" cdk, use if needed
      ./configure
    
    or you may specify a path to DVB API include files
      ./configure CPPFLAGS=-I/path/to/dvb-kernel/linux/include

  - compile 
      make
      make install

  - test
      dvbsnoop -help

  - PROBLEMS compiling dvbsnoop?
      dvbsnoop should compile smoothly on any ANSI-C-Compiler. But it was
      tested on GCC (gcc-3.x) only.
      If you see any problems during 'autoconf.sh' or 'configure' execution,
      please check if you have the latest versions of 'autoconf' and 'configure'
      installed. In cases, please update your system (check packages 
      automake, autoconf and libtool). Please see also mini FAQ at the end
      of this file.

  - Special Platforms
      Cygwin:
          dvbsnoop may be used on Microsoft Windows Platforms using cygwin
	  (http://www.cygwin.com).  Due to a missing dvb hardware layer you may
	  use dvbsnoop in offline mode only.  To compile dvbsnoop for cygwin,
	  please read annex "cygwin".


Posting dvbsnoop output:
========================
  If you are posting dvbsnoop output to mailing lists, newsgroups, public boards
  or whatever, please always include the dvbsnoop header:

   e.g.: " dvbsnoop V1.2.49 -- http://dvbsnoop.sourceforge.net/" 

   The version information is helpful if there are discussions about the
   decoding output.



Using source code snippets or dvbsnoop knowledge for your own purpose:
======================================================================
  Feel free to use dvbsnoop source for your own programs as knowledge 
  or code base.  In any cases, please include a link or reference to
  dvbsnoop in your program or documentation... Thanks.



Bugs, requests:
===============
  Well, if you find some bugs, please let me know.
  (check first, if the data stream is not broken).

  Reoport bugs to: http://sourceforge.net/tracker/?group_id=85040

  Please do not send binary data stream files or large 
  decoding output via email! (If needed, I will ask for it!)
  But it is a good advise to save the data stream using
  the option "dvbsnoop -s ... -b ... > file" on your harddrive.
  It might be helpful for further investigations.

  To prevent spam-filtering please preceed your mail subject
  with "dvbsnoop: "  (e.g. mail topic: "dvbsnoop: bugreport xyz")



Keywords:
=========
    DVB stream analyzer mpeg stream analyzer, TS stream analyzer, MPEG,
    MPG, descriptor, digital television, satellite TV, cable TV, DVB-C,
    DVB-S, DVB-T, MHP, DSM-CC, SI, PES, TOT, PAT, PMT, SDT, EIT, NIT,
    TDST, RST, SIT, DIT, BAT, EMM, ECM, PSI, SI tables, SSU, INT, UNT, datagram,
    sections, transport stream analyzer, packetized elementary stream, demux,
    ISO/IEC 13818-1, ISO/IEC 13818-6, ETSI EN 300468, ETSI EN 301162,
    ETSI TS 102006, ETSI EN 301192, ETSI TR 101202, ITU H.222.0,
    data carousel, object carousel, dvb snoop, TV ANYTIME


   


(c) 2001-2007   Rainer Scherg (Rainer.Scherg@gmx.de)
http://dvbsnoop.sourceforge.net







Annex
=====

Install on Cygwin
=================

dvbsnoop <= version 1.4.0:
==========================

To make dvbsnoop run on cygwin platforms, you have to:

1.) copy dvb-api include files to your cygwin installation.
2.) tweak some cygwin header files.

Tnx to Kamal for this description:


-----Original Message-----
From: Kamalanand [mailto:kamal_dasu@xxxxxxxxxx] 
Subject: RE: dvbsnoop as analyzer on Windows - worked

Rainer,

I had to apply a few fixes in my environment to make dvbsnoop build with
cygwin. This might be very specific to my environment, however wanted to
share this with you if others face a similar problem.

I am using the following cygwin version downloaded using setup.exe on 
http://wwww.cygwin.com :
CYGWIN_NT-5.1 my-pc 1.5.18(0.132/4/2) 2005-07-02 20:30 i686 unknown unknown
Cygwin

I have the following installed in the cygwin environment
1) Dvbsnoop http://dvbsnoop.sourceforge.net/ under ~/dvbsnoop-1.4.00/ 
2) Downloaded the linux kernel 2.6.12 sources from http://www.kernel.org/ ,
extracted to /linux-2.6

These are the things I did to have a successful build,

1) Copied the dvb includes from the /linux-2.6/include/linux/dvb under
/usr/include/linux/dvb
(Actaully I made a symbolic link but its upto you.)

2) The cygwin installation had the __u64 type missing in the
/usr/include/asm/types.h , 
So added that to /usr/include/asm/types.h. This is needed by the struct
dmx_stc in /usr/include/lnux/dvb/dmx.h
..
typedef __signed__ int __s64;
typedef unsigned int __u64;
..

3) Then noticed the dmx_pes.c includes file_io.h which includes the
sys/ioctl.h. I 
figured that the IOCTL macros are needed to compile 
~/dvbsnoop-1.4.0.0/src/dvb_api/dmx_pes.c file. The IOCTL macros are used in
the /usr/include/linux/dvb/dmx.h which get called in the dmx_pes.c. Now
cygwin /usr/include/sys/ioctl.h does not have the macros in it and
/usr/include/asm/ioctl.h is missing in the cygwin environment for some
reason. 
Anyway I copied the /include/linux/asm-i386/ioctl.h from linux kernel
sources to the /usr/include/asm/ioctl.h . Then added the following to the
/usr/include/sys/ioctl.h

#include <asm/ioctl.h>

4) However the ~/dvbsnoop-1.4.0.0/src/misc/packet_mem.c refused to compile
due to various type incopatabilities with strings.h and stdlib.h under
cygwin. Basically it needed the definitions for u_char and u_long. So I
tried the following to fix the problem :

/* #include <string.h>  */
/* #include <stdlib.h>   */
#include <sys/types.h>

Maybe there is a better way to do this, for now this seemed to work for me

5) Ran the following 
    ~/dvbsnoop-1.4.0.0/configure script 
    ~/dvbsnoop-1.4.0.0/make clean
    ~/dvbsnoop-1.4.0.0/make 
    ~/dvbsnoop-1.4.0.0/make install
 

Now I am able to do offline analysis and decode the MPEG streams. 

Thanks & Regards
Kamal



dvbsnoop > version 1.4.0:
==========================

To make dvbsnoop run on cygwin platforms, you have to:

1.) copy dvb-api include files to your cygwin installation.

2.) maybe: you have tweak some cygwin header files.

3.) see src/dvb_api/dvb_api.h: uncomment the IOCTL, etc. #defines
    (please read remark in header file)

4.) Next: go on with standard procedure...:
      ./configure
      make 
      etc.
    
      if you encounter some problems, try  "make distclean"
      prior to autogen.sh




Problems compiling dvbsnoop?
============================

Mini-FAQ from the tuxbox project (linux@dbox2):


Q: Why is there no configure script?
A: "autoconf" creates configure from "configure.ac". You can call
   "./autogen.sh", which will call "autoconf" for you.

Q: Why is there no "Makefile", neither in the root
   directory nor in any subdirectory?
A: "configure" creates "Makefile" from "Makefile.in". "./configure --help"
   usually shows the available options.

Q: Why is there no "Makefile.in"?
A: "automake" creates "Makefile.in" from "Makefile.am". You can call
   "./autogen.sh", which will call "automake" for you. If you call
   "automake" manually, then make sure your working directory contains
   "configure.ac".


