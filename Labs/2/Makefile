CC	= gcc
CFLAGS = -Wall -Og -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread
TEST_SCRIPT = createTestFolders

all: syncFolders 


append: append.c csapp.o
	$(CC) -o append append.c csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

syncFolders: syncFolders.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)

test: syncFolders
	@echo "not implemented"

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(LDFLAGS) $(LDLIBS)

clean:
	-@\rm *.o  *.gch syncFolders 2> /dev/null || true
