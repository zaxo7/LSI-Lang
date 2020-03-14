#include "global.h"
#include "functions.h"

scope* add_son(scope* , scope* );

scope* scope_init(void);

scope* get_father(scope* ,int );

int tab_push_scope(scope* , scope* );

int tab_push(table* , int );

int build_table(int , table* , int );

void* allocate_table(int , int , int*) ;

void* init_table(int );

void print_sym_tab();

void print_tables();

void permut(int* , int);