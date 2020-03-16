#ifndef DEF_GLOBAL

#define DEF_GLOBAL


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define YYSTYPE value

#define MAX_VAR 50

#define NILL 0

char* ProgName;

int b;

enum operateurs
{
	_plus, _minus, _mult, _div, _mod, _pow
};

enum rel_op
{
	_inf, _sup, _equal, _and, _or, _sup_equal, _inf_equal
};

enum types
{
	I, F, L, C, ID, FUN, PRO, STR, TAB, TO_SET, E_, ES_, S_
};

typedef struct Val
{
	int id;
	int type;
	void* val;
} value;

typedef struct Var
{
	int id;
	value* var;
	char* name;
	int scope_id;
	bool constant;
} variable;


typedef struct Sc
{
	int id;
	char *name;
	int nbr_sons;
	struct Sc **sons;
} scope;

typedef struct Tab
{
	int dimensions;
	int* size;
	int type;
	void* table;
}table;

typedef struct F
{
	int nbr_E;
	int* E;
	int nbr_S;
	int* S;
	int nbr_ES;
	int* ES;
	int ret_type;
}function;

scope *scope_tree, *current_scope;

int scope_unique_id, variable_unique_id;

variable sym_tab[MAX_VAR];




#endif