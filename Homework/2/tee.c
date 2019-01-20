#include "csapp.h"
#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
	// -a option appends, no option overwrites
	int aFlag = 0;
	int i, returnCheck;
	int *fds;
	for(i = 1; i< argc; i++){
		if(argv[i][0] == '-' && argv[i][1] == 'a'){
			aFlag = 1;
		}		
	}
	
	if(argc - 1 - aFlag == 0){
		printf("Please pass filenames");
		return 1;
	}

	fds = (int *) malloc((argc-1-aFlag)*sizeof(int*));
	for (i = 1; i < argc; i++){
		if(argv[i][0] != '-' && argv[i][1] != 'a'){
			returnCheck = fds[i-1] = open(argv[i], O_WRONLY|O_CREAT|((aFlag)?O_APPEND:O_TRUNC), S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
			if(returnCheck < 0){
				printf("Failed to open file: %s\n", argv[i]);
				return 2;
			}
		}
	}
	
	int size;
	char buffer[BUFFER_SIZE];
	while((size = read(STDIN_FILENO, buffer, BUFFER_SIZE)) != 0){
		write(STDOUT_FILENO, buffer, size);
		for(i = 0; i < argc - 1 - aFlag; i++){
			write(fds[i], buffer, size);
		}
	}
	for(i=0; i < sizeof(fds); i++){
		close(fds[i]);
	}
	free(fds);

	return 0;
}
