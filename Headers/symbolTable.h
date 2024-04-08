
#include "general.h"

typedef struct line_table{
    int value;
    char name[MAX_WORD_LENGTH];
    char type[MAX_WORD_LENGTH];
    struct line_table *next;  /* Pointer to the next line */
} line_table;

line_table* make_symbol(char *name, char *type, int value);

void addToSymbolList(char *name, char *type, int value);

int searchSymbolList(char*);

int searchOperandSymbolList(char* name);

int findValue(char* name);

void free_line_table(line_table *line);

void freeTable(line_table *head);

void addToNum(line_table *line,int num);

void addIC(int IC);

int getValue(char* name);

int isExternal(char* name);

int existDefine(char* name);

extern line_table * first_Symbol;

int existDataSymbolList(char* name);

void updateDataValue(int);
void printSymbolTable(void);