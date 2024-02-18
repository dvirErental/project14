#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "general.h"
#include "table.h"
line_table firstPass(FILE* fp);
line_table * make_symbol_table(FILE* fp);
