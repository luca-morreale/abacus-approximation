#define BOOST_TEST_MODULE GraphTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "../include/graph.h"
#include "../include/parser.h"
#include "../include/executer.h"

using namespace std;

BOOST_AUTO_TEST_CASE(buildGraph)
{
    ifstream in("/home/luca/projects/School/aapp/code/src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");

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
    BOOST_CHECK_EQUAL("output", current->out);
    BOOST_CHECK_EQUAL("c", current->incoming[0]);
    BOOST_CHECK_EQUAL("b", current->incoming[1]);

    in.close();
}

// test set & get


BOOST_AUTO_TEST_CASE(graphSetGet)
{
    ifstream in("/home/luca/projects/School/aapp/code/src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");

    graph->set("a", 1.5);
    float a;
    graph->get("a", a);
    BOOST_CHECK_EQUAL(1.5, a);

    graph->set("c", 7.3);
    int c;
    graph->get("c", c);
    BOOST_CHECK_EQUAL(7, c);
}