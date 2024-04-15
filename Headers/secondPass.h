#include "firstPass.h"

void secondPass(FILE*, char*);

int discoverOperandTypeSecondPass(char* op);

char* buildRegisterBinaryCode(char* reg1, char* reg2,char* are);

int theIndexArray(char* word);

char* discoverARE(char* op);
int isArrayAddressSecondPass(char* op);
char* extractSubstringUntilBrackets(char* str);

void buildOutPut(infoTable* firstInfo, line_table* firstSym, char*) ;

char encodeBitsPair(int bit1, int bit2) ;

void encodeBits(char bits[14], FILE* fp) ;

void buildOB(infoTable* firstInfo, char*) ;

void buildExt(line_table* firstSym, char*);

void buildEnt(line_table* firstSym, char*);
