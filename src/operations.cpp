
#include "include/operations.h"



Operation *newOperation(char *op, char *inList[], size_t length, char *out)
{
    Operation *operation = (Operation *) malloc(sizeof(Operation));

    strcpy(operation->op, op);
    strcpy(operation->out, out);
    copyIncomingList(operation, inList, length);
    
    operation->length = length;

    return operation;
}


void copyIncomingList(Operation *operation, char *inList[], size_t length)
{
    int i;
    for(i = 0; i < length; i++) {
        strcpy(operation->incoming[i], inList[i]);
    }
}


Operation *get(OpList *list, unsigned int index)
{
    OpList *cursor = list;
    while (cursor != NULL && cursor->index == index) {
        cursor = cursor->next;
    }

    return cursor->op;
}


void append(OpList *list, Operation *op)
{
    if (list->op == NULL) {
        list->op = op;
    }

    OpList **cursor = &list;
    while ((*cursor)->next != NULL) {
        cursor = &(*cursor)->next;
    }

    (*cursor)->next = newOpList(op);
}


OpList *newOpList(Operation *op)
{
    OpList *list = (OpList *) malloc(sizeof(OpList));
    list->next = NULL;
    list->op = op;
    return list;
}


void freeOperations(OpList *list)
{
    OpList **cursor = &list;

    while((*cursor) != NULL) {
        OpList *tmp = *cursor;
        cursor = &(*cursor)->next;
        free(tmp);
    }
}
