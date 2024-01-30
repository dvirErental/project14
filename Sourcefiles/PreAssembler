void copyFile(FILE* op){
    FILE* cop = fopen("ChangedOriginal", "w");
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, op) != NULL){
        fputs(line, cop);
    }
    return;
}
