#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#include "interpreter.h"


// model1 = var
static char model1[10][10];
// model2 = val
static char model2[10][10];


void set(char a[], char b[]) {
	for (int i = 0; i < 10; i++) {
		int compare = strcmp(a, model1[i]);
		//already exist
		if (compare == 0) {
			strcpy(model2[i], b);
			break;
		}
			
		//not exist
		else if (strcmp(model1[i] , "") ==0){
			strcpy(model1[i], a);
			strcpy(model2[i], b);
			break;
		}
		else
			continue;
	}
}
/*
void printArr() {
	printf("printing out the kernel memory...\n");
	for (int i = 0; i < 5; i++) {
		printf("%s %s \n", model1[i], model2[i]);
	}

}

void printModel1() {
	for (int i = 0; i < 10; i++) {
		printf("%s at index %d\n", model1[i], i);
	}
}

void printModel2() {
	printf("displaying the memory...\n")
	for (int i = 0; i < 10; i++) {
		printf("%s at index %d\n", model2[i], i);
	}
}*/

void printvar(char var[]) {

	int found = 0;
	for (int i = 0; i < 10; i++) {
		if (strcmp((model1[i]), var) == 0) {
			printf("%s\n", model2[i]);
			found = 1;
			break;
		}
	}
	//if not found, give an error message.
	if (found == 0)
		printf("Error, there is no %s in the memory. \n", var);
	
}

/*
int main() {
	char t[50] = "var";
	char r[50] = "val";
	char u[50] = "good";
	char q[50] = "bad";
	char k[50] = "var";
	char p[50] = "l";
	char o[50] = "yyy";
	char g[50] = "g";

	set(t, r);
	printArr();
	printf("model1 printing...\n");
	printModel1();
	printf("model2 printing...\n");
	printModel2();

	printf("-------------\n");
	set(u,q);
	printArr();
	printf("model1 printing...\n");
	printModel1();
	printf("model2 printing...\n");
	printModel2();

	printf("-------------\n");
	set(t, p);
	printArr();
	printf("model1 printing...\n");
	printModel1();
	printf("model2 printing...\n");
	printModel2();

	printf("-------------\n");
	set(o, g);
	printArr();
	printf("model1 printing...\n");
	printModel1();
	printf("model2 printing...\n");
	printModel2();
	
	printf("testing printvar: %t \n", t);
	printvar(t);
	printf("should print l\n");
	printvar(u);
	printf("should print bad\n");
	printvar(o);

	return 0;
}*/




	











