#include "../Headers/PreAssembler.h"
char* commands[16];
FILE* preAssemble(FILE* op) {

    int macsFound = 0;
    int lineNum = 1;
    char line[MAX_LINE_LENGTH];
    char *firstWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    char *secondWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    char *thirdWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    node *current;
    initializeCommands();
    FILE *ModOrig = fopen("../Examples/hope", "w");
    while (!feof(op)) {
        fgets(line, MAX_LINE_LENGTH, op);
        if (sscanf(line, "%s%s%s", firstWord, secondWord, thirdWord)) {
            if (isFileIndication(firstWord)) {
                firstWord = secondWord;
                secondWord = thirdWord;
            }
            if (strcmp(firstWord, "mcr") == 0) {
                lineNum = createMacro(op, secondWord, lineNum, macsFound);
                macsFound++;
            }

            else if (existNode(firstWord) != NULL) {
                current = existNode(firstWord);
                fputs(current->content, ModOrig);
                lineNum++;
            }
            else {
                fputs(line, ModOrig);
                lineNum++;
            }
        }
    }
    return ModOrig;
}


int createMacro(FILE* fp, char* name, int lineNum, int macsFound){
    char line[MAX_LINE_LENGTH];
    char* tempCont = NULL;
    char* content = mallocError(MAX_LINE_LENGTH* sizeof(char));
    char* firstWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    node* temp;
    while (!feof(fp)){
        fgets(line,MAX_LINE_LENGTH,fp);
        if(sscanf(line, "%s", firstWord) == 1 && strcmp(firstWord, "endmcr") == 0){
            if (macsFound==0) {
                temp = make_node(name, content, lineNum);
                copy_head(first, temp);
            }
            else{
                add_to_list(name, content, lineNum);
            }
        }
        else{
            tempCont = realloc(content, (strlen(content)+ strlen(line))* sizeof(char));
            if (tempCont != NULL)
                content = tempCont;
            else
                /*print error here*/
            lineNum++;
        }
    }
    if(feof(fp)) {
        //print error here
    }
    return lineNum;
}

int isFileIndication(const char* a){
    int i = 0;
    while (a[i] != '\0'){
        if((a[i] <= 'Z' && a[i] >= 'A') || (a[i] <= '9' && a[i] >= '0') || (strcmp(a, ".define") == 0))
            i++;
        else
            return 0;
    }
    return 1;
}