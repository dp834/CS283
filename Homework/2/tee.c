#include "csapp.h"
#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
	// -a option appends, no option overwrites
	int aFlag = 0; //used to see if append argument was used
	int i, returnCheck;
	int *fds;
	for(i = 1; i< argc; i++){//looks for the -a option
		if(argv[i][0] == '-' && argv[i][1] == 'a'){
			aFlag = 1;
		}		
	}
	
	if(argc - 1 - aFlag == 0){// checks that some filename was passed
		printf("Please pass filenames");
		return 1;
	}

	fds = (int *) malloc((argc-1-aFlag)*sizeof(int*));//create a array of file descriptors 
	for (i = 1; i < argc; i++){//opens all the files passed and stores them in the fds array
		if(argv[i][0] != '-' && argv[i][1] != 'a'){
			//opens with flags create, write only, truncate or append(depends on if -a was passed), with permissions user read write and group read write 
			returnCheck = fds[i-1] = open(argv[i], O_WRONLY|O_CREAT|((aFlag)?O_APPEND:O_TRUNC), S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
			if(returnCheck < 0){
				printf("Failed to open file: %s\n", argv[i]);
				return 2;
			}
		}
	}
	
	int size;
	char buffer[BUFFER_SIZE];
	while((size = read(STDIN_FILENO, buffer, BUFFER_SIZE)) != 0){//reads stdin and adds to buffer until eof is reached
		write(STDOUT_FILENO, buffer, size);//write what is read to stdout
		for(i = 0; i < argc - 1 - aFlag; i++){//for each file in the fds write what is in the buffer to each file
			write(fds[i], buffer, size);
		}
	}
	for(i=0; i < sizeof(fds); i++){//close all the files that were opened
		close(fds[i]);
	}
	free(fds);//free the memory from the fd pointer

	return 0;
}
