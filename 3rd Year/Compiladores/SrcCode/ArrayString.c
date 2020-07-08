#include "ArrayString.h"

// adiciona uma string a lista
void addString(ArrayString* header, char* newString){
    if(strcmp(header->string, "") == 0){ 
        header->string = strdup(newString);
        return;
    }

    ArrayString* currPos = header;
    while(currPos->next != NULL){
        currPos = currPos->next;
    }
    currPos->next = startHeader();
    currPos->next->string = strdup(newString);
}

// garante que td é inicializado a NULL
ArrayString* startHeader(){
    ArrayString* header = (ArrayString*)malloc(sizeof(ArrayString));
    header->string = "";
    header->next = NULL;
    return header;
}

// return do formato string dos paramtypes
char* toString(ArrayString* header){
    char* returnString;
    char finalString[128] = "";
    ArrayString* currParam = header;
    // caso nao tenha params
    if(strcmp(currParam->string, "") == 0){
        returnString = strdup(finalString);
        return returnString;
    } else {
        strcat(finalString, currParam->string);
    }
    
    // caso haja mais do que um param
    while(currParam->next != NULL){
        strcat(finalString, ",");
        strcat(finalString, currParam->next->string);
        currParam = currParam->next;
    } 

    returnString = strdup(finalString);
    return returnString;
}