#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "graph.h"

namespace parser {

    const std::regex regex("(_?\\w+)( (\\+|-|\\*|\\/|<|<=|>|>=|==|\\!=|&&|\\|\\||<<a|<<c|&|\\||~)( )+([\\w.]+)( )+([\\w.]+))? *\n*");

    /**
     * Extracts the graph parsing the input stream from the file.
     * std::ifstream &cin   reference to the input file stream
     * std::string type     type of the input data
     * 
     * return graph::GraphPtr   pointer to the graph generated
     */
    graph::GraphPtr extractGraph(std::ifstream &cin, std::string type);

    /**
     * Parses a string extractin the node and edge information.
     * std::string str      string to be parsed
     * 
     * return graph::NodePtr    pointer to the extracted node
     */
    graph::NodePtr parse(std::string str);

    /**
     * Checks if the string do not contains comments and is not empty.
     * std::string str      string to be checked
     *
     * return bool      true if the string is valid, false if is empty or contains a comment
     */
    bool isValidString(std::string str);

    /**
     * Generates a node from a list of information.
     * std::vector<std::string> list    list containing all the information of edges and node
     *
     * return graph::NodePtr    pointer to the generated node
     */
    graph::NodePtr nodeFromList(std::vector<std::string> list);

}

#endif /* PARSER_H */