typedef struct PCB_REC {
	FILE *PC;
	FILE *startLine;
	int start; // startAddressRAM
	struct PCB_REC *next;
	int pageTable[10]; //index=page #, value=frame #.
	int PC_page, PC_offset, pages_max;
	char * fileName;
} PCB;

void addToReady(PCB *p);
PCB *getFromReady();
PCB *makePCB(FILE *p, int startAddressRAM);
PCB *getHead();
void printPCB();
void printPageTable(PCB *p);
void initPageTable(PCB * p);
PCB * findPCBinRam(int ramIndex);