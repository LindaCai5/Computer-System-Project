#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "shellmemory.h"
#include "shell.h"
#include "ram.h"
#include "kernel.h"
#include "pcb.h"
//returns 1 if the first four char are exec


int run(char *filename) {
	FILE *ptr;
	char buffer[1000], buf0[100], buf1[100], buf2[100], buf3[100];
	int result = 0;
	char buff[100];
	
	ptr = fopen(filename,"rt");
	if (ptr == NULL) return 4; // file not found
	
	while(!feof(ptr)) {
		fgets(buffer, 999, ptr);

		for (int i = 0; i < 4; i++) {
			buff[i] = buffer[i];
		}
		if (strcmp(buff, "exec") == 0) {
			//printf("shell recognizes exec 4 words!\n");
			prompt2(buffer);
		}
	    else if (strlen(buffer)>1) 
			result = prompt(buffer);

		if (result == 99) break;
		
	}

	fclose(ptr);

	if (result == 99) return 99;

	return 0;
}

int interpreter(char buf0[], char buf1[], char buf2[]) {
	
	int result = 0; // no errors

	if (strcmp(buf0,"help")==0) {
		printf("Legal commands:\n");
		printf("help              display this help\n");
		printf("quit              exits the shell\n");
		printf("set VAR STRING    assign STRING to VAR\n");
		printf("print VAR         display contents of VAR\n");
		printf("run SCRIPT.TXT    interpret SCRIPT.TXT\n");

		result = 0;
	}
	else if (strcmp(buf0,"quit")==0) {
		result = 99; // exit shell code
	}
	else if (strcmp(buf0,"set")==0) {
		if (strlen(buf1)<1 || strlen(buf2)<1) return 1; // set error

		add(strdup(buf1), strdup(buf2));
	}
	else if (strcmp(buf0,"print")==0) {
		if (strlen(buf1)<1) return 2; // print error

		printf("%s\n", get(buf1));
	}
	else if (strcmp(buf0,"run")==0) {
		if (strlen(buf1)<1) return 3; // run error
		//printf("interpreter detects run command!\n");
		result = run(buf1);
	}
	else if (strcmp(buf0, "exec") == 0) {
		//command exists
	}
	else {
		result = 98; // command does not exist
	}

	return result;
}

int interpreter2(char buf0[], char buf1[], char buf2[], char buf3[]) {
	int result = 0; // no errors
	
	FILE* ptr1;
	FILE* ptr2; 
	FILE* ptr3;
	if (strcmp(buf0, "exec") == 0) {

		//first buffer
		//create file pointers for each and add to RAM
		if (strcmp(buf1, "") != 0) {
			
			ptr1 = fopen(buf1, "rt");
			if (ptr1 == NULL)
				return 4; //file not found
			else
				
				myinit(ptr1);
		}
		else //first parameter not given
			return 5; //no parameter given error

		//second buffer can be empty
		if (strcmp(buf2, "") != 0) {

			ptr2 = fopen(buf2, "rt");
			if (ptr2 == NULL)
				return 4; //file not found
			else
				myinit(ptr2);
		}

		//third buffer can be empty
		if (strcmp(buf3, "") != 0) {
			
			ptr3 = fopen(buf3, "rt");
			if (ptr3 == NULL)
				return 4; //file not found
			else
				
				myinit(ptr3);
		}



		





		//now that we gathered the file pointers for each program. We need to assign them to RAM.

		//printRAM();

		//----------------------------------------------------------------

		//printReadyQ();
		
		


		//calling kernel's scheduler
		scheduler();

		//printRAM();
	}

}
