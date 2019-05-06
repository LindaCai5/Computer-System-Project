#include <stdio.h>
#include"memorymanager.h"

// Global data structures representing hardware
//

FILE *ram[10];

// Data structure management functions
//

void initRAM() {
	int i;

	for (i = 0; i < 10; i++) ram[i] = NULL;
}

int addToRAM(FILE *p) {
	int i;

	if (p == NULL) return -1; // error 

	for (i = 0; i < 10 && ram[i] != NULL; i++); // find next available space

	if (i < 10) {
		ram[i] = p;
		
		return i; // position in RAM
	}
	else
		return -2; // out of memory error
}

void clearRAM() {
	for (int i = 0; i < 10; i++) {
		ram[i] = NULL;
	}
}

//my checking function:
void printRam() {
	printf("printing ram contents\n");
	for (int i = 0; i < 10; i++) {
		printf("[%d]\n", ftell(ram[i]));
	}
}