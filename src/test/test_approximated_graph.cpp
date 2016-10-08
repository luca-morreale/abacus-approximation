#define BOOST_TEST_MODULE ApproximatedGraphTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "approximated_graph.h"
#include "parser.h"

using namespace std;

BOOST_AUTO_TEST_CASE(buildApproxGraph)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");
    approximation::ApproximatedGraphPtr graph = new approximation::ApproximatedGraph(*original);

    BOOST_CHECK_EQUAL("int", graph->getType());

    graph::NodePtr current = graph->next();
    BOOST_CHECK_EQUAL("a", current->out);
    BOOST_CHECK_EQUAL("0", current->incoming[0]);
    BOOST_CHECK_EQUAL("0", current->incoming[1]);
    
    current = graph->next();
    BOOST_CHECK_EQUAL("b", current->out);
    BOOST_CHECK_EQUAL("-", current->op);

    current = graph->next();
    BOOST_CHECK_EQUAL("c", current->out);
    BOOST_CHECK_EQUAL("/", current->op);

    current = graph->next();
    BOOST_CHECK_EQUAL("c", current->out);
    BOOST_CHECK_EQUAL("&", current->op);

    current = graph->next();
    BOOST_CHECK_EQUAL("b", current->out);
    BOOST_CHECK_EQUAL("*", current->op);

    current = graph->next();
    BOOST_CHECK_EQUAL("d", current->out);
    BOOST_CHECK_EQUAL("0.7", current->incoming[0]);

    current = graph->next();
    BOOST_CHECK_EQUAL("output", current->out);
    BOOST_CHECK_EQUAL("c", current->incoming[0]);
    BOOST_CHECK_EQUAL("b", current->incoming[1]);

    in.close();
}


BOOST_AUTO_TEST_CASE(substitutionApproxGraph)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");
    approximation::ApproximatedGraphPtr graph = new approximation::ApproximatedGraph(*original);

    graph::Nodes replacements;
    graph::NodePtr tmp, current;
    
    current = graph->next();
    current = graph->next();
    current = graph->next();

    tmp = newNode(current);
    tmp->out = "d";
    tmp->op = "<<";
    replacements.push_back(tmp);

    tmp = newNode(current);
    tmp->incoming[0] = "d";
    tmp->op = "||";
    replacements.push_back(tmp);

    graph->substitute(replacements, current);

    approximation::ApproximatedGraphPtr copy = new approximation::ApproximatedGraph(*graph);


    current = copy->next();
    BOOST_CHECK_EQUAL("a", current->out);
    BOOST_CHECK_EQUAL("0", current->incoming[0]);
    BOOST_CHECK_EQUAL("0", current->incoming[1]);
    
    current = copy->next();
    BOOST_CHECK_EQUAL("b", current->out);
    BOOST_CHECK_EQUAL("-", current->op);

    current = copy->next();
    BOOST_CHECK_EQUAL("d", current->out);
    BOOST_CHECK_EQUAL("<<", current->op);
    BOOST_CHECK_EQUAL("1", current->incoming[0]);
    BOOST_CHECK_EQUAL("2", current->incoming[1]);

    current = copy->next();
    BOOST_CHECK_EQUAL("c", current->out);
    BOOST_CHECK_EQUAL("||", current->op);
    BOOST_CHECK_EQUAL("d", current->incoming[0]);
    BOOST_CHECK_EQUAL("2", current->incoming[1]);

    current = copy->next();
    BOOST_CHECK_EQUAL("c", current->out);
    BOOST_CHECK_EQUAL("&", current->op);


    in.close();
}