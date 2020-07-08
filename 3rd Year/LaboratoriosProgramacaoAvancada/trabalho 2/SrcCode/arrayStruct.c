#include "arrayStruct.h"

// creates the new Member for the LinkedArray
LinkedArray* newMember(float x, float y){

    // memory alloc for the new member
    LinkedArray* newMemb = (LinkedArray*)malloc(sizeof(LinkedArray));

    // register the coords
    newMemb->x = x;
    newMemb->y = y;
    newMemb->next = NULL;

    return newMemb;
}

// get member in 'index' position
LinkedArray* get(LinkedArray* header, int index){

    // error detector
    if(header == NULL) return NULL;

    // pointer responsible to "travel" through the list
    LinkedArray* current = header;
    int currIndex = 0;

    for(currIndex; currIndex < index; currIndex++){
        // "travel" through the list
        current = current->next;

        // error detector
        if(current = NULL) return NULL;
    }

    return current;
}