#include "general.h"
/**
 * initializes the 16 commands into an commands array
 */
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
/**
 * checks if parameter is the name of a command
 * @param word parameter to check
 * @return the index of the command if it is in fact a command, otherwise -1
 */
int isCommand(char* word){
    int index;
    for (index = 0; index <NUM_OF_COMMANDS; index++){
        if (strcmp(word,commands[index]) == 0)
            return index;
    }
    return -1;
}

/**
 * modified version of malloc, but checks for error
 * @param object_size
 * @return pointer to space for the object the function was called for
 */
void *mallocError(long object_size) {
    void *object_ptr = malloc(object_size);
    if (object_ptr == NULL) {
        printf("Failed dynamically memory");
    }
    return object_ptr;
}

/**
 * checks if a is a legal name for a file (all caps, final letter ':')
 * @param a name to check
 * @return true if it's legal, otherwise false.
 */
int isSymbolDefinition(const char* a){
    int i = 0;
    while (a[i] != '\0') {
        if ((a[i] <= 'Z' && a[i] >= 'A') || (a[i] <= '9' && a[i] >= '0'))
            i++;
    }
    if(a[i] == ':' && a[i+1] == '\0')
        return true;
    return false;
}


/**
 * translates given number to it's binarary representation, keeps it to length of length - can lose data if used incorrectly
 * @param num  - num to translate
 * @param length - number of bits to return
 * @return num's representation in binary (in 'length' bits)
 */
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
