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
        print_error(ERROR_CODE_1);
    }
    return object_ptr;
}

struct Error errors[4] = {
        //errors[0].
        {ERROR_CODE_0,  "No Error"},
        {ERROR_CODE_1,  "Failed dynamically memory"},
        {ERROR_CODE_2, "Macro has more than one definition"},
        {ERROR_CODE_3, "two definitions with same name"}
};

void print_line_error(int error_code, int lineErr) {
    fprintf(stderr,"in line %d ERROR %s\n",  lineErr, errors[error_code].error_msg);
}

void print_error(int error_code) {
    fprintf(stderr,"ERROR %s\n", errors[error_code].error_msg);
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

char* translateToBinary(int num,int digits) {
    char *binaryStr = (char *) malloc(digits + 1); // +1 for null terminator

    // Check for memory allocation failure
    if (binaryStr == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Null terminate the string
    binaryStr[digits] = '\0';

    // Iterate through each bit and set the corresponding character in the string
    for (int i = digits - 1; i >= 0; i--) {
        binaryStr[digits - 1 - i] = ((num >> i) & 1) ? '1' : '0';
    }

    return binaryStr;
}

char* command_to_machine_code(char * command,int type_op1,int type_op2,int ARE){
    int opcode=isCommand(command);
    char machineCode[NUM_OF_BITS]="0000";
    strcat(machineCode, translateToBinary(opcode,BITS_IN_OPCODE));
    strcat(machineCode, translateToBinary(type_op1,BITS_IN_OP1));
    strcat(machineCode, translateToBinary(type_op2,BITS_IN_OP2));
    strcat(machineCode, translateToBinary(ARE,BITS_IN_ARE));

}
