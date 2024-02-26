
#include "infoTable.h"

infoTable* first_info;

void makeInfoTable(int address, char* sourceCode, int num){
    first_info = mallocError(sizeof(infoTable));
    first_info -> address[0] = address;
    first_info -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(first_info->sourceCode, sourceCode);
    strcpy(first_info->binaryCode, translateToTwosCompliment(num));
    first_info -> next = NULL;
}
void startInfoTable(infoTable* info){
    first_info = mallocError(sizeof(info));
    first_info = info;
}

void addLineToInfoTable(int address, char* sourceCode, int num){
    infoTable* temp = first_info;
    while(temp != NULL)
        temp = temp->next;

}
void addSetLineToInfoTable(infoTable* info){
    infoTable* temp;
    while(temp -> next != NULL)
        temp = temp->next;
    temp->next = mallocError(sizeof(info));
    temp->next = info;
}

infoTable* createDataLine(int address, char* sourceCode){
    int* num;
    char** words = mallocError(sizeof(int)*MAX_WORD_LENGTH*10);
    int nums;
    char* numsInput;
    int location;
    int  j;
    int k;
    line_table* thisSymbol=first_Symbol;
    numsInput = strstr(sourceCode, ".data");
    nums=sscanf(numsInput+strlen(".data"), "%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6], words[7]);
    num = mallocError(nums*sizeof(int));
    while (words[k] != NULL){
        if (words[k][0] >= '0' && words[k][0] <= '9'){
            location = searchList(words[k]);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[k] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", words[0]);
                exit(1);
            }
        }
        num[k] = atoi(words[k]);
    }
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

void createStringLine(int address, char* stringToSave, int index, int isFirst){
    infoTable* temp;
    if (stringToSave[index] != '"') {
        temp->address = &address;
        temp->binaryCode[0] = mallocError(sizeof(translateToTwosCompliment(stringToSave[index], NUM_OF_BITS)));
        temp->binaryCode[0] = (translateToTwosCompliment(stringToSave[index], NUM_OF_BITS));
        if(isFirst) {
            startInfoTable(temp);
            return (createStringLine(++address, stringToSave, ++index, false));
        }
        else{
            addSetLineToInfoTable(temp);
            return (createStringLine(++address, stringToSave, ++index, false));
        }
    }
    else {
        temp->address = &address;
        temp -> binaryCode[0] = mallocError(sizeof(char)*(NUM_OF_BITS+1));
        temp-> binaryCode[0] = "00000000000000";
        addSetLineToInfoTable(temp);
        return;
    }
}
