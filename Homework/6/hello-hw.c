#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8
char *messages[NUM_THREADS];

//struct for passing information
struct dataStruct{
	int sum;
	int id;
	char *string;
};

void *PrintHello(void *threadarg){
	int taskid, sum;
	char *hello_msg;

	//cast passed arg to the type we have
	struct dataStruct *args = (struct dataStruct*) threadarg;
	//set all variables from the passed data
	taskid = args->id;
	sum = args->sum;
	hello_msg = args->string;
	
	printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
	
	//free malloc'd memory
	free(threadarg);
	
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, t, sum;
	sum=0;
	messages[0] = "Hello-0";
	messages[1] = "Hello-1";
	messages[2] = "Hello-2";
	messages[3] = "Hello-3";
	messages[4] = "Hello-4";
	messages[5] = "Hello-5";
	messages[6] = "Hello-6";
	messages[7] = "Hello-7";
	for(t = 0; t < NUM_THREADS; t++)
	{
		sum = sum + t;
		//make a new struct for each to have, up to them to free
		struct dataStruct *newStruct= malloc(sizeof(struct dataStruct));
		//set the data in each struct
		newStruct->sum = sum;
		newStruct->id = t;
		newStruct->string = messages[t];
		printf("Creating thread %d\n", t);
		//create the threads
		pthread_create(&threads[t], NULL, PrintHello, (void *) newStruct);
	}
	pthread_exit(NULL);
}
