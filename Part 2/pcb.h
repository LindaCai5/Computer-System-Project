#include <stdio.h>
typedef struct PCB {
	FILE *PC; /*ptr that points to the first line of the program*/
}PCB;

PCB* makePCB(FILE* p);
