
#define NUM_OF_BITS 14
#include <string.h>
#include <ctype.h>
#include "symbolTable.h"


typedef struct infoTable{
    int address[MAX_NUM_OF_WORDS];
    char sourceCode[MAX_LINE_LENGTH];
    char binaryCode[MAX_NUM_OF_WORDS][NUM_OF_BITS+1];/*for \0*/
    struct infoTable* next;
}infoTable;

void makeInfoTable(int, char*, int, char*);

void addLineToInfoTable(int, char*, int, char*);

int createDataLine(int, char*);

int isValidDataString(const char *str);

int createStringLine(int, char*);

void executeCommandFirstPass(char*, int, int, int, char*);

void addSetLineToInfoTable(infoTable* info);

void addCompleteLineToInfoTable(infoTable* info);

infoTable* searchInfoTable(char*);

infoTable* getFirstLine();

void freeInfoTable(void);

void printInfoTable();

