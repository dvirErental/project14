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
 * checks if a is a legal name for a file (final letter ':')
 * @param a name to check
 * @return TRUE if it's legal, otherwise FALSE.
 */
int isSymbolDefinition(const char* a){
    int i = 0;
    while (a[i] != '\0') {
        if ((a[i] <= 'Z' && a[i] >= 'A') || (a[i] <= '9' && a[i] >= '0') || (a[i] <='z' && a[i] >= 'a'))
            i++;
        else
            return 0;
    }
    if((a[i] == ':' && a[i+1] == '\0') && ((a[0] >='a' &&a[0] <='z') || (a[0] >= 'A') && a[0] <='Z'))
        return 1;
    return 0;
}


/**
 * translates given number to its binary representation, keeps it to length of length - can lose data if used incorrectly
 * @param num  - num to translate
 * @param length - number of bits to return
 * @return nums' representation in binary (in 'length' bits)
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

int isRegisterName(const char* name){
    if (name[0] == 'r' && name[1] >= '0' && name[1] <= '7' && name[2] == '\0')
        return name[1] - '0';
    return FALSE;
}


/*void flipBits(char* word){
    int index;
    for(index = 0; index<NUM_OF_BITS; index++){
        if(word[index] == '0')
            word[index] = '1';
        else
            word[index] = '0';
    }
}*/

int wordLength(const char *word) {
    int length = 0;
    while (*word && !isspace(*word)) {
        length++;
        word++;
    }
    return length;
}
int contains_brackets(const char *word) {
    int found_open = 0;
    while (*word) {
        if (*word == '[')
            found_open = 1;

        else if (*word == ']') {
            if (found_open)
                return 1;
        }

        word++;
    }
    return 0;
}

int calculateL(char* line, int isSymbolDefinition){
    int L = 0;
    int index = 0;
    char* currentWord = mallocError(sizeof(char) * MAX_WORD_LENGTH);
    while(index < MAX_LINE_LENGTH){
        sscanf(&line[index], "%s", currentWord);
        if (isSymbolDefinition){
            isSymbolDefinition = FALSE;
            continue;
        }
        if (strcmp(currentWord,"" ) == 0)
            break;
        if (contains_brackets(currentWord))
            L+=2;
        else
            L++;
        index+= wordLength(currentWord);
    }
    return L;
}

long lengthOf(const char* word){
    int counter = 0;
    while(word[counter] != '\0')
        counter++;
    return counter;
}
