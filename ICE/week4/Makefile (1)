CC	= gcc
CFLAGS = -Wall -Og -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

fork01: fork01-ck.c csapp.o
	$(CC) -o fork01 fork01-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork03: fork03-ck.c csapp.o
	$(CC) -o fork03 fork03-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork07: fork07-ck.c csapp.o
	$(CC) -o fork07 fork07-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork08: fork08-ck.c csapp.o
	$(CC) -o fork08 fork08-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork10: fork10-ck.c csapp.o
	$(CC) -o fork10 fork10-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork11: fork11-ck.c csapp.o
	$(CC) -o fork11 fork11-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork14: fork14-ck.c csapp.o
	$(CC) -o fork14 fork14-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

fork15: fork15-ck.c csapp.o
	$(CC) -o fork15 fork15-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

sig-0: sig-0-ck.c csapp.o
	$(CC) -o sig-0 sig-0-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

sig-3: sig-3-ck.c csapp.o
	$(CC) -o sig-3 sig-3-ck.c csapp.o $(LDFLAGS) $(LDLIBS)

pipe1: pipe1.c
	$(CC) -o pipe1 pipe1.c $(LDFLAGS) $(LDLIBS)

pipe2: pipe2.c
	$(CC) -o pipe2 pipe2.c $(LDFLAGS) $(LDLIBS)
 
execvetest: execvetest-ck.c
	$(CC) -o execvetest execvetest-ck.c
	$(CC) -o myecho myecho-ck.c

csapp.o: csapp.c
	$(CC) -c csapp.c

