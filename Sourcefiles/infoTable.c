
#include "infoTable.h"

infoTable* first_info;

void makeInfoTable(int address, char* sourceCode, int num, char* stringAlternative){
    first_info = mallocError(sizeof(infoTable));
    first_info -> address[0] = address;
    first_info -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(first_info->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "")==0)
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
    if (first_info == NULL) {
        makeInfoTable(address, sourceCode, num, stringAlternative);
        return;
    }
    infoTable* temp = first_info;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = mallocError(sizeof(infoTable));
    temp->next-> address[0] = address;
    temp->next -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(temp->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "") == 0)
        strcpy(temp->next->binaryCode[0], translateToTwosCompliment(num, NUM_OF_BITS));
    else
        strcpy(temp->next->binaryCode[0], stringAlternative);

    temp ->next-> next = NULL;
}

void addSetLineToInfoTable(infoTable* info){
    addLineToInfoTable(info->address[0], info->sourceCode,0, info->binaryCode[0]);
}

void addCompleteLineToInfoTable(infoTable* info){
    if (first_info == NULL){
        first_info = mallocError(sizeof(*info));
        first_info = info;
        return;
    }
    infoTable* temp = first_info;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = mallocError(sizeof(infoTable));
    temp->next = info;
}

int isValidDataString(const char *str) {
    // מחזיר אפס אם המחרוזת חוקית, אחרת מחזיר את המספר הראשון שלא הצליחנו לקרוא
    char *endptr;
    char *deleteLabel;
    strcpy(deleteLabel,str);
    strcpy( deleteLabel,cutString(deleteLabel, ':'));
    while (isspace(*deleteLabel)) deleteLabel++; // דחיפות מרווחים
    strtol(deleteLabel + 5, &endptr, 10);
    while (isspace(*endptr)) endptr++; // דחיפות מרווחים
    while (*endptr != '\0') {
        if (*endptr != ',' && !isspace(*endptr)) // בודק אם יש תו שאינו פסיק או רווח
            if (isWord(endptr)) return 1;
            else return 0;
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
    char *mutable_str= mallocError(sizeof(sourceCode));
    strcpy(mutable_str, sourceCode);
    mutable_str = cutString(mutable_str, '.');
    mutable_str +=4;
     // מתחיל אחרי המילה "data"
    token = strtok(mutable_str, ", ");
    count = 0;
    while (token != NULL) {
        if ((token[0]<='0' || token[0]>='9')&&token[0]!='-'){
            if (token[lengthOf(token) - 1] == '\n') token[lengthOf(token) - 1] = '\0';
            if (existDefine(token))
                numbers[count] = getValue(token);}
        else{
            numbers[count] = atoi(token);
            strcpy(temp -> binaryCode[count], translateToTwosCompliment(numbers[count],NUM_OF_BITS));
            temp->address[count]=address+count;}
            (count)++;
            token = strtok(NULL, ", ");
    }
    temp -> sourceCode = mallocError(sizeof(sourceCode));
    strcpy(temp->sourceCode, sourceCode);
    temp -> next= NULL;
    addCompleteLineToInfoTable(temp);
    return address+count;
}

int createStringLine(int address, char* stringToSave, int isFirst){
    int index = 1;
    infoTable* temp = mallocError(sizeof(infoTable));
    while ((stringToSave[index] >='a'&& stringToSave[index]<='z') || (stringToSave[index] >='A' && stringToSave[index]<='Z')){
        temp->address[index] = address;
        strcpy(temp->binaryCode[index], (translateToTwosCompliment(stringToSave[index], NUM_OF_BITS)));
        if(isFirst) {
            startInfoTable(temp);
            isFirst=0;
        }
        else{
            addSetLineToInfoTable(temp);
        }
        index++;
        address++;
    }
    temp->address[index] = address;
    strcpy(temp-> binaryCode[index], "00000000000000");
    temp -> sourceCode = mallocError(sizeof(stringToSave));
    strcpy(temp->sourceCode, stringToSave);
    temp -> next= NULL;
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
    if(isFirst) {
        makeInfoTable(address, line, 0, binaryWord);
    }
    else{
        addLineToInfoTable(address, line, 0, binaryWord);
    }

}

void printInfoTable(){
    infoTable* temp = first_info;
    while (temp != NULL){
        printf("\n%s %s %d", temp->sourceCode, temp->binaryCode[0], temp->address[0]);
        temp = temp->next;
    }
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