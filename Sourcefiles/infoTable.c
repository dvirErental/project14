
#include "../Headers/infoTable.h"

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
    temp->next-> address[1] = -1;
    strcpy((temp->next)->sourceCode, sourceCode);
    if(strcmp(stringAlternative, "") == 0)
        strcpy(temp->next->binaryCode[0], translateToTwosCompliment(num, NUM_OF_BITS));
    else
        strcpy(temp->next->binaryCode[0], stringAlternative);

    ((temp -> next) -> next) = NULL;
}

/**
 * adds an already built line into the info Table(assuming only one binary code needed)
 * @param info the built line
 */
void addSetLineToInfoTable(infoTable* info){
    addLineToInfoTable(info->address[0], info->sourceCode,0, info->binaryCode[0]);
}
/**
 * similar to previous function, with the difference that it can contain more than one binary code.
 * @param info the built line to add
 */
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
/**
 * checks if a given string is a valid representaion of a .data command.
 * @param str the string to check
 * @return true if it is, otherwise false.
 */
int isValidDataString(const char *str) {

    char *endptr = mallocError(sizeof(char)* MAX_WORD_LENGTH);
    char *deleteLabel = mallocError(sizeof(char)* lengthOf(str));
    strcpy(deleteLabel,str);
    strcpy( deleteLabel,cutString(deleteLabel, ':'));
    while (isspace(*deleteLabel))
        deleteLabel++; /*דחיפות מרווחים*/
    strtol(deleteLabel + 5, &endptr, 10);
    while (isspace(*endptr))
        endptr++; // דחיפות מרווחים
    while (*endptr != '\0') {
        if (*endptr != ',' && !isspace(*endptr)) { /* בודק אם יש תו שאינו פסיק או רווח*/
            if (isWord(endptr))
                return TRUE;
            else
                return FALSE;
        }
        strtol(endptr + 1, &endptr, 10); /* הולך למספר הבא*/
        while (isspace(*endptr))
            endptr++; /* דחיפות מרווחים*/
    }
    return 1;
}

/**
 * creates a data line
 * @param address the starting address of the given line to create
 * @param sourceCode - the source code for the line
 * @return the new address following the addition of the data line.
 */
int createDataLine(int address, char* sourceCode) {
    infoTable* temp = mallocError(sizeof(infoTable));
    int numbers[MAX_NUM_OF_WORDS];
    int count = 0;
    char *token;
    int i;
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
                token[strlen(token) - 1] = '\0'; /* Remove newline character if present*/
            if (existDefine(token))
                numbers[count] = getValue(token);
            }
            // Translate number to binary and store in temp->binaryCode
        strcpy(temp->binaryCode[count], translateToTwosCompliment(numbers[count], NUM_OF_BITS));
        count++;
        token = strtok(NULL, ", ");
    }
    for (i = 0; i < count; i++) {
        temp->address[i] = address+i-1;
    }
    temp->address[i] = -1;
    strcpy(temp->sourceCode, sourceCode);
    temp->next = NULL;
    addCompleteLineToInfoTable(temp);
    return address + count;
}

/**
 * creates a string line in the info table
 * @param address - the starting address for the info table.
 * @param stringToSave - the word to save as a string.
 * @return the new address following the addtion of the string line.
 */
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

/**
 * creates a info line for the first word of a command.
 * @param line the line in which the command appears  (will become the source code)
 * @param op1 the type of the first operand(if there is one)
 * @param op2 the type of the second operand(if there is one)
 * @param address the address that should be stored in the info table with the command.
 * @param word the command name.
 */
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



/**
 * searches the info table for a line with a matching source code to the given parameter
 * @param sourceCode the parameter to compare with.
 * @return the pointer to the line with the matching source code if there is one, otherwise NULL.
 */
infoTable* searchInfoTable(char* sourceCode){
    infoTable* temp = first_info;
    while (temp != NULL){
        if (strcmp(temp->sourceCode, sourceCode) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void printInfoTable(void){
    infoTable* temp = first_info;
    int index;
    while(temp!=NULL){
        index = 0;
        printf("%d\t", temp->address[0]);
        while(temp->binaryCode[index][0] =='0'||temp->binaryCode[index][0] == '1'){
            printf("%s\n", temp->binaryCode[index]);
            temp++;
        }
        temp = temp->next;
    }
}

infoTable* getFirstLine(){
    return first_info;
}



void freeInfoTable(){
    first_info = NULL;
}