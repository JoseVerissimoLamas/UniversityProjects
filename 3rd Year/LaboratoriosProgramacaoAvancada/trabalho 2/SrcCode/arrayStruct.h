#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Linked List containing the point's coords and the next member of the list
typedef struct linkedList{
    float x;
    float y;
    struct linkedList* next;
} LinkedArray;

// creates the new Member for the LinkedArray
LinkedArray* newMember(float x, float y);

// get member in 'index' position
LinkedArray* get(LinkedArray* header, int index);