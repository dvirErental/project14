
#include "infoTable.h"

infoTable* first_info = NULL;
/**
 * one of two main functions of infotable, initializes first_info
 * @param address - the address for the first line (generally 100)
 * @param sourceCode - the source code for the first line
 * @param num - the number to be translated into binary and saved as the binary code
 * @param stringAlternative - alternate way to save the binary code is just by sending it in as you want it.
 */
void makeInfoTable(int address, char* sourceCode, int num, char* stringAlternative){
    first_info = mallocError(sizeof(infoTable));
    first_info -> address[0] = address;
    strcpy(first_info->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "")==0)
        strcpy(first_info->binaryCode[0], translateToTwosCompliment(num, NUM_OF_BITS));
    else
        strcpy(first_info->binaryCode[0], stringAlternative);

    first_info -> next = NULL;
}

/**
 * other main function of infotable.c, creates the lines that aren't the first info table.
 * @param address
 * @param sourceCode
 * @param num
 * @param stringAlternative
 */
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
    strcpy((temp->next)->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "") == 0)
        strcpy(temp->next->binaryCode[0], translateToTwosCompliment(num, NUM_OF_BITS));
    else
        strcpy(temp->next->binaryCode[0], stringAlternative);

    ((temp -> next) -> next) = NULL;
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
    char *endptr = mallocError(sizeof(char)* MAX_WORD_LENGTH);
    char *deleteLabel = mallocError(sizeof(char)* lengthOf(str));
    strcpy(deleteLabel,str);
    strcpy( deleteLabel,cutString(deleteLabel, ':'));
    while (isspace(*deleteLabel))
        deleteLabel++; // דחיפות מרווחים
    strtol(deleteLabel + 5, &endptr, 10);
    while (isspace(*endptr))
        endptr++; // דחיפות מרווחים
    while (*endptr != '\0') {
        if (*endptr != ',' && !isspace(*endptr)) { // בודק אם יש תו שאינו פסיק או רווח
            if (isWord(endptr))
                return 1;
            else
                return 0;
        }
        strtol(endptr + 1, &endptr, 10); // הולך למספר הבא
        while (isspace(*endptr))
            endptr++; // דחיפות מרווחים
    }
    return 1;
}
int createDataLine(int address, char* sourceCode) {
    infoTable* temp = mallocError(sizeof(infoTable));
    int numbers[MAX_NUM_OF_WORDS];
    int count = 0;
    char *token;
    char *mutable_str = mallocError(strlen(sourceCode) + 1); // Allocate memory for mutable_str
    strcpy(mutable_str, sourceCode);
    mutable_str = cutString(mutable_str, '.');
    mutable_str += 4; // Skip the "data" keyword
    token = strtok(mutable_str, ", ");
    while (token != NULL) {
        // Check if token is a number or a defined symbol
        if ((token[0] >= '0' && token[0] <= '9') || token[0] == '-') {
            numbers[count] = atoi(token);
        }
        else {
            if (token[strlen(token) - 1] == '\n')
                token[strlen(token) - 1] = '\0'; // Remove newline character if present
            if (existDefine(token))
                numbers[count] = getValue(token);
            }
            // Translate number to binary and store in temp->binaryCode
        strcpy(temp->binaryCode[count], translateToTwosCompliment(numbers[count], NUM_OF_BITS));
        count++;
        token = strtok(NULL, ", ");
    }

    temp->address[0] = address;
    strcpy(temp->sourceCode, sourceCode);
    temp->next = NULL;
    addCompleteLineToInfoTable(temp);
    return address + count;
}


    int createStringLine(int address, char* stringToSave) {
    int index = 0;
    infoTable temp;  

    while (((stringToSave[index] >= 'a') && (stringToSave[index] <= 'z')) ||
           ((stringToSave[index] >= 'A') && (stringToSave[index] <= 'Z'))) {
        temp.address[0] = address;
        strcpy(temp.binaryCode[0], (translateToTwosCompliment(stringToSave[index], NUM_OF_BITS)));
        strcpy(temp.sourceCode, "");  // Assuming sourceCode is a string pointer

        addSetLineToInfoTable(&temp);  // Pass the address of temp to the function

        index++;
        address++;
    }

    addLineToInfoTable(address, "", 0, "00000000000000");
    return address + 1;
}

void executeCommandFirstPass(char* line, int op1, int op2, int address, char* word){
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
    addLineToInfoTable(address, line, 0, binaryWord);
}

void printInfoTable(){
    infoTable* temp = first_info;
    while (temp != NULL){
        printf("\n%s %s %d", temp->sourceCode, temp->binaryCode[0], temp->address[0]);
        temp = temp->next;
    }

}

infoTable* searchInfoTable(char* sourceCode){
    infoTable* temp = first_info;
    while (temp != NULL){
        if (strcmp(temp->sourceCode, sourceCode) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
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
