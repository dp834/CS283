#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage: %s <folder A> <folder B>\n", argv[0]);
		return 1;
	}

	DIR *dirA, *dirB;
	struct dirent *dirDataA, *dirDataB;

	printf("Folder A: %s\nFolder B: %s\n", argv[1], argv[2]);

	return 0;
}
