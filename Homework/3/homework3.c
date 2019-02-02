#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


#define BUFFER_SIZE 32
#define FIND_FOUND 1
#define PREFIX_FOUND 2
#define NON_FOUND 0
#define true 1
#define false 0


int isTXTFile(char*);
int preSearch(FILE*, char*, char*);
void prependInFile(FILE*, char*, char*, char*);
void replaceInFile(FILE*, char*, char*, char*);

int main(int argc, char *argv[]){

	FILE *files;
	char *find, *replace, *prefix, *currentFileName;
	DIR *directory;
	struct dirent *dirData;
	if(argc != 4){
		printf("Usage: %s <find> <replace> <prefix>\n", argv[0]);
		return 2;
	}

	find = argv[1];
	replace = argv[2];
	prefix = argv[3];

	//printf("Find: %s\nReplace: %s\nPrefix: %s\n", find, replace, prefix);

	directory = opendir(".");
	if(!directory){
		perror("Couldn't open directory");
		return 8;
	}
	while(!(dirData = readdir(directory))){
		currentFileName = dirData->d_name;
		if(!isTXTFile(currentFileName)){

		}
		files = fopen(currentFileName, "r+");

		if(!files){
			perror("Error opening file");
			return 1;
		}

		switch(preSearch(files, find, prefix)){
			case(FIND_FOUND):
				printf("Replacing find with replace\n");
				replaceInFile(files, find, replace, currentFileName);
				break;
			case(PREFIX_FOUND):
				printf("Prepending prefix with find\n");
				prependInFile(files, prefix, find, currentFileName);
				break;
			case(NON_FOUND):
				printf("Did not find any prefix or find\n");
				break;
			default:
				perror("preSearch returned unknown error\n");
				return 4;
		}
	}

	return 0;
}

int preSearch(FILE* file, char *find, char *prefix){
	char *buffer = malloc(BUFFER_SIZE*sizeof(char));
	if(!buffer){
		perror("Failed to get memory");
	}
	int prefixFound = false;
	char *searchResult = NULL;
	while(fgets(buffer, BUFFER_SIZE, file)){
		searchResult = strchr(buffer, *find);
		if(searchResult && !strncmp(find, searchResult, strlen(find))){
			return FIND_FOUND;
		}
		if(!prefixFound){
			searchResult = strchr(buffer, *prefix);
			if(searchResult && !strncmp(prefix, searchResult, strlen(prefix))){
				prefixFound = true;
			}
		}
	}
	free(buffer);
	if(searchResult){
		free(searchResult);
	}
	return (prefixFound)? PREFIX_FOUND : NON_FOUND;
}

void prependInFile(FILE *file, char *prefix, char *find, char *originalFileName){
	rewind(file);
	char *tempFileName = "homework3.tempFile";
	FILE *tempFile = fopen(tempFileName, "w+");
	if(!tempFile){
		perror("Couldnt' open temp file");
		exit(6);
	}

	char *buffer = NULL;
	int i, j;
	long unsigned int bufferLen = 0;

	while(getline(&buffer, &bufferLen, file) != -1){
		if(!buffer){
			perror("getlineFailed");
			exit(7);
		}
		for(i = 0; buffer[i] != '\0'; i++){
			if(!strncmp(prefix, buffer + i, strlen(prefix))){
				for(j = 0; j < strlen(find); j++){
					putc(find[j], tempFile);
				}
			}else{ 
				putc(buffer[i], tempFile);
			}
		}
	}
	rename(tempFileName, originalFileName);	
}


void replaceInFile(FILE* file, char *find, char *replace, char *originalFileName){
	rewind(file);
	char *tempFileName = "homework3.tempFile";
	FILE *tempFile = fopen(tempFileName, "w+");
	if(!tempFile){
		perror("Couldnt' open temp file");
		exit(6);
	}

	char *buffer = NULL;
	int i, j;
	long unsigned int bufferLen = 0;

	while(getline(&buffer, &bufferLen, file) != -1){
		if(!buffer){
			perror("getlineFailed");
			exit(7);
		}
		for(i = 0; buffer[i] != '\0'; i++){
			if(!strncmp(find, buffer + i, strlen(find))){
				for(j = 0; j < strlen(replace); j++){
					putc(replace[j], tempFile);
				}
				i += strlen(find) - 1;
			}else{ 
				putc(buffer[i], tempFile);
			}
		}
	}
	rename(tempFileName, originalFileName);	
}

int isTXTFile(char* file){
	return( strncmp(file + strlen(file) - 4, ".txt", 4));
}
