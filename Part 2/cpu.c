#include <stdio.h>
#include<stdlib.h>
#include "kernel.h"
#include "cpu.h"
#include "interpreter.h"
#include "shell.h"



struct CPU thisCPU;



/*execution: after the "exec" command ...
* load all programs into ram[] 
* append the PCBs to the Ready Queue
* FIFO & RR
* exec() function is an interpreter function in interpreter.c 
* it handles filename argument verfication error
* it opens each program file
* it calls the kernel function to load each program into simulation
* it starts the execution of the loaded program
* exec() first calls myinit() to add each program into the simulation
* then calls scheduler() to run loaded programs.
*
*/
//quant = 2

//checking prompt
void check(char buffer[]) {
	char buff[100]; 
	int result = 0;
	for (int i = 0; i < 4; i++) {
		buff[i] = buffer[i];
	}

	if (strcmp(buff, "exec") == 0) {
		prompt2(buffer);
	}
	else {
		//I deleted result = here, see if it is affected by it
		prompt(buffer);
	}
}




//@parameter r = PCB PC file pointer - will be updated
//return 1 signaling that file is not finished
//returning 0 signaling it is finished.
int runn(FILE * r) {
	
	//initialization
	
	//printf("initial CPU IP is %d\n", ftell(thisCPU.IP));
	
	if (fgets(thisCPU.IR, 999, thisCPU.IP) != NULL) {
		printf("printing...%s\n", thisCPU.IR);
		prompt(thisCPU.IR);
		if (fgets(thisCPU.IR, 999, thisCPU.IP) != NULL) {
			printf("printing...%s\n", thisCPU.IR);
			prompt(thisCPU.IR);
			r = thisCPU.IP;
			return 1;
		}
		else {
			//printf("end of file.\n");
			return 0;
		}
	}
	else {
		//printf("end of file.\n");
		return 0;
	}
}