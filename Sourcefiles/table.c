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
    line_table * temp = first;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = make_line_table(name, type, value);
}
void copy_head(node* old,node* new){
    /* old = mallocError(strlen(new->name)*sizeof(char)+(strlen(new->content)*sizeof(char))+sizeof(new->next));*/
    old = mallocError(sizeof(new));
    if(new->name == NULL)
        old->name = NULL;
    old->name = new->name;        /* Set the name of the node */
    old->content = new->content;  /* Set the content string of the node */
    old->line = new->line;    /* Set the line number associated with the content */
}

void free_node(node *node1){
    /* Free memory allocated for the name, content and node */
    free(node1->name);
    free(node1->content);
    free(node1);
}

void free_list(node *head){
    /* Free memory for the current node and its contents while storing the current node in a temporary pointer */
    while(head != NULL) {
        node *temp = head;
        head = head->next;
        free_node(temp);
    }
}
node* copyNode(node* old){
    node* new;
    new = mallocError(sizeof(node));
    new->name = mallocError((strlen(old->name) + 1) * sizeof(char));
    strcpy(new->name, old->name);
    new->content = mallocError((strlen(old->content) + 1) * sizeof(char));
    strcpy(new->content, old->content);
    new->line = old->line;
    new->next = old->next;
    return new;
}
