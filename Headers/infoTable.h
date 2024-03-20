
#define NUM_OF_BITS 14
#include <string.h>
#include "symbolTable.h"


typedef struct infoTable{
    int* address;
    char* sourceCode;
    char* binaryCode[NUM_OF_BITS];
    struct infoTable* next;
}infoTable;

void makeInfoTable(int, char*, int);

void addLineToInfoTable(int, char*, int);

infoTable* createDataLine(int, char*);

void createStringLine(int, char*, int, int);

void startInfoTable(infoTable*);

int executeCommand(char*, int, int, int);

char* dataToBinary()
//שני מערכים דו ממדיים  = address והקוד הבינארי לכל מילה