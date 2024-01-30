#include <stdio.h>
#include <string.h>
#include "general.c"
#include "datastrct.c"
#define MAX_LINE_LENGTH 81
#define ENDMCR_LETTERS 7
void copyFile(FILE*);
FILE* preAssemble(FILE*);
void createMacro(FILE*, char*, int, int);
int skip(int, FILE*);
extern node* first;