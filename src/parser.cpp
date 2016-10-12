#include "include/parser.h"
#include <iostream>


namespace parser {

    graph::GraphPtr extractGraph(std::ifstream &cin, std::string type)
    {
        graph::GraphPtr graph = new graph::Graph(type);

        std::string buf;
        while(getline(cin, buf)) {
            auto list = parse(buf, nodeRegex);
            graph->appendToGraph(deriveNode(list));
        }
        return graph;
    }

    graph::Edges extractEdges(std::ifstream &cin)
    {
        graph::Edges edges;
        std::string buf;
        while(getline(cin, buf)) {
            auto list = parse(buf, inputRegex);
            insertIn(edges, list);
        }
        return edges;
    }

    std::vector<std::string> parse(std::string str, const std::regex &regex)
    {
        std::smatch matches;
        std::vector<std::string> list;

        if(!isValidString(str)) {
            return list;
        }

        if (std::regex_search(str, matches, regex)) {
            for (int i = 1; i < matches.size(); i += 2) {
                std::string el = matches[i];
                list.push_back(el);
            }
        }
        return list;
    }

    graph::NodePtr deriveNode(std::vector<std::string> &list)
    {
        if(!list.empty()) {
            return graph::newNode(list[1], &list[2], list.size() - 2, list[0]);
        }
        return NULL;
    }

    void insertIn(graph::Edges &edges, std::vector<std::string> list)
    {
        if (!list.empty()) {
            edges[list[0]] = list[1];
        }
    }

    bool isValidString(std::string str) 
    {
        return str.size() > 2 && str.find("#") == std::string::npos;
    }


} /* namespace parser */