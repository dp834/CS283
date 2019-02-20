CC	= gcc
CFLAGS = -Wall -Og -g -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

.PHONY: all

all: p824 p824-2


csapp.o: csapp.c
	$(CC) -c csapp.c

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

test:
	./p824
	./p824-2

clean:
	\rm *.o 
