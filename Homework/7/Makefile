CC	= gcc
CFLAGS = -Wall -Og -g -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

.PHONY:all

all: dotpr-hw

dotpr-hw: dotpr-hw.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

clean:
	\rm *.o  p1217 p1216 hello-hw
