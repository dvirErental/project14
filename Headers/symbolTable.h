//
// Created by dvir on 10/02/2024.
//

#ifndef PROJECT14REAL_SYMBOLTABLE_H
#define PROJECT14REAL_SYMBOLTABLE_H
#include "general.h"
typedef struct line_table{
    int value;
    char *name;
    char* type;
    struct line_table *next;  /* Pointer to the next line */
} line_table;

line_table* make_symbol(char *name, char *type, int value);

void addToSymbolList(char *name, char *type, int value);

int searchSymbolList(char*);

void free_line_table(line_table *line);

void freeTable(line_table *head);

void addToNum(line_table *line,int num);

void addIC(int IC);

extern line_table * first_Symbol;
#endif //PROJECT14REAL_SYMBOLTABLE_H
extern line_table * first_Symbol;
void updateDataValue(int);