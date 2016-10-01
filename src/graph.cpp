#include "include/graph.h"
#include <iostream>

namespace graph {

    Graph::Graph(std::string type)
    {
        this->cursor = 0;
        this->type = type;
    }

    NodePtr Graph::next()
    {
        return (nodes.size() <= cursor)? NULL : nodes[cursor++];
    }

    NodePtr Graph::rollback()
    {
        return (0 >= cursor)? NULL : nodes[--cursor];
    }

    void Graph::appendToGraph(NodePtr node)
    {
        if(this->isValidNode(node)) {
            this->nodes.push_back(node);
            this->addEdges(node);
        }
    }

    void Graph::addEdges(NodePtr node)
    {
        if(this->isNewEdge(node->out)) {
            this->set(node->out, 0);
        }

        for(std::string key : node->incoming) {
            if(this->isNewEdge(key) && this->isValidEdge(key)) {
                this->set(key, 0);
            }
        }
    }

    bool Graph::isValidNode(NodePtr node)
    {
        return node != NULL;
    }

    bool Graph::isNewEdge(std::string edge)
    {
        return this->edges.find(edge)  == this->edges.end();
    }

    bool Graph::isValidEdge(std::string edge)
    {
        return edge.size() > 0;
    }

    void Graph::set(std::string key, int value)
    {
        std::ostringstream os;
        os << value;
        this->edges[key] = os.str();
    }

    void Graph::set(std::string key, float value)
    {
        std::ostringstream os;
        os << value;
        this->edges[key] = os.str();
    }

    void Graph::set(std::string key, double value)
    {
        std::ostringstream os;
        os << value;
        this->edges[key] = os.str();
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

    std::string Graph::getType()
    {
        return this->type;
    }

    Graph::~Graph()
    {
        for (NodeIterator it = this->nodes.begin(); it != this->nodes.end(); it++) {
            free(*it);
        }
    }

    #ifdef DEBUG
        void Graph::debug()
        {
            for (EdgeIterator it = this->edges.begin(); it != this->edges.end(); it++) {
                std::cout << "edge: " << it->first << " value: " << it->second << std::endl;
            }

            for (NodeIterator it = this->nodes.begin(); it != this->nodes.end(); it++) {
                std::cout << "out: " << (*it)->out << " op: " << (*it)->op << " operands list: ";
                for (std::vector<std::string>::iterator sit = (*it)->incoming.begin(); sit != (*it)->incoming.end(); sit++) {
                    std::cout << *sit << " ";
                }
                std::cout << std::endl;
            }

        }
    #endif


} /* namespace graph */