CC	= gcc
CFLAGS = -Wall -I .. 
LDLIBS = -lpthread

hostinfo: hostinfo.c csapp.o
	$(CC) -o hostinfo $(CFLAGS) hostinfo.c csapp.o $(LDFLAGS) $(LDLIBS)

echoclient: echoclient-ck.c csapp.o
	$(CC) -o echoclient echoclient-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

echoserver: echoserveri-ck.c csapp.o echo-ck.o
	$(CC) -o echoserver echoserveri-ck.c echo-ck.o csapp.o $(LDFLAGS) $(LDLIBS)
