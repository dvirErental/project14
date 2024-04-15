#include <stdio.h>
#include "../Headers/PreAssembler.h"
#include "../Headers/secondPass.h"

int main(int argc, char* argv[]){
    FILE* fp;
    char* fileName[LONGEST_POSSIBLE_FILE_NAME];/*assuming longest possible file name is 20*/
    int index = 1;
    while(index<argc) {
        strcpy(fileName, argv[index]);
        strcat(fileName, ".as");
        fp = fopen(fileName, "r");
        fp = preAssemble(fp, argv[index]);
        fclose(fp);
        strcpy(fileName, argv[index]);
        strcat(fileName, ".am");
        fp = fopen(fileName, "r");
        firstPass(fp);
        secondPass(fp, argv[index]);
        index++;
    }
}