CC	= gcc
CFLAGS = -Wall -g -Og  
PROG=frp
NO_FIND_OR_PREFIX=noFindOrPrefix
FIND_NO_PREFIX=findNoPrefix
PREFIX_NO_FIND=prefixNoFind
FIND_AND_PREFIX=findAndPrefix


all: homework3

homework3: homework3.c 
	$(CC) -o $(PROG) $< $(CFLAGS)

test: homework3
	@cp $(NO_FIND_OR_PREFIX) $(NO_FIND_OR_PREFIX).txt  
	@cp $(FIND_NO_PREFIX) $(FIND_NO_PREFIX).txt  
	@cp $(PREFIX_NO_FIND) $(PREFIX_NO_FIND).txt  
	@cp $(FIND_AND_PREFIX) $(FIND_AND_PREFIX).txt  
	./$(PROG) popcorn cheese poster 
	@echo "\n\n*******************************************************"
	diff $(NO_FIND_OR_PREFIX) $(NO_FIND_OR_PREFIX).txt  ||true 
	@echo "\n\n*******************************************************"
	diff $(FIND_NO_PREFIX) $(FIND_NO_PREFIX).txt  ||true 
	@echo "\n\n*******************************************************"
	diff $(PREFIX_NO_FIND) $(PREFIX_NO_FIND).txt  ||true 
	@echo "\n\n*******************************************************"
	diff $(FIND_AND_PREFIX) $(FIND_AND_PREFIX).txt ||true 

clean: 
	-@\rm $(PROG) *.o $(NO_FIND_OR_PREFIX).txt $(FIND_NO_PREFIX).txt $(PREFIX_NO_FIND).txt $(FIND_NO_PREFIX).txt $(FIND_AND_PREFIX).txt 2> /dev/null || true

