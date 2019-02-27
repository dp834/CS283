CC	= gcc
CFLAGS = -Wall -Og -g -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

.PHONY:client

all: client

csapp.o: csapp.c
	$(CC) -c csapp.c

client: client.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@ www.google.com 80 index.html

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
	./$@

clean:
	\rm *.o 
