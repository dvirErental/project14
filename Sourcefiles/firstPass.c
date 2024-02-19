#include "../Headers/firstPass.h"
/*assuming max number of words in a line is 6*/
line_table firstPass(FILE* fp) {
    int IC = 0, DC = 0;
    int address = 100;
    int lineLength = 0;
    boolean isFirst = true;
    boolean symbolFlag = false;
    char line[MAX_LINE_LENGTH];
    char* firstWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* secondWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* thirdWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* fourthWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* fifthWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* sixthWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);

    while (!feof(fp)) {
        fgets(line, MAX_LINE_LENGTH, fp);
        if (sscanf(line, "%s%s%s%s%s%s", firstWord, secondWord, thirdWord, fourthWord, fifthWord, sixthWord)) {
            if (!strcmp(firstWord, ".define")){
                if (!searchList(secondWord)) {
                    printf("multiple definitions using same name");
                    continue;
                }
                else if (isFirst == true){
                    make_line_table(secondWord, "mdefine", atoi(thirdWord));
                    isFirst = false;
                    continue;
                }
                else {
                    add_to_list(secondWord, "mdefine", atoi(thirdWord));
                    continue;
                }
            }
            if (isFileIndication(firstWord))
                symbolFlag = true;//לאתחל בסוף
            if (strcmp(secondWord, ".string") == 0 || strcmp(secondWord, ".data") == 0){
                if (symbolFlag == true) {
                    if(isFirst == true)
                        make_line_table(firstWord, ".data", DC);
                    //להוסיף את הנתונים לטבלה הגדולה
                }
            }
            if (strcmp(firstWord, ".entry") == 0 || strcmp(firstWord, ".extern") == 0){
                //להשלים
            }

        }
    }
}

int discoverOperandType(const char* op){
    if(op[0] == '#')
        return 0;
    else if (isLabel(op))
        return 1;
    else if (isArrayAddress(op))
        return 2;
    else if (isRegisterName(op))
        return 3;
    else{
        printf("ERROR: illegal operand");
        return -1;
    }
}

int isLabel(const char* op){
    int i = 0;
    while (op[i] != '\0')
        i++;
    if (op[i-1] == ':')
        return 1;
    return 0;
}

int isArrayAddress(const char* op){
    int i = 0;

    while (op[i] != '\0'){
        if (op[0] == '[')
            break;
    }
    if (op[i] == '\0')
        return 0;
    while (op[i] != '\0')
        i++;
    if (op[i-1] == ']')
        return 1;
    return 0;
}

int isRegisterName(const char* op){
    if ((op[0] == 'r') && (op[1] >= '0') && (op[1] <= '7') && (op[2] == '\0'))
        return 1;
    return 0;
}


