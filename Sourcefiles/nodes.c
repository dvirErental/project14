
#include "nodes.h"


node* first;

/**
 * primary function of nodes.h - creates a macro with the given parameters.
 * @param name - the name of the macro.
 * @param content - the content to store inside the macro
 * @param line_num - the line Number in which the macro was declared in.
 * @return a pointer to the new macro.
 */
node *make_node(char *name, char *content, int line_num){
    node *temp;

    temp = mallocError(sizeof(node));
    temp->name = mallocError(((strlen(name)) + 1) * sizeof(char));
    strcpy(temp->name, name);
    temp->content = mallocError((strlen(content) + 1) * sizeof(char));
    strcpy(temp->content, content);
    temp->line = line_num;
    temp->next = NULL;
    return temp;
}

/**
 * checks if a macro already exists with the name given in the parameter
 * @param name the name to check
 * @return a pointer to the macro if one exists with the same name as the parameter, otherwise NULL.
 */
node* existNode(char *name){/* Check if the node exists in the list */
    node *temp = copyNode(first);

    while (temp != NULL) {
        if (strcmp(name, temp->name) == 0) {/* If the node exists already */
            printf("Node %s already exists in the list\n", name);
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/**
 * adds a macro to the macro list.
 * @param name the name of the new macro
 * @param content the content of the new macro
 * @param line_num the line number in which the new macro was declared upon.
 */
void add_to_list(char *name, char *content, int line_num){/* Add a new node to the list */
    node* temp = first;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = make_node(name, content, line_num);
}

/**
 * free the node
 * @param the node to free
 */
void free_node(node *node1){
    /* Free memory allocated for the name, content and node */
    free(node1->name);
    free(node1->content);
    free(node1);
}

/**
 * Frees memory for the current node and its contents while storing the current node in a temporary pointe
 * @param head - the first node in the list to free.
 */
void free_list(node *head){
    while(head != NULL) {
        node *temp = head;
        head = head->next;
        free_node(temp);
    }
}

/**
 * copies a given node
 * @param old - the node to copy
 * @return a pointer to the copied node.
 */
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
