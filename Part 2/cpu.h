#include <stdio.h>

struct CPU {
	FILE* IP;
	char IR[1000]; //instruction register -> stores instruction that will be sent to interpreter() for execution
	int quanta; //quanta = 2 , 2 lines of code for each file.
};

extern struct CPU thisCPU;
int runn(FILE* r);

