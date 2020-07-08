#include "ArrayString.h"


/*  IDEIA:
    obter a tabela de simbolos atraves da AST, assim excusamos de mexer no yac
*/

// variaveis do metodo
typedef struct SymbolTableVars{
    // info da var: "Name'\t'[ParamTypes]'\t'Type['\t'param]"
    char* varName;
    ArrayString* varParamTypes;
    char* varType;
    char* varParam;
    bool isMethod;
    // prox var
    struct SymbolTableVars* nextVar;
} stVar;

// tabela de simbolos de um metodo
typedef struct SymbolTable{
    // titulo da tabla: "'Tipo' 'Nome'[(ParamTypes)] Symbol Table"
    char* tableType;
    char* tableName;
    ArrayString* tableParamTypes;
    // lista das vars dentro do metodo
    struct SymbolTableVars* varsList;
    // tabela do prox metodo
    struct SymbolTable* nextMethod;
} symbTable;


// cria a tabela incluindo: "'Tipo' 'Nome'[(ParamTypes)] Symbol Table"
symbTable* newTable(char* type, char* name, ArrayString* paramTypes);
// Cria uma var com as suas infos: "Name'\t'[ParamTypes]'\t'Type['\t'param]"
stVar* newVar(char* name, ArrayString* paramTypes, char* type, char* param, bool method);
// Adiciona a var na ultima posicao
void addVar(symbTable* currTable, stVar* var);
// Adiciona a var na ultima posicao
void addTable(symbTable* currTable, symbTable* table);