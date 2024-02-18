
#include "infoTable.h"

infoTable* first;

infoTable* makeInfoTable(int address, char* sourceCode, int num){
    first = mallocError(sizeof(infoTable));
    first->address = address;
    first -> sourceCode

}
