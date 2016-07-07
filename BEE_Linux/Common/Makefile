CC = gcc
CFLAGS= -Wall -g

SOURCE = LinkedList.c \
	 Util.c
	 
OBJECT = $(SOURCE:.c=.o)
EXEC   = common.o

all : common

common : $(OBJECT)
	$(LD) -r -o $(EXEC) $^
	
clean :
	rm -rf *~ *.o $(EXEC)