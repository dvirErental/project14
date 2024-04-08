
#define NUM_OF_BITS 14
#include <string.h>
#include <ctype.h>
#include "symbolTable.h"


typedef struct infoTable{
    int address[MAX_NUM_OF_WORDS];
    char* sourceCode;
    char binaryCode[MAX_NUM_OF_WORDS][NUM_OF_BITS];
    struct infoTable* next;
}infoTable;

void makeInfoTable(int, char*, int, char*);

void addLineToInfoTable(int, char*, int, char*);

int createDataLine(int, char*);

int isValidDataString(const char *str);

int createStringLine(int, char*);

void startInfoTable(infoTable*);

void executeCommandFirstPass(char*, int, int, int, char*);

void addSetLineToInfoTable(infoTable* info);

void printInfoTable();

void addCompleteLineToInfoTable(infoTable* info);

infoTable* searchInfoTable(char*);

void freeInfoLine(infoTable *line);

void freeInfoTable(infoTable *head);

char* dataToBinary();
//שני מערכים דו ממדיים  = address והקוד הבינארי לכל מילה
int isNumberValue(const char*);

int searchForMdefine(const char*);
