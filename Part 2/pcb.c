#include <stdio.h>
#include "pcb.h"
/*whenever a program is launched, a PCB is created*/


/*annotation: PCB's ptr and Ram's ptr both point to 
* program's first line, but after the first quanta, 
* RAM's ptr doesn't change but PCB's ptr points to next line
* RAM's ptr doesn't change but PCB's ptr points to next line
*/

//makePCB

PCB* makePCB(FILE* p) {
	if (p == NULL) {
		printf("The pointer passed is null.\n");
		return NULL;
	}
	PCB* a = malloc(sizeof(PCB));
	a->PC = p;
	return a;
}