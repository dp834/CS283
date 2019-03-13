#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMTHRDS 4
#define VECLEN 100000

pthread_t callThd[NUMTHRDS];
double *array_a;
double *array_b;
double big_sum;
int veclen;

void *dotprod(void *arg){
	int index = *((int *) arg);//cast to int pointer and dereference, makes compiler happy
	free(arg);
	double *x;
	double *y;
	printf("Thread: %d\n", index);
	/* ... */
	x = array_a;
	y = array_b;
	/* ... */
	double *mysum = malloc(sizeof(double));
	*mysum = 0;
	int i, start, end;
	start = index*VECLEN;
	end   = start + VECLEN;
	
	for (i=start; i<end ; i++){
		(*mysum) += (x[i] * y[i]);
	}
	/* ... */
	/* ... */
	printf("Sum: %f\n", *mysum);
	pthread_exit(mysum);
}

int main (int argc, char *argv[]){
	long i;
	double *a, *b;
	void *status;
	a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
	b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
	for (i=0; i<VECLEN*NUMTHRDS; i++){
		a[i]=1;
		//a[i] = i;
		b[i]=a[i];
	}
	veclen = VECLEN;
	array_a = a;
	array_b = b;
	big_sum = 0;
	/* ... */
	/* create threads */
	/* ... */
	for(i=0;i<NUMTHRDS;i++){
		/* Each thread works on a different set of data.
			The offset is specified by 'i'. The size of
			the data for each thread is indicated by VECLEN.
		 */
		int *copy = malloc(sizeof(int));
		*copy = i;
		pthread_create(&callThd[i], NULL, dotprod, (void *) copy);
	}

	double *tempSum;
	for(i=0; i<NUMTHRDS; i++){
		pthread_join(callThd[i], (void **) &tempSum);
		big_sum += *tempSum;
		free(tempSum);
	}
	printf ("Sum = %f \n", big_sum);
	free (a);
	free (b);
}
