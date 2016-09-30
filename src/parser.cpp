#include "include/parser.h"


namespace parser {

    graph::GraphPtr extractGraph(std::ifstream &cin, std::string type)
    {
        graph::GraphPtr graph = new graph::Graph(type);

        std::string buf;
        while(getline(cin, buf)) {
            graph->appendToGraph(parse(buf));
        }
        return graph;
    }

    graph::NodePtr parse(std::string str)
    {
        if (!isValidString(str)) return NULL;

        std::smatch matches;
        std::vector<std::string> list;
        
        if (std::regex_search(str, matches, regex)) {
            for (int i = 1; i < matches.size(); i += 2) {
                std::string el = matches[i];
                list.push_back(el);
            }
            return nodeFromList(list);
        }
        return NULL;
    }

    bool isValidString(std::string str) 
    {
        return str.size() > 2 && str.find("#") == std::string::npos;
    }

    graph::NodePtr nodeFromList(std::vector<std::string> list)
    {
        return graph::newNode(list[1], &list[2], list.size() - 2, list[0]);
    }

} /* namespace parser */