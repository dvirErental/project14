#include "secondPass.h"

void secondPass(infoTable* first, line_table* first_sym, FILE* fp) {
    int IC = 0;
    char* line = mallocError(sizeof(char) * MAX_LINE_LENGTH);
    int lineNum = 1;
    int index;
    int goTwice;
    int operand1Type;
    int operand2Type;
    int errorFlag = FALSE;
    char words[MAX_WORD_LENGTH][MAX_WORD_LENGTH];
    int address=100;
    infoTable *temp;
    while (!feof(fp)) {
        fgets(line, MAX_LINE_LENGTH, fp);
        cutString(line, ':');
        if (sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
                   words[7], words[8], words[9])) {
            if (isSymbolDefinition(words[0])) {
                index = 1;
            } else
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
                if ((temp = searchInfoTable(line)) == NULL) {
                    printf("Error, line %d, invalid command %s", lineNum, words[index]);
                    errorFlag = TRUE;
                    break;
                }

                if (((isCommand(words[index]) >= 0 && isCommand(words[index]) <= 3)) || isCommand(words[index]) == 6) {
                    operand1Type = discoverOperandTypeSecondPass(words[index + 1]);
                    operand2Type = discoverOperandTypeSecondPass(words[index + 2]);
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
                        strcpy(temp->binaryCode[1], buildRegisterBinaryCode(words[index + 1], words[index + 2]));
                        continue;
                    }
                    if (operand1Type == TYPE3) {
                        strcpy(temp->binaryCode[1], buildRegisterBinaryCode(words[index + 1], "r0"));
                    }
                    if (operand1Type == TYPE2) {
                        searchSymbolList(words[index + 1]);
                    }
                    if (operand1Type == TYPE0 && operand2Type == TYPE0) {
                            if (temp->binaryCode[0] != NULL) {
                                strcpy(temp->binaryCode[1],
                                       translateToTwosCompliment(atoi(words[index + 1]), NUM_OF_BITS));
                                strcpy(temp->binaryCode[2],
                                       translateToTwosCompliment(atoi(words[index + 2]), NUM_OF_BITS));
                            }
                        }
                        if (operand1Type == TYPE0 && operand2Type == TYPE1) {
                            if (temp->binaryCode[0] != NULL) {
                                strcpy(temp->binaryCode[1],
                                       translateToTwosCompliment(atoi(words[index + 1]), NUM_OF_BITS));
                                strcpy(temp->binaryCode[2],
                                       translateToTwosCompliment(atoi(words[index + 2]), NUM_OF_BITS));
                            }
                        }
                    } else {
                        printf("Error, line %d, invalid command %s", lineNum, words[index]);
                        errorFlag = TRUE;
                        break;
                    }

                }
            }
        }
    }

}
char* buildRegisterBinaryCode(char* reg1, char* reg2) {
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
    strcat(binary, "00");
    return binary;
}
int discoverOperandTypeSecondPass(char* op) {
    if(strcmp(op, "") == 0)
        return -1;
    if(op[0] == '#')
        return TYPE0;
    else if (searchOperandSymbolList(op))
        return TYPE1;
    else if (isArrayAddress(op))
        return TYPE2;
    else if (isRegisterName(op))
        return TYPE3;
    else
        return -1;
}

/*
if (((isCommand(words[index])>=0 && isCommand(words[index])<= 3))|| isCommand(words[index]) == 6) {
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
} */