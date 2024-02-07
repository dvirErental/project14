#include <stdio.h>
#include "../Headers/PreAsse.h"

int main(){

    FILE* fp = fopen("../Examples/input1", "r");
    preAssemble(fp);
}