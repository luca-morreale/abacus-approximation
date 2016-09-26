
#include "include/operations.h"

using namespace graph;

Node *graph::newNode(std::string op, std::string inList[], size_t length, std::string out)
{
    Node *node = (Node *) malloc(sizeof(Node));

    node->op = op;
    node->out = out;
    cloneIncomingList(node, inList, length);
    
    node->length = length;

    return node;
}


void graph::cloneIncomingList(Node *node, std::string inList[], size_t length)
{
    for(int i = 0; i < length; i++) {
        node->incoming[i] = inList[i];
    }
}
