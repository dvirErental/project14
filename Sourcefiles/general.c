#include "general.h"

void initializeCommands(void){
    commands[0] = "mov";
    commands[1] = "cmp";
    commands[2] = "add";
    commands[3] = "sub";
    commands[4] = "not";
    commands[5] = "clr";
    commands[6] = "lea";
    commands[7] = "inc";
    commands[8] = "dec";
    commands[9] = "jmp";
    commands[10] = "bne";
    commands[11] = "red";
    commands[12] = "prn";
    commands[13] = "jsr";
    commands[14] = "rts";
    commands[15] = "hlt";
}
int isCommand(char* word){
    int index;
    for (index = 0; index <NUM_OF_COMMANDS; index++){
        if (strcmp(word,commands[index]) == 0)
            return 0;
    }
    return -1;
}
void *mallocError(long object_size) {
    void *object_ptr = malloc(object_size);
    if (object_ptr == NULL) {
        print_error(ERROR_CODE_1);
    }
    return object_ptr;
}

Error errors[] = {
        {ERROR_CODE_0,  "No Error"},
        {ERROR_CODE_1,  "Failed dynamically memory"},
        {ERROR_CODE_2, "Macro has more than one definition"},
        {ERROR_CODE_3, "two definitions with same word"},
};

void print_line_error(int error_code, int lineErr) {
    fprintf(stderr,"in line %d ERROR %s\n",  lineErr, errors[error_code].error_msg);
}

void print_error(int error_code) {
    fprintf(stderr,"ERROR %s\n", errors[error_code].error_msg);
}
