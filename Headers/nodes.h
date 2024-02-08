/* Represents a node in a linked list */
typedef struct node {
    char *name;         /* Name node */
    char *content;      /* Content stored in the node */
    int line;           /* Line number of the macro */
    struct node *next;  /* Pointer to the next node in the linked list */
} node;

node* make_node(char *name, char *content, int line_num);/* the function create node for a macro with char name as the name of macro
 content is the content and line_num is the line that macro need going to*/

void copy_head(node* old,node* new);/*copy the new to the head*/

node *existNode(char *name);/*Searches for a node in a linked list. return the node of the macro if it was found and NULL if didn't*/

void add_to_list (char *name, char *content, int line_num); /*Adds a node to the linked list.*/

void free_node(node *node1);/* Free memory of the node*/

void free_list(node *head);/*free list*/

extern node* first;
