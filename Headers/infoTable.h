
#define NUM_OF_BITS 14
#include <string.h>
#include "general.h"


typedef struct infoTable{
    int* address;
    char* sourceCode;
    char* binaryCode[NUM_OF_BITS];
    struct infoTable* next;
}infoTable;

void makeInfoTable(int, char*, int);

void addLineToInfoTable(int, char*, int);

infoTable* createLine(int, char*, int);