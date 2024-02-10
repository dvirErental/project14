//
// Created by dvir on 10/02/2024.
//

#ifndef PROJECT14REAL_TABLE_H
#define PROJECT14REAL_TABLE_H
#include "general.h"
typedef struct line_table{
    int value;
    char *name;
    char* type;
    struct line_table *next;  /* Pointer to the next line */
} line_table;

#endif //PROJECT14REAL_TABLE_H
