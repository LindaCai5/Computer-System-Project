// Public functions


extern FILE *ram[10];

void initRAM();
int addToRAM(FILE *p); // return startAddress or error codes
void clearRAM();
void printRam();
