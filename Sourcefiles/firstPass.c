#include "../Headers/firstPass.h"
/*assuming max number of words in a line is 10*/
/*Symbol declaration is done with all capital letters followed by a colon*/

void firstPass(void) {
    FILE* fp = fopen("../TextFiles/postPreAssembler", "r");
    int IC = 0, DC = 0;
    int address = 100;
    int addressIndex = 0;
    int lineNum = 0;
    int index;
    int isFirstSymbol = TRUE;
    int symbolDefinitionFlag;
    int errorFlag = FALSE;
    char line[MAX_LINE_LENGTH];
    char words[10][MAX_WORD_LENGTH] = {"","","","","","","","","",""};
    initializeCommands();
    while (!feof(fp)) {
        symbolDefinitionFlag = FALSE;
        printf("    %d   ", ++lineNum);
        fgets(line, MAX_LINE_LENGTH, fp);
        if (sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
                   words[7], words[8], words[9])) {

            if (!strcmp(words[0], ".define")){
                if (searchSymbolList(words[1])) {
                    printf("multiple definitions using same name");
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
                index = 1;
            }
            else
                index = 0;
            if (strcmp(words[1], ".string") == 0 || strcmp(words[1], ".data") == 0){
                if (symbolDefinitionFlag == TRUE) {
                    if(isFirstSymbol == TRUE) {
                        first_Symbol = make_symbol(words[0], ".data", DC);
                        isFirstSymbol = FALSE;
                    }
                    else
                        addToSymbolList(words[0], ".data", DC);}
                else {
                    printf("data without symbol");
                    errorFlag = TRUE;
                }
                if (strcmp(words[1], ".string") == 0) {
                    addLineToInfoTable(address++, line, 0, translateToTwosCompliment((int)words[index+1][1], NUM_OF_BITS));
                    address = createStringLine(address, &words[index + 1][2]);
                }
                else{
                    if (isValidDataString(line)) {
                        address = createDataLine(address, line);
                    }
                    else
                        printf("not valid string/data in line %d", lineNum);
                }

                DC += sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3],
                             words[4],words[5],words[6], words[7], words[8], words[9]);
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
            if(isCommand(words[index])<=3 || isCommand(words[index]) == 6)//change 3 to define
                executeCommandFirstPass(line, discoverOperandType(words[index+1]),
                                    discoverOperandType(words[index+2]), address,words[index]);
            else if ((isCommand(words[index]) != 14) && (isCommand(words[index]) != 15))
                executeCommandFirstPass(line, 0, discoverOperandType(words[index+1]), address,words[index]);
            else
                executeCommandFirstPass(line, 0, 0, address,words[index]);
            IC+= calculateL(line, symbolDefinitionFlag);
            address+= calculateL(line, symbolDefinitionFlag);

        }
    }
    if (errorFlag){
        printf("error was found in first pass we will not continue to second pass\n");
    }
    //addIC(IC);
    //freeTable(first_Symbol);
    printInfoTable();

    fclose(fp);
    printf("first pass finished");
}

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

int isArrayAddress(const char* op){
    if (containsBrackets(op) && (op[wordLength(op)-1] == ']'))
        return TRUE;
    return FALSE;
}



