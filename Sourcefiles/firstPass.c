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
            if (firstWord[0]==';'){
                continue;
            }
            if (!strcmp(firstWord, ".define")){
                if (!searchList(secondWord)) {
                    print_error(3);
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

