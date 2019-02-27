/* Figure 8.18 */
#include "csapp.h"
#define N 2

void childSegFaultHandler(int sig){
	printf("I caught the seg fault\n");
	exit(0);	
}

int main() {
	int status, i;
	pid_t pid;  /* Parent creates N children */
	for (i = 0; i < N; i++){ 
		if ((pid = Fork()) == 0){ /* child */ 
			if(i == 0){//set segfault handler for only the first child
				signal(SIGSEGV, childSegFaultHandler);
			}
			*(char *) 0 = 0;//tries to write memory to location 0, will trigger seg fault
			exit(100+i);  /* Parent reaps N children in no particular order */
		}
	}
	while ((pid = waitpid(-1, &status, 0)) > 0){    
		if (WIFEXITED(status)){ 
			printf("child %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
		}else{ 
			printf("child %d terminated by signal %d: ", pid, WTERMSIG(status));
			fflush(stdout);
			psignal(WTERMSIG(status), NULL);
		}
	}  /* The normal termination is if there are no more children */
	if (errno != ECHILD){ 
		unix_error("waitpid error");
	}
	exit(0); 
}
