#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define NUM_OF_COMMANDS 16
#define MAX_LINE_LENGTH 81
#define MAX_WORD_LENGTH 10
#define MAX_NUM_OF_WORDS 10
#define NUM_OF_BITS 14
#define MAX_COMMAND_LENGTH 5
#define BITS_IN_OPCODE 4
#define BITS_IN_OP1 2
#define BITS_IN_OP2 2
#define BITS_IN_ARE 2
#define BITS_IN_REGISTER_LENGTH 3
#define MIN_NUM -32767
#define FALSE 0
#define TRUE 1
extern char* commands[];
void initializeCommands(void);/*initialize the command*/
int isCommand (char*); /*check if the string is a command*/
int isSymbolDefinition(const char* );



void *mallocError(long object_size);
int wordLength(const char*);
int isFileIndication(const char*);
char* translateToTwosCompliment(int,int);
int isRegisterName(const char*);
void flipBits(char* word);
int calculateL(char* line, int isFileIndication);
long lengthOf(const char*);
