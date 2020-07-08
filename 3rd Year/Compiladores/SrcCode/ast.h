#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>


typedef enum ExpressionType {
    _NONE, _UNDEF, _VOID, _INTLIT, _STRLIT, _BOOLLIT, _REALLIT, _STRARR
} ExpType;

typedef struct ExpressionArray{
    enum ExpressionType expType;
    struct ExpressionArray* next;
} ExpArray;

struct args{
    int line;
    int col;
    char* val;
};

// Struct da arvore AS
typedef struct ast {
    char *nodeType;
    // tipo da expressao (meta3)
    //ExpType expType;
    ExpArray* expArr;
    // se e param (para print da ast)
    bool isParam;
    bool isMethod;
    bool isError;
    int line;
    int col;
    // os nos filhos sao os nodes que consistem dentro da exp do parent
    struct ast* sonNode; 
    struct ast* nextNode;
} asTree;

/*#### Aqui ficam as funoes para serem partilhadas pelos lex e yac ####*/

// Criar um no
asTree* newNode(char *nodetype, int line, int col);
// Display da arvore
void displayAST(int numbPontinhos, asTree* node, bool isNoted);

// converter de tipo para string e vice versa
char* type2str(ExpType type);
char* type2finalString(ExpArray* type);
ExpType str2type(char* type);

// Add no filho ao parent
void addSon(asTree* parent, asTree* son);
// Add next node 
void addNext(asTree* current, asTree* next);
// Liberta memoria
void freeAST(asTree* node);
// Acrescenta o nome do ID
char* idName(char* id);
// Acrescenta o valor ao tipo
char* typeValue(char* type, char* value);

ExpArray* startExpArr(ExpType expT);

