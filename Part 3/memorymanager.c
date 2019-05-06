#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "pcb.h"
#include "memorymanager.h"
#include "ram.h"
#include "kernel.h"



//my function:
int countLines(FILE *fileptr) {
	int count_lines = 0;
	char chr;
	chr = getc(fileptr);
	while (chr != EOF)
	{
		//Count whenever new line is encountered
		if (chr == '\n')
		{
			count_lines = count_lines + 1;
		}
		//take next character from file.
		chr = getc(fileptr);
	}
	count_lines++;
	fclose(fileptr); //close file.
	//printf("There are %d lines in a file\n", count_lines);
	return count_lines;
}

int countTotalPages(FILE *f) {
	FILE *bufptr = fdopen(dup (fileno(f)), "r");
	int numOfLines = countLines(bufptr);
	//need to floor it!!
	int a = numOfLines / 4;
	int b = numOfLines % 4;

	if (b == 0) {
		//printf("%d pages are assigned\n", a);
		return a;
	}
	else {
		//printf("%d pages are assigned\n", a+1);
		return a + 1;
	}

}


FILE* findPage(int pageNumber, FILE*f) {
	FILE *fp2 = fdopen(dup(fileno(f)), "r");
	char w[20];
	int linesToSkip = (pageNumber) * 4; //page 0 = first line, page 1=fifth line
	int i = 0;
	while (i < linesToSkip && fgets(w, 20, fp2) != NULL) {
		//printf("%s\n", w);
		i++;
	}
	//printf("INSIDE fp2 at: %d\n", ftell(fp2));
	rewind(f);
	//printf("INSIDE f at %d\n", ftell(f));
	return fp2;
}

//Use FIFO technique to search ram[] for a frame not equaling NULL
//return the index number & assign it to the frame
//else return -1
int findFrame(FILE *page) {
	for (int i = 0; i < 10; i++) {
		if (ram[i] == NULL) {
			ram[i] = page;
			return i;
		}
	}
	return -1;
}

//only invoked when findFrame returns -1
//use a random # generator to pick a frame #
//if the frame # does not belong to the pages (perfect) return that frame #
//if it belongs to that PCB then iteratively increase the frame number modulo wise,
//until you come to a frame number not belong to PCB's pages
//return that #
int findVictim(PCB* p) {
	int frameTrial = rand() % 10; //random # from 0 to 9
	//printf("random number is %d\n", frameTrial);
	for (int i = 0; i < 10; i++) {
		if (p->pageTable[i] == frameTrial) { 
			//the frame # picked has this pcb pages,
			//increase frame rand modulo wise.
			frameTrial = (frameTrial + 1) % 10;
			//printf("new frameTrial num is %d\n", frameTrial);
			//run the loop again...
			i = 0; 
		}
	}
	
	return frameTrial;
}

//if the frameNumber is -1
//then we use victimFrame,
//overwrite ram[frameNumber] or ram[victimFrame] w/ FILE *page
int updateFrame(int frameNumber, int victimFrame, FILE *page) {
	if (frameNumber == -1) { //we use victim frame
		ram[victimFrame] = page;
	}
	else { //we use the empty frame
		ram[frameNumber] = page;
	}
}

//the pcb page table must also be updated to reflect changes
//pcb page table of victim must also be updated
//we do this once for the PCB asking for page fault
//we might do it for victim PCB
//p->pageTable[pageNumber] = frameNumber(or= victimFrame)
int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame) {
	if (frameNumber == -1) {
		p->pageTable[pageNumber] = victimFrame;
	}
	else {
		p->pageTable[pageNumber] = frameNumber;
	}
}







//returns 1 if successful launching the program
//returns 0 otherwise
int launcher(FILE *p, char * filename) {

	//copy file into backing store
	char command[50];
	strcpy(command, "cp ");
	strcat(command, filename);
	strcat(command, " BackingStore");
	system(command);
	//close original file pointers in pwd
	fclose(p);
	//open the file pointer in backing store folder
	system("cd BackingStore");
	FILE *ptr = fopen(filename, "rt");


	//algorithm for loading 1 text file:
	int c = countTotalPages(ptr);
	rewind(ptr);
	int startFrame[2];
	//initiate loading 2 pages at the beginning
	for (int i = 0; i < 2; i++) {
		//tmp is what needs to be stored in RAM
		FILE * tmp = findPage(i, ptr);
		startFrame[i] = findFrame(tmp);
		if (c == 1) //if one page just assign one frame only
			break;
	}
	//printf("frames assigned are: %d AND %d\n", startFrame[0], startFrame[1]);
	printRam();
	myinit(ptr, startFrame, c, filename);
	return 1;

}

