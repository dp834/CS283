/*
* badcnt.c - An improperly synchronized counter program 
*/
#include "csapp.h"

void *thread1 (void *vargp); /* Thread routine prototype */
void *thread2 (void *vargp); /* Thread routine prototype */
void *thread3 (void *vargp); /* Thread routine prototype */

/* Global shared variables */
volatile int cnt = 0; /* Counter */
/* Objects declared as volatile are omitted from optimization because their
   values can be changed by code outside the scope of current code at any time. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) 
 {
  int niters;
  pthread_t tid1, tid2;

  /* Check input argument */
  if (argc != 2) 
   {
    printf("usage: %s <niters>\n", argv[0]);
    exit(0);
   }
  niters = atoi(argv[1]);

  /* Create threads and wait for them to finish */
  Pthread_create(&tid1, NULL, thread3, &niters);
  Pthread_create(&tid2, NULL, thread3, &niters);
  Pthread_join(tid1, NULL);
  Pthread_join(tid2, NULL);

  /* Check result */
  if (cnt != (2 * niters))
   printf("BOOM! cnt=%d\n", cnt);
    else
     printf("OK cnt=%d\n", cnt);
  exit(0);
 }

/* Thread routine */
void *thread1 (void *vargp)
 {
  int i, niters = *((int *)vargp);

  for (i = 0; i < niters; i++)
  cnt++;

  return NULL;
 }

/* Thread routine */
void *thread2 (void *vargp)
 {
  int i, niters = *((int *)vargp);

  for (i = 0; i < niters; i++)
   {
   	/* protected by mutex */
   	pthread_mutex_lock (&mutex );
    cnt++;
   	pthread_mutex_unlock (&mutex );
   }

  return NULL;
 }


/* Thread routine */
void *thread3 (void *vargp)
 {
  int i, niters = *((int *)vargp);

 	pthread_mutex_lock (&mutex );
  for (i = 0; i < niters; i++)
   {
   	/* protected by mutex */
    cnt++;
   }
 	pthread_mutex_unlock (&mutex );

  return NULL;
 }

