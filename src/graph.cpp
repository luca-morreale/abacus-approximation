
#include "include/graph.h"

namespace graph {

	GraphPtr newGraph(std::string type)
	{
	    GraphPtr graph = (GraphPtr) malloc(sizeof(Graph));
	    graph->cursor = 0;
	    graph->type = type;
	    return graph;
	}

	NodePtr Graph::next()
	{
	    return (nodes.size() < cursor)? NULL : nodes[cursor++];
	}

	void Graph::appendToGraph(NodePtr node)
	{
	    nodes.push_back(node);
	    addEdges(node);
	}

	void Graph::addEdges(NodePtr node)
	{
	    if(edges.find(node->out) == edges.end()) {
	        set(node->out, 0);
	    }
	    for(std::string key : node->incoming) {
	        if(edges.find(key)  == edges.end()) {
	            set(key, 0);
	        }
	    }
	}

	void Graph::set(std::string key, int value)
	{
	    std::ostringstream os; 
	    os << value; 
	    edges[key] = os.str(); 
	}

	void Graph::set(std::string key, float value)
	{
	    std::ostringstream os; 
	    os << value; 
	    edges[key] = os.str(); 
	}

	void Graph::set(std::string key, double value)
	{
	    std::ostringstream os; 
	    os << value; 
	    edges[key] = os.str(); 
	}

	void Graph::get(std::string key, int &out)
	{
	    out = std::stoi(edges[key], NULL);
	}

	void Graph::get(std::string key, float &out)
	{
	    out = std::stof(edges[key], NULL);
	}

	void Graph::get(std::string key, double &out)
	{
	    out = std::stod(edges[key], NULL);
	}


}