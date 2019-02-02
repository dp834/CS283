CC	= gcc
CFLAGS = -Wall -g -Og -I $(CSAPP_INC) -I  
PROG=pfa
ORIGINAL_TEXT=originalText
MODIFIED_TEXT=testText.txt


all: homework3

homework3: homework3.c 
	$(CC) -o $(PROG) $< $(CFLAGS)

test: homework3
	@cp $(ORIGINAL_TEXT) $(MODIFIED_TEXT) 
	./$(PROG) test to prefixParam
#	@echo "\n\n---------------------------------------------"
#	@cat $(MODIFIED_TEXT) 
	diff $(ORIGINAL_TEXT) $(MODIFIED_TEXT) || true

clean: 
	-@\rm $(PROG) *.o $(MODIFIED_TEXT) 2> /dev/null || true
