#include "include/edge.h"


Edge *newEdge(char *key, char *value)
{
	Edge *edge = (Edge *) malloc(sizeof(Edge));

    strcpy(edge->key, key);
    strcpy(edge->value, value);

    return edge;
}

EdgeList *newEdgeList(Edge *edge);
char *get(EdgeList *list, char *key);
void append(EdgeList *list, char *key, char *value);
void set(EdgeList *list, char *key, int value);
void set(EdgeList *list, char *key, double value);
void freeEdges(EdgeList *list);




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
