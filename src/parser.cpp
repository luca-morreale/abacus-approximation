
#include "include/parser.h"

using namespace parser;


graph::Node *parser::parse(std::string str)
{
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


graph::Node *parser::nodeFromList(std::vector<std::string> list)
{
    return graph::newNode(list[1], &list[2], list.size() - 2, list[0]);
}
