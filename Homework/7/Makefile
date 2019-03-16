CC	= gcc
CFLAGS = -Wall -Og -g -I . 
LDLIBS = -lpthread

.PHONY:all

all: dotpr-hw

dotpr-hw: dotpr-hw.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS) $(CFLAGS)

csapp.o: csapp.c
	$(CC) -c csapp.c

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS) 
	./$@

clean:
	\rm *.o dotpr-hw 
