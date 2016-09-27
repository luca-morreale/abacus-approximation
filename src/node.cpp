
#include "include/node.h"

namespace graph {

    NodePtr newNode(std::string op, std::string inList[], size_t length, std::string out)
    {
        NodePtr node = (NodePtr) malloc(sizeof(Node));

        node->op = op;
        node->out = out;
        cloneIncomingList(node, inList, length);
        
        node->length = length;

        return node;
    }


    void cloneIncomingList(NodePtr node, std::string inList[], size_t length)
    {
        for(int i = 0; i < length; i++) {
            node->incoming[i] = inList[i];
        }
    }

} /* namespace graph */