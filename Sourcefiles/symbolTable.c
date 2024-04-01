//
// Created by dvir on 10/02/2024.
//

#include "../Headers/symbolTable.h"
line_table * first_Symbol;
line_table* make_symbol(char *name, char *type, int value){
    line_table *temp;

    temp = mallocError(sizeof(line_table));
    temp->name = mallocError((strlen(name) + 1) * sizeof(char));
    strcpy(temp->name, name);
    temp->type = mallocError((strlen(type) + 1) * sizeof(char));
    strcpy(temp->type, type);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void addToSymbolList(char *name, char *type, int value){
    line_table *temp = first_Symbol;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = make_symbol(name, type, value);
}
int searchSymbolList(char* name){
    int location = 0;
    line_table *temp = first_Symbol;
    while (temp != NULL){
        location++;
        if (!(strcmp(temp->name,name)))
            return location;
    }
    return 0;
}

void freeLine(line_table *line){
    /* Free memory allocated for the name, content and node */
    free(line->name);
    free(line->type);
    free(line);
}

void freeTable(line_table *head){
    /* Free memory for the current node and its contents while storing the current node in a temporary pointer */
    while(head != NULL) {
        line_table *temp = head;
        head = head->next;
        freeLine(temp);
    }
}

void addIC(int IC){
    line_table *temp = first_Symbol;
    while (temp!= NULL){
        if (strcmp(temp->type,"data")==0){
            temp->value += 100+IC;
        }
        temp = temp->next;
    }
}

void addToNum(line_table *line,int num){
    line->value=line->value+num;
}
