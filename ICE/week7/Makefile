CC	= gcc
CFLAGS = -Wall -I .. 
LDLIBS = -lpthread

.PHONY: echoserver

hostinfo: hostinfo.c csapp.o
	$(CC) -o hostinfo $(CFLAGS) hostinfo.c csapp.o $(LDFLAGS) $(LDLIBS)

echoclient: echoclient-ck.c csapp.o
	$(CC) -o echoclient echoclient-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

echoserver: echoserveri-ck.c csapp.o echo-ck.o
	$(CC) -o echoserver echoserveri-ck.c echo-ck.o csapp.o $(LDFLAGS) $(LDLIBS)
	kill $(ps | grep echoserver | awk '{print $1}') || true
	./echoserver 6969 &
