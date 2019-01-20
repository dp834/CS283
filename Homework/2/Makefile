CC	= gcc
CFLAGS = -Wall -Og -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

append: append.c csapp.o
	$(CC) -o append append.c csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

rio_cat: rio_cat.c csapp.o
	$(CC) -o rio_cat rio_cat.c csapp.o $(LDFLAGS) $(LDLIBS)

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)
