#include "secondPass.h"

void secondPass() {
    FILE* fp = fopen("../TextFiles/postPreAssembler", "r");
    char* line = mallocError(sizeof(char) * MAX_LINE_LENGTH);
    int lineNum = 1;
    int index;
    int operand1Type;
    int operand2Type;
    int errorFlag = FALSE;
    char words[MAX_WORD_LENGTH][MAX_WORD_LENGTH] = {"","","","","","","","","",""};
    infoTable *temp;
    char are1[2];
    char are2[2];
    int countBinaryLines;
    printf("\n%s\n", extractSubstringUntilBrackets("LIST[sz]"));
    while (!feof(fp)) {
        fgets(line, MAX_LINE_LENGTH, fp);
        cutString(line, ':');
        if (sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
                   words[7], words[8], words[9])) {
            if (isSymbolDefinition(words[0])) {
                index = 1;
            }
            else
                index = 0;

            if ((!strcmp(words[index], ".define")) || (!strcmp(words[index], ".string")) ||
                (!strcmp(words[index], ".data"))) {
                continue;
            }
            if (!strcmp(words[index], "entry")) {
                if (searchSymbolList(words[1 + index])) {
                    printf("Error, line %d, multiple declarations for same symbol", lineNum);
                    errorFlag = TRUE;
                    break;
                }
                addToSymbolList(words[1 + index], "entry", getValue(words[1 + index]));
                continue;

            }
            if (isCommand(words[index]) != -1) {
                countBinaryLines=1;
                if ((temp = searchInfoTable(line)) == NULL) {
                    printf("Error, line %d, invalid command %s", lineNum, words[index]);
                    errorFlag = TRUE;
                    break;
                }

                if (((isCommand(words[index]) >= 0 && isCommand(words[index]) <= 3)) || isCommand(words[index]) == 6) {
                    operand1Type = discoverOperandTypeSecondPass(words[index + 1]);
                    operand2Type = discoverOperandTypeSecondPass(words[index + 2]);
                    strcpy(are1, discoverARE(words[index + 1]));
                    strcpy(are2, discoverARE(words[index + 2]));
                    if (operand1Type == -1) {
                        printf("Error, line %d, invalid operand %s", lineNum, words[index + 1]);
                        errorFlag = TRUE;
                        break;
                    }
                    if (operand2Type == -1) {
                        printf("Error, line %d, invalid operand %s", lineNum, words[index + 2]);
                        errorFlag = TRUE;
                        break;
                    }
                    if (operand1Type == TYPE3 && operand2Type == TYPE3) {
                        strcpy(temp->binaryCode[1], buildRegisterBinaryCode(words[index + 1], words[index + 2],are1));
                        continue;
                    }
                    if (operand1Type == TYPE3) {
                        strcpy(temp->binaryCode[1], buildRegisterBinaryCode(words[index + 1], "r0",are1));
                        countBinaryLines++;
                    }
                    if (operand1Type == TYPE2) {
                        if (existDataSymbolList(words[index + 1])){
                            strcpy(temp->binaryCode[1], strcat(translateToTwosCompliment(getValue(words[index + 1]), NUM_OF_BITS-BITS_IN_ARE), are1));
                            strcpy(temp->binaryCode[2], strcat(translateToTwosCompliment(theIndexArray(words[index + 1]),NUM_OF_BITS-BITS_IN_ARE),"00"));
                            countBinaryLines+=2;
                        }
                        else{
                            printf("Error, line %d, invalid operand %s", lineNum, words[index + 1]);
                            errorFlag = TRUE;
                            break;
                        }
                    }
                    if (operand1Type == TYPE1) {
                        if (existDataSymbolList(words[index + 1])){
                            strcpy(temp->binaryCode[1], strcat(translateToTwosCompliment(getValue(words[index + 1]), NUM_OF_BITS-BITS_IN_ARE), are1));
                            countBinaryLines++;
                        }
                        else{
                            printf("Error, line %d, invalid operand %s", lineNum, words[index + 1]);
                            errorFlag = TRUE;
                            break;
                        }
                    }
                    if (operand1Type == TYPE0) {
                        strcpy(temp->binaryCode[1], strcpy(translateToTwosCompliment(atoi(cutString(words[index + 1],'#')), NUM_OF_BITS-BITS_IN_ARE),are1));
                        countBinaryLines++;
                    }
                    if (operand2Type == TYPE3) {
                        strcpy(temp->binaryCode[countBinaryLines], buildRegisterBinaryCode(words[index + 2], "r0",are1));
                        continue;
                    }
                    if (operand2Type == TYPE2) {
                        if (existDataSymbolList(words[index + 2])){
                            strcpy(temp->binaryCode[countBinaryLines], strcat(translateToTwosCompliment(getValue(words[index + 2]), NUM_OF_BITS-BITS_IN_ARE), are1));
                            strcpy(temp->binaryCode[countBinaryLines+1], strcat(translateToTwosCompliment(theIndexArray(words[index + 2]),NUM_OF_BITS-BITS_IN_ARE),"00"));
                        }
                        else{
                            printf("Error, line %d, invalid operand %s", lineNum, words[index + 2]);
                            errorFlag = TRUE;
                            break;
                        }
                        continue;
                    }
                    if (operand2Type == TYPE1) {
                        if (existDataSymbolList(words[index + 2])){
                            strcpy(temp->binaryCode[countBinaryLines], strcat(translateToTwosCompliment(getValue(words[index + 2]), NUM_OF_BITS-BITS_IN_ARE), are1));

                        }
                        else{
                            printf("Error, line %d, invalid operand %s", lineNum, words[index + 2]);
                            errorFlag = TRUE;
                            break;
                        }
                        continue;
                    }
                    strcpy(temp->binaryCode[countBinaryLines], strcpy(translateToTwosCompliment(atoi(cutString(words[index + 2],'#')), NUM_OF_BITS-BITS_IN_ARE),are1));
                }
                if (((isCommand(words[index]) >= 4 && isCommand(words[index]) <= 5)) || isCommand(words[index]) < 14){
                    operand1Type = discoverOperandTypeSecondPass(words[index + 1]);
                    strcpy(are1, discoverARE(words[index + 1]));
                    if (operand1Type == -1) {
                        printf("Error, line %d, invalid operand %s", lineNum, words[index + 1]);
                        errorFlag = TRUE;
                        break;
                    }
                    if (operand1Type == TYPE3) {
                        strcpy(temp->binaryCode[1], buildRegisterBinaryCode(words[index + 1], "r0",are1));
                    }
                    if (operand1Type == TYPE2) {
                        if (existDataSymbolList(words[index + 1])){
                            strcpy(temp->binaryCode[1], strcat(translateToTwosCompliment(getValue(words[index + 1]), NUM_OF_BITS-BITS_IN_ARE), are1));
                            strcpy(temp->binaryCode[2], strcat(translateToTwosCompliment(theIndexArray(words[index + 1]),NUM_OF_BITS-BITS_IN_ARE),"00"));
                        }
                        else{
                            printf("Error, line %d, invalid operand %s", lineNum, words[index + 1]);
                            errorFlag = TRUE;
                            break;
                        }
                    }
                    if (operand1Type == TYPE1) {
                        if (existDataSymbolList(words[index + 1])){
                            strcpy(temp->binaryCode[1], strcat(translateToTwosCompliment(getValue(words[index + 1]), NUM_OF_BITS-BITS_IN_ARE), are1));
                        }
                        else{
                            printf("Error, line %d, invalid operand %s", lineNum, words[index + 1]);
                            errorFlag = TRUE;
                            break;
                        }
                    }
                    if (operand1Type == TYPE0) {
                        strcpy(temp->binaryCode[1], strcpy(translateToTwosCompliment(atoi(cutString(words[index + 1],'#')), NUM_OF_BITS-BITS_IN_ARE),are1));
                    }
                }
            }
        }
    }

    if (errorFlag){
        printf("Error was found in second pass\n");
        exit(0);
    }
}

int theIndexArray(char* word) {
    char *index;
    strcpy(index, word);
    index = strtok(index, "[");
    index = strtok(NULL, "]");
    if (index != NULL) {
        if (index[0] >= '0' && index[0] <= '9')
            return atoi(index);
        else if (existDefine(index))
            return getValue(index);
    }
    exit(0);
}

char* discoverARE(char* op) {
    if(strcmp(op, "") == 0)
        return "ERROR";
    if ((op[0] == '#') || (isRegisterName(op)))
        return "00";
    else if (existDataSymbolList(op) || isArrayAddress(op))
        return "10";
    else if (isExternal(op))
        return "01";
    else
        return "ERROR";
}
char* buildRegisterBinaryCode(char* reg1, char* reg2,char* are) {
    int numreg1 =whichRegister(reg1);
    int numreg2 =whichRegister(reg2);
    char* binary= (char*)mallocError(sizeof(char) * NUM_OF_BITS);
    binary[0] = '0';
    binary[1] = '0';
    binary[2] = '0';
    binary[3] = '0';
    binary[4] = '0';
    binary[5] = '0';
    strcat(binary, translateToTwosCompliment(numreg1, BITS_IN_REGISTER_LENGTH));
    strcat(binary, translateToTwosCompliment(numreg2, BITS_IN_REGISTER_LENGTH));
    strcat(binary, are);
    return binary;
}

int discoverOperandTypeSecondPass(char* op) {
    if(strcmp(op, "") == 0)
        return -1;
    if(op[0] == '#')
        return TYPE0;
    else if (searchOperandSymbolList(op))
        return TYPE1;
    else if (isArrayAddressSecondPass(op))
        return TYPE2;
    else if (isRegisterName(op))
        return TYPE3;
    else
        return -1;
}

int isArrayAddressSecondPass(const char* op){

    if (containsBrackets(op) && (existDataSymbolList(extractSubstringUntilBrackets(op))))
        return TRUE;
    return FALSE;
}


char* extractSubstringUntilBrackets(char* str) {
    // Find the position of '[' character
    char* pos = strchr(str, '[');

    if (pos != NULL) {
        // Calculate the length of the substring before '['
        size_t length = pos - str;

        // Allocate memory for the new string (including null terminator)
        char* substring = (char*)malloc((length + 1) * sizeof(char));
        if (substring == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        // Copy characters from the original string to the new string
        strncpy(substring, str, length);
        substring[length] = '\0'; // Null-terminate the string

        return substring;
    } else {
        // If '[' is not found, return a copy of the original string
        return strdup(str);
    }
}