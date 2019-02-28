#include "csapp.h"
#define NUM_ELEMENTS 1024 
#define NUM_THREADS 8 
void * do_work (void * arg);

struct AR
{
	double *array;
	int size;
	double *sum;
};

int main (int argc, char * argv) 
{
	double array[NUM_ELEMENTS];
	double sum[NUM_THREADS];
	double totalSum=0;
	pthread_t id[NUM_THREADS];
	struct AR * arg;
	void  *return_value;
	int i;

	for (i = 0; i < NUM_ELEMENTS; i++) array[i] = i;

	arg = (struct AR * ) calloc (NUM_THREADS, sizeof (struct AR) ) ;
	for(i = 0; i < NUM_THREADS; i++){
		(arg+i) -> array = array + i*(NUM_ELEMENTS/NUM_THREADS);
		(arg+i) -> size = (NUM_ELEMENTS/NUM_THREADS);
		(arg+i) -> sum = sum + i;
		if (pthread_create ((id+i), NULL, do_work, (void * ) (arg+i)) ) 
		{
			fprintf (stderr, "Error\n") ;
			exit (1) ;
		}
	}
	for(i=0;i<NUM_THREADS; i++){
		if (pthread_join(id[i], &return_value))
		{
			fprintf(stderr,"Error\n");
			exit(1);
		}
		totalSum += sum[i];
	}
	printf("sum = %10.1lf\n", totalSum);
	return(0);
}

void * do_work (void * arg) 
{
	struct AR * argument;
	int i, size;
	double * array;
	double * sum;

	argument = (struct AR * ) arg;

	size = argument -> size;
	array = argument -> array;
	sum = argument -> sum;

	* sum = 0;
	for (i = 0; i < size; i ++ ) {
		*sum += array[i];
	}
	return NULL;
}


