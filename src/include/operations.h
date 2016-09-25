#ifndef OPERATIONS_H
#define OPERATIONS_H


#include <stdlib.h>
#include <string.h>
#include <vector>

typedef struct {
	char *incoming[10];
	size_t length;
	char out[10];
	char op[5];
} Operation;


typedef struct OpList {
	Operation *op;
	OpList *next;
	unsigned int index;
} OpList;


Operation *newOperation(char *op, char *inList[], size_t length, char *out);
void copyIncomingList(Operation *operation, char *inList[], size_t length);

OpList *newOpList(Operation *op);
Operation *get(OpList *list, unsigned int index);
void append(OpList *list, Operation *op);
void freeOperations(OpList *list);



#endif /* OPERATIONS_H */