#include <stdio.h>
#include "shell.h"
#include"memorymanager.h"
#include "ram.h"

// Global data structures simulating hardware
//

struct CPU {
	FILE *IP;
	char IR[1000];
	int quanta;
	int offset;
} cpu;

void initCPU() {
	cpu.quanta = 2;
	cpu.IP = NULL;
	cpu.IR[0] = '\0';
	cpu.offset = 0;
}

void setCPU(FILE *PC) {
	cpu.IP = PC;
	cpu.IR[0] = '\0';
}

void setOffset(int offset) {
	cpu.offset = offset;
}


int runCPU(int quanta) {
	int result;
	char *p;
	cpu.quanta = quanta;

	//move cpu's IP
	//printf("CPU's IP at %d.\n", ftell(cpu.IP));



	int i = 0;
	while (cpu.quanta > 0 && i<cpu.quanta) {
		//check the CPU offset reaches 4, if so, call a pagefault interrupt.
		if (cpu.offset == 4) {
			return -1; //need to return the new offset after page fault is resolved.
			break;
		}
		
		printf("CPU CURRENT OFFSET: %d.\n", cpu.offset);

		p = fgets(cpu.IR, 999, cpu.IP);
		cpu.offset++;
		printf("cpu.IP at %d\n", ftell(cpu.IP));

		

		printf(">>>%s\n",cpu.IR); // debug code

		result = prompt(cpu.IR);
		if (p == NULL || feof(cpu.IP)) {
			printRam();
			return -99; // end of program
		}
		if (result != 0) return result;

		cpu.quanta--;
	}

	return cpu.offset; //return offset
}
