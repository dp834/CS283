CC	= gcc
CFLAGS = -Wall -Og  -g
PROG = lab2
FOLDER_A_ORIG = origA
FOLDER_B_ORIG = origB
FOLDER_A = testFolder1
FOLDER_B = testFolder2


all: syncFolders 

syncFolders: syncFolders.c 
	$(CC) -o $(PROG) $<  $(CFLAGS) 

test: syncFolders
	-@rm -rf $(FOLDER_A) 2> /dev/null || true
	-@rm -rf $(FOLDER_B) 2> /dev/null || true
	-@mkdir $(FOLDER_A) $(FOLDER_B)
	-@cp -p $(FOLDER_A_ORIG)/* $(FOLDER_A)
	-@cp -p $(FOLDER_B_ORIG)/* $(FOLDER_B)
	-@echo "---------------------------------------------------"
#	valgrind --leak-check=full -v ./$(PROG) $(FOLDER_A) $(FOLDER_B)
	./$(PROG) $(FOLDER_A) $(FOLDER_B)
	-@echo "---------------------------------------------------"
	diff --brief -r $(FOLDER_A) $(FOLDER_B)

clean:
	-@\rm -r -f *.o  *.gch $(PROG) $(FOLDER_A) $(FOLDER_B) &> /dev/null || true
