#include "buildOutPut.h"

#include <stdio.h>

// פונקציה שממירה ביט זוגי של שני ביטים לתו מוצפן בבסיס ארבע
char encodeBitsPair(int bit1, int bit2) {
    // הממיר מבסיס 2 לבסיס 10
    int value = bit1 * 2 + bit2;
    // הממיר מבסיס 10 לבסיס 4 מוצפן
    switch (value) {
        case 0:
            return '*';
        case 1:
            return '#';
        case 2:
            return '%';
        case 3:
            return '!';
        default:
            return '?'; // במקרה של ערך לא תקין
    }
}

void encodeBits(int bits[14], FILE* fp) {
    char encodedString[8]; // מחרוזת שמכילה את התווים המוצפנים
    int i, j = 0;
    for (i = 0; i < NUM_OF_BITS; i += 2) { // מעבר על הביטים בצעדים של שניים
        encodedString[j++] = encodeBitsPair(bits[i], bits[i + 1]);
    }
    encodedString[j] = '\n';
    fprintf(fp, "%s", encodedString);
}

void buildOB(infoTable* firstInfo) {
    int i = 0;
    FILE *filePointer;

    filePointer = fopen("ps.ob", "w");
    if (filePointer == NULL) {
        printf("לא ניתן לפתוח את הקובץ.\n");
        return;

    }
    while(firstInfo != NULL){
        while(firstInfo->address[i]>100){
            fprintf(filePointer, "%d ", firstInfo->address[i]);
            encodeBits((int*)(firstInfo->binaryCode[i]-'0'), filePointer);
            i++;
        }
        i=0;
        firstInfo = firstInfo->next;
    }
    fclose(filePointer);
}

void buildEnt(line_table* firstSym) {
    FILE *filePointer;
    filePointer = fopen("ps.ent", "w");
    if (filePointer == NULL) {
        printf("לא ניתן לפתוח את הקובץ.\n");
        return;
    }
    while (firstSym != NULL) {
        if (strcmp(firstSym->type, "entry") == 0){
            fprintf(filePointer, "%s %d\n", firstSym->name, firstSym->value);}
        firstSym = firstSym->next;
    }
    fclose(filePointer);
}

void buildExt(line_table* firstSym) {
    FILE *filePointer;
    filePointer = fopen("../TextFiles/ps.ext", "w");
    if (filePointer == NULL) {
        printf("לא ניתן לפתוח את הקובץ.\n");
        return;
    }
    while (firstSym != NULL) {
        if (strcmp(firstSym->type, "external") == 0){
            fprintf(filePointer, "%s %d\n", firstSym->name, firstSym->value);}
        firstSym = firstSym->next;
    }
    fclose(filePointer);
}