#include "../Headers/general.h"
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
        exit(-1);
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
            break;
    }
    if((a[i] == ':' && a[i+1] == '\0') && ((a[0] >='a' &&a[0] <='z') || ((a[0] >= 'A') && a[0] <='Z')))
        return 1;
    return 0;
}


/**
 * translates given number to it's binary representation, keeps it to length of length - can lose data if used incorrectly
 * @param num  - num to translate
 * @param length - number of bits to return
 * @return nums' representation in binary (in 'length' bits)
 */
char* translateToTwosCompliment(int num,int length) {
    char *str = malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    str[length] = '\0'; // Null-terminate the string
    /* Filling the string with '0' or '1' based on the two's complement representation*/
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
/**
 * checks if a given char* is identical to the name of one of the registers
 * @param name the char* to check
 * @return 1(True) if the given string is a register, otherwise 0(False)
 */
int isRegisterName(const char* name){
    if (name[0] == 'r' && name[1] >= '0' && name[1] <= '7' && (name[2] == '\0' || (name[2] == ',' && name[3] == '\0')))
        return TRUE;
    return FALSE;
}
/**
 * return which number register the given string is representing
 * @param name the string to check
 * @return the number of the register.
 */
int whichRegister(const char* name){
    if (name[1] == '0')
        return 0;
    if (name[1] == '1')
        return 1;
    if (name[1] == '2')
        return 2;
    if (name[1] == '3')
        return 3;
    if (name[1] == '4')
        return 4;
    if (name[1] == '5')
        return 5;
    if (name[1] == '6')
        return 6;
    if (name[1] == '7')
        return 7;
    return -1;
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
int containsBrackets(const char *word) {
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

int calculateL(char *line, int isFileIndication) {
    int index;
    char words[MAX_NUM_OF_WORDS][MAX_WORD_LENGTH] = {"","","","","","","","","",""};
    int numOfWords = sscanf(line, "%s%s%s%s%s%s%s%s%s%s", words[0], words[1], words[2], words[3], words[4], words[5], words[6],
           words[7], words[8], words[9]);
    int actualNum = numOfWords;
    for(index = 0; index<numOfWords; index++){
        if (containsBrackets(words[index]))
            actualNum++;
    }
    if (actualNum-isFileIndication == 3 && isRegisterName(words[isFileIndication+1]) &&
    isRegisterName(words[isFileIndication+2]))
        actualNum--;
    return actualNum-isFileIndication;
}
int lengthOf(const char* word){
    int index = 0;
    while(word[index] != '\0')
        index++;
    return index;
}

char* cutString(char *str, char delimiter) {
    char *delimiterPtr = strchr(str, delimiter);
    if (delimiterPtr != NULL) {
        char *substring = delimiterPtr + 1;
        return substring;
    }
    return str;
}

int isWord(const char *str) {
    int wordLength = strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    const char *pos = str + wordLength;

    if (*pos == ' ' || *pos == '\n' || *pos == '\0') {
        return 1;
    }

    return 0;
}