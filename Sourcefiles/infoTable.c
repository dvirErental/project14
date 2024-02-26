
#include "infoTable.h"

infoTable* first;

void makeInfoTable(int address, char* sourceCode, char*){
    first = mallocError(sizeof(infoTable));
    first -> address = address;
    first -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(first->sourceCode, sourceCode);
    strcpy(first->binaryCode, translateToBinary(num));
    first -> next = NULL;
}

void addLineToInfoTable(int address, char* sourceCode, int num){
    infoTable* temp = first;
    while(temp != NULL)
        temp = temp->next;

}

infoTable* createLine(int address, char* sourceCode, int num){
    infoTable* next;
    next = mallocError(sizeof(infoTable));
    next-> address = address;
    next -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(next->sourceCode, sourceCode);
    next ->
}
