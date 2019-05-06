#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shellmemory.h"



//accepts 2 parameters: c which is the parta's command code/index
//the other is partb char*.
char *repo[] = { "help\n", "quit\n", "set", "print", "run\n" };

void interpreter(char* parta, char partb[], char partc[]) {

	if (strcmp(parta, repo[0]) == 0) {
		
		for (int i = 0; i < 5; i++) {
			printf("%s\n", repo[i]);
		}
	}
	else if (strcmp(parta, repo[1]) == 0) {
		printf("Bye!");
		exit(0);
	}
	else if (strcmp(parta, repo[2]) == 0) {
		set(partb, partc);
		//printArr();

	}
	else if (strcmp(parta, repo[3]) == 0) {
		printvar(partb);
		
	}


}



