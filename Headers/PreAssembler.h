#include <stdio.h>
#include <string.h>
#include "general.h"
#include "nodes.h"
#define MAX_LINE_LENGTH 81
#define ENDMCR_LETTERS 7
void copyFile(FILE*);
FILE* preAssemble(FILE*);
int createMacro(FILE*, char*, int, int);
int skip(int, FILE*);
int isFileIndication(const char*);
extern node* first;