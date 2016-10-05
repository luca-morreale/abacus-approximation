#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <vector>

#include "node.h"
#include "syntax.h"

namespace approximation {

    typedef graph::Nodes (*Approximation)(graph::NodePtr node);

    graph::Nodes approximateSum(graph::NodePtr node);
    graph::Nodes approximateMinus(graph::NodePtr node);
    graph::Nodes approximateMult(graph::NodePtr node);
    graph::Nodes approximateDiv(graph::NodePtr node);
    graph::Nodes approximateLoop(graph::NodePtr node);
    graph::Nodes approximateType(graph::NodePtr node);  //uhm

}

#endif