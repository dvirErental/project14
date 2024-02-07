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
void *handle_malloc(long object_size) {
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
};

void print_line_error(int error_code, int lineErr) {
    fprintf(stderr,"in line %d ERROR %s\n",  lineErr, errors[error_code].error_msg);
}

void print_error(int error_code) {
    fprintf(stderr,"ERROR %s\n", errors[error_code].error_msg);
}
