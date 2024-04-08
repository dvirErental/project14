#include "secondPass.h"

char encodeBitsPair(int bit1, int bit2) ;

void encodeBits(int bits[14], FILE* fp) ;

void buildOB(infoTable* firstInfo) ;

void buildExt(line_table* firstSym);

void buildEnt(line_table* firstSym);
