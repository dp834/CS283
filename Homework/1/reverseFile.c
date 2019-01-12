#include <stdio.h>

typedef struct lineNode{
	char line[50li];


int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Pass file to reverse as the argument\n");
		return 1;
	}
	printf("%s\n", argv[1]);



	return 0;
}

