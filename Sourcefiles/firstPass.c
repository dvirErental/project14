#include "../Headers/firstPass.h"
/*assuming max number of words in a line is 10*/
line_table firstPass(FILE* fp) {
    int IC = 0, DC = 0;
    int address = 100;
    int lineLength = 0;
    int lineNum = 0;
    int i;
    boolean isFirst = true;
    boolean symbolFlag = false;
    char line[MAX_LINE_LENGTH];
    char** words = mallocError(sizeof(char)*MAX_WORD_LENGTH*10);

    while (!feof(fp)) {
        fgets(line, MAX_LINE_LENGTH, fp);
        if (sscanf(line, "%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5])) {

            if (!strcmp(words[0], ".define")){
                if (searchList(words[1])) {
                    printf("multiple definitions using same name");
                    continue;
                }
                else if (isFirst == true){
                    make_symbol(words[1], "mdefine", atoi(words[2]));
                    isFirst = false;
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
                    if(isFirst == true) {
                        first_Symbol = make_symbol(words[0], ".data", DC);
                        isFirst = false;
                    }
                    else
                        add_to_symbol_list(words[0], ".data", DC);
                }
                else
                    printf("data without symbol");
                if (strcmp(words[1], ".string") == 0)
                    createStringLine(DC, line, 0, isFirst);
                else
                    createDataLine(DC, line);
                DC += sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3],
                             words[4],words[5],words[6], words[7], words[8], words[9]);
            }
            continue;
            if (strcmp(words[0], ".entry") == 0 || strcmp(words[0], ".extern") == 0){
                if (isFirst == true) {
                    first_Symbol = make_symbol(words[1], "external", -1);
                    isFirst = false;
                    i++;
                }
                while (words[i] != NULL){
                    lineLength++;
                    add_to_symbol_list(words[i+1], "external", -1);
                    i++;
                }
            }
            continue;
        }
    }
}

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


