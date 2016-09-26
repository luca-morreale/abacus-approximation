
#include "include/graph.h"

using namespace graph;


template <typename T>
Node *Graph<T>::next()
{
	return (nodes.size() < cursor)? NULL : nodes[cursor++];
}


template <typename T>
void Graph<T>::append(Node *node)
{
	nodes.push_back(node);
	// add edges
}

template <typename T>
void Graph<T>::set(std::string key, T value)
{
	std::ostringstream os; 
   	os << value; 
    edges[key] = os.str(); 
}


int Graph<int>::get(std::string key)
{
	return std::stoi(edges[key], NULL);
}


float Graph<float>::get(std::string key)
{
	return std::stof(edges[key], NULL);
}


double Graph<double>::get(std::string key)
{
	return std::stod(edges[key], NULL);
}
