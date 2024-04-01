#include <stdio.h>
#include "../Headers/PreAssembler.h"
//
int main(){
    FILE* fp = fopen("../TextFiles/input1", "r");
    preAssemble(fp);
    printf("the code worked");
}