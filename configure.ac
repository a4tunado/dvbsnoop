AC_INIT([dvbsnoop],[1.4.50],[rasc@users.sourceforge.net])
AM_INIT_AUTOMAKE([dist-bzip2 no-define])

AC_PROG_CC
AC_PROG_RANLIB

AC_CHECK_HEADER([linux/dvb/dmx.h])
AC_CHECK_HEADER([ost/dmx.h])

if test "$ac_cv_header_ost_dmx_h" = yes; then
	AC_DEFINE([HAVE_OST_DMX_H])
elif test "$ac_cv_header_linux_dvb_dmx_h" = yes; then
	AC_DEFINE([HAVE_LINUX_DVB_DMX_H])
else
	AC_MSG_ERROR([linux dvb api headers are required to build dvbsnoop])
fi

AC_OUTPUT([
Makefile
src/Makefile
src/datacarousel/Makefile
src/descriptors/Makefile
src/dvb_api/Makefile
src/ebu/Makefile
src/misc/Makefile
src/pes/Makefile
src/sections/Makefile
src/strings/Makefile
src/testdata/Makefile
src/ts/Makefile
src/tvanytime/Makefile
src/private/Makefile
src/private/default/Makefile
src/private/premiere.de/Makefile
src/net_ip/Makefile
])

