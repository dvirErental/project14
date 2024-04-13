#include "../Headers/firstPass.h"
/*assuming max number of words in a line is 10*/

/**
 * Main function of first pass
 * does what the recommended algorithm does.
 */
void firstPass(void) {
    FILE* fp = fopen("../TextFiles/postPreAssembler", "r");
    int IC = 0, DC = 0;
    int address = 100;
    int lineNum = 0;
    int index;
    int isFirstSymbol = TRUE;
    int symbolDefinitionFlag;
    int errorFlag = FALSE;
    char line[MAX_LINE_LENGTH] = "";
    char words[MAX_NUM_OF_WORDS][MAX_WORD_LENGTH] = {"","","","",
                                                     "","","","","",""};
    initializeCommands();/*fills the command array with the commands*/
    while (!feof(fp)) {
        symbolDefinitionFlag = FALSE;
        ++lineNum;
        fgets(line, MAX_LINE_LENGTH, fp);
        if (sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
                   words[7], words[8], words[9])) {/*separates the line from one long string into words in an array*/

            if (!strcmp(words[0], ".define")){
                if (searchSymbolList(words[1])) {
                    printf("ERROR: multiple definitions using same name");
                    errorFlag = TRUE;
                }
                else if (isFirstSymbol){
                    first_Symbol = make_symbol(words[1], "mdefine", atoi(words[3]));
                    isFirstSymbol = FALSE;
                }
                else {
                    addToSymbolList(words[1], "mdefine", atoi(words[3]));
                }
                continue;
            }
            if (isSymbolDefinition(words[0])) {
                symbolDefinitionFlag = TRUE;
                index = 1;/*know to start from second word from now on*/
            }
            else
                index = 0;
            if (strcmp(words[1], ".string") == 0 || strcmp(words[1], ".data") == 0){
                if (symbolDefinitionFlag == TRUE) {
                    words[0][strlen(words[0])-1] = '\0';
                    if(isFirstSymbol == TRUE) {
                        first_Symbol = make_symbol(words[0], "data", DC);
                        isFirstSymbol = FALSE;
                    }
                    else
                        addToSymbolList(words[0], "data", DC);}
                else {
                    printf("ERROR: data without symbol");
                    errorFlag = TRUE;
                }
                if (strcmp(words[1], ".string") == 0) {
                    addLineToInfoTable(address++, line, 0, translateToTwosCompliment((int)words[index+1][1], NUM_OF_BITS));
                    DC = createStringLine(DC, &words[index + 1][2]);
                }
                else{
                    if (isValidDataString(line)) {
                        DC = createDataLine(DC, line);
                    }
                    else
                        printf("not valid string/data in line %d", lineNum);
                }

                continue;
            }
            if (!strcmp(words[0], ".extern")){
                if (searchSymbolList(words[1])){
                    printf("Error, line %d, multiple declarations for same symbol", lineNum);
                    errorFlag = TRUE;
                }
                if (isFirstSymbol == TRUE) {
                    first_Symbol = make_symbol(words[1],"external", 0);
                    isFirstSymbol = FALSE;
                }
                else
                    addToSymbolList(words[1], "external", 0);

                while((index<MAX_NUM_OF_WORDS) && (strcmp(words[index],"")!=0)){
                    addToSymbolList(words[index], "external", 0);
                    index++;
                }
                continue;
            }
            if (!strcmp(words[0], ".entry")){
                continue;
            }
            if (symbolDefinitionFlag) {
                words[0][strlen(words[0])-1] = '\0';
                if (searchSymbolList(words[0])) {
                    printf("Error, line %d, multiple declarations for same symbol", lineNum);
                    errorFlag = TRUE;
                }
                if (isFirstSymbol) {
                    first_Symbol = make_symbol(words[1], "code", IC + 100);
                    isFirstSymbol = FALSE;
                } else
                    addToSymbolList(words[0], "code", IC + 100);
            }

            if (isCommand(words[index]) == -1){
                printf("illegal Command, line %d", lineNum);
                errorFlag = TRUE;
            }
            if(isCommand(words[index])<=TWO_OPERAND_COMMANDS || isCommand(words[index]) == OTHER_TWO_OPERAND_COMMAND)
                executeCommandFirstPass(line, discoverOperandType(words[index+1]),
                                    discoverOperandType(words[index+2]), address,words[index]);
            else if ((isCommand(words[index]) != ZERO_OPERAND_COMMAND) && (isCommand(words[index]) != OTHER_ZERO_OPERAND_COMMAND))
                executeCommandFirstPass(line, 0, discoverOperandType(words[index+1]), address,words[index]);
            else
                executeCommandFirstPass(line, 0, 0, address,words[index]);
            IC+= calculateL(line, symbolDefinitionFlag);
            address+= calculateL(line, symbolDefinitionFlag);

        }
    }
    if (errorFlag){
        printf("error was found in first pass we will not continue to second pass\n");
        exit(0);
    }
    updateData(IC);
    fclose(fp);
    printf("first pass finished\n");
    printSymbolTable();
}

/**
 * discovers which type of operand a given word is.
 * @param op the operand to discover
 * @return the number which represents the type of operand.
 */
int discoverOperandType(char* op){
    if(strcmp(op, "") == 0)
        return -1;
    if(op[0] == '#'|| existDefine(op))
        return TYPE0;
    else if (isArrayAddress(op))
        return TYPE2;
    else if (isRegisterName(op))
        return TYPE3;
    else
            return TYPE1;
}

/**
 * checks if a given char* is an array address based off the way it's written.
 * @param op the char* to check
 * @return 1(True) if it can represent an array, otherwise 0(false)
 */
int isArrayAddress(const char* op){
    if (containsBrackets(op) && (op[wordLength(op)-1] == ']'))
        return TRUE;
    return FALSE;
}



