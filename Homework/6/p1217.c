/**
	A:
	Nothing prints because the program will exit which kills the thread that it spawned. The main program will exit while the thread is sleeping. The thread will exit when the parent exits so it will never print.
	
	B:
	Pthread_join(tid, NULL);
	Pthread_exit(NULL);	

 **/

#include "csapp.h"

void *thread (void *vargp);

int main(){
	pthread_t tid;
	
	Pthread_create(&tid, NULL, thread, NULL);
	Pthread_join(tid, NULL);

	Pthread_create(&tid, NULL, thread, NULL);
	Pthread_exit(0);
}

void *thread(void * vargp){
	Sleep(1);
	printf("Hello, world!\n");
	return NULL;
}
