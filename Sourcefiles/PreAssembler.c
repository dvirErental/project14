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
    initializeCommands();/*initialize the commands array*/
    FILE *ModOrig = fopen("../TextFiles/postPreAssembler", "w+");
    while (!feof(op)) {
        fgets(line, MAX_LINE_LENGTH, op);
        if(line[0] == ';')
            continue;
        if (sscanf(line, "%s%s%s", firstWord, secondWord, thirdWord)) {
            if (isSymbolDefinition(firstWord)) {/*if the first word is a symbol definition*/
                strcpy(firstWord, secondWord);/*copy the second word to the first word to ignore the symbol name*/
                strcpy(secondWord, thirdWord);/*copy the third word to the second word to ignore the symbol value*/
            }
            if (strcmp(firstWord, "mcr") == 0) {/*if found mcr create macro*/
                lineNum = createMacro(op, secondWord, lineNum, macsFound);
                macsFound++;
            }
            else if (macsFound)  {
                current = existNode(firstWord);
                if (current == NULL) {
                    fputs(line, ModOrig);
                    lineNum++;
                }
                else {
                    fputs(current->content, ModOrig);/*print the content of the macro to the postPreAssembler*/
                    lineNum++;
                }
            }
            else {
                fputs(line, ModOrig);/*print the line to the postPreAssembler*/
                lineNum++;
            }
        }
    }
    free_list(first);
    return ModOrig;
}




int createMacro(FILE* fp, char* name, int lineNum, int macsFound){
    char line[MAX_LINE_LENGTH];
    char* content = mallocError(MAX_LINE_LENGTH* sizeof(char));
    content[0] = '\0';
    char* firstWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    while (!feof(fp)){
        fgets(line,MAX_LINE_LENGTH,fp);
        sscanf(line, "%s", firstWord);


        if(strcmp(firstWord, "endmcr") == 0){/*if found endmcr end macro create the macro*/
            if (macsFound==0) {
                first=mallocError(sizeof(node));
                first=make_node(name, content, lineNum);
                return ++lineNum;
            }
            else{
                add_to_list(name, content, lineNum);
                return ++lineNum;
            }
        }
        else{/*else add the line to the content*/
            printf("\n*");
            char* temp = realloc(content, (strlen(content)+MAX_LINE_LENGTH)*sizeof(char));
            if (temp == NULL) {
                printf("Failed dynamically memory");
                free(content);
                exit(1);
            }
            content = temp;
            strcat(content, line);
        }
    }
    return lineNum;
}
