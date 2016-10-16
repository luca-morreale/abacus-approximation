#define BOOST_TEST_MODULE SelectionTests

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "approximation.h"
#include "parser.h"

using namespace std;


BOOST_AUTO_TEST_CASE(sumSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(approximation::approximateSum, original);
    BOOST_CHECK_EQUAL(10, nodes.size());

    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(subtractionSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(approximation::approximateMinus, original);
    BOOST_CHECK_EQUAL(2, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(divisionSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(approximation::approximateDiv, original);
    BOOST_CHECK_EQUAL(1, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(multSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(approximation::approximateMult, original);
    BOOST_CHECK_EQUAL(0, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(valueSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(approximation::approximateValue, original);
    BOOST_CHECK_EQUAL(13, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(multipleSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(approximation::approximateMinus, original);
    BOOST_CHECK_EQUAL(2, nodes.size());
    nodes = approximation::selectSuitableNodes(approximation::approximateSum, original);
    BOOST_CHECK_EQUAL(10, nodes.size());
    nodes = approximation::selectSuitableNodes(approximation::approximateMult, original);
    BOOST_CHECK_EQUAL(0, nodes.size());
    nodes = approximation::selectSuitableNodes(approximation::approximateDiv, original);
    BOOST_CHECK_EQUAL(1, nodes.size());
    
    delete(original);
    in.close();
}