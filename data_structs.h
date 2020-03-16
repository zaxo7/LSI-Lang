#include "global.h"
#include "functions.h"

scope* add_son(scope* , scope* );

scope* init_scope(void);

scope* get_father(scope* ,int );

int tab_push_scope(scope* , scope* );

//int tab_push(table* , int );
void* tab_push(void* tab, int size, void* val, int type);


void* init_args(int id, int mode);

void* add_arg(function* func, int id, int mode)
;


int build_table(int , table* , int );

void* allocate_table(int , int , int*) ;

void* init_table(int );






void print_sym_tab();

void print_tables();

void print_functions();