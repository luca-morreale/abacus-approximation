#ifndef OPERATIONS_H
#define OPERATIONS_H


#include <cstdlib>
#include <string>
#include <vector>

namespace graph {

	typedef struct {
		std::string incoming[10];
		size_t length;
		std::string out;
		std::string op;
	} Node;

	typedef Node * NodePtr;

	typedef std::vector<NodePtr> Nodes;


	graph::NodePtr newNode(std::string op, std::string inList[], size_t length, std::string out);
	void cloneIncomingList(NodePtr node, std::string inList[], size_t length);

}

#endif /* OPERATIONS_H */