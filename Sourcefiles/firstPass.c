#include "../Headers/firstPass.h"
/*assuming max number of words in a line is 10*/

/**
 * main functino of first Pass.
 * @param file following macro creations.
 * @return information table
 */
line_table firstPass(FILE* fp) {
    int IC = 0, DC = 0;
    int address = 100;
    int lineLength = 0;
    int lineNum = 0;
    boolean isFirstSymbol = true;
    boolean isFirstInfoLine = true;
    boolean symbolFlag = false;
    boolean errorFlag = false;
    char line[MAX_LINE_LENGTH];
    char** words = mallocError(sizeof(char)*MAX_WORD_LENGTH*10);
    infoTable thisInfo;
    while (!feof(fp)) {
        lineNum++;
        fgets(line, MAX_LINE_LENGTH, fp);
        if (sscanf(line, "%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5])) {

            if (!strcmp(words[0], ".define")){
                if (searchList(words[1])) {
                    printf("multiple definitions using same name");
                    continue;
                }
                else if (isFirstSymbol){
                    make_symbol(words[1], "mdefine", atoi(words[2]));
                    isFirstSymbol = false;
                    continue;
                }
                else {
                    add_to_symbol_list(words[1], "mdefine", atoi(words[2]));
                    continue;
                }
            }
            if (isFileIndication(words[0]))
                symbolFlag = true;//לאתחל בסוף
            if (strcmp(words[1], ".string") == 0 || strcmp(words[1], ".data") == 0){
                if (symbolFlag == true) {
                    if(isFirstSymbol == true) {
                        first_Symbol = make_symbol(words[0], ".data", DC);
                        isFirstSymbol = false;
                    }
                    else
                        add_to_symbol_list(words[0], ".data", DC);
                }
                else {
                    printf("data without symbol");
                    errorFlag = true;
                }
                if (strcmp(words[1], ".string") == 0)
                    createStringLine(DC, line,isFirstInfoLine);
                else
                    createDataLine(DC, line,thisInfo);
                DC += sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3],
                             words[4],words[5],words[6], words[7], words[8], words[9]);
            }
            if (strcmp(words[0], ".entry") == 0 || strcmp(words[0], ".extern") == 0){
                if (isFirstInfoLine == true) {
                    first_Symbol = make_symbol(words[1],"external", DC);
                    isFirstInfoLine = false;
                }
                else
                    add_to_symbol_list(words[1], words[0], 0);
            }
            if (symbolFlag){
                if(searchList(words[0])) {
                    printf("Error: multiple definitions for same label. Line number %d", lineNum);
                    errorFlag = true;
                    continue;
                }
                if(isFirstSymbol){
                    make_symbol(words[0], "code", IC+100);
                }
                else
                    add_to_symbol_list(words[0], "code", IC+100);
            }
            continue;

        }
    }
}
/**
 * discovers operand type
 * @param name of function
 * @return type of operand (by number)
 */
int discoverOperandType(const char* op){
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

/**
 * checks if parameter is a label.
 * @param op name to check
 * @return true(1) if paramater is a label, otherwise false(0)
 */
int isLabel(const char* op){
    int i = 0;
    while (op[i] != '\0')
        i++;
    if (op[i-1] == ':')
        return true;
    return false;
}
/**
 * checks is parameter is an array Address
 * @param op name to check
 * @return true if parameter is an array address, otherwise false.
 */
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
/**
 * checks if parameter is a register name
 * @param op name to check
 * @return true if parameter is a register name, otherwise false.
 */
int isRegisterName(const char* op){
    if ((op[0] == 'r') && (op[1] >= '0') && (op[1] <= '7') && (op[2] == '\0'))
        return true;
    return false;
}


