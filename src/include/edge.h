#ifndef EDGE_H
#define EDGE_H

#include <string.h>


typedef struct {
	char key[10];
	char value[20];
} Edge;


typedef struct EdgeList {
	Edge *edge;
	EdgeList *next;
} EdgeList;


Edge *newEdge(char *key, char *value);

EdgeList *newEdgeList(Edge *edge);
char *get(EdgeList *list, char *key);
void append(EdgeList *list, char *key, char *value);
void set(EdgeList *list, char *key, int value);
void set(EdgeList *list, char *key, double value);
void freeEdges(EdgeList *list);

#endif /* EDGE_H */
