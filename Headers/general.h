#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_OF_COMMANDS 16
#define MAX_LINE_LENGTH 81
#define MAX_WORD_LENGTH 10
#define MAX_WORDS_IN_LINE 6
#define START_ADDRESS 100
extern char* commands[];
void initializeCommands(void);/*initialize the command*/
int isCommand (char*); /*check if the string is a command*/


typedef enum {
    false = 0,
    true
} boolean;


void *mallocError(long object_size);



void print_line_error(char*, int lineErr);/*print the error and the line its was happened*/
void print_error(char*);/*print error message*/
int isFileIndication(const char*);
char* translateToBinary(int);
