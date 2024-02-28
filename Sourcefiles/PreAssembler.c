#include "../Headers/PreAssembler.h"
char* commands[16];
/**
 * main function of preAssembler.
 * @param op - receives file to open macros for.
 * @return copy of original file but with macros saved and opened.
 */
FILE* preAssemble(FILE* op) {
    int macsFound = 0;
    int lineNum = 1;
    char line[MAX_LINE_LENGTH];
    char *firstWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    char *secondWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    char *thirdWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    node *current;
    initializeCommands();
    FILE *ModOrig = fopen("../Examples/postPreAssembler", "w");/*create file for after macros have been opened.*/
    while (!feof(op)) {
        fgets(line, MAX_LINE_LENGTH, op);
        if(line[0] == ';')
            continue;
        if (sscanf(line, "%s%s%s", firstWord, secondWord, thirdWord)) {
            if (isFileIndication(firstWord)) {
                strcpy(firstWord, secondWord);
                strcpy(secondWord, thirdWord);
            }
            if (strcmp(firstWord, "mcr") == 0) {
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
                    fputs(current->content, ModOrig);
                    lineNum++;
                }
            }
            else {
                fputs(line, ModOrig);
                lineNum++;
            }
        }
    }
    free_list(first);
    return ModOrig;
}

/**
 *
 * @param fp - original file to create macros from
 * @param name name of macro to create
 * @param lineNum line number the macro was created in.
 * @param macsFound positive if a macro has already been create, otherwise false.
 * @return returns the line number that was reached following the function
 */
int createMacro(FILE* fp, char* name, int lineNum, int macsFound){
    char line[MAX_LINE_LENGTH];
    char* tempCont = NULL;
    char* content = mallocError(MAX_LINE_LENGTH* sizeof(char));
    char* firstWord = mallocError(MAX_WORD_LENGTH * sizeof(char));/*to prevent segmentation fault*/
    while (!feof(fp)){
        fgets(line,MAX_LINE_LENGTH,fp);
        sscanf(line, "%s", firstWord);

        if(strcmp(firstWord, "endmcr") == 0){
            if (macsFound==0) {
                first= mallocError(sizeof(node));
                first=make_node(name, content, lineNum);
                return ++lineNum;
            }
            else{
                add_to_list(name, content, lineNum);
                return ++lineNum;
            }
        }
        else{
            printf("\n*");
            content = realloc(content, (strlen(content)+MAX_LINE_LENGTH)*sizeof(char));
            strcat(content, line);
        }
    }
    if(feof(fp)) {
        //print error here
    }
    return lineNum;
}
