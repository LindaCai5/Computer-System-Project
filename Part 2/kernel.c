#include "shell.h"
#include <stdio.h>
#include "pcb.h"
#include "interpreter.h"
#include <string.h>
#include "ram.h"
#include "kernel.h"
#include "cpu.h"
#include <stdbool.h>



//Ready Queue data structure
typedef struct node { //FIFO & RR
	PCB* content;
	struct node* next;
}node;
node* head;
node* tail;

//addToReady FIFO - private - only be called by functions in Kernel.
void addToReady(PCB* pcb) {
	if (pcb == NULL) {
		printf("The pcb passed is null.\n");
	}
	//2 cases: null ready list & list w/ node already
	//case1: base case
	if (head == NULL) {
		node * first = malloc(sizeof(node));
		first->content = pcb;
		first->next = NULL;
		head = first;
		tail = first;
		
	}
	//case2: step case
	else {
		node* cur = head;
		//advance the pointer
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = malloc(sizeof(node));
		cur->next->content = pcb;
		cur->next->next = NULL;
		tail = cur->next;
		
	}
	
}


//print readyqueue method
void printReadyQ() {
	if (head == NULL && tail == NULL) {
		printf("ready list is empty!\n");
	}
	
	//printf("printing the ready list.\n");
	node * i = head;
	printf("pcb pointer addresses about to be printed: \n");
	
	while (i != NULL) {
		printf("[%d]\n", i->content);
		printf("file pointer address [%d].\n", i->content->PC);
		if (i->next == NULL) {
			break;
		}
		i = i->next;
	}
}

addToTail(node* a) {

	node* cur = a;
	head = cur->next;
	cur->next = NULL;
	tail->next = cur;
	tail = cur;

}

removeAway(node* a) {
	//base case(only 1 node left)

		head = a->next;
		a->next = NULL;	
		freeMem(a->content->PC);
}


//myinit
/* calls addToRAM to add the pointer to next available cell in ram[]
* calls PCB to create a PCB using malloc
* calls addToReady to add the PCB onto the ready queue
*/

//assume no null ptr passed
void myinit(FILE* p) {
	//add pointer to RAM
	int suc;
	suc = addToRAM(p);
	if (suc == 1)
		printf("ptr failed to be added to RAM.\n");

	//makePCB
	PCB* block = makePCB(p);
	addToReady(block);
}

//scheduler : called after all programs have been loaded into simulator
/* it checks if CPU is available
* it copies the PCB PC pointer to to CPU IP pointer 
*it calls the run quanta function w/in cpu.c to runscript by reading quanta
*lines from the file using IP into IR, which calls interpreter(IR)
*if not finished (rmb to update the PCB PC pointer to the new line read
* and place the PCB at the end of the Ready Queue
* also it has the responsibility to adjust head and tail for addition at the end
*
*
*/

void removeOne(node* a) {
	head = NULL;
	tail = NULL;
	freeMem(a->content->PC);
}

void scheduler() {
	char buf[100];
	//set the quanta
	thisCPU.quanta = 2;
	//now we have a CPU to work with

	int state;
	

	//loop
	//1 PCB each time
	//when to stop the looping through readyQueue? When there is no more PCB left in there.
	
		
		//printf("initial PCB's PC is at %d\n", ftell(head->content->PC));
		
		/*test case to see if updating PCB PC ptr is successful!
		printf("outside runn scope: pcb ptr should also be at %d\n", ftell(head->content->PC));
		printf("should print the thrid line...\n");
		printf("%s\n", fgets(buf, 999, head->content->PC));*/
		
		int undone = sizeRam();//need to be changed!!! need to be the size of parameters passed , could be 1 or 2 or 3.
		//printf("SIZE OF RAM IS %d\n", undone);
		if (undone > 1) {
			while (undone != 0) {
				thisCPU.IP = head->content->PC;
				state = runn(head->content->PC);
				if (state == 0) { //file done
					//printf("a file is now finished.\n");
					removeAway(head);
					undone--;
				}
				else if (state == 1) {
					addToTail(head);
				}
				//printReadyQ();
			}
		}
		else if (undone == 1) {
			int un = 1;
			while (un != 0) {
				thisCPU.IP = head->content->PC;
				state = runn(head->content->PC);
				if (state == 0) {
					removeOne(head);
					break;
				}
				else if (state == 1) {
					continue;
				}
				//printReadyQ();
			}
		}

	
}

int main(void) {


	initShellMemory();
	printf("Kernel 1.0\n");
	printf("Welcome to the Linda shell!\n");
	printf("Version 1.0 Created January 2019\n");

	char buffer[1000];
	int done = 0, result = 0;
	char buff[100];
	while (!done) {
		printf("$ ");
		fgets(buffer, 999, stdin);

		//testing the first 4 characters.

		for (int i = 0; i < 4; i++) {
			buff[i] = buffer[i];
		}

		if (strcmp(buff, "exec") == 0) {
			//printf("shell recognizes exec 4 words!\n");
			prompt2(buffer);
		}
		else {
			result = prompt(buffer);
		}

		if (result == 99) done = 1;
	}

	printf("Good bye.\n");
	return 0;
}