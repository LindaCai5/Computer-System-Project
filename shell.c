#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"


int i = 1;

int main() {
	//arr1 records the partb
	char * arr1[50];
	//arr2 records the partc
	char * arr2[50];
	char string2[20][20];
	char string[20][20];
	int i = 0;
	int j = 1;
	int l = 0;
	//for print's partb
	char qqq[20];
	while (1) {	
		char line[100];
		char *lineptr = line;

		//new data structure
		char part1[50];
		char part2[50];
		char part3[50];
		char *parta = part1;
		char *partb = part2;
		char *partc = part3;
		

		printf("Welcome to the Linda Shell!\n");
		printf("Version 1.0 Created January 2019\n");
		printf("$");
		fgets(line, 100, stdin);
		int count_of_space = 0;
		for (int i = 0; i < strlen(line); i++) {
			if (line[i] == ' ')
				count_of_space++;
		}
		//printf("The count of space is %d\n", count_of_space);

		const char s[2] = " ";

		if (count_of_space == 0 || count_of_space == 1 || count_of_space == 2) {
			parta = strtok(line, s);
			partb = NULL;
			partc = NULL;
		}

		if (count_of_space == 1 || count_of_space == 2) {
			partb = parta;
			partb = strtok(NULL, s);
		}
		if (count_of_space == 2) {
			partc = partb;
			partc = strtok(NULL, s);
		}

		//printf("The 3 parts: %s. %s. %s. \n", parta, partb, partc);
		//help or quit
		if (count_of_space == 0 ) {
			interpreter(parta, partb, partc);
		}
		//set 
		else if (count_of_space == 2) {
			strcpy(string[i], partb);
			strcpy(string[j], partc);
			interpreter(parta, partb, partc);
			i += 2;
			j += 2;
		}
		//print
		else if (count_of_space == 1) {
			
			//printf("Partb is %s.\n", partb);
			//"un"concatenate the partb to normal string w/out the /n.
			char t[10];
			char *prt = t;
			char delim[] = "\n";
			char *ptr = strtok(partb, delim);			
			strcpy(string2[l], partb);
			//printf("The STRING IS %s.", string2[l]);
			printvar(string2[l]);
			l++;
		}
	
		


	}
	
	
	return 0;
}
