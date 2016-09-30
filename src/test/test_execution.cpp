#define BOOST_TEST_MODULE ExecutionTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "graph.h"
#include "parser.h"
#include "executer.h"

using namespace std;

BOOST_AUTO_TEST_CASE(correctOperation)
{
    ifstream in("/home/luca/projects/School/aapp/code/src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");

    graph::NodePtr current = graph->next();
    int out = executer::sum<int>(current->incoming[0], current->incoming[1], graph);
    BOOST_CHECK_EQUAL(0, out);
    graph->set(current->out, out);


    current = graph->next();
    out = executer::minus<int>(current->incoming[0], current->incoming[1], graph);
    BOOST_CHECK_EQUAL(-5, out);
    graph->set(current->out, out);

    in.close();
}


BOOST_AUTO_TEST_CASE(run_single_node)
{
    ifstream in("/home/luca/projects/School/aapp/code/src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");

    graph::NodePtr current = graph->next();
    executer::runNode(current, graph);
    
    int out;
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->next();
    executer::runNode(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(-5, out);

    current = graph->next();
    executer::runNode(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->next();
    executer::runNode(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    in.close();
}

BOOST_AUTO_TEST_CASE(execution)
{
    
    ifstream in("/home/luca/projects/School/aapp/code/src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::runGraph(graph);
    
    int out;
    graph->get("output", out);
    BOOST_CHECK_EQUAL(-10, out);

    in.close();
}
