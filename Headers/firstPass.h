#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTable.h"
#include "infoTable.h"

#define TYPE0 0
#define TYPE1 1
#define TYPE2 2
#define TYPE3 3
#define TYPE_ERROR -1

line_table firstPass(FILE*);
line_table * make_symbol_table(FILE*);
int discoverOperandType(const char*);
int isLabel(const char*);
int isArrayAddress(const char*);
int isRegisterName(const char*);
