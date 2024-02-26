
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
    char* firstNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* secondNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* thirdNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* fourthNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* fifthNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* sixthNum= mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* seventhNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* eighthNum = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    int nums;
    char* numsInput;
    int location;
    int  j;
    line_table* thisSymbol=first_Symbol;
    numsInput = strstr(sourceCode, ".data");
    nums=sscanf(numsInput+strlen(".data"), "%s%s%s%s%s%s%s%s", firstNum, secondNum, thirdNum, fourthNum, fifthNum, sixthNum, seventhNum, eighthNum);
    num = mallocError(nums*sizeof(int));
    if (firstNum != NULL){
        if (firstNum[0] >= '0' && firstNum[0] <= '9'){
            location = searchList(firstNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[0] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", firstNum);
                exit(1);
            }
        }
        num[0] = atoi(firstNum);
    }
    if (secondNum != NULL){
        if (secondNum[0] >= '0' && secondNum[0] <= '9'){
            location = searchList(secondNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[1] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", secondNum);
                exit(1);
            }
        }
        num[1] = atoi(secondNum);

    }
    if (thirdNum != NULL){
        if (thirdNum[0] >= '0' && thirdNum[0] <= '9'){
            location = searchList(secondNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[2] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", thirdNum);
                exit(1);
            }
        }
        num[2] = atoi(thirdNum);

    }
    if (fourthNum != NULL){
        if (fourthNum[0] >= '0' && fourthNum[0] <= '9'){
            location = searchList(fourthNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[3] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", fourthNum);
                exit(1);
            }
        }
        num[3] = atoi(fourthNum);

    }
    if (fifthNum != NULL){
        if (fifthNum[0] >= '0' && fifthNum[0] <= '9'){
            location = searchList(fifthNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[4] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", fifthNum);
                exit(1);
            }
        }
        num[4] = atoi(fifthNum);

    }
    if (sixthNum != NULL){
        if (sixthNum[0] >= '0' && sixthNum[0] <= '9'){//
            location = searchList(sixthNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[5] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", sixthNum);
                exit(1);
            }
        }
        num[5] = atoi(sixthNum);

    }
    if (seventhNum != NULL){
        if (seventhNum[0] >= '0' && seventhNum[0] <= '9'){
            location = searchList(seventhNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[6] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", seventhNum);
                exit(1);
            }
        }
        num[6] = atoi(seventhNum);

    }
    if (eighthNum != NULL){
        if (eighthNum[0] >= '0' && eighthNum[0] <= '9'){
            location = searchList(eighthNum);
            for (j = 0; j < location; j++)
                thisSymbol = thisSymbol->next;
            if (strcmp(thisSymbol->type,"mdefine") == 0){
                num[7] = thisSymbol->value;
            }
            else{
                printf("error: %s is not a number", eighthNum);
                exit(1);
            }
        }
        num[7] = atoi(eighthNum);

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
