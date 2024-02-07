#include "../Headers/PreAsse.h"
node* first;
char* commands[16];
FILE* preAssemble(FILE* op) {

    int macsFound = 0;
    int lineNum = 1;
    char line[MAX_LINE_LENGTH];
    char *firstWord;
    char *secondWord = "";
    char *thirdWord = "";
    node *current;
    initializeCommands();
    FILE *ModOrig = fopen("Post_preAssembler", "w");
    while (!feof(op)) {
        fgets(line, MAX_LINE_LENGTH, op);
        if (sscanf(line, "%s%s%s", firstWord, secondWord, thirdWord)) {
            if (isFileIndication(firstWord)) {
                firstWord = secondWord;
                secondWord = thirdWord;
                if (strcmp(firstWord, "mcr") == 0)
                    lineNum += skip(lineNum, op);
                else if (isCommand(firstWord) == 0) {
                    fputs(line, ModOrig);
                    lineNum++;
                } else if ((current = search_list(first, firstWord, 0)) != NULL) {
                    fputs(current->content, ModOrig);
                    lineNum++;
                } else if (strcmp(firstWord, "mcr") == 0) {
                    lineNum = createMacro(op, secondWord, lineNum, macsFound);
                    macsFound++;
                } else {
                    fprintf(stderr, "ERROR, unidentified command/macro in line, skipped that line %d/n", lineNum);
                    lineNum++;
                }
            }
        }
    }
    return ModOrig;
}


int createMacro(FILE* fp, char* name, int lineNum, int macsFound){
    char line[MAX_LINE_LENGTH];
    char* content = "";
    char* firstWord = "";
    node* temp;
    while (!feof(fp)){
        fgets(line,MAX_LINE_LENGTH,fp);
        if(sscanf(line, "%s", firstWord) == 1 && strcmp(firstWord, "endmcr") == 0){
            if (macsFound==0) {
                temp = make_node(name, content, lineNum);
                copy_head(first, temp);
            }
            else{
                add_to_list(&first, name, content, lineNum);
            }
        }
        else{
            strcat(content, line);
            lineNum++;
        }
    }
    if(feof(fp)) {
        //print error here
    }
    return lineNum;
}

int skip(int lineNum, FILE* op){
    int counter = lineNum + 1;
    char line[MAX_LINE_LENGTH];
    char* firstWord = "";
    while (!feof(op)){
        fgets(line,MAX_LINE_LENGTH,op);        sscanf(line, "%s", firstWord);
        if (strcmp(firstWord, "endmcr") == 0){
            counter++;
            break;
        }
        counter++;
    }
    return counter;
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