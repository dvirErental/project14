#include <stdio.h>
#include <string.h>
#include "general.h"
#include "nodes.h"
#define MAX_LINE_LENGTH 81
#define MAX_WORD_LENGTH 10

FILE* preAssemble(FILE*);/*the pre-assembler get input from a file ant return the post pre assembly file*/

int createMacro(FILE*, char*, int, int);/*create a macro*/
