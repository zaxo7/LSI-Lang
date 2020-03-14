#ifndef DEF_FUNCTIONS
#define DEF_FUNCTIONS
#include "global.h"
#include "data_structs.h"

int yyerror(char* );

int declare(char* );

void init_all(void);

int set_val(int , void* , int );

int set_const(int );

variable* get_var(int );

int auto_set_type(int );



#endif