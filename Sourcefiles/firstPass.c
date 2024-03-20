#include "../Headers/firstPass.h"
/*assuming max number of words in a line is 10*/
/*Symbol decleration is done with all capital letters followed by a colon*/
line_table firstPass(FILE* fp) {
    int IC = 0, DC = 0;
    int address = 100;
    int lineLength = 0;
    int lineNum = 0;
    int index = 0;
    boolean isFirstSymbol = true;
    boolean isFirstInfo = true;
    boolean symbolDefinitionFlag = false;
    boolean errorFlag = false;
    char line[MAX_LINE_LENGTH];
    char** words = mallocError(sizeof(char)*MAX_WORD_LENGTH*MAX_NUM_OF_WORDS);
    while (!feof(fp)) {
        fgets(line, MAX_LINE_LENGTH, fp);
        lineNum++;
        if (sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
                   words[7], words[8], words[9])) {

            if (!strcmp(words[0], ".define")){
                if (searchSymbolList(words[1])) {
                    printf("multiple definitions using same name");
                    errorFlag = true;
                    continue;
                }
                else if (isFirstSymbol == true){
                    make_symbol(words[1], "mdefine", atoi(words[2]));
                    isFirstSymbol = false;
                    continue;
                }
                else {
                    addToSymbolList(words[1], "mdefine", atoi(words[2]));
                    continue;
                }
            }
            if (isSymbolDefinition(words[0]))
                symbolDefinitionFlag = true;//לאתחל בסוף
            if (strcmp(words[1], ".string") == 0 || strcmp(words[1], ".data") == 0){
                if (symbolDefinitionFlag == true) {
                    if(isFirstSymbol == true) {
                        first_Symbol = make_symbol(words[0], ".data", DC);
                        isFirstSymbol = false;
                    }
                    else
                        addToSymbolList(words[0], ".data", DC);
                }
                else
                    printf("data without symbol");
                if (strcmp(words[1], ".string") == 0)
                    createStringLine(DC, line, 0, isFirstInfo);
                else
                    createDataLine(DC, line);
                DC += sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3],
                             words[4],words[5],words[6], words[7], words[8], words[9]);
                continue;
            }
            if (!strcmp(words[0], ".extern")){
                if (searchSymbolList(words[1])){
                    printf("Error, line %d, multiple declerations for same symbol", lineNum);
                    errorFlag = true;
                }
                if (isFirstSymbol == true) {
                    first_Symbol = make_symbol(words[1],"external", 0);
                    isFirstSymbol = false;
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
                if (searchSymbolList(words[1])){
                    printf("Error, line %d, multiple declarations for same symbol", lineNum);
                    errorFlag = true;
                }
                if (isFirstSymbol)
                    make_symbol(words[1], ".entry", 0);
                else
                    addToSymbolList(words[1], ".entry", 0 );
                continue;
            }
            if (isSymbolDefinition(words[0])){
                if (searchSymbolList(words[0])){
                    printf("Error, line %d, multiple declarations for same symbol", lineNum);
                    errorFlag = true;
                }
                if (isFirstSymbol) {
                    first_Symbol = make_symbol(words[1], "code", IC + 100);
                    isFirstSymbol = false;
                }
                else
                    addToSymbolList(words[0], "code", IC+100);
            }
            if(symbolDefinitionFlag)
                index = 1;
            else
                index = 0;
            if (!isCommand(words[index])){
                printf("illegal Command, line %d", lineNum);
                errorFlag = true;
            }
            IC+=executeCommand(line, index, discoverOperandType(words[index+1]), discoverOperandType(words[index+2]));


        }
    }
}

int discoverOperandType(const char* op){
    if(strcmp(op, "") == 0)
        return -1;
    if(op[0] == '#')
        return TYPE0;
    else if (isLabel(op))
        return TYPE1;
    else if (isArrayAddress(op))
        return TYPE2;
    else if (isRegisterName(op))
        return TYPE3;
    else{
        printf("ERROR: illegal operand");
        return TYPE_ERROR;
    }
}

int isLabel(const char* op){
    int i = 0;
    while (op[i] != '\0')
        i++;
    if (op[i-1] == ':')
        return true;
    return false;
}

int isArrayAddress(const char* op){
    int i = 0;

    while (op[i] != '\0'){
        if (op[0] == '[')
            break;
    }
    if (op[i] == '\0')
        return false;
    while (op[i] != '\0')
        i++;
    if (op[i-1] == ']')
        return true;
    return false;
}

int isRegisterName(const char* op){
    if ((op[0] == 'r') && (op[1] >= '0') && (op[1] <= '7') && (op[2] == '\0'))
        return true;
    return false;
}


