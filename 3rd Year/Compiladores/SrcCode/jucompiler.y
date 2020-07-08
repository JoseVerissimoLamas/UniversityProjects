%{
    //Beatriz Isabel Santos 2017263066
    //José Veríssimo Lamas  2017259895

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include "ast.h"
	#include "y.tab.h"
	int yylex();
    void yyerror (char *s);
	extern int line;   
    extern int collumn;
    extern int token;
    extern int flag_erros;
    extern int flag_yacc;
    extern int flag_t;
	extern int token;
	extern int auxCollumn;
	extern bool syntaxError;
	extern char* yytext;
	asTree* tree;

%}

%token <s> AND
%token <s> ASSIGN
%token <s> STAR
%token <s> COMMA
%token <s> EQ
%token <s> GE
%token <s> GT
%token <s> LE
%token <s> LT
%token <s> LBRACE
%token <s> LPAR
%token <s> LSQ
%token <s> RBRACE
%token <s> RPAR
%token <s> RSQ
%token <s> PLUS
%token <s> MINUS
%token <s> DIV
%token <s> MOD
%token <s> NE
%token <s> NOT
%token <s> OR
%token <s> SEMICOLON
%token <s> ARROW
%token <s> LSHIFT
%token <s> RSHIFT
%token <s> XOR
%token <s> CLASS
%token <s> BOOL
%token <s> DOTLENGTH
%token <s> DOUBLE
%token <s> ELSE
%token <s> IF
%token <s> INT
%token <s> PRINT
%token <s> PARSEINT
%token <s> PUBLIC
%token <s> RETURN
%token <s> STATIC
%token <s> STRING
%token <s> VOID
%token <s> WHILE
%token <s> RESERVED
%token <s> INTLIT REALLIT STRLIT ID BOOLLIT

%nonassoc THEN
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left XOR
%left EQ NE
%left LT LE GT GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%left LPAR LSQ RPAR RSQ

%type <root> Program Program_opt MethodDecl FieldDecl FieldDecl_opt Type MethodHeader FormalParams FormalParams_opt MethodBody MethodBody_opt VarDecl VarDecl_opt Statement Statement_opt MethodInvocation MethodInvocation_opt Assignment ParseArgs Expression Expr ExprOpt FormalParams_m Expression_opt
Semicolon_opt

%union {
	char *node;
	struct args *s;
	asTree* root;
}


%%
Program: 
		CLASS ID LBRACE Program_opt RBRACE				{	tree = newNode("Program",$<s->line>1, $<s->col>1);
															asTree* idNode = newNode(idName($<s->val>2), $<s->line>2, $<s->col>2); 
															addSon(tree, idNode);
															addNext(idNode, $4); 
															$$ = tree;}
		;

Program_opt: 											{	$$ = NULL;}
		|Program_opt MethodDecl  						{	if($1!= NULL){
																$$ = $1;
																addNext($$, $2);
															}else{$$ = $2;};}
		|Program_opt FieldDecl 							{	if($1 != NULL){
																$$ = $1;
																addNext($$, $2);
															}else{$$ = $2;};}
		|Program_opt SEMICOLON 							{	$$ = $1;}
		;

MethodDecl: 
 		PUBLIC STATIC MethodHeader MethodBody 			{	$$ = newNode("MethodDecl", -1, -1);
		 													addSon($$, $3);
															addNext($3, $4);}
 		;

FieldDecl: 
		PUBLIC STATIC Type ID FieldDecl_opt SEMICOLON   {	$$ = newNode("FieldDecl", -1, -1);
															asTree* auxId = newNode(idName($<s->val>4),$<s->line>4,$<s->col>4);
															addSon($$, $3);
															addSon($$, auxId);
															asTree* aux = $5;
															while(aux != NULL){
																asTree* aux2 = newNode("FieldDecl",$<s->line>1, $<s->col>1);
																addSon(aux2, newNode($3->nodeType, -1, -1));
																addNext(aux2->sonNode, aux);
																addNext($$, aux2);
																asTree* aux3 = aux;
																aux = aux->nextNode;
																aux3->nextNode = NULL;
															}
														}
		|error SEMICOLON								{	$$ = NULL;}
		;

FieldDecl_opt:											{	$$ = NULL;}
		|FieldDecl_opt COMMA ID  						{	if($1 != NULL){
																$$ = $1; 
																addNext($1, newNode(idName($<s->val>3),$<s->line>3,$<s->col>3));
															}else{
																$$ = newNode(idName($<s->val>3),$<s->line>3,$<s->col>3);}
														}
		;

Type: 
		BOOL  											{	$$ = newNode("Bool",  -1, -1); }
		|INT 											{	$$ = newNode("Int",   -1, -1);}
		|DOUBLE											{	$$ = newNode("Double",  -1, -1);}
		;

MethodHeader:
		Type ID LPAR FormalParams_m RPAR				{$$ = newNode("MethodHeader",$<s->line>2, $<s->col>2);
														addSon($$, $1);
														addNext($1, newNode(idName($<s->val>2), $<s->line>2,$<s->col>2));
														asTree* aux = newNode("MethodParams", -1, -1); 
														addSon($$, aux);
														addSon(aux, $4);}
														
		|VOID ID LPAR FormalParams_m RPAR				{$$ = newNode("MethodHeader",  $<s->line>2, $<s->col>2);
														asTree* aux = newNode("Void",  -1, -1);
														addSon($$, aux);
														addNext(aux, newNode(idName($<s->val>2), $<s->line>2,$<s->col>2));
														asTree* aux2 = newNode("MethodParams", -1, -1); 
														addSon($$, aux2);
														addSon(aux2, $4);
														}
		;

FormalParams_m:											{ 	$$ = NULL;}
			|FormalParams								{ 	$$ = $1;}
			;

FormalParams: 
		Type ID FormalParams_opt						{	$$ = newNode("ParamDecl",  -1, -1);
															addSon($$, $1);
															addNext($$->sonNode, newNode(idName($<s->val>2), $<s->line>2,$<s->col>2));
															asTree* aux2 = $3;
															while(aux2 != NULL){
																addNext($$, aux2);
																asTree* aux3 = aux2;
																aux2 = aux2->nextNode;
																aux3->nextNode = NULL;
															}
														}
		|STRING LSQ RSQ ID 								{	$$ = newNode("ParamDecl",  -1, -1);
															addSon($$, newNode("StringArray",  -1, -1));
															addSon($$, newNode(idName($<s->val>4), $<s->line>4,$<s->col>4));}
		;

FormalParams_opt: 										{	$$ = NULL;}
		|FormalParams_opt COMMA Type ID  				{	asTree* aux = newNode("ParamDecl",  -1, -1);
															addSon(aux, newNode($3->nodeType,  -1, -1));
															addNext(aux->sonNode, newNode(idName($<s->val>4), $<s->line>4,$<s->col>4));
															if($1 != NULL){
																$$ = $1;
																addNext($1,aux);
															}else{
																$$ = aux;
															}
														}
		;

MethodBody:
		LBRACE MethodBody_opt RBRACE 					{	$$ = newNode("MethodBody",  -1, -1);
															addSon($$, $2);}
		;

MethodBody_opt:											{	$$ = NULL;}
		|MethodBody_opt Statement 						{	if( $1 != NULL){
																$$ = $1;
																addNext($$, $2);
															}else{$$ = $2;}}
		|MethodBody_opt VarDecl 						{	if( $1 != NULL){
																$$ = $1;
																addNext($$, $2);
															}else{$$ = $2;}}
		;

VarDecl:
		Type ID VarDecl_opt SEMICOLON					{	$$ = newNode("VarDecl", -1, -1);
															addSon($$, $1);
															addSon($$, newNode(idName($<s->val>2),$<s->line>2,$<s->col>2));
															asTree* aux = $3;
															while(aux != NULL){
																asTree* aux2 = newNode("VarDecl", -1, -1);
																addSon(aux2, newNode($1->nodeType, -1, -1));
																addNext(aux2->sonNode, aux);
																addNext($$, aux2);
																asTree* aux3 = aux;
																aux = aux->nextNode;
																aux3->nextNode = NULL;
															}
														}
		;

VarDecl_opt:											{	$$ = NULL;}
		|VarDecl_opt COMMA ID							{	if($1 != NULL){
																$$ = $1; 
																addNext($1, newNode(idName($<s->val>3), $<s->line>3,$<s->col>3));
															}else{
																$$ = newNode(idName($<s->val>3), $<s->line>3,$<s->col>3);}
														}
		;

Statement: 
		LBRACE Statement_opt RBRACE							{if($2 != NULL && $2->nextNode != NULL){
																	$$ = newNode("Block",  -1, -1);
																	addSon($$, $2);
																}
																else{
																	$$ = $2;
															}}
		|IF LPAR Expression RPAR Statement %prec THEN		{	$$ = newNode("If", $<s->line>1, $<s->col>1);
																addSon($$, $3);
																
																if($5 == NULL){
																	$5 = newNode("Block", $<s->line>1,$<s->col>1);
																	addNext($3, $5);
																}else if(($5 != NULL && $5->nextNode != NULL)){
																	asTree* aux = newNode("Block", $<s->line>1,$<s->col>1);
																	addNext($3, aux);
																	addSon(aux, $5);
																}else{addNext($3, $5);}
																
																addSon($$, newNode("Block", $<s->line>1,$<s->col>1));}
		|IF LPAR Expression RPAR Statement ELSE Statement 	{	$$ = newNode("If", $<s->line>1,$<s->col>1);
																addSon($$, $3);
																if($5 == NULL){
																	$5 = newNode("Block", $<s->line>1,$<s->col>1);
																	addNext($3, $5);
																}else if(($5 != NULL && $5->nextNode != NULL)){
																	asTree* aux = newNode("Block", $<s->line>1,$<s->col>1);
																	addNext($3, aux);
																	addSon(aux, $5);
																}else{addNext($3, $5);}

																if($7 == NULL){
																	$7 = newNode("Block", $<s->line>1,$<s->col>1);
																	addNext($$->sonNode, $7);
																}else if(($7 != NULL && $7->nextNode != NULL)){
																	asTree* aux = newNode("Block", $<s->line>1,$<s->col>1);
																	addNext($$->sonNode, aux);
																	addSon(aux, $7);
																}else{addNext($$->sonNode, $7);}}
																
		|WHILE LPAR Expression RPAR Statement 				{	$$ = newNode("While", $<s->line>1,$<s->col>1);
																addSon($$, $3);
																if($5 == NULL){
																	$5 = newNode("Block", $<s->line>1,$<s->col>1);
																	addSon($$, $5);
																}else if($5 != NULL && $5->nextNode != NULL){
																	asTree* aux = newNode("Block", $<s->line>1,$<s->col>1);
																	addSon($$, aux);
																	addSon(aux, $5);
																}else{addNext($3, $5);}}
		|RETURN Expression_opt SEMICOLON 					{	$$ = newNode("Return", $<s->line>1,$<s->col>1);
																if($2 != NULL){addSon($$, $2);}}
		|Semicolon_opt SEMICOLON   							{	$$ = $1;}
		|PRINT LPAR Expression RPAR SEMICOLON  				{	$$ = newNode("Print", $<s->line>1,$<s->col>1);
																addSon($$, $3);}
		|PRINT LPAR STRLIT RPAR SEMICOLON 					{	$$ = newNode("Print", $<s->line>1,$<s->col>1);
																addSon($$, newNode(typeValue("StrLit", $<s->val>3), $<s->line>3,$<s->col>3));}
		|error SEMICOLON 							    	{	$$ = NULL;}
		;

Statement_opt :											{	$$ = NULL;}
		|Statement_opt Statement 						{	if($1 != NULL){
																$$ = $1;
																addNext($$, $2);
															}else{$$ = $2;}}
		;

Expression_opt:											{	$$ = NULL;}
		|Expression          							{$$ = $1;}
		;

Semicolon_opt:											{	$$ = NULL;}								
		|MethodInvocation 								{$$ = $1;}
		|Assignment										{$$ = $1;}
		|ParseArgs										{$$ = $1;}


MethodInvocation:
		ID LPAR RPAR 									{	$$ = newNode("Call", $<s->line>1, $<s->col>1);
															addSon($$, newNode(idName($<s->val>1), $<s->line>1,$<s->col>1));}
		|ID LPAR Expression MethodInvocation_opt RPAR 	{
															$$ = newNode("Call", $<s->line>1, $<s->col>1);
															addSon($$, newNode(idName($<s->val>1), $<s->line>1,$<s->col>1));
															addSon($$, $3);
															addSon($$, $4);}
		|ID LPAR error RPAR								{	$$ = NULL;}
		;

MethodInvocation_opt: 									{	$$ = NULL;}	
		|MethodInvocation_opt COMMA Expression  		{	if($1 != NULL){
																$$ = $1;
																addNext($$, $3);
														}else{$$ = $3;}}
		;
Assignment:
		ID ASSIGN Expression 							{	$$ = newNode("Assign", $<s->line>2,$<s->col>2);
															addSon($$, newNode(idName($<s->val>1), $<s->line>1,$<s->col>1));
															addSon($$, $3);}
		;

ParseArgs: 
		PARSEINT LPAR ID LSQ Expression RSQ RPAR  		{	$$ = newNode("ParseArgs", $<s->line>1,$<s->col>1);
															addSon($$, newNode(idName($<s->val>3), $<s->line>3,$<s->col>3));
															addSon($$, $5);}
		|PARSEINT LPAR error RPAR						{	$$ = NULL; }
		;

Expression:
	Assignment											{	$$ = $1;}
	|Expr												{	$$ = $1;}
	;

Expr:
	Expr MINUS Expr 									{	$$ = newNode("Sub", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr PLUS Expr       								{	$$ = newNode("Add", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr STAR Expr 									{	$$ = newNode("Mul", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr DIV Expr 										{	$$ = newNode("Div", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr MOD Expr 										{	$$ = newNode("Mod", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr AND Expr 										{	$$ = newNode("And", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr OR Expr										{	$$ = newNode("Or", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr XOR Expr										{	$$ = newNode("Xor", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr LSHIFT Expr									{	$$ = newNode("Lshift", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr RSHIFT Expr									{	$$ = newNode("Rshift", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr EQ Expr										{	$$ = newNode("Eq",$<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr GE Expr 										{	$$ = newNode("Ge", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr GT Expr 										{	$$ = newNode("Gt", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr LE Expr 										{	$$ = newNode("Le", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr LT Expr 										{	$$ = newNode("Lt", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}
	|Expr NE Expr										{	$$ = newNode("Ne", $<s->line>2,$<s->col>2);
															addSon($$, $1);
															addSon($$, $3);}	
	
	|ParseArgs											{	$$ = $1;}
	|NOT Expr %prec NOT									{	$$ = newNode("Not", $<s->line>1,$<s->col>1);
															addSon($$, $2);}
	|MethodInvocation 									{	$$ = $1;}
	|LPAR Expression RPAR 										{	$$ = $2;}
	|PLUS Expr %prec NOT								{	$$ = newNode("Plus", $<s->line>1,$<s->col>1);
															addSon($$, $2);}
	|MINUS Expr	%prec NOT								{	$$ = newNode("Minus", $<s->line>1,$<s->col>1);
															addSon($$, $2);}
	|ID ExprOpt											{	asTree* aux = newNode(idName($<s->val>1), $<s->line>1,$<s->col>1);
															if($2!=NULL){
																addSon($2, aux);
																$$ = $2;
															}else{
																$$ = newNode(idName($<s->val>1), $<s->line>1,$<s->col>1);
															}}
	|INTLIT 											{	$$ = newNode(typeValue("DecLit", $<s->val>1), $<s->line>1, $<s->col>1);}
	|REALLIT 											{	$$ = newNode(typeValue("RealLit", $<s->val>1), $<s->line>1, $<s->col>1);}
	|BOOLLIT											{	$$ = newNode(typeValue("BoolLit", $<s->val>1), $<s->line>1, $<s->col>1);}
	
	|LPAR error RPAR 									{	$$ = NULL;}
	;

ExprOpt:												{	$$ = NULL;}
	|DOTLENGTH											{	$$ = newNode("Length", $<s->line>1,$<s->col>1);}
	;

%%

void yyerror (char *s){
    syntaxError = true;
	if(yychar == STRLIT){
		printf("Line %d, col %d: %s: \"%s\n", line, auxCollumn, s, yylval.s->val);
	} else{
		printf("Line %d, col %d: %s: %s\n", line, (int)(collumn - strlen(yytext) + 1) ,s, yytext);
	}
}