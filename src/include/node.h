#ifndef OPERATIONS_H
#define OPERATIONS_H


#include <cstdlib>
#include <string>
#include <vector>

namespace graph {

    typedef struct Node {
        std::vector<std::string> incoming;
        size_t length;
        std::string out;
        std::string op;
    } Node;

    typedef Node * NodePtr;

    typedef std::vector<NodePtr> Nodes;
    
    typedef std::vector<graph::NodePtr>::iterator NodeIterator;

    /**
     * Creates a node using the given informations.
     * std::string op           string representing the operation
     * std::string inList[]     array of string containing incoming edges
     * size_t length            length of the above array
     * std::string out          outgoing edge
     *
     * return NodePtr   pointer to the generated node
     */
    NodePtr newNode(std::string op, std::string inList[], size_t length, std::string out);
    NodePtr newNode(NodePtr other);

    /**
     * Copies the list of incoming edges inside the node.
     * NodePtr node             node to be filled
     * std::string inList[]     list of incoming edge
     * size_t length            length of incoming edge
     */
    void cloneIncomingList(NodePtr node, std::string inList[], size_t length);
    void cloneIncomingList(NodePtr node, NodePtr other);

}

#endif /* OPERATIONS_H */