#include <stdio.h>
#include "../Headers/PreAssembler.h"
#include "../Headers/secondPass.h"
int main(){
    /*FILE* pa = fopen("../TextFiles/input1", "r");
    FILE* ppa = preAssemble(pa);
    fclose(ppa);
    fclose(pa);
    printf("the code worked");*/
    firstPass();
    secondPass();
}