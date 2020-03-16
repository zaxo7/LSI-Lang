#include "data_structs.h"

//la fonction qui ajoute un sous scope(environement)
scope* add_son(scope* root, scope* son)
{
	if(!root)
		printf("can't add son to NULL father\n");
	else
	{
		printf("adding son with id=%d to %d\n", son->id, root->id);
		tab_push_scope(root, son);
	}
	return son;
}


//la fonction qui retourne le scope pére
scope* get_father(scope* root, int id)
{
	printf("looking for the father of %d\n", id);
	for (int i = 0; i < root->nbr_sons; ++i)
	{
		if(root->sons[i]->id == id)
			return root;
		else
			if( get_father(root->sons[i], id))
				return get_father(root->sons[i], id);
			else
				continue;
	}
	

	printf("error get father\n");
	return NULL;
}
//la fonction qui initialise un scope et le donner un id unique
scope* init_scope(void)
{
	//printf("scope_init:creating a son %d\n", scope_unique_id);
	scope* son = NULL;
	son = malloc(sizeof(scope));
	if(!son)
		yyerror("init_scope:malloc error");

	son->id = scope_unique_id++;
	son->name = NULL;
	son->nbr_sons = 0;
	son->sons = NULL;

	return son;
}

//ajouter un scope a la table du scope
int tab_push_scope(scope* root, scope* son)
{
	//si il n'a aucun fils
	if(!root->nbr_sons)
	{
		root->sons = (scope**)malloc(sizeof(scope*));
	}
	else
	{
		root->sons = realloc(root->sons, sizeof(scope*) * root->nbr_sons + 1);

		if(!root->sons) // si la reallocation ne marche pas on alloue et en copie les données
		{
			printf("tab_push_scope:realloc failed using malloc\n");
			
			scope** new_tab = NULL;

			new_tab = malloc(sizeof(scope*) * root->nbr_sons + 1);

			if(!new_tab)
				yyerror("tab_push_scope:error with malloc");

			memcpy((void*)new_tab, (void*)root->sons, root->nbr_sons);
			
			
			free(root->sons);
			

			root->sons = new_tab;
			
		}

	}

	root->sons[root->nbr_sons++] = son;
	printf("added one son new nbr_sons=%d new son_ptr %p\n", root->nbr_sons, root->sons[root->nbr_sons-1]);
	printf("new table of sons\n");
	for (int i = 0; i < root->nbr_sons; ++i)
	{
		printf("%p, \n", root->sons[i]);
	}
	return 1;
}
//ajouter une entrée a la table de tailles pour un tableau
/*int tab_push(table* tab, int size)
{
	if(!tab)
		yyerror("tab_push: error table NULL");
	else
	{
		int* new_tab = realloc(tab->size, sizeof(int) * tab->dimensions + 1);

		if(!new_tab) // si la reallocation ne marche pas on alloue et en copie les données
		{
			new_tab = malloc(sizeof(table*) * tab->dimensions + 1);

			if(!new_tab)
				yyerror("tab_push:error can't allocate a new cell");

			memcpy((void*)new_tab, (void*)tab->size, tab->dimensions);
			
			
			free(tab->size);
			tab->size = new_tab;
		}

		tab->size[tab->dimensions++] = size;

	}


	// printf("pushed %d => new size %d\n", tab->size[tab->dimensions-1], tab->dimensions);
		return 1;
}*/

int build_table(int id, table* tab, int type)
{
	tab->table = allocate_table(type, tab->dimensions, tab->size);
	if(!tab->table)
		yyerror("build_table:error allocating the table\n");

	tab->type = type;

	//permut(tab->size, tab->dimensions);


	set_val(id, (void*)tab, TAB);

	return 1;
}

void* allocate_table(int type, int dimensions, int* size)
{
	
	void* tmp = NULL;

	int tab_size = 0;

	for (int i = 0; i < dimensions; ++i)
	{
		tab_size += size[i];
	}

	int unit;
	switch(type)
	{
		case I:
			unit = sizeof(int);
			break;
		case F:
			unit = sizeof(float);
			break;
		case L:
			unit = sizeof(long);
			break;
		case C:
			unit = sizeof(char);
			break;
		default:
			yyerror("allocate_table:can't find the type");
			break;
	}


	tmp = malloc(unit * tab_size);

	if(!tmp)
		yyerror("allocate_table:error with pointer\n");

	memset(tmp, 0, unit * tab_size);


	return tmp;


}



void* init_table(int size)
{
	//printf("intialising table\n");
	table* tab = (table*)malloc(sizeof(table));

	if(!tab)
		yyerror("init_table:error with malloc");

	tab->dimensions = 1;
	tab->size = (int*)malloc(sizeof(int*));

	tab->size[0] = size;

	tab->type = -1;

	tab->table = NULL;

	return tab;
}

void* init_args(int id, int mode)
{
	function* val = NULL;

	val = malloc(sizeof(function));

	if(!val)
		yyerror("init_args:malloc error");

	memset(val, 0, sizeof(function));
	switch(mode)
	{
		case E_:
			val->nbr_E++;
			val->E = malloc(sizeof(int));
			val->E[0] = id;
			break;
		case S_:
			val->nbr_S++;
			val->S = malloc(sizeof(int));
			val->S[0] = id;

			break;
		case ES_:
			val->nbr_ES++;
			val->ES = malloc(sizeof(int));
			val->ES[0] = id;

			break;
		default:
			yyerror("init_args:bad arg mode");
	}


	return val;

}

void* add_arg(function* func, int id, int mode)
{
	switch(mode)
	{
		case E_:
			if(!func->E)
			{
				func->E = malloc(sizeof(int));
				func->E[func->nbr_E++] = id;
			}
			else
				func->E = tab_push(func->E, func->nbr_E++, (void*)&id, I);
			break;
		case S_:
			if(!func->S)
			{
				func->S = malloc(sizeof(int));
				func->S[func->nbr_S++] = id;
			}
			else
				func->S = tab_push(func->S, func->nbr_S++, (void*)&id, I);
			break;
		case ES_:
			if(!func->ES)
			{
				func->ES = malloc(sizeof(int));
				func->ES[func->nbr_ES++] = id;
			}
			else
				func->ES = tab_push(func->ES, func->nbr_ES++, (void*)&id, I);
			break;
		default:
			yyerror("add_arg:unknown mode");
			break;
	}

	
	return (void*)func;
}

void* tab_push(void* tab, int size, void* val, int type)
{	
	if(!tab)
	{
		yyerror("tab_push:null table given\n");
		tab = malloc(sizeof(int) * size + 1);
	}
	//printf("pushiing %d new size %d\n", *(int*)val, size);
	switch(type)
	{
		case I:
			if(!(tab = realloc(tab, sizeof(int)* size + 1)))
			{
				printf("using malloc\n");
				void* new_tab = NULL;

				new_tab = malloc(sizeof(int)* size + 1);

				if(!new_tab)
					yyerror("tab_push:error with malloc");


				memcpy(new_tab, tab, size);

				((int*)new_tab)[size] = *(int*)val;

				free(tab);

				tab = new_tab;

			}
			else
			{
				((int*)tab)[size] = *(int*)val;
			}
			break;
		default:
			yyerror("tab_push:error unknown type");
			break;
	}

	return tab;
}
































void print_sym_tab()
{
	printf("id\tscope\tname\ttype\tvalue\n");
	for(int i = 0; i < MAX_VAR && (sym_tab[i].id+1); i++)
	{
		printf("%d\t%d\t", sym_tab[i].id, sym_tab[i].scope_id);
		if(sym_tab[i].name)
			printf("%s\t", sym_tab[i].name);
		else
			printf("NULL\t");
		if(sym_tab[i].var)
		{
			switch(sym_tab[i].var->type)
			{
				case I:
						printf("int\t%d\n", *((int*)(sym_tab[i].var->val)));
					break;
				case L:
						printf("long\t%ld\n", *((long*)(sym_tab[i].var->val)));
						break;
				case F:
						printf("float\t%f\n", *((float*)sym_tab[i].var->val));
						break;
				case C:
						printf("char\t%c\n", *((char*)sym_tab[i].var->val));
						break;
				case ID:
						printf("ID\t-\n");
						break;
				case FUN:
						printf("function\t-\n");
						break;
				case PRO:
						printf("procedure\t-\n");
						break;
				case STR:
						printf("struct\t%d>\n", *((int*)(sym_tab[i].var->val)));
						break;
				case TAB:
						printf("table\t-\n");
						break;
				case TO_SET:
						printf("to_set\t-\n");
						break;
				default:
						printf("%d\t-\n", sym_tab[i].var->type);
			}
		}
		else
			printf("NULL\tNULL\n");
	}
}


void print_tables()
{
	printf("\n\nid\tname\ttype\tdimensions\tscope\n");
	for(int i = 0; i < MAX_VAR && (sym_tab[i].id+1); i++)
	{
		if(sym_tab[i].var && sym_tab[i].var->val && (sym_tab[i].var->type == TAB))
		{
			printf("%d\t", sym_tab[i].id);
			if(sym_tab[i].name)
				printf("%s\t", sym_tab[i].name);
			else
			printf("NULL\t");

			switch(((table*)(sym_tab[i].var->val))->type)
			{
				case I:
					printf("int\t");
					break;
				case L:
					printf("long\t");
					break;
				case F:
					printf("float\t");
					break;
				case C:
					printf("char\t");
					break;
			}
			printf("%d->[", ((table*)(sym_tab[i].var->val))->dimensions);
			for (int j = 0; j < ((table*)(sym_tab[i].var->val))->dimensions; ++j)
			{
				printf("%d,", ((table*)(sym_tab[i].var->val))->size[j]);
			}
			printf("]\t%d\n", sym_tab[i].scope_id);
		}


	}



}


void print_functions()
{
	printf("\n\nid\tname\tret_type\targs\t\t\t\t\tscope\n");
	for(int i = 0; i < MAX_VAR && (sym_tab[i].id+1); i++)
	{
		if(sym_tab[i].var && sym_tab[i].var->val && ((sym_tab[i].var->type == FUN) || (sym_tab[i].var->type == PRO)))
		{
			printf("%d\t", sym_tab[i].id);
			if(sym_tab[i].name)
				printf("%s\t", sym_tab[i].name);
			else
			printf("NULL\t");

			switch(((function*)(sym_tab[i].var->val))->ret_type)
			{
				case I:
					printf("int\t");
					break;
				case L:
					printf("long\t");
					break;
				case F:
					printf("float\t");
					break;
				case C:
					printf("char\t");
					break;
				default:
					printf("NULL(PROCEDURE)\t");
					break;
			}
			printf("E(%d)>[", ((function*)(sym_tab[i].var->val))->nbr_E);
			for (int j = 0; j < ((function*)(sym_tab[i].var->val))->nbr_E; ++j)
			{
				printf("%d,", ((function*)(sym_tab[i].var->val))->E[j]);
			}
			printf("]S(%d)>[", ((function*)(sym_tab[i].var->val))->nbr_S);
			for (int j = 0; j < ((function*)(sym_tab[i].var->val))->nbr_S; ++j)
			{
				printf("%d,", ((function*)(sym_tab[i].var->val))->S[j]);
			}
			printf("]ES(%d)>[", ((function*)(sym_tab[i].var->val))->nbr_ES);
			for (int j = 0; j < ((function*)(sym_tab[i].var->val))->nbr_ES; ++j)
			{
				printf("%d,", ((function*)(sym_tab[i].var->val))->ES[j]);
			}
			printf("]\t\t\t%d\n", sym_tab[i].scope_id);
		}


	}



}