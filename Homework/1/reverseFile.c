#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

typedef struct lineNode{
	char line[BUFFER_SIZE];
	struct lineNode *next;
}lineNode;


int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Pass file to reverse as the argument\n");
		return 1;
	}
	char buffer[BUFFER_SIZE];

	lineNode *head = (lineNode *) malloc(sizeof(lineNode));
	if(!head){
		printf("Could not get memory");
		return 3;
	}

	
	FILE* file = fopen(argv[1], "r");
	if(!file){
		printf("Could not open file: %s\n", argv[1]);
		return 2;
	}
	
	while(fgets(head->line, BUFFER_SIZE, file)){
		lineNode *temp = (lineNode *) malloc(sizeof(lineNode));
		if(!temp){
			printf("Could not get memory");
			return 3;
		}
		temp->next = head;
		head = temp;
	}

	while(head){
		printf("%s", head->line);
		lineNode *temp;
		temp = head->next;
		free(head);
		head = temp;
	}
	
	return 0;
}

