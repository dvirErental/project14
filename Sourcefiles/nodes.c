
#include "nodes.h"


node* first;
node *make_node(char *name, char *content, int line_num){/* Create a new node */
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

void add_to_list(char *name, char *content, int line_num){/* Add a new node to the list */
    node* temp = first;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = make_node(name, content, line_num);
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
node* copyNode(node* old){ /*copy a node to a new node*/
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
