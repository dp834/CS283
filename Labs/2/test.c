#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void createDir(char *dir, int t);
int pause_sec(int x);


int main() {
	createDir("A/", 0);
	createDir("B/", 1);
}


void createDir(char *dir, int t) {
	char d[30];
	sprintf(d, "mkdir ./%s", dir);
	system(d);

	int dirCount = rand() % 100 + 1;
	char c[50];

	if(t == 1) {
		dirCount+=15; //this is just so dir B has more files
	}

	for(int i = 0; i < dirCount; i++) {
		sprintf(c, "touch ./%sfile%d.txt", dir, i);
		system(c);
	}

	pause_sec(2);

	for(int i = 0; i < dirCount; i++) {
		if((rand() % 5 + 1) == 1) {
			sprintf(c, "echo 'Hello World!' > ./%sfile%d.txt", dir, i);
			system(c);
		}
	}
}


int pause_sec(int x) {
	long T1,T3,T2;
	T1=time(&T2);
	T3=(time(&T2)) + x;
	while(time(&T2) < T3);
	return(x);
}
