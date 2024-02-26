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
            return index;
    }
    return -1;
}
void *mallocError(long object_size) {
    void *object_ptr = malloc(object_size);
    if (object_ptr == NULL) {
        printf("Failed dynamically memory");
    }
    return object_ptr;
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

char* translateToTwosCompliment(int num,int length) {
    char *str = (char *)malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    str[length] = '\0'; // Null-terminate the string
    // Filling the string with '0' or '1' based on the two's complement representation
    int mask = 1 << (length - 1);
    for (int i = 0; i < length; i++) {
        if (num & mask)
            str[i] = '1';
        else
            str[i] = '0';
        mask >>= 1;
    }

    return str;
}

boolean is_whitespace(char c) {
    return c == ' ' || c == '\t'; // Add other whitespace characters if needed
}
