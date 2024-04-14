#include <stdio.h>
#include "../Headers/PreAssembler.h"
#include "../Headers/secondPass.h"

int main(int argc, char* argv[]){
    FILE* fp;
    char* fileName[LONGEST_POSSIBLE_FILE_NAME];/*assuming longest possible file name is 20*/
    int index = 1;
    while(index<argc){
        strcpy(fileName, strcat(argv[index], ".as"));
        fp = fopen(fileName, "r");
        fp = preAssemble(fp, argv[index]);
        firstPass(fp);
        secondPass(fp);
        index++;
    }
}