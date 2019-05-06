#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

int parse(char buffer[], char arg0[], char arg1[], char arg2[]) {
	int i = 0, j;

	// skip white space
	
	while(i<1000 && buffer[i]==' ') i++;

	// extract argo0
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg0[j] = buffer[i];
		j++; i++;
	}

	arg0[j] = '\0';
	//printf("print arg0 %s\n", arg0);

	while(i<1000 && buffer[i]==' ') i++;

	// extract arg1
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg1[j] = buffer[i];
		j++; i++;
	}

	arg1[j] = '\0';

	while(i<1000 && buffer[i]==' ') i++;

	// extract arg2
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg2[j] = buffer[i];
		j++; i++;
	}

	arg2[j] = '\0';

	while(i<1000 && buffer[i]==' ') i++;
    //printf("[%s] [%s] [%s]\n", arg0, arg1, arg2);

	// check if there is more data (illegal)
	
	if (i==1000 || buffer[i]=='\n' || buffer[i]=='\r' || buffer[i]=='\0')
		return 1; // completed successfully (true)
	else
		return 0;
}

int prompt(char buffer[]) {
	//printf("BUFFER IS %s\n", buffer);
	char buf0[100], buf1[100], buf2[100];
	int result = 0;

	result = parse(buffer,buf0,buf1,buf2);
	//printf("BUF0 is %s\n", buf0);
	result = interpreter(buf0,buf1,buf2);

	if (result == 99) return 99;
	if (result == 98) printf("Command does not exist\n");
	if (result ==  1) printf("Wrong number of set parameters\n");
	if (result ==  2) printf("Wrong number of print parameters\n");
	if (result ==  3) printf("Run is  missing filename\n");
	if (result ==  4) printf("Script filename not found\n");

	return 0;
}

int parse2(char buffer[], char arg0[], char arg1[], char arg2[], char arg3[]) {
	int i = 0, j;

	// skip white space

	while (i < 1000 && buffer[i] == ' ') i++;

	// extract argo0

	j = 0;

	while (i < 1000 && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r') {
		arg0[j] = buffer[i];
		j++; i++;
	}

	arg0[j] = '\0';

	while (i < 1000 && buffer[i] == ' ') i++;

	// extract arg1

	j = 0;

	while (i < 1000 && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r') {
		arg1[j] = buffer[i];
		j++; i++;
	}

	arg1[j] = '\0';

	while (i < 1000 && buffer[i] == ' ') i++;

	// extract arg2

	j = 0;

	while (i < 1000 && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r') {
		arg2[j] = buffer[i];
		j++; i++;
	}

	arg2[j] = '\0';

	while (i < 1000 && buffer[i] == ' ') i++;

	//extract arg3

	j = 0;

	while (i < 1000 && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r') {
		arg3[j] = buffer[i];
		j++; i++;
	}

	arg3[j] = '\0';

	while (i < 1000 && buffer[i] == ' ') i++;

	

	

}




int prompt2(char buffer[]) {
	
	char buf0[100], buf1[100], buf2[100], buf3[100];
	int result = 0;

	result = parse2(buffer, buf0, buf1, buf2, buf3);
	//printf("[%s] [%s] [%s] [%s]\n", buf0, buf1, buf2, buf3);
	result = interpreter2(buf0, buf1, buf2, buf3);
	if (result == 4)
		printf("file not found error.\n");
	if (result == 5)
		printf("no parameter is given to be opened.\n");
	return 0;


}





