#include<stdlib.h>
#include<stdio.h>
#include"memorymanager.h"
#include "pcb.h"




PCB *head = NULL, *tail = NULL;

void printPageTable(PCB *p) {
	printf("printing Page Table...\n");
	for (int i = 0; i < 10; i++) {
		printf(" [[page/ind: %d, frame: %d]]\n", i, p->pageTable[i]);
	}
}

void initPageTable(PCB * p) {
	for (int i = 0; i < 10; i++) {
		p->pageTable[i] = -1;
	}
}

//print PCB head
void printPCB() {
	PCB *temp = head;

	printf("Addr:");

	while (temp != NULL) {
		printf("pcb start: %d \n", temp->start);
		printf("pcb max pages: %d \n", temp->pages_max);
		printf("pcb pages at: %d \n", temp->PC_page);
		printf("pcb offset: %d \n", temp->PC_offset);
		printf("pcb filename is %s\n", temp->fileName);
		printPageTable(temp);
		temp = temp->next;
	}

	printf("\n");
}

PCB *makePCB(FILE *p, int startAddressRAM) {
	PCB *pcb;

	if (p == NULL) return NULL;

	pcb = (PCB *)malloc(sizeof(PCB));
	if (pcb == NULL) return NULL;

	pcb->PC = p;
	pcb->start = startAddressRAM;
	pcb->next = NULL;
}

void addToReady(PCB *p) {
	p->next = NULL;
	
	if (head == NULL) {
		head = p;
		tail = p;
	}
	else {
		tail->next = p;
		tail = p;
	}
	
}

PCB *getHead() {
	return head;
}
PCB *getFromReady() {
	PCB *temp;

	if (head == NULL) return NULL;

	temp = head;
	head = head->next;
	temp->next = NULL;

	if (head == NULL) tail = NULL;

	return temp;
}

PCB * findPCBinRam(int ramIndex) {
	PCB * tmp = head;
	while (tmp != NULL) {
		//search its page table
		for (int i = 0; i < 10; i++) {
			if (tmp->pageTable[i] == ramIndex) {
				return tmp->fileName;
			}
		}
		tmp = tmp->next;
	}
}

