#include "PreAsse.h"
void copyFile(FILE* op){
    FILE* cop = fopen("ChangedOriginal", "w");
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, op) != NULL) {
        fputs(line, cop);
    };
}

void copyMacs(FILE* fp){
    int lineNum = 1;
    char line[MAX_LINE_LENGTH];
    char* firstWord;
    char* macroName;
    char macro[] ="mcr";
    while((fgets(line, MAX_LINE_LENGTH, fp)) != NULL){
        if(sscanf(line, "%s%s", firstWord, macroName) == 2 && strcmp(firstWord, macro) == 0){
            createMacro(fp,macroName,lineNum);
        }
        lineNum++;
    }
}

void createMacro(FILE* fp, char* name, int lineNum){
    char line[MAX_LINE_LENGTH];
    char* content;
    char* firstWord;
    char endMacro[] ="endmcr";
    while((fgets(line, MAX_LINE_LENGTH, fp)) != NULL){
        if(sscanf(line, "%s", firstWord) == 1 && strcmp(firstWord, endMacro) == 0){
            make_node(name, content,lineNum);
            return;
        }
        else{strcat(content, line);
            lineNum++;
        }
    }
}
