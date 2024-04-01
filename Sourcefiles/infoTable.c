
#include "infoTable.h"

infoTable* first_info;

void makeInfoTable(int address, char* sourceCode, int num, char* stringAlternative){
    first_info = mallocError(sizeof(infoTable));
    first_info -> address[0] = address;
    first_info -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(first_info->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "")!=0)
        strcpy(first_info->binaryCode[0], translateToTwosCompliment(num, NUM_OF_BITS));
    else
        strcpy(first_info->binaryCode[0], stringAlternative);

    first_info -> next = NULL;
}
void startInfoTable(infoTable* info){
    first_info = mallocError(sizeof(*info));
    first_info = info;
}

void addLineToInfoTable(int address, char* sourceCode, int num, char* stringAlternative){
    infoTable* temp = first_info;
    while(temp != NULL)
        temp = temp->next;
    temp = mallocError(sizeof(infoTable));
    temp-> address[0] = address;
    temp -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(temp->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "") != 0)
        strcpy(temp->binaryCode[0], translateToTwosCompliment(num, NUM_OF_BITS));
    else
        strcpy(temp->binaryCode[0], stringAlternative);

    temp -> next = NULL;
}

void addSetLineToInfoTable(infoTable* info){
    addLineToInfoTable(info->address[0], info->sourceCode,0, info->binaryCode);
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
int createDataLine(int address, char* sourceCode){
    //קשה לקרוא את הקוד, תוודא שעשית את כל מה שצריך:
    // חצי השני של החלק התשיעי באלגוריתם המעבר הראשון.
    infoTable* temp = mallocError(sizeof(infoTable));

    int numbers[40];
    int count;
    char *token;
    char *mutable_str = strdup(sourceCode + 4); // מתחיל אחרי המילה "data"
    token = strtok(mutable_str, ", ");
    count = 0;
    while (token != NULL) {
        numbers[count] = atoi(token);
        strcpy(temp -> binaryCode[count], translateToTwosCompliment(numbers[count],NUM_OF_BITS));
        temp->address[count]=address+count;
        (count)++;
        token = strtok(NULL, ", ");
    }
    free(mutable_str);
    temp -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(temp->sourceCode, sourceCode);
    temp -> next= NULL;
    return address+count;
}

int createStringLine(int address, char* stringToSave, int isFirst){
    int index = 0;
    infoTable* temp = mallocError(sizeof(infoTable));
    while (stringToSave[index] != '"') {
        temp->address[index] = address;
        strcpy(temp->binaryCode[index], (translateToTwosCompliment(stringToSave[index], NUM_OF_BITS)));
        if(isFirst) {
            startInfoTable(temp);
        }
        else{
            addSetLineToInfoTable(temp);
        }
        index++;
        address++;
    }
    temp->address[index] = address;
    strcpy(temp-> binaryCode[index], "00000000000000");
    addSetLineToInfoTable(temp);
    return address+1;
}

void executeCommandFirstPass(char* line, int index, int op1, int op2, int isFirst, int address, char* word){
    char binaryWord[NUM_OF_BITS] = "";
    char* opCode = translateToTwosCompliment(isCommand(word), BITS_IN_OPCODE);
    char* op1Binary = translateToTwosCompliment(op1, BITS_IN_OP1);
    char* op2Binary = translateToTwosCompliment(op2, BITS_IN_OP2);
    char* are = "00";
    strcat(binaryWord, "0000");
    strcat(binaryWord, opCode);
    strcat(binaryWord, op1Binary);
    strcat(binaryWord, op2Binary);
    strcat(binaryWord, are);

    if (isFirst)
        makeInfoTable(address, line, 0, binaryWord);
    else
        addLineToInfoTable(address, line, 0, binaryWord);
}


/*int isNumberValue(const char* word) {
    int num;
    if (searchForMdefine(word))
        return searchForMdefine(word);
    else if (word[0] == '#') {
        num = atoi(&word[1]);
        return num;
    }
    return MIN_NUM;
}*/
/*int searchForMdefine(const char* name){
    line_table *temp = first_Symbol;
    while (temp != NULL){
        if ((strcmp(temp->name,name) == 0) && (strcmp(temp->type, "mdefine") == 0))
            return temp->value;
    }
    return 0;
}*/


/*to be used for executeCommand in secondPass
if (isCommand(words[index])>=0 && isCommand(words[index])<= 4) {
for (goTwice = 0; goTwice < 2; goTwice++){
if (isRegisterName(words[index + 1])) {
registerNum = isRegisterName(words[index + 1]);
binaryWords[goTwice] = "000000";
strcat(binaryWords[goTwice], translateToTwosCompliment(registerNum, BITS_IN_REGISTER_LENGTH));
strcat(binaryWords[goTwice], "11");
}
else if (isNumberValue(words[index+1]) != MIN_NUM){
numberValue = isNumberValue(words[index+1]);

}
index++;
}
}
 */