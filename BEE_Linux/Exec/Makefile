CC = gcc
CFLAGS= -Wall -g

SOURCE = ExecMain.c

OBJECT = $(SOURCE:.c=.o)

OUTDIR = ../bin

EXEC   = BeeExec

all : BeeExec

BeeExec : $(OBJECT)
	$(CC) $(CFLAGS) -static -o $(OUTDIR)/$(EXEC) $^

clean :
	rm -rf *~ *.o $(OUTDIR)/$(EXEC)