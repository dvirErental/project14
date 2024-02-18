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
        print_error("Failed dynamically memory");
    }
    return object_ptr;
}


void print_line_error(char* error_content, int lineErr) {
    fprintf(stderr,"in line %d ERROR %s\n",  lineErr, error_content);
}

void print_error(char* error) {
    fprintf(stderr, error);
}


int isFileIndication(const char* a){
    int i = 0;
    while (a[i] != '\0'){
        if((a[i] <= 'Z' && a[i] >= 'A') || (a[i] <= '9' && a[i] >= '0') || (strcmp(a, ".define") == 0) || (a[i] == ':'))
            i++;
        else
            return 0;
    }
    if (a[i-1] != ':')
        return 0;
    return 1;
}

char* translateToBinary(int num) {
    int bits = sizeof(int) * 8;
    char *binaryStr = (char *) malloc(bits + 1); // +1 for null terminator

    // Check for memory allocation failure
    if (binaryStr == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Null terminate the string
    binaryStr[bits] = '\0';

    // Iterate through each bit and set the corresponding character in the string
    for (int i = bits - 1; i >= 0; i--) {
        binaryStr[bits - 1 - i] = ((num >> i) & 1) ? '1' : '0';
    }

    return binaryStr;
}