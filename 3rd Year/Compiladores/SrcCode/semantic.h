
#include "symbol_table.h"
#include "ast.h"


// display das tabelas
void displayTables(symbTable* root);
// faz a tabela da class, recebe o no Program da ast
symbTable* makeTable_Program(asTree* programNode);
// faz a tabela do MethodDecl
symbTable* makeTable_MethodDecl(asTree* MethodDeclNode);

bool compareParamTypes(ArrayString* paramTypes, ExpArray* paramTypes2);
bool compareParamTypesUNEXACT(ArrayString* paramTypes, ExpArray* paramTypes2, int *numbExacts);
// procura a tabela do metodo descrito
symbTable* searchMethodTable(char* methodName, ExpArray* methodParamTypes);
// inicia o processo de atualizar a AST
void enterAST(asTree* root);
// upgrade AST
void upgradeAST(asTree* methodBodyNode, symbTable* methodTable);
// faz os calls de maneira diferente pq o java assim quer
void upgradeCalls(asTree* methodBodyNode, symbTable* methodTable);
// verifica se o Id foi declarado no metodo onde esta ou se e uma var global
void checkId(char* idName, asTree* currNode, symbTable* methodTable);
char* getId(char* nodeType);
// check int and reallit stuff
ExpType checkNumbSons(asTree* currNode);
ExpType checkBools(asTree* currNode, bool isXor);
ExpType checkEqls(asTree* currNode);
// aplica o tipo ao Id(method) e a call
void checkCall(asTree* callNode, symbTable* methodTable);
bool checkVars(char* varName);
bool checkVarsMethods(char* varName, symbTable* currMethodTable);
bool checkVarReserved(char* varName);
ExpArray* ArrayString2ExpArray(ArrayString* arrStr);
bool checkMethod(char* methodName, ExpArray* methodParams);
ExpType shiftss(asTree* currNode);
void checkIdClass(char* idName, asTree* currNode, symbTable* methodTable);
ExpType checkMinusPlus(ExpType sonExpType);
ExpType checkAssign(ExpType var, ExpType value);
char* node2operator(char* nodeType);
char* checkReturnType(symbTable* currMethodTable);
void checkOperatorError(asTree* currNode, char* nodeType);
void checkReturnError(symbTable* methodDecl, asTree* methodBodySon);
void checkAssignError(asTree* currNode, char* nodeType);
char* concat(char *s1, char *s2);
void checkBounds(char* declit, asTree* node, char* originalString, int n);
int count(char *s);
void checkBoolsError(asTree* currNode, char* nodeType);
long int getCol(asTree* currNode);
// completa a tabela do MethodDecl
void completeTable(asTree* MethodDeclNode, symbTable* methodTable);