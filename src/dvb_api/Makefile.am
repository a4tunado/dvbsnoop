AM_CPPFLAGS = -I$(top_srcdir)/src \
              -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE


noinst_LIBRARIES = libdvbapi.a

noinst_HEADERS = \
	dvb_api.h \
	file_io.h \
	dmx_pes.h \
	dmx_sect.h \
	dmx_ts.h \
	dmx_tspidscan.h \
	dmx_tspidbandwidth.h \
	dmx_error.h \
	fe_signal.h \
	fe_info.h \
	fe_misc.h 


libdvbapi_a_SOURCES = \
	dmx_pes.c \
	dmx_sect.c \
	dmx_ts.c \
	dmx_tspidscan.c \
	dmx_tspidbandwidth.c \
	dmx_error.c \
	fe_signal.c \
	fe_info.c \
	fe_misc.c


