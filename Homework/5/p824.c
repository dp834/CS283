/* Figure 8.18 */
#include "csapp.h"
#define N 2
int main() {
	int status, i, fd;
	pid_t pid;  /* Parent creates N children */
	fd = open("readOnlyFile", O_CREAT|O_RDONLY, S_IRUSR);
	write(fd, "test", 5);
	for (i = 0; i < N; i++){ 
		if ((pid = Fork()) == 0){ /* child */ 
			if(write(fd, "test", 4)<0){
				*(char *) 0 = 0;
				raise(SIGSEGV);
			}else{
				exit(100+i);  /* Parent reaps N children in no particular order */
			}
		}
	}
	while ((pid = waitpid(-1, &status, 0)) > 0){    
		if (WIFEXITED(status)){ 
			printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
		}else{ 
			printf("child %d terminated by signal %d: ", pid, WIFSIGNALED(status));
			fflush(stdout);
			psignal(WIFSIGNALED(status), NULL);
		}
	}  /* The normal termination is if there are no more children */
	if (errno != ECHILD){ 
		unix_error("waitpid error");
	}
	exit(0); 
}
