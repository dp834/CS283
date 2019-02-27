#include <stdio.h>

int main(int argc, char *argv[]){
	
	if(argc != 2){
		printf("Please pass in number to convert as second argument to command\n");
		return 1;
	}

	int input; 
	sscanf(argv[1], "%d", &input);//assumes signed int
	unsigned int mask = 2147483648;//2^31
	
	for(int i = 0; i <32 ;i++){
		if(mask & input){
			printf("1");
		}else{
			printf("0");
		}
		mask = mask >> 1;
	}
	printf("\n");

	return 0;
}
