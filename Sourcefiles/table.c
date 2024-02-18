//
// Created by dvir on 10/02/2024.
//

#include "../Headers/table.h"
line_table * first;
line_table * make_line_table(char *name, char *type, int value){
    line_table *temp;

    temp = mallocError(sizeof(line_table));
    temp->name = mallocError((strlen(name) + 1) * sizeof(char));
    strcpy(temp->name, name);
    temp->type = mallocError((strlen(type) + 1) * sizeof(char));
    strcpy(temp->type, type);
    temp->value = value;
    temp->next = NULL;
}

void add_to_list(char *name, char *type, int value){
    line_table *temp = first;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = make_line_table(name, type, value);
}
void searchList(char* name){
    line_table *temp = first;
    while (temp != NULL )
}

void free_line_table(line_table *line){
    /* Free memory allocated for the name, content and node */
    free(line->name);
    free(line->type);
    free(line);
}

void free_table(line_table *head){
    /* Free memory for the current node and its contents while storing the current node in a temporary pointer */
    while(head != NULL) {
        line_table *temp = head;
        head = head->next;
        free_line_table(temp);
    }
}

