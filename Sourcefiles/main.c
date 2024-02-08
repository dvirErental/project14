#include <stdio.h>
#include "../Headers/PreAssembler.h"
//
int main(){
    FILE* fp = fopen("../Examples/input1", "r");
    preAssemble(fp);
    printf("the code worked");
}