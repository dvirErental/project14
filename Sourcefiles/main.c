#include <stdio.h>
#include "../Headers/PreAssembler.h"
#include "../Headers/firstPass.h"

int main(){
    /*FILE* pa = fopen("../TextFiles/input1", "r");
    FILE* ppa = preAssemble(pa);
    fclose(ppa);
    printf("the code worked");*/
    firstPass();
}