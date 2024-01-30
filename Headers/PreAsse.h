#include <stdio.h>
#include <string.h>
#include "datastrct.h"
#include "datastrct.c"
#define MAX_LINE_LENGTH 81
void copyFile(FILE*);
void copyMacs(FILE*);
void createMacro(FILE*, char*, int);