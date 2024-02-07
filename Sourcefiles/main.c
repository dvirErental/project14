#include <stdio.h>
#include "../Headers/PreAsse.h"

int main(){
    initializeCommands();
    FILE* fp = fopen("../Examples/input1", "r");
    preAssemble(fp);
}