#include <stdio.h>
#include "../Headers/PreAssembler.h"
#include "../Headers//firstPass.h"
//
int main(){
    FILE* pa = fopen("../TextFiles/input1", "r");
    preAssemble(pa);
    printf("the code worked");
    FILE* fp = fopen("../TextFiles/postPreAssembler", "r");
    firstPass(fp);
}