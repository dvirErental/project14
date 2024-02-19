#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "general.h"
#include "table.h"
line_table firstPass(FILE*);
line_table * make_symbol_table(FILE*);
int discoverOperandType(const char*);
int isLabel(const char*);
int isArrayAddress(const char*);
int isRegisterName(const char*);
