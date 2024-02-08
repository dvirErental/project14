//
// Created by dvirerental on 1/30/24.
//

#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"

node* first;
node* make_node(char *name, char *content, int line_num){
    node *temp;

    temp = mallocError(sizeof(node));
    temp->name = mallocError((strlen(name) + 1) * sizeof(char));
    strcpy(temp->name, name);
    temp->content = mallocError((strlen(content) + 1) * sizeof(char));
    strcpy(temp->content, content);
    temp->line = line_num;
    temp->next = NULL;
}

node* existNode(char *name){
    node *temp = first;

    while (first != NULL) {
        if (strcmp(name, first->name) == 0) {/* If the node exists already */
            printf("Node %s already exists in the list\n", name);
            first = temp;
            return first;
        }
        first = first->next;
    }
    first = temp;
    return NULL;
}

void add_to_list(char *name, char *content, int line_num){
   node* temp = first;
   while (temp->next != NULL)
       temp = temp->next;
   temp->next = make_node(name, content, line_num);
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
