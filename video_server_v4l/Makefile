PROGRAM	    = video_server
INCLUDEDIR  = -I./include
INCLD	    = ./include
SRCDIR	    = ./capture
HDRS	    =
SRCS	    = $(SRCDIR)/main.c \
	      $(SRCDIR)/framedifferencing.c \
	      $(SRCDIR)/time_count.c \
	      $(SRCDIR)/capture.c

#if you want to build for webcam, you should set this flag -DWEBCAM
CAMERA_TYPE	= #-DWEBCAM

########################################################
CC 	    = gcc

#OPENCV_INC  = -I/usr/local/include/opencv
OPENCV_INC = -I/usr/include/opencv/
IPL_LIB	    = -L/usr/local/lib -L/usr/lib  -L/usr/X11R6/lib
OPENCV_LIB  = -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux
#OPT_FLAG   = -O3 -axNP -ipo

CFLAGS 	    = -g $(OPT_FLAG) $(INCLUDEDIR) $(OPENCV_INC)
LDLIBS	    = $(OPENCV_LIB) $(IPL_LIB) -lm  -lX11


OBJS	    = $(SRCS:.c=.o)

.c.o:	
	$(CC) $(CFLAGS) $(CAMERA_TYPE) -c -o $@ $<

all:	      $(PROGRAM)

$(SRCS):      $(HDRS)

clean:
	      rm -f $(OBJS) $(PROGRAM) *~ *.o $(SRCDIR)/*~ $(INCLD)/*~ *.ppm *.jpg *.mpg

$(PROGRAM):   $(OBJS) $(HDRS)
	      ${CC} $(LDLIBS) -o  $(PROGRAM) $(OBJS) ${CFLAGS}
	      rm -f $(SRCDIR)/*.o 
