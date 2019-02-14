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
	if(argc != 3){
		printf("Usage: %s <folder A> <folder B>\n", argv[0]);
		return 1;
	}

	struct dirent **dirDataA; 
	struct dirent **dirDataB;
	int fileCountA, fileCountB;

	if((fileCountA = scandir(argv[1], &dirDataA, filterHiddenFiles, alphasort)) < 0){
		perror("Couldn't open directory 1");
		return 2;
	}
	if((fileCountB = scandir(argv[2], &dirDataB, filterHiddenFiles, alphasort)) < 0){
		perror("Couldn't open directory 2");
		return 2;
	}

	fileCountA--;
	fileCountB--;

	char *tempStringFreeAfterUse;

	while(fileCountA > -1 && fileCountB > -1){
		//printf("looking at files A: %s\n                 B: %s\n", dirDataA[fileCountA]->d_name, dirDataB[fileCountB]->d_name);
		switch(compareFiles(dirDataA[fileCountA]->d_name, dirDataB[fileCountB]->d_name)){
			case(IN_A_NOT_B):
				tempStringFreeAfterUse = joinFolderFile(argv[1], dirDataA[fileCountA]->d_name);
				copyFile(tempStringFreeAfterUse, argv[2]);
				free(tempStringFreeAfterUse);
				free(dirDataA[fileCountA--]);
				break;
			case(IN_B_NOT_A):
				tempStringFreeAfterUse = joinFolderFile(argv[2], dirDataB[fileCountB]->d_name);
				deleteFile(tempStringFreeAfterUse);
				free(tempStringFreeAfterUse);
				free(dirDataB[fileCountB--]);
				break;
			case(SAME_NAME):
				compareTimestampAndCopy(argv[1], dirDataA[fileCountA]->d_name, argv[2], dirDataB[fileCountB]->d_name);				
				free(dirDataA[fileCountA--]);
				free(dirDataB[fileCountB--]);
				break;
			default:
				perror("compareFiles failed");
				return 3;
		}
	}

	while(fileCountA > -1){//Files are only in A
		copyFile(joinFolderFile(argv[1], dirDataA[fileCountA]->d_name), argv[2]);
		free(dirDataA[fileCountA--]);
	}

	while(fileCountB > -1){//Files are only in B
		deleteFile(joinFolderFile(argv[2], dirDataB[fileCountB]->d_name));
		free(dirDataB[fileCountB--]);
	}
	free(dirDataB);
	free(dirDataA);
	return 0;
}

int filterHiddenFiles(const struct dirent *dir){
	return *(dir->d_name) - '.';
}

int compareFiles(char *fileA, char *fileB){
	int cmpReturn = strcmp(fileA, fileB);
	if(cmpReturn > 0){
		return IN_A_NOT_B;
	}else if(cmpReturn < 0){
		return IN_B_NOT_A;
	}else{
		return SAME_NAME;
	}
	return DO_NOTHING;
}

void compareTimestampAndCopy(char *folderA, char *fileA, char *folderB, char *fileB){
	struct stat statA, statB;
	char *joinedA, *joinedB;

	joinedA = joinFolderFile(folderA, fileA);
	if(stat(joinedA, &statA) < 0){
		printf("Stat failed");
	}

	joinedB = joinFolderFile(folderB, fileB);
	if(stat(joinedB, &statB) < 0){
		printf("Stat failed");
	}

	if(difftime(statA.st_mtime, statB.st_mtime) < 0){
		copyFile(joinedB, joinedA);
	}else{
		copyFile(joinedA, joinedB);
	}
	free(joinedA);
	free(joinedB);
}

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


void copyFile(char *source, char *destination){
	printf("Copying file from '%s' to '%s'\n", source, destination);
	if(!fork()){
		execl("/bin/cp", "/bin/cp", "-p", source, destination, (char *) 0);
		exit(0);
	}
}

void deleteFile(char *file){
	printf("Deleting file '%s'\n", file);
	if(!fork()){
		execl("/bin/rm", "/bin/rm", file, (char *) 0);
		exit(0);
	}
}
