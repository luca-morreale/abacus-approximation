
#include "include/graph.h"

using namespace graph;


Node *Graph::next()
{
	return (nodes.size() < cursor)? NULL : nodes[cursor++];
}


void Graph::appendNode(Node *node)
{
	nodes.push_back(node);
}