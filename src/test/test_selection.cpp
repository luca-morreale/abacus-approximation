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

    auto nodes = approximation::selectSuitableNodes(original, approximation::approximateSum);
    BOOST_CHECK_EQUAL(16, nodes.size());

    

    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(subtractionSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(original, approximation::approximateMinus);
    BOOST_CHECK_EQUAL(2, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(divisionSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(original, approximation::approximateDiv);
    BOOST_CHECK_EQUAL(1, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(multSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(original, approximation::approximateMult);
    BOOST_CHECK_EQUAL(0, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(valueSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(original, approximation::approximateValue);
    BOOST_CHECK_EQUAL(19, nodes.size());
    
    delete(original);
    in.close();
}

BOOST_AUTO_TEST_CASE(multipleSelection)
{
    ifstream in("../../src/test/complex_benchmark.graph");
    graph::GraphPtr original = parser::extractGraph(in, "int");

    auto nodes = approximation::selectSuitableNodes(original, approximation::approximateMinus);
    BOOST_CHECK_EQUAL(2, nodes.size());
    nodes = approximation::selectSuitableNodes(original, approximation::approximateSum);
    BOOST_CHECK_EQUAL(16, nodes.size());
    nodes = approximation::selectSuitableNodes(original, approximation::approximateMult);
    BOOST_CHECK_EQUAL(0, nodes.size());
    nodes = approximation::selectSuitableNodes(original, approximation::approximateDiv);
    BOOST_CHECK_EQUAL(1, nodes.size());
    
    delete(original);
    in.close();
}