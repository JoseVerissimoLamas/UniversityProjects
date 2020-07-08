#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lista ligada para as strings (usado para os ParamTypes)
typedef struct LinkedListString{
    char* string;
    struct LinkedListString* next;
} ArrayString;

// adiciona uma string a lista
void addString(ArrayString* header, char* newString);
// inicializa a lista dos ParamTypes
ArrayString* startHeader();
// return do formato string dos paramtypes
char* toString(ArrayString* header);