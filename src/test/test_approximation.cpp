#define BOOST_TEST_MODULE ApproximationTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "approximation.h"
#include "parser.h"

using namespace std;

BOOST_AUTO_TEST_CASE(sumApproximation)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    graph::NodePtr current = original->next();
    int mask = -1;

    graph::Nodes replacements = approximation::approximateSum(current, mask);
    BOOST_CHECK_EQUAL(-1, mask);
    BOOST_CHECK_EQUAL(1, replacements.size());
    BOOST_CHECK_EQUAL(current->incoming[0], replacements[0]->incoming[0]);
    BOOST_CHECK_EQUAL(current->incoming[1], replacements[0]->incoming[1]);
    BOOST_CHECK_EQUAL("|", replacements[0]->op);
    BOOST_CHECK_EQUAL(current->out, replacements[0]->out);

    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(subtractionApproximation)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    original->next();
    graph::NodePtr current = original->next();
    int mask = -1;

    graph::Nodes replacements = approximation::approximateMinus(current, mask);
    BOOST_CHECK_EQUAL(-1, mask);
    BOOST_CHECK_EQUAL(2, replacements.size());
    BOOST_CHECK_EQUAL(current->incoming[1], replacements[0]->incoming[0]);
    BOOST_CHECK_EQUAL(current->incoming[1], replacements[0]->incoming[1]);
    BOOST_CHECK_EQUAL("~", replacements[0]->op);
    BOOST_CHECK_EQUAL("tmp", replacements[0]->out);

    BOOST_CHECK_EQUAL(current->incoming[0], replacements[1]->incoming[0]);
    BOOST_CHECK_EQUAL("tmp", replacements[1]->incoming[1]);
    BOOST_CHECK_EQUAL("&", replacements[1]->op);
    BOOST_CHECK_EQUAL(current->out, replacements[1]->out);
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(divisionApproximation)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    for(int i=0; i<2; i++) {
        original->next();
    }

    graph::NodePtr current = original->next();
    int mask = -1;

    graph::Nodes replacements = approximation::approximateDiv(current, mask);
    BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (-1)(mask));
    BOOST_CHECK_EQUAL(2, replacements.size());
    BOOST_CHECK_EQUAL(current->incoming[0], replacements[0]->incoming[0]);
    BOOST_CHECK_EQUAL(std::to_string(mask), replacements[0]->incoming[1]);
    BOOST_CHECK_EQUAL(">>", replacements[0]->op);
    BOOST_CHECK_EQUAL("tmp", replacements[0]->out);

    BOOST_CHECK_EQUAL(current->incoming[1], replacements[1]->incoming[1]);
    BOOST_CHECK_EQUAL("tmp", replacements[1]->incoming[0]);
    BOOST_CHECK_EQUAL("-", replacements[1]->op);
    BOOST_CHECK_EQUAL(current->out, replacements[1]->out);
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(multApproximation)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    for(int i=0; i<4; i++) {
        original->next();
    }

    graph::NodePtr current = original->next();
    int mask = -1;

    graph::Nodes replacements = approximation::approximateMult(current, mask);
    BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (-1)(mask));
    BOOST_CHECK_EQUAL(2, replacements.size());
    BOOST_CHECK_EQUAL(current->incoming[0], replacements[0]->incoming[0]);
    BOOST_CHECK_EQUAL(std::to_string(mask), replacements[0]->incoming[1]);
    BOOST_CHECK_EQUAL("<<", replacements[0]->op);
    BOOST_CHECK_EQUAL("tmp", replacements[0]->out);

    BOOST_CHECK_EQUAL(current->incoming[1], replacements[1]->incoming[1]);
    BOOST_CHECK_EQUAL("tmp", replacements[1]->incoming[0]);
    BOOST_CHECK_EQUAL("+", replacements[1]->op);
    BOOST_CHECK_EQUAL(current->out, replacements[1]->out);
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(valueApproximation)
{
    ifstream in("../../src/test/benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    for(int i=0; i<3; i++) {
        original->next();
    }

    graph::NodePtr current = original->next();
    int mask = -1;

    graph::Nodes replacements = approximation::approximateValue(current, mask);
    BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (-1)(mask));
    BOOST_CHECK_EQUAL(2, replacements.size());
    BOOST_CHECK_EQUAL(current->incoming[0], replacements[0]->incoming[0]);
    BOOST_CHECK_EQUAL(std::to_string(mask), replacements[0]->incoming[1]);
    BOOST_CHECK_EQUAL("&", replacements[0]->op);
    BOOST_CHECK_EQUAL("tmp", replacements[0]->out);

    BOOST_CHECK_EQUAL(current->incoming[1], replacements[1]->incoming[1]);
    BOOST_CHECK_EQUAL("tmp", replacements[1]->incoming[0]);
    BOOST_CHECK_EQUAL(current->op, replacements[1]->op);
    BOOST_CHECK_EQUAL(current->out, replacements[1]->out);
    
    delete(original);
    in.close();
}
