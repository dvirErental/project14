
#include "infoTable.h"

infoTable* first_info;

void makeInfoTable(int address, char* sourceCode, int num){
    first_info = mallocError(sizeof(infoTable));
    first_info -> address = address;
    first_info -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(first_info->sourceCode, sourceCode);
    strcpy(first_info->binaryCode, translateToTwosCompliment(num));
    first_info -> next = NULL;
}

void addLineToInfoTable(int address, char* sourceCode, int num){
    infoTable* temp = first_info;
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
