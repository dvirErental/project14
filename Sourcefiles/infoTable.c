
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

int isValidDataString(const char *str) {
    // מחזיר אפס אם המחרוזת חוקית, אחרת מחזיר את המספר הראשון שלא הצליחנו לקרוא
    char *endptr;
    strtol(str + 4, &endptr, 10);
    while (isspace(*endptr)) endptr++; // דחיפות מרווחים
    while (*endptr != '\0') {
        if (*endptr != ',' && !isspace(*endptr)) // בודק אם יש תו שאינו פסיק או רווח
            return 0;
        strtol(endptr + 1, &endptr, 10); // הולך למספר הבא
        while (isspace(*endptr)) endptr++; // דחיפות מרווחים
    }
    return 1;
}
infoTable* createDataLine(int address, char* sourceCode){
    //קשה לקרוא את הקוד, תוודא שעשית את כל מה שצריך:
    // חצי השני של החלק התשיעי באלגוריתם המעבר הראשון.
    infoTable* temp;

    int numbers[40];
    int count;
    char *token;
    char *mutable_str = strdup(sourceCode + 4); // מתחיל אחרי המילה "data"
    token = strtok(mutable_str, ", ");
    count = 0;
    while (token != NULL) {
        numbers[count] = atoi(token);
        temp -> binaryCode[count] = translateToTwosCompliment(numbers[count],NUM_OF_BITS);
        temp->address[count]=address+count;
        (count)++;
        token = strtok(NULL, ", ");
    }
    free(mutable_str);
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

int executeCommand(char* line, int index, int op1, int op2){
    char** binaryWords = mallocError(sizeof(char)*MAX_WORD_LENGTH*(MAX_COMMAND_LENGTH));
    char** words = mallocError(sizeof(char)*MAX_WORD_LENGTH*(MAX_COMMAND_LENGTH+1));
    if(index == 0)
        sscanf(line, "%s%s%s%s", words[0], words[1], words[2], words[3]);
    else
        sscanf(line, "%s%s%s", words[0], words[1], words[2]);
    char* opCode = translateToTwosCompliment(isCommand(words[index]), BITS_IN_OPCODE);
    char* op1Binary = translateToTwosCompliment(op1, BITS_IN_OP1);
    char* op2Binary = translateToTwosCompliment(op2, BITS_IN_OP2);
    char* are = "00";
    strcpy(words[0], strcat(strcat(strcat("0000", opCode),
                                   strcat(op1Binary, op2Binary)), are));
    /*this translates the COMMAND NAME to binary, still need to translate the operands*/
}