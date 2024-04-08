#include "firstPass.h"

void secondPass(infoTable* first, line_table* first_sym, FILE* fp);

int discoverOperandTypeSecondPass(char* op);

char* buildRegisterBinaryCode(char* reg1, char* reg2);