CC	= gcc
CFLAGS = -Wall -Og -g -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

.PHONY:all p1216 p1217 hello-hw

all: p1216 p1217 hello-hw

p1217: p1217.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

hello-hw: hello-hw.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

p1216: p1216.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@ 10	

csapp.o: csapp.c
	$(CC) -c csapp.c

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

clean:
	\rm *.o  p1217 p1216 hello-hw
