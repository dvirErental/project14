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

typedef struct Error {
    int error_id;
    char *error_msg;  /* Error message*/
} Error;

typedef enum {
    FALSE = 0,
    TRUE
} boolean;


void *mallocError(long object_size);

typedef enum ERROR_CODES {
    ERROR_CODE_0 = 0,
    ERROR_CODE_1,
    ERROR_CODE_2

} ERROR_CODES;

void print_line_error(int error_code, int lineErr);/*print the error and the line its was happened*/
void print_error(int error_code);/*print error message*/