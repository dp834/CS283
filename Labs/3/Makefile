CC	= gcc
CFLAGS = -Wall -Og -g -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

.PHONY:client serverTester

all: server

csapp.o: csapp.c
	$(CC) -c csapp.c

client: client.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@ www.google.com 80 index.html

server: server.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@  8080

serverTester: serverTester.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@ localhost 8080 Makefile 

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

clean:
	\rm *.o 
