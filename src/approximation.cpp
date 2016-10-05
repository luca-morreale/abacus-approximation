#include "include/approximation.h"


namespace approximation {

    graph::Nodes approximateSum(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement[0]->op = "|";
        return replacement;
    }

    graph::Nodes approximateMinus(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));
        
        replacement[0]->op = "~";
        replacement[0]->out = "tmp";
        replacement[0]->incoming[0] = replacement[0]->incoming[1];

        replacement[1]->op = "&";
        replacement[1]->incoming[1] = "tmp";

        return replacement;
    }

    graph::Nodes approximateMult(graph::NodePtr node)
    {

    }
    graph::Nodes approximateDiv(graph::NodePtr node)
    {

    }

    graph::Nodes approximateLoop(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        
        if(syntax::isNumber(replacement[0]->incoming[0])) {
            int index = std::stoi(replacement[0]->incoming[0]) * 2;
            replacement[0]->incoming[0] = index +"";
        } else {
            int index = std::stoi(replacement[0]->incoming[1]) * 2;
            replacement[0]->incoming[1] = index +"";
        }

        return replacement;
    }

    graph::Nodes approximateType(graph::NodePtr node)  //uhm
    {

    }

}