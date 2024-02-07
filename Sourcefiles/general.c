#include "general.h"

void initializeCommands(void){
    commands = (char*[]){"mov", "cmp", "add", "sub", "not", "clr", "lea",
                         "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts",
                         "hlt"};
}
int isCommand(char* word){
    int index;
    for (index = 0; index <NUM_OF_COMMANDS; index++){
        if (strcmp(word,commands[index]) == 0)
            return 0;
    }
    return -1;
}
