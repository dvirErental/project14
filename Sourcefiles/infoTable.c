
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

infoTable* createDataLine(int address, char* sourceCode, int* num){
    infoTable* temp;
    temp = mallocError(5*sizeof(infoTable));
    int i;
    while(num[i]< (sizeof(num) / sizeof(num[0]))){
        temp -> binaryCode[i] = translateToTwosCompliment(num[i],NUM_OF_BITS);
        i++;
        temp->address[i]=address+i;
    }
    temp -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(temp->sourceCode, sourceCode);
    temp -> next= NULL;
}
