//
// Created by dvir on 10/02/2024.
//

#include "../Headers/symbolTable.h"
line_table * first_Symbol;
line_table* make_symbol(char *name, char *type, int value){
    line_table *temp;

    temp = mallocError(sizeof(line_table));
    strcpy(temp->name, name);
    strcpy(temp->type, type);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void addToSymbolList(char *name, char *type, int value){
    line_table *temp = first_Symbol;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = mallocError(sizeof(line_table));
    temp->next = make_symbol(name, type, value);
}
int searchSymbolList(char* name){
    int location = 0;
    line_table *temp = first_Symbol;
    while (temp != NULL){
        location++;
        if (!(strcmp(temp->name,name)))
            return location;
        temp = temp->next;
    }
    return 0;
}

int findValue(char* name){
    int location = 0;
    line_table *temp = first_Symbol;
    while (temp != NULL){
        location++;
        if (!(strcmp(temp->name,name)))
            return temp->value;
        temp = temp->next;
    }
    return 0;
}

int searchOperandSymbolList(char* name){
    int location = 0;
    line_table *temp = first_Symbol;
    while (temp != NULL){
        location++;
        if (!(strcmp(temp->name,name)))
            if ((strcmp(temp->type,"data")==0)||(strcmp(temp->type,"external")==0))
                return location;
        temp = temp->next;
    }
    return 0;
}

int existDataSymbolList(char* name){
    int location = 0;
    line_table *temp = first_Symbol;
    while (temp != NULL){
        location++;
        if (!(strcmp(temp->name,name)))
            if (strcmp(temp->type,"data")==0)
                return 1;
        temp = temp->next;
    }
    return 0;
}


int getValue(char* name){
    line_table *temp = first_Symbol;
    while (temp != NULL){
        if (!(strcmp(temp->name,name)))
            return temp->value;
        temp = temp->next;
    }
    return 0;
}

int existDefine(char* name){
    line_table *temp = first_Symbol;
    while (temp != NULL){
        if (strcmp(temp->type,"mdefine")==0){
            if (!(strcmp(temp->name,name)))
                return 1;
        }
        temp = temp->next;
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
        freeLine(temp);
        head = head->next;
    }
}

void addIC(int IC){
    line_table *temp = first_Symbol;
    while ((temp != NULL)&&(temp->type!=NULL)){
        if (strcmp(temp->type,".data")==0){
            temp->value += 100+IC;
        }
        temp = temp->next;
    }
}

void addToNum(line_table *line,int num){
    line->value=line->value+num;
}

int isExternal(char* name){
    line_table *temp = first_Symbol;
    while (temp != NULL){
        if (strcmp(temp->type,"external")==0){
            if (!(strcmp(temp->name,name)))
                return 1;
        }
        temp = temp->next;
    }
    return 0;
}

