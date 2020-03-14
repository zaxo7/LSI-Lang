%{
	#include "global.h"
	#include "functions.h"
	#include "lsi.yac.h"
%}


ident [A-Za-z_](([A-Za-z0-9]_)?[A-Za-z0-9]+)*

int_const	-?[0-9]+

long_const	{int_const}L

float_const {int_const}\.[0-9]*

%s DECLARATIONS
%s ACTIONS

%%


Prog\ .*	{
			ProgName = strchr(yytext, ' ')+1;
			BEGIN(DECLARATIONS);
			return(PROG);
		}

<DECLARATIONS>begin	{

						BEGIN(ACTIONS);
						return(BEG);
					}

<DECLARATIONS>const {

						return(CONST);
					}
<DECLARATIONS>function {

							return(FUNCTION);
						}
<DECLARATIONS>procedure {

							return(PROCEDURE);
						}
<DECLARATIONS>table		{

							return(TABLE);
						}
<DECLARATIONS>struct	{

							return(STRUCT);
						}
<DECLARATIONS>E {

					return(E);
				}
<DECLARATIONS>S {

					return(E);
				}
<DECLARATIONS>ES 	{

						return(E);
					}



<ACTIONS>end		{

						BEGIN(INITIAL);
						return(END);
					}

int 	{

			return(INT);
		}
float 	{
			
			return(FLOAT);
		}
long 	{
			
			return(LONG);
		}
char	{

			return(CHAR);
		}
var		{

			return(VAR);
		}
if		{

			return(IF);
		}
then	{

			return(THEN);
		}
else	{

			return(ELSE);
		}
while	{

			return(WHILE);
		}
for		{

			return(WHILE);
		}
AND		{

			return(AND);
		}
OR		{

			return(OR);
		}

: 		{

			return(COLON);
		}
,		{

			return(COMMA);
		}
;      {

			return(EOL);
		}
\(		{

			return(LP);
		}
\)		{

			return(RP);
		}
\{		{

			return(LB);
		}
\}		{

			return(RB);
		}
\[		{

			return(LBR);
		}
]		{

			return(RBR);
		}
=		{

			return(AFFECT);
		}
==		{

			return(EQUAL);
		}
>		{

			return(SUP);	
		}
\<		{

			return(INF);
		}
!		{

			return(NOT);
		}
\+		{

			return(PLUS);
		}
-		{

			return(MINUS);
		}
\/		{

			return(DIV);
		}
\*		{

			return(MULT);
		}
\^		{

			return(POW);
		}
%		{

			return(MOD);
		}
{float_const}	{
					yylval.type = F;
					yylval.val = (float*)malloc(sizeof(float));
					/* printf("lex:converting %s to float!\n", yytext); */
					*((float*)yylval.val) = atof(yytext);
					return(FLOAT_CONST);
				}
{long_const}	{
					yylval.type = L;
					yylval.val = (long*)malloc(sizeof(long));
					*((long*)yylval.val) = atol(yytext);
					/* printf("\nlex:converting %s to long! => %ld\n", yytext, *((long*)yylval.val)); */
					return(LONG_CONST);
				}
{int_const}	{
				yylval.type = I;
				yylval.val = (int*)malloc(sizeof(int));
				/* printf("\nlex:converting %s to int!\n", yytext); */
				*((int*)yylval.val) = atoi(yytext);
				return(INT_CONST);
			}

\'.\'	{

			return(CHAR_CONST);
		}


{ident}	{
			yylval.id = declare(yytext);
			//printf("yylex:id = %d\n",yylval.id);
			yylval.type = ID;
			return(IDENT);
		}

.		{

		}
\n 		{

			
		}


%%