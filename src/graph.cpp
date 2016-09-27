
#include "include/graph.h"

namespace graph {

	GraphPtr newGraph(std::string type)
	{
	    GraphPtr graph = (GraphPtr) malloc(sizeof(Graph));
	    graph->cursor = 0;
	    graph->type = type;
	    return graph;
	}

	NodePtr next(GraphPtr graph)
	{
	    return (graph->nodes.size() < graph->cursor)? NULL : graph->nodes[graph->cursor++];
	}

	void appendToGraph(GraphPtr graph, NodePtr node)
	{
	    graph->nodes.push_back(node);
	    addEdges(graph, node);
	}

	void addEdges(GraphPtr graph, NodePtr node)
	{
	    if(graph->edges.find(node->out) == graph->edges.end()) {
	        set(graph, node->out, 0);
	    }
	    for(std::string key : node->incoming) {
	        if(graph->edges.find(key)  == graph->edges.end()) {
	            set(graph, key, 0);
	        }
	    }
	}

	void set(GraphPtr graph, std::string key, int value)
	{
	    std::ostringstream os; 
	    os << value; 
	    graph->edges[key] = os.str(); 
	}

	void set(GraphPtr graph, std::string key, float value)
	{
	    std::ostringstream os; 
	    os << value; 
	    graph->edges[key] = os.str(); 
	}

	void set(GraphPtr graph, std::string key, double value)
	{
	    std::ostringstream os; 
	    os << value; 
	    graph->edges[key] = os.str(); 
	}


	void get(GraphPtr graph, std::string key, int &out)
	{
	    out = std::stoi(graph->edges[key], NULL);
	}

	void get(GraphPtr graph, std::string key, float &out)
	{
	    out = std::stof(graph->edges[key], NULL);
	}

	void get(GraphPtr graph, std::string key, double &out)
	{
	    out = std::stod(graph->edges[key], NULL);
	}


}