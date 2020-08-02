# dmenu version
VERSION = 4.9

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# Xinerama, comment if you don't want it
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2
# OpenBSD (uncomment)
#FREETYPEINC = $(X11INC)/freetype2

# includes and libs
# >>>>>>>>>>>>>>>>>>>> json
# ==================== json
INCS = -I$(X11INC) -I$(FREETYPEINC)
# <<<<<<<<<<<<<<<<<<<< json
# >>>>>>>>>>>>>>>>>>>> fuzzymatch-json
# ==================== fuzzymatch-json
LIBS = -L$(X11LIB) -lX11 $(XINERAMALIBS) $(FREETYPELIBS)
# <<<<<<<<<<<<<<<<<<<< fuzzymatch-json

# flags
# >>>>>>>>>>>>>>>>>>>> json
# ==================== json
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" $(XINERAMAFLAGS)
CFLAGS   = -std=c99 -pedantic -Wall -Os $(INCS) $(CPPFLAGS)
# <<<<<<<<<<<<<<<<<<<< json
LDFLAGS  = $(LIBS)

# compiler and linker
CC = cc

# >>>>>>>>>>>>>>>>>>>> json
# ==================== json
# <<<<<<<<<<<<<<<<<<<< json
