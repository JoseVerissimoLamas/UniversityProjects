#include "symbol_table.h"

// cria a tabela incluindo: "'Tipo' 'Nome'[(ParamTypes)] Symbol Table"
symbTable* newTable(char* type, char* name, ArrayString* paramTypes){
    // Alocar memoria para a tabela
    symbTable* nTable = (symbTable*)malloc(sizeof(symbTable));

    // Regista o tipo, nome e paramTypes da tabela
    nTable->tableType = strdup(type);
    nTable->tableName = strdup(name);
    nTable->tableParamTypes = paramTypes;
    
    // inicializa os nexts a NULL
    nTable->nextMethod = NULL;
    nTable->varsList = NULL;
    
    return nTable;
}

// Cria uma var com as suas infos: "Name'\t'[ParamTypes]'\t'Type['\t'param]"
stVar* newVar(char* name, ArrayString* paramTypes, char* type, char* param, bool method){
    // Alocar memoria para a var
    stVar* nVar = (stVar*)malloc(sizeof(stVar));

    // Registar o nome, paramTypes, tipo e param da var
    nVar->varName = strdup(name);
    nVar->varParamTypes = paramTypes;
    nVar->varType = strdup(type);
    nVar->varParam = strdup(param);
    nVar->isMethod = method;

    // inicializa o next a NULL
    nVar->nextVar = NULL;

    return nVar;
}

// Adiciona a var na ultima posicao
void addVar(symbTable* currTable, stVar* var){
    if(currTable == NULL || var == NULL){return;}

    if(currTable->varsList == NULL){ currTable->varsList = var; return; }
    stVar* aux = currTable->varsList;
    if(aux->nextVar == NULL){
        aux->nextVar = var;
    }else{
        while(aux->nextVar !=NULL){
            aux = aux->nextVar;
        }
        aux->nextVar = var;
    }
}

// Adiciona a tabela na ultima posicao
void addTable(symbTable* currTable, symbTable* table){
    if(currTable == NULL || table == NULL){return;}

    symbTable* aux = currTable;
    if(aux->nextMethod == NULL){
        aux->nextMethod = table;
    }else{
        while(aux->nextMethod !=NULL){
            aux = aux->nextMethod;
        }
        aux->nextMethod = table;
    }
}

