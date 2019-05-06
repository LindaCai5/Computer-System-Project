#include<stdlib.h>
#include<stdio.h>
#include "memorymanager.h"
#include "shell.h"
#include "ram.h"
#include "cpu.h"
#include "pcb.h"
//need to update pagetable!

FILE * skipLines(int pageNumber, char * filename) {
	FILE * newptr = fopen(filename, "r");
	int linesToSkip = (pageNumber) * 4; //page 0 = first line, page 1=fifth line
	//printf("%d lines to SKIP...\n", linesToSkip);
	char w[20];
	for (int i = 0; i < linesToSkip; i++) {
		fgets(w, 20, newptr);
		//printf("%s\n", w);
	}
	return newptr;
}


int findVic(PCB* p) {
	int frameTrial = rand() % 10; //random # from 0 to 9
	printf("random number is %d\n", frameTrial);
	for (int i = 0; i < 10; i++) {
		if (p->pageTable[i] == frameTrial) {
			printf("trying another random number...");
			//the frame # picked has this pcb pages,
			//increase frame rand modulo wise.
			frameTrial = (frameTrial + 1) % 10;
			printf("new frameTrial num is %d\n", frameTrial);
			//run the loop again...
			i = 0;
		}
	}
	//printf("returning this frametrial: %d\n", frameTrial);
	return frameTrial;
}


int myinit(FILE *p, int startFrame[2], int maxPages, char * fileName) {
	
	PCB *pcb;
	pcb = makePCB(p, startFrame[0]);
	if (pcb != NULL) {
		addToReady(pcb);
	}
	pcb->startLine = p;
	pcb->fileName = fileName;
	pcb->pages_max = maxPages;
	//track which page and offset the execution is currently at.
	pcb->PC_offset = 0;
	pcb->PC_page = 0;
	initPageTable(pcb);
	pcb->pageTable[0] = startFrame[0];
	pcb->pageTable[1] = startFrame[1];
	printPageTable(pcb);
	return 0;
}

void terminate(PCB *p) {
	clearRAM(p->start);
	free(p);
}

int pagefault(PCB* pcb) {
	//printf("entering pagefault section TRIAL PRINTING RAM:\n");
	//printRam();
	pcb->PC_page++;
	if (pcb->PC_page > pcb->pages_max) {
		//EOF = terminate
		return 99;
	}
	else {
		printf("Page Fault: Run Out of Page to Read In Frame\n");
		//check to see if frame for next one in pagetable is valid
		if (pcb->pageTable[pcb->PC_page] != -1) {
			printf("Page Found in Ram!\n");
			//next page indeed has a frame number
			int frame = pcb->pageTable[pcb->PC_page];
			pcb->PC = ram[frame];
			pcb->PC_offset = 0;
		}
		else {//page not found in ram, go to disk
			//a) finding the page in the backing store
			printf("Page Not Found in Ram!\n");
			
			int pagenum = pcb->PC_page;
			FILE * startt = pcb->fileName;
			FILE *rec = skipLines(pagenum, startt);
			//store rec pointer in ram.

			//b)backing store algorithm

			//b.1) there is free cell in RAM:
			int ind = findFrame(rec);
			if (ind != -1) { //there is space left in RAM
				printf("B1 CASE) There Is Space Left In RAM.\n");
				ram[ind] = rec;
				pcb->pageTable[pcb->PC_page] = ind;
				
			}
			//b.2) no free cell in RAM - find victim:
			else {
				printf("B2 CASE) There Is No Space Left In Ram.\n");
				printf("Ram BEFORE removing victim:\n");
				printRam();
				printf("Page Table BEFORE finding victim:\n");
				printPageTable(pcb);
				int a = findVic(pcb); //frame number selected
				ram[a] = rec;
				printf("Ram Updated:\n");
				printRam();
				pcb->pageTable[pcb->PC_page] = a;
				
				printf("Page Table Updated:\n");
				printPageTable(pcb);
			}
		}
	}
	
}


void scheduler() {
	PCB *pcb;
	int result;

	// initialize CPU
	initCPU();

	// execute the processes
	while (getHead() != NULL) { //execute one PCB at a time
		// printPCB(); // for debugging

		pcb = getFromReady();

		if (pcb != NULL) {
			setCPU(pcb->PC);
			//need to set the CPU offset
			printf("before runcpu: pcb offset at %d.\n", pcb->PC_offset);
			setOffset(pcb->PC_offset);

			//IMPORTANT PART --- EXECUTION:
			result = runCPU(2);

			pcb->PC_offset = result;
			printf("after runcpu: pcb offset at %d.\n", pcb->PC_offset);
			
			if (result == -1) {
				printf("scheduler noticing page fault...\n");
				result = pagefault(pcb);
				if (pcb->PC_offset == -1)
					pcb->PC_offset = 0;
			}
			if (result == -99) terminate(pcb);
			else addToReady(pcb);
		}
	}
}

//initialize every cell of the array to null
void boot() {
	//initialize frames to null
	for (int i = 0; i < 10; i++) {
		ram[i] = NULL;
	}
	//delete the backing store folder
	system("rm -rf BackingStore");
	//create new directory
	system("mkdir BackingStore");
}

int main() {
	boot();
	
	int result = 0;

	//initRAM();
	initCPU();

	result = shell();

	return result;
}
