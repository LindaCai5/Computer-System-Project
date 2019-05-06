#include <stdio.h>


FILE* ram[10]; //array of file pointers
/* do not load mysh into RAM , only programs from exec */
//basically file pointer assigning & file reading
/*when a file is loaded into RAM
* fopen the script
* find the next available cell in ram[]
* assign the FILE pointer from fopen to that cell
* To read a line from program do fgets(ram[k], buffer, limit)
* when program finishes, do fclose (ram[k], and then ram[k] = NULL;
*/

//addToRAM
int addToRAM(FILE *p) {
	if (p == NULL) {
		printf("File pointer passed is null\n");
		return 1;
	}
	
	for (int i = 0; i < 10; i++) {
		if (ram[i] == NULL) {
			ram[i] = p;
			return 0; //successfuly added
		}
		else
			continue;
	}
	printf("Ram is FULL.\n");
	return 1;
}

printRAM() {
	for (int i = 0; i < 10; i++) {
		printf("at %d and RAM has [ %d ].\n", i, ram[i]);
	}
}

int sizeRam() {
	int size = 0;
	for (int i = 0; i < 10; i++) {
		if (ram[i] != 0)
			size++;
	}
	return size;
}

void freeMem(FILE* p) {
	//printf("free mem here, p is %d\n", p);
	
	for (int i = 0; i < 10; i++) {
		//printf("ram has ... [%d]\n", ram[i]);
		if (p == ram[i]) {
			fclose(ram[i]);
			ram[i] = NULL;
		}
			
	}
}