SRCNAME = tapet.c
OBJNAME = ${SRCNAME:.c=.o}

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

CFLAGS = -Os -Wall -I/usr/include -I${X11INC} `imlib2-config --cflags` 
LDFLAGS = -L/usr/lib -L${X11LIB} -lX11 `imlib2-config --libs`

CC = cc
