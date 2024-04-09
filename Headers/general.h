#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define NUM_OF_COMMANDS 16
#define MAX_LINE_LENGTH 81
#define MAX_WORD_LENGTH 10
#define MAX_NUM_OF_WORDS 10
#define NUM_OF_BITS 14
#define BITS_IN_OPCODE 4
#define BITS_IN_OP1 2
#define BITS_IN_OP2 2
#define BITS_IN_ARE 2
#define BITS_IN_REGISTER_LENGTH 3
#define FALSE 0
#define TRUE 1
extern char* commands[];
void initializeCommands(void);/*initialize the command*/
int isCommand (char*); /*check if the string is a command*/
int isSymbolDefinition(const char* );/*check if the string is a symbol definition*/
int containsBrackets(const char*);/*check if the string contains brackets*/
int whichRegister(const char* name);/*returns the register number*/
int lengthOf(const char*);/*returns the length of the string*/
void *mallocError(long object_size);
int wordLength(const char*);/*returns the length of the word*/
char* translateToTwosCompliment(int,int);/*translate the number to twos compliment in size we want*/
int isRegisterName(const char*);/*check if the string is a register name*/
int calculateL(char* line, int isFileIndication);
char* cutString(char *str, char delimiter) ;/*cut the string by the delimite and return the new string*/
int isWord(const char *str) ;/*check if the string is a word*/
char* removeLastChar(char* str);/*remove the last char from the string and return the new string*/
