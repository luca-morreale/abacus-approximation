#define BOOST_TEST_MODULE ControlStructureTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "graph.h"
#include "parser.h"
#include "executer.h"

using namespace std;


BOOST_AUTO_TEST_CASE(controlStructureExecution)
{
    
    ifstream in("/home/luca/projects/School/aapp/code/src/test/complex_benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;
    
    int out;
    graph::NodePtr current;
    for (int i = 0; i < 3; i++) {       // run the three initial operation
        current = graph->next();
        exec.runBasicOperation(current, graph);
    }
    
    current = graph->next();
    exec.runBasicOperation(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);
    BOOST_CHECK_EQUAL("_if", current->out);

    exec.skipToEndBlock(current->out, graph);
    current = graph->next();
    BOOST_CHECK_EQUAL("output", current->out);
    exec.runBasicOperation(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->next();
    BOOST_CHECK_EQUAL("_if", current->out);
    exec.runNode(current, graph);
    

    current = graph->next();
    BOOST_CHECK_EQUAL("output", current->out);
    exec.runBasicOperation(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(5, out);


    in.close();
}


BOOST_AUTO_TEST_CASE(loopStructureExecution)
{
    
    ifstream in("/home/luca/projects/School/aapp/code/src/test/complex_benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;
    
    int out;
    graph::NodePtr current;
    for (int i = 0; i < 3; i++) {       // run the three initial operation
        current = graph->next();
        exec.runBasicOperation(current, graph);
    }

    for (int i = 0; i < 2; i++) {   // run the two if structure
        current = graph->next();
        exec.runNode(current, graph);


        current = graph->next();
        exec.runBasicOperation(current, graph);
    }

    // here we start check the loop

    current = graph->next();
    exec.runBasicOperation(current, graph);     // set counter to zero
    current = graph->next();
    exec.runBasicOperation(current, graph);     // set i to zero

    current = graph->next();
    BOOST_CHECK_EQUAL("_for", current->out);
    exec.runNode(current, graph);

    graph->get("i", out);
    BOOST_CHECK_EQUAL(10, out);

    graph->get("counter", out);
    BOOST_CHECK_EQUAL(45, out);

    in.close();
}


BOOST_AUTO_TEST_CASE(completeExecution)
{
    
    ifstream in("/home/luca/projects/School/aapp/code/src/test/complex_benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;

    exec.runGraph(graph);

    int out;
    graph->get("i", out);
    BOOST_CHECK_EQUAL(10, out);

    graph->get("counter", out);
    BOOST_CHECK_EQUAL(45, out);

    in.close();
}