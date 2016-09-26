#ifndef GRAPH_H
#define GRAPH_H


#include "node.h"
#include "edge.h"


namespace graph {

	typedef struct {
		std::vector<Node*> nodes;
		Edges edges;
		unsigned int cursor;

		Node *next();
		void appendNode(Node *node);


	} Graph;

}


#endif /* GRAPH_H */