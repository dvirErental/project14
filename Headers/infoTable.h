
#define NUM_OF_BITS 14
#include "general.h"


typedef struct infoTable{
    int address;
    char* sourceCode;
    char binaryCode[NUM_OF_BITS];
    struct infoTable* next;
}infoTable;

infoTable* makeInfoTable(int, char*, int);

void addLineToInfoTable(int, char*, int);