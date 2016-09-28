#include "include/node.h"


namespace graph {

    NodePtr newNode(std::string op, std::string inList[], size_t length, std::string out)
    {
        NodePtr node = new Node;
        node->op = op;
        node->out = out;
        node->length = length;

        cloneIncomingList(node, inList, length);
        return node;
    }


    void cloneIncomingList(NodePtr node, std::string inList[], size_t length)
    {
        for(int i = 0; i < length; i++) {
            node->incoming.push_back(inList[i]);
        }
    }

} /* namespace graph */