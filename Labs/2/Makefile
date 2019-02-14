CC	= gcc
CFLAGS = -Wall -Og  -g
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
	-@rm -rf $(FOLDER_A) 2> /dev/null || true
	-@rm -rf $(FOLDER_B) 2> /dev/null || true
	-@mkdir $(FOLDER_A) $(FOLDER_B)
	-@cp -p $(FOLDER_A_ORIG)/* $(FOLDER_A)
	-@cp -p $(FOLDER_B_ORIG)/* $(FOLDER_B)
	-@echo "---------------------------------------------------"
	./$(PROG) $(FOLDER_A) $(FOLDER_B)
	-@echo "---------------------------------------------------"
	diff --brief -r $(FOLDER_A) $(FOLDER_B)

%: %.c csapp.o
	$(CC) -o $@ $< csapp.o $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	-@\rm -r *.o  *.gch $(PROG) $(FOLDER_A) $(FOLDER_B) 2> /dev/null || true
