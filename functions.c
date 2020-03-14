#include "functions.h"

//la fonction pour gérer les erreurs
int yyerror(char* s)
{
	printf("%s\n",s);
	exit(0);
}


//la fonction qui declare des variables dans la table des symboles
int declare(char* var_name)
{
	printf("declaring %s\n", var_name);

	int i;
	for (i = 0; i < MAX_VAR && (sym_tab[i].id+1); i++)
	{
		if(!strncmp(var_name, sym_tab[i].name, strlen(var_name) > strlen(sym_tab[i].name) ? strlen(var_name):strlen(sym_tab[i].name)) && (	sym_tab[i].scope_id == current_scope->id  ))
		{
			yyerror("variable exists");
			return sym_tab[i].id;
		}
	}

	sym_tab[i].id = variable_unique_id++;
	sym_tab[i].name = strdup(var_name);
	sym_tab[i].scope_id = current_scope->id;


	return variable_unique_id - 1;
}

//la fonction pour initialiser tous
void init_all()
{

	scope_unique_id = 0;
	variable_unique_id = 0;

	scope_tree = scope_init();
	scope_tree->name = strdup("global");

	current_scope = scope_tree;

	//en initialise la table des symboles
	for(int i = 0; i < MAX_VAR; i++)
	{
		sym_tab[i].id = -1;
		sym_tab[i].name = NULL;
		sym_tab[i].var = NULL;
		sym_tab[i].scope_id = -1;
		sym_tab[i].constant = false;
	}
}

//la function qui change la valeur et le type des symboles
int set_val(int id, void* val, int type)
{
	variable* variable = get_var(id);
	printf("set_val: setting %s to %d\n", variable->name, type);

	if(!variable)
		yyerror("setting a variable that dosn't exists");

	if(!variable->var)
	{
		variable->var = malloc(sizeof(value));
		if(!variable->var)
			yyerror("malloc error");
	}


	variable->var->type = type;

	variable->var->val = val;

	

	return 1;
}
//la fonction qui change le type vers constante
int set_const(int id)
{
	variable* variable = get_var(id);
	printf("set_val: setting %s to const\n", variable->name);

	if(!variable)
		yyerror("setting a variable that dosn't exists");


	variable->constant = true;
	

	return 1;
}


//la fonction pour aider a initialiser le type d'une liste de variables
int auto_set_type(int type)
{
	
	printf("auto_set_type: %d\n", type);
	for (int i = 0; i < MAX_VAR; i++)
	{
		//si c'est un symbole sans valeur en continue
		if(!sym_tab[i].var)
			continue;

		//en change le type pour tous les variables qui ont le type TO_SET
		if(sym_tab[i].var->type == TO_SET)
		{
			void* val = NULL;
			//en alloue pour chaque type sa propre taille
			switch(type)
			{
				case I:
					val = malloc(sizeof(int));
					memset(val, 0, sizeof(int));
					break;
				case F:
					val = malloc(sizeof(float));
					memset(val, 0, sizeof(float));
					break;
				case L:
					val = malloc(sizeof(long));
					memset(val, 0, sizeof(long));
					break;
				case C:
					val = malloc(sizeof(char));
					memset(val, 0, sizeof(char));
					break;
			}
			set_val(sym_tab[i].id, val, type);
		}
		
	}
	return 1;
}

//la fonction qui cherche une variable avec son ID
variable* get_var(int id)
{
	for (int i = 0; i < MAX_VAR; i++)
	{
		if(sym_tab[i].id == id)
			return &sym_tab[i];
	}
	return NULL;
}




