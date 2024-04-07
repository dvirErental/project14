#include "secondPass.h"

void secondPass(infoTable* first, line_table* first_sym, FILE* fp) {
    int IC = 0;
    char* line = mallocError(sizeof(char) * MAX_LINE_LENGTH);
    int lineNum = 1;
    int index;
    int goTwice;
    int errorFlag = FALSE;
    char words[MAX_WORD_LENGTH][MAX_WORD_LENGTH];
    while (!feof(fp)) {
        fgets(line, MAX_LINE_LENGTH, fp);
        cutString(line,':');
        if (sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
                   words[7], words[8], words[9])) {
            if (isSymbolDefinition(words[0])) {
                index = 1;
            }
            else
                index = 0;
            if ((!strcmp(words[index], ".define")) || (!strcmp(words[index], ".string")) || (!strcmp(words[index], ".data"))) {
                continue;
            }
            if (!strcmp(words[index], "entry")) {
                if (searchSymbolList(words[1 + index])) {
                    printf("Error, line %d, multiple declarations for same symbol", lineNum);
                    errorFlag = TRUE;}
                addToSymbolList(words[1+index], "entry", getValue(words[1+index]));
                continue;

            }


        }
    }
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