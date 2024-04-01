
#define NUM_OF_BITS 14
#include <string.h>
#include <ctype.h>
#include "symbolTable.h"


typedef struct infoTable{
    int* address;
    char* sourceCode;
    char* binaryCode[NUM_OF_BITS];
    struct infoTable* next;
}infoTable;

void makeInfoTable(int, char*, int, char*);

void addLineToInfoTable(int, char*, int, char*);

int createDataLine(int, char*);
int isValidDataString(const char *str);

int createStringLine(int, char*, int);

void startInfoTable(infoTable*);

void executeCommandFirstPass(char*, int, int, int, int, int, char*);

char* dataToBinary();
//שני מערכים דו ממדיים  = address והקוד הבינארי לכל מילה
int isNumberValue(const char*);

int searchForMdefine(const char*);
