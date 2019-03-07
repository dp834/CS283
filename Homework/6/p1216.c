#include "csapp.h"

void *thread (void *vargp);

int main(int argc, char**argv){

	if(argc != 2){
		printf("Usage: %s <number of threads>\n", argv[0]);
		exit(1);
	}

	int count = atoi(argv[1]);
	int i;
	
	pthread_t *tid = malloc(count*sizeof(pthread_t));
	for(i = 0; i < count; i++){
		Pthread_create(&tid[i], NULL, thread, NULL);
	}
	for(i = 0; i < count; i++){
		Pthread_join(tid[i],NULL);
	}
	exit(0);
}

void *thread(void *vargp){
	printf("Hello, world!\n");
	return NULL;
}
