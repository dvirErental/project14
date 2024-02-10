#include "../Headers/firstPass.h"

table firstPass(FILE* fp) {
    int IC = 0, DC = 0;
    int address = 100;
    char *line[MAX_LINE_LENGTH];
    char* firstWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* secondWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* thirdWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* fourthWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* fifthWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    char* sixthWord = mallocError(sizeof(int)*MAX_WORD_LENGTH);
    while (!feof(fp)) {
        fgets(fp, line);

        {

        }
    }
}