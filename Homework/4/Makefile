CC	= gcc
CFLAGS = -Wall -Og -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

append: append.c csapp.o
	$(CC) -o append append.c csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

test: test.c csapp.o
	$(CC) -o test test.c csapp.o $(LDFLAGS) $(LDLIBS)

