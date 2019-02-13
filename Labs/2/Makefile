CC	= gcc
CFLAGS = -Wall -Og 
LDLIBS = -lpthread
PROG = lab2
FOLDER_A_ORIG = origA
FOLDER_B_ORIG = origB
FOLDER_A = testFolder1
FOLDER_B = testFolder2


all: syncFolders 

append: append.c csapp.o
	$(CC) -o append append.c csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

syncFolders: syncFolders.c csapp.o
	$(CC) -o $(PROG) $< csapp.o $(CFLAGS) $(LDFLAGS) $(LDLIBS)

test: syncFolders
	-@rm $(FOLDER_A) 2> /dev/null || true
	-@rm $(FOLDER_B) 2> /dev/null || true
	-@cp -r $(FOLDER_A_ORIG) $(FOLDER_A)
	-@cp -r $(FOLDER_B_ORIG) $(FOLDER_B)
	-@echo "---------------------------------------------------"
	./$(PROG) $(FOLDER_A) $(FOLDER_B)

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	-@\rm *.o  *.gch $(PROG) $(FOLDER_A) $(FOLDER_B) 2> /dev/null || true
