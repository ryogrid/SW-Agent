CC = gcc
OPENCV_INC=-I/usr/include/opencv/
CFLAGS= -Wall -g $(OPENCV_INC) #-DWEBCAM

LD_SCRIPT = ld.script
LDFLAGS = -Wl,--script=ld.2.6.script
LIBS = -lrt

LIBCOMMON= ../Common/common.o

OUTDIR = ../bin

USERDEF = 

SOURCE = Bee.c           	\
         BinaryLoader.c  	\
         ElfLoader.c     	\
         ProcessInfo.c   	\
         MemoryMap.c     	\
         ElfDumper.c     	\
         SystemCalls.c	 	\
	 SystemCallsName.c	\
	 DeviceEmulation.c	\
	 tls.c           	\
	 Socket/tcp_util.c

ASM_SRC = SystemCallHandle.s

OBJECT = $(SOURCE:.c=.o) $(ASM_SRC:.s=.o)

EXEC = BEE

all : BEE

$(LIBCOMMON):
	$(MAKE) -C ../Common


BEE :  $(OBJECT) $(LIBCOMMON)
	$(CC) $(CFLAGS) -static -o $(OUTDIR)/$(EXEC) $(LDFLAGS) $^ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(USERDEF)

clean :
	rm -rf *~ *.o $(OUTDIR)/$(EXEC)