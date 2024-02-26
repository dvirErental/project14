//
// Created by shaih on 2/18/2024.
//

#include "binaryTranslation.h"
char* change_to_machine_code(char * command,int type_op1,int type_op2,int ARE){
    int opcode=isCommand(command);
    char machineCode[NUM_OF_BITS]="0000";
    strcat(machineCode, translateToBinary(opcode,BITS_IN_OPCODE));
    strcat(machineCode, translateToBinary(type_op1,BITS_IN_OP1));
    strcat(machineCode, translateToBinary(type_op2,BITS_IN_OP2));
    strcat(machineCode, translateToBinary(ARE,BITS_IN_ARE));
}



