
PROGRAM	    = CaptureSystem
INCLUDEDIR  = -I./include
INCLD	    = ./include
SRCDIR	    = ./capture
HDRS	    =
SRCS	    = $(SRCDIR)/main.c \
	      $(SRCDIR)/framedifferencing.c \
	      $(SRCDIR)/time_count.c \
	      $(SRCDIR)/camctrlthread.c \
	      $(SRCDIR)/capture.c \
	      $(SRCDIR)/camera.c \
	      $(SRCDIR)/visca.c \
	      $(SRCDIR)/queue.c

########################################################
CC 	    = gcc

#OPENCV_INC  = -I/usr/local/include/opencv
OPENCV_INC = -I/usr/include/opencv/
IPL_LIB	    = -L/usr/local/lib -L/usr/lib  -L/usr/X11R6/lib
OPENCV_LIB  = -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux
#OPT_FLAG   = -O3 -axNP -ipo

CFLAGS 	    = -g $(OPT_FLAG) $(INCLUDEDIR) $(OPENCV_INC)
LDLIBS	    = $(OPENCV_LIB) $(IPL_LIB) -lm  -pthread -lX11

.c.o:
	${CC} -c $< -o $@ ${CFLAGS}

OBJS	    = $(SRCS:.c=.o)

all:	      $(PROGRAM)

$(SRCS):      $(HDRS)

clean:
	      rm -f $(OBJS) $(PROGRAM) *~ *.o $(SRCDIR)/*~ $(INCLD)/*~ *.ppm *.jpg *.mpg

$(PROGRAM):   $(OBJS) $(HDRS)
	      ${CC} ${CFLAGS} $(LDLIBS) -o  $(PROGRAM) $(OBJS) 
	      rm -f $(SRCDIR)/*.o 


