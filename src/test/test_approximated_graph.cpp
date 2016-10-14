#define BOOST_TEST_MODULE ApproximatedGraphTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "approximated_graph.h"
#include "parser.h"
#include "executer.h"

using namespace std;

BOOST_AUTO_TEST_CASE(buildApproxGraph)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");
    approximation::ApproximatedGraph graph(*original);

    BOOST_CHECK_EQUAL("int", graph.getType());

    graph::NodePtr current = graph.next();
    BOOST_CHECK_EQUAL("a", current->out);
    BOOST_CHECK_EQUAL("0", current->incoming[0]);
    BOOST_CHECK_EQUAL("0", current->incoming[1]);
    
    current = graph.next();
    BOOST_CHECK_EQUAL("b", current->out);
    BOOST_CHECK_EQUAL("-", current->op);

    current = graph.next();
    BOOST_CHECK_EQUAL("c", current->out);
    BOOST_CHECK_EQUAL("/", current->op);

    current = graph.next();
    BOOST_CHECK_EQUAL("c", current->out);
    BOOST_CHECK_EQUAL("&", current->op);

    current = graph.next();
    BOOST_CHECK_EQUAL("b", current->out);
    BOOST_CHECK_EQUAL("*", current->op);

    current = graph.next();
    BOOST_CHECK_EQUAL("d", current->out);
    BOOST_CHECK_EQUAL("0.7", current->incoming[0]);

    current = graph.next();
    BOOST_CHECK_EQUAL("output", current->out);
    BOOST_CHECK_EQUAL("c", current->incoming[0]);
    BOOST_CHECK_EQUAL("b", current->incoming[1]);

    delete(original);
    in.close();
}


BOOST_AUTO_TEST_CASE(substitutionApproxGraph)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");
    approximation::ApproximatedGraph graph(*original);

    graph::Nodes replacements;
    graph::NodePtr tmp, current;
    
    current = graph.next();
    current = graph.next();
    current = graph.next();

    tmp = newNode(current);
    tmp->out = "d";
    tmp->op = "<<";
    replacements.push_back(tmp);

    tmp = newNode(current);
    tmp->incoming[0] = "d";
    tmp->op = "||";
    replacements.push_back(tmp);

    auto copy = graph.substitute(replacements, current);

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


    delete(original);
    delete(copy);
    in.close();
}

BOOST_AUTO_TEST_CASE(testSeparateRun)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");
    approximation::ApproximatedGraph graph(*original);

    executer::Executer exec;
    exec.runGraph(original);

    graph::NodePtr a = graph.next();
    graph::NodePtr b = original->next();
    BOOST_CHECK_PREDICATE(std::not_equal_to<graph::NodePtr>(), (a)(b));
    BOOST_CHECK_EQUAL("a", a->out);
    BOOST_CHECK_EQUAL("0", a->incoming[0]);
    BOOST_CHECK_EQUAL("0", a->incoming[1]);

    delete(original);
    in.close();
}

