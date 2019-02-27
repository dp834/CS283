#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define IN_A_NOT_B 0
#define IN_B_NOT_A 1
#define SAME_NAME 2
#define DO_NOTHING -1

int compareFiles(char*, char*);
int filterHiddenFiles(const struct dirent*);
void compareTimestampAndCopy(char*, char*, char*, char*);
char* joinFolderFile(const char*, const char*);
void copyFile(char*, char*);
void deleteFile(char *);

int main(int argc, char **argv){
	if(argc != 3){//checks all arguments are passed
		printf("Usage: %s <folder A> <folder B>\n", argv[0]);
		return 1;
	}

	struct dirent **dirDataA; 
	struct dirent **dirDataB;
	int fileCountA, fileCountB;
	
	//gets all files from folder A and sorts them alphabetically, get stored in dirDataA
	if((fileCountA = scandir(argv[1], &dirDataA, filterHiddenFiles, alphasort)) < 0){
		perror("Couldn't open directory 1");
		return 2;
	}
	//same as above but gets stored in dirData B
	if((fileCountB = scandir(argv[2], &dirDataB, filterHiddenFiles, alphasort)) < 0){
		perror("Couldn't open directory 2");
		return 2;
	}

	//these contain the number of files read by scandir
	//need to decrement as arrays are zero indexed but the length is not
	fileCountA--;
	fileCountB--;

	//used as a pointer to store malloced space and free 
	//generally just for joining the folder and filenames
	char *tempStringFreeAfterUse;

	while(fileCountA > -1 && fileCountB > -1){//while both folders still have files to read
		//the way I am traversing the dirData's makes the files sorted largest (alphabetically) to smallest
		switch(compareFiles(dirDataA[fileCountA]->d_name, dirDataB[fileCountB]->d_name)){//compare their names (the lists are sorted)
			case(IN_A_NOT_B)://if A > B then A is not in B and copy A to B
				printf("File '%s' in folder '%s' not '%s', copying\n\t",dirDataA[fileCountA]->d_name, argv[1], argv[2]);
				tempStringFreeAfterUse = joinFolderFile(argv[1], dirDataA[fileCountA]->d_name);
				copyFile(tempStringFreeAfterUse, argv[2]);
				free(tempStringFreeAfterUse);
				free(dirDataA[fileCountA--]);
				break;
			case(IN_B_NOT_A)://if A < B then B is not in A so remove file in B
				printf("File '%s' in folder '%s' not '%s', deleting\n\t",dirDataB[fileCountB]->d_name, argv[2], argv[1]);
				tempStringFreeAfterUse = joinFolderFile(argv[2], dirDataB[fileCountB]->d_name);
				deleteFile(tempStringFreeAfterUse);
				free(tempStringFreeAfterUse);
				free(dirDataB[fileCountB--]);
				break;
			case(SAME_NAME)://if the names are the same compare the timestamps
				compareTimestampAndCopy(argv[1], dirDataA[fileCountA]->d_name, argv[2], dirDataB[fileCountB]->d_name);				
				free(dirDataA[fileCountA--]);
				free(dirDataB[fileCountB--]);
				break;
			default://should never happen
				perror("compareFiles failed");
				return 3;
		}
	}
	
	//either we read all the files in A or all of the files in B
	//go through remaining files accordingly

	while(fileCountA > -1){//Files are only in A, copy remaining files to B
		printf("File '%s' in folder '%s' not '%s', copying\n\t",dirDataA[fileCountA]->d_name, argv[1], argv[2]);
		tempStringFreeAfterUse = joinFolderFile(argv[1], dirDataA[fileCountA]->d_name);
		copyFile(tempStringFreeAfterUse, argv[2]);
		free(tempStringFreeAfterUse);
		free(dirDataA[fileCountA--]);
	}

	while(fileCountB > -1){//Files are only in B, remove remaning files in b
		printf("File '%s' in folder '%s' not '%s', deleting\n\t",dirDataB[fileCountB]->d_name, argv[2], argv[1]);
		tempStringFreeAfterUse = joinFolderFile(argv[2], dirDataB[fileCountB]->d_name);
		deleteFile(tempStringFreeAfterUse);
		free(tempStringFreeAfterUse);
		free(dirDataB[fileCountB--]);
	}
	free(dirDataB);
	free(dirDataA);
	return 0;
}

//filters the hidden files when calling scanddir
int filterHiddenFiles(const struct dirent *dir){
	return *(dir->d_name) - '.';
}

/**
 * Compares two files (strings) and returns a status code for what to do
 * just wraps strcmp
 **/
int compareFiles(char *fileA, char *fileB){
	int cmpReturn = strcmp(fileA, fileB);
	if(cmpReturn > 0){
		return IN_A_NOT_B;
	}else if(cmpReturn < 0){
		return IN_B_NOT_A;
	}else{
		return SAME_NAME;
	}
	return DO_NOTHING;//Should never be reached
}

/**
 * Given two files and their folders it will compare the last modified time and copies the newer version to the other folder
 * 
**/
void compareTimestampAndCopy(char *folderA, char *fileA, char *folderB, char *fileB){
	struct stat statA, statB;
	char *joinedA, *joinedB;

	joinedA = joinFolderFile(folderA, fileA);
	if(stat(joinedA, &statA) < 0){//read stat info from file, report if failed
		printf("Stat failed");
	}

	joinedB = joinFolderFile(folderB, fileB);//read stat info from file, report if failed
	if(stat(joinedB, &statB) < 0){
		printf("Stat failed");
	}

	if(difftime(statA.st_mtime, statB.st_mtime) < 0){
		printf("File '%s' found in both folders, '%s' newer, copying to '%s'\n\t", fileA, folderB, folderA); 
		copyFile(joinedB, folderA);
	}else{
		printf("File '%s' found in both folders, '%s' newer, copying to '%s'\n\t", fileA, folderA, folderB); 
		copyFile(joinedA, folderB);
	}
	free(joinedA);
	free(joinedB);
}


/**
 * Takes a folder name as a string and the filename as a string 
 * returns a string <folder name>/<filename>
 * uses malloc on the returned string so caller must free the pointer
**/
char* joinFolderFile(const char *folder, const char *file){
	char *joinedString = (char *) (malloc(sizeof(char)*(2 + strlen(folder) + strlen(file))));
	if(!joinedString){
		printf("Could not malloc");
		exit(4);
	}
	char *originalS = joinedString;
	while(*folder){
		*joinedString++ = *folder++;
	}
	*joinedString++ = '/';
	while(*file){
		*joinedString++ = *file++;
	}
	*joinedString = '\0';
	return originalS;
}


void copyFile(char *source, char *destination){//copies a file using the cp command and keeps the modification info the same
	printf("Copying file from '%s' to '%s'\n\n", source, destination);
	if(!fork()){//spawns child to run the command
		execl("/bin/cp", "/bin/cp", "-p", source, destination, (char *) 0);
		exit(0);
	}
}

void deleteFile(char *file){//deletes the file pased as a string using the rm command
	printf("Deleting file '%s'\n\n", file);
	if(!fork()){//spawns child to run the command
		execl("/bin/rm", "/bin/rm", file, (char *) 0);
		exit(0);
	}
}
