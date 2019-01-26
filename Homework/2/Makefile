CC	= gcc
CFLAGS = -Wall -Og -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

all: problem1 problem2 problem3


append: append.c csapp.o
	$(CC) -o append append.c csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

rio_cat: rio_cat.c csapp.o
	$(CC) -o rio_cat rio_cat.c csapp.o $(LDFLAGS) $(LDLIBS)

problem1: cpfile

problem2: fstatcheck

problem3: tee


%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)

clean:
	\rm *.o cpfile fstatcheck tee
