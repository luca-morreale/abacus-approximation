#define BOOST_TEST_MODULE ExecutionTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "graph.h"
#include "parser.h"
#include "executer.h"
#include "operations.h"

using namespace std;


BOOST_AUTO_TEST_CASE(correctOperation)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");

    graph::NodePtr current = graph->next();
    int out = operations::sum<int>(current->incoming[0], current->incoming[1], graph);
    BOOST_CHECK_EQUAL(0, out);
    graph->set(current->out, out);


    current = graph->next();
    out = operations::minus<int>(current->incoming[0], current->incoming[1], graph);
    BOOST_CHECK_EQUAL(-5, out);
    graph->set(current->out, out);

    delete(graph);
    in.close();
}


BOOST_AUTO_TEST_CASE(run_single_node)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;

    graph::NodePtr current = graph->next();
    exec.runNode(current, graph);
    
    int out;
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->next();
    exec.runNode(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(-5, out);

    current = graph->next();
    exec.runNode(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->next();
    exec.runNode(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    delete(graph);
    in.close();
}

BOOST_AUTO_TEST_CASE(simpleExecution)
{
    
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;

    exec.runGraph(graph);
    
    int out;
    graph->get("output", out);
    BOOST_CHECK_EQUAL(-10, out);

    delete(graph);
    in.close();
}
