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

	FILE *file;
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
	while((dirData = readdir(directory)) != NULL){
		currentFileName = dirData->d_name;
		if(!isTXTFile(currentFileName)){
			continue;
		}
		printf("\n-----------------------------------------------\nOpening file: %s\n", currentFileName);
		file = fopen(currentFileName, "r+");

		if(!file){
			perror("Error opening file");
			return 1;
		}

		switch(preSearch(file, find, prefix)){
			case(FIND_FOUND):
				printf("Replacing '%s' with '%s'\n", find, replace);
				replaceInFile(file, find, replace, currentFileName);
				break;
			case(PREFIX_FOUND):
				printf("Prepending '%s' with '%s'\n", prefix, find);
				prependInFile(file, prefix, find, currentFileName);
				break;
			case(NON_FOUND):
				printf("Did not find '%s' or '%s'\n", find, prefix);
				break;
			default:
				perror("preSearch returned unknown error\n");
				return 4;
		}

		fclose(file);
	}
	closedir(directory);
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
	return (prefixFound)? PREFIX_FOUND : NON_FOUND;
}

void prependInFile(FILE *file, char *prefix, char *find, char *originalFileName){
	rewind(file);
	char *tempFileName = ".homework3.tempFile";
	FILE *tempFile = fopen(tempFileName, "w+");
	if(!tempFile){
		perror("Couldnt' open temp file");
		exit(6);
	}

	char *buffer = NULL;
	int i, j, currentLine;
	long unsigned int bufferLen = 0;
	currentLine = 1;
	while(getline(&buffer, &bufferLen, file) != -1){
		if(!buffer){
			perror("getlineFailed");
			exit(7);
		}
		for(i = 0; buffer[i] != '\0'; i++){
			if(!strncmp(prefix, buffer + i, strlen(prefix))){
				printf("Found '%s' on line %d, prepending with '%s'\n", prefix, currentLine, find);
				for(j = 0; j < strlen(find); j++){
					putc(find[j], tempFile);
				}
			}
			putc(buffer[i], tempFile);
		}
		currentLine++;
	}
	rename(tempFileName, originalFileName);	
}


void replaceInFile(FILE* file, char *find, char *replace, char *originalFileName){
	rewind(file);
	char *tempFileName = ".homework3.tempFile";
	FILE *tempFile = fopen(tempFileName, "w+");
	if(!tempFile){
		perror("Couldnt' open temp file");
		exit(6);
	}

	char *buffer = NULL;
	int i, j, currentLine;
	long unsigned int bufferLen = 0;
	currentLine = 1;
	while(getline(&buffer, &bufferLen, file) != -1){
		if(!buffer){
			perror("getlineFailed");
			exit(7);
		}
		for(i = 0; buffer[i] != '\0'; i++){
			if(!strncmp(find, buffer + i, strlen(find))){
				printf("Found '%s' on line %d, replacing with '%s'\n", find, currentLine, replace);
				for(j = 0; j < strlen(replace); j++){
					putc(replace[j], tempFile);
				}
				i += strlen(find) - 1;
			}else{ 
				putc(buffer[i], tempFile);
			}
		}
		currentLine++;
	}
	rename(tempFileName, originalFileName);	
}

int isTXTFile(char* file){
	return !(strncmp(file + strlen(file) - 4, ".txt", 4));
}
