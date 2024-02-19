#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_OF_COMMANDS 16
#define MAX_LINE_LENGTH 81
#define MAX_WORD_LENGTH 10
#define NUM_OF_BITS 14
#define BITS_IN_OPCODE 4
#define BITS_IN_OP1 2
#define BITS_IN_OP2 2
#define BITS_IN_ARE 2

extern char* commands[];
void initializeCommands(void);/*initialize the command*/
int isCommand (char*); /*check if the string is a command*/

typedef enum {
    false = 0,
    true = 1
} boolean;

void *mallocError(long object_size);

int isFileIndication(const char*);
char* translateToBinary(int,int);
char* command_to_machine_code(char * command,int type_op1,int type_op2,int ARE);
