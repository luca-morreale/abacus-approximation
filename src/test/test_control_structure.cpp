#define BOOST_TEST_MODULE ControlStructureTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "graph.h"
#include "parser.h"
#include "executer.h"

using namespace std;


BOOST_AUTO_TEST_CASE(controlStructureExecution)
{
    
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;
    
    int out;
    graph::NodePtr current;
    for(int i = 0; i < 3; i++) {
        current = graph->next();
        exec.runBasicOperation(current, graph);
    }

    current = graph->next();
    BOOST_CHECK_EQUAL("_if", current->out);

    exec.runBasicOperation(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->current();
    BOOST_CHECK_EQUAL("c", current->out);   // check do not skip forward executing control op


    in.close();
}

BOOST_AUTO_TEST_CASE(guidedIfExecution)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr graph = parser::extractGraph(in, "int");
    executer::Executer exec;
    
    int out;
    graph::NodePtr current;
    for(int i = 0; i < 3; i++) {
        current = graph->next();
        exec.runBasicOperation(current, graph);
    }

    current = graph->next();                // first _if node
    exec.runBasicOperation(current, graph);
    graph->get(current->out, out);
    exec.skipToEndBlock(current->out, graph);
    
    current = graph->next();
    BOOST_CHECK_EQUAL("out", current->out);
    exec.runBasicOperation(current, graph);
    graph->get(current->out, out);
    BOOST_CHECK_EQUAL(0, out);

    current = graph->next();                // second _if node
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
    
    ifstream in("../../src/test/complex_benchmark.graph");
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
    
    ifstream in("../../src/test/complex_benchmark.graph");
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

    current = graph->next();                    // first loop
    exec.runNode(current, graph);


    current = graph->next();
    exec.runBasicOperation(current, graph);     // set counter to zero
    current = graph->next();
    exec.runBasicOperation(current, graph);     // set i to zero

    current = graph->next();
    BOOST_CHECK_EQUAL("_for", current->out);
    exec.runNode(current, graph);

    graph->get("i", out);
    BOOST_CHECK_EQUAL(10, out);

    graph->get("sum", out);
    BOOST_CHECK_EQUAL(450, out);


    in.close();
}