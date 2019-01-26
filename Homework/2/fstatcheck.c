#include "csapp.h"

int main(int argc, char**argv) {
	struct stat stat; //stat struct provided by csapp
	char *type, *readok; //used to store info

	if (argc != 2){
		printf("No fd passed");
		return 1;
	}

	Fstat((int)((*argv[1])-'0'), &stat); //Calls fstat on the number passed from the command line and stores info in the stat structure
	if (S_ISREG(stat.st_mode)) {//checks if the stat structure has regular mode
		type = "regular";
	} else if (S_ISDIR(stat.st_mode)) {//checks if stat structure has dir
		type = "directory";
	} else {//if neither reg or dir it's other
		type = "other";
	}

	if ((stat.st_mode & S_IRUSR)) {//check if stat has usr read permissions
		readok = "yes";
	} else {
		readok = "no";
	}

	printf("type: %s, read: %s\n", type, readok);//print results
	exit(0);
}
