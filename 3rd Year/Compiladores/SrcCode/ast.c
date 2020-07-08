#include "ast.h"

// Criar um novo no para a arvore
asTree* newNode(char *nodetype, int line, int col){
    // Alocar memoria para o no
    asTree* node = (asTree*)malloc(sizeof(asTree));
    // Copiar o tipo do no para a o no
    node->nodeType = strdup(nodetype);

    // tipo da expressao (meta3)
    node->expArr = (ExpArray*)malloc(sizeof(ExpArray));
    node->expArr->expType = _NONE;
    node->expArr->next = NULL;

    node->isParam = false;
    node->isMethod = false;
    node->isError = false;
    node->line = line;
    node->col = col;

    return node;
}

// Display da arvore toda (recursivamente)
void displayAST(int numbPontinhos, asTree* node, bool isNoted) {
    if(node == NULL){return;}
    for(int i = 0; i < numbPontinhos; i++){printf("..");}
    printf("%s", node->nodeType);
    if(isNoted && node->expArr->expType != _NONE){
        if(node->isMethod){
            if(node->expArr->expType == _UNDEF) printf(" - %s", type2finalString(node->expArr));
            else printf(" - (%s)", type2finalString(node->expArr));
        } 
        else printf(" - %s", type2finalString(node->expArr));
    }else if(isNoted && node->isMethod){
        printf(" - ()");
    }printf("\n");
    displayAST(numbPontinhos+1, node->sonNode, isNoted);
    displayAST(numbPontinhos, node->nextNode, isNoted);
}


char* type2str(ExpType type){
    if (type == _NONE) return "none";
    else if (type == _INTLIT) return "int";
    else if (type == _REALLIT) return "double";
    else if (type == _BOOLLIT) return "boolean";
    else if (type == _STRLIT) return "String";
    else if (type == _STRARR) return "String[]";
    else if (type == _VOID) return "void";
    else if (type == _UNDEF) return "undef";
    else return "none";
}

char* type2finalString(ExpArray* type){
    if( type->next != NULL ){
        char fString[128] = "";
        ExpArray* currPos = type;
        strcat(fString, type2str(currPos->expType) );
        while(currPos->next != NULL){
            strcat(fString, ",");
            strcat(fString, type2str(currPos->next->expType) );
            currPos = currPos->next;
        }
        return strdup(fString);
    }else{
        return type2str(type->expType);
    }
}

ExpType str2type(char* type){
    if (type == NULL) return _NONE;
    else if (strcmp(type, "int") == 0) return _INTLIT;
    else if (strcmp(type, "Int") == 0) return _INTLIT;
    else if (strcmp(type, "double") == 0) return _REALLIT;
    else if (strcmp(type, "Double") == 0) return _REALLIT;
    else if (strcmp(type, "boolean") == 0) return _BOOLLIT;
    else if (strcmp(type, "Bool") == 0) return _BOOLLIT;
    else if (strcmp(type, "String") == 0) return _STRLIT;
    else if (strcmp(type, "String[]") == 0) return _STRARR;
    else if (strcmp(type, "StringArray") == 0) return _STRARR;
    else if (strcmp(type, "void") == 0) return _VOID;
    else if (strcmp(type, "Void") == 0) return _VOID;
    else if (strcmp(type, "undef") == 0) return _UNDEF;
    else return _NONE;
}


// Associar o prox. no
void addNext(asTree* current, asTree* next){
    if(current == NULL || next == NULL){return;}
    asTree* aux = current;
    // caso o no ainda nao tenha um nextNode, associa
    if(aux->nextNode == NULL){
        aux->nextNode = next;
    }
    // caso ja tenha, o next passa a ser o nextNode
    // do proximo node sem um nextNode
    else{
        while(aux->nextNode !=NULL){
            aux = aux->nextNode;
        }
        aux->nextNode = next;
    }
}

// Assosiar o no filho
void addSon(asTree* parent, asTree* son){

    if(parent == NULL || son == NULL){return;}

    // se ainda nao tiver um no filho
    if(parent->sonNode == NULL){
        parent->sonNode = son;
    }// caso ja tenha, passa a ser o next do filho
    else{
        addNext(parent->sonNode,son);
    }
}

// Libertar da memoria (recursivamente)
void freeAST(asTree* node){
    if (node != NULL){return;}
    if (node->sonNode != NULL){ freeAST(node->sonNode);}
    if (node->nextNode != NULL){freeAST(node->nextNode);}
    free(node->nodeType);
    free(node);
}

// Acrescenta o nome do ID
char* idName(char* id){
    char* aux = (char*)malloc(strlen(id)+5);
    sprintf(aux, "Id(%s)", id);
    return aux;
}

// Acrescenta o valor ao tipo
char* typeValue(char* type, char* value){
    char* aux = (char*)malloc(strlen(type)+strlen(value)+5);
    if(strcmp(type,"StrLit")==0){
       sprintf(aux, "%s(\"%s)", type, value);
    }else{
       sprintf(aux, "%s(%s)", type, value);
    }
    return aux;
}

ExpArray* startExpArr(ExpType expT){
    ExpArray* newArr = (ExpArray*)malloc(sizeof(ExpArray));
    newArr->expType = expT;
    newArr->next = NULL;
    return newArr;
}

