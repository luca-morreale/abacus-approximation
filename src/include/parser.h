#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "graph.h"
#include "syntax.h"

namespace parser {

    const std::string word("[\\w.-]");
    const std::string operations("\\+|-|\\*|\\/|<|<=|>|>=|==|\\!=|&&|\\|\\||<<a|<<c|&|\\||~|abs");
    const std::regex nodeRegex("(_?\\w+)( (" + operations + ")( )+(" + word + "+)( )+(" + word + "+))? *\n*");
    const std::regex inputRegex("((\\w+))( (" + word + ")+) *\n*");

    /**
     * Extracts the graph parsing the input stream from the file.
     * std::ifstream &cin   reference to the input file stream
     * std::string type     type of the input data
     * 
     * return graph::GraphPtr   pointer to the graph generated
     */
    graph::GraphPtr extractGraph(std::ifstream &cin, std::string type);

    /**
     * Extracts the set of edges from a given input file stream.
     */
    graph::Edges extractEdges(std::ifstream &cin);

    /**
     * Parses a string extractin the node and edge information.
     * std::string str      string to be parsed
     * 
     * return graph::NodePtr    pointer to the extracted node
     */
    std::vector<std::string> parse(std::string str, const std::regex &regex);

    /**
     * Generates a node from a list of information.
     * std::vector<std::string> list    list containing all the information of edges and node
     *
     * return graph::NodePtr    pointer to the generated node, or NULL if the list is empty
     */
    graph::NodePtr deriveNode(std::vector<std::string> &list);

    void insertIn(graph::Edges &edges, std::vector<std::string> list);

    /**
     * Checks if the string do not contains comments and is not empty.
     * std::string str      string to be checked
     *
     * return bool      true if the string is valid, false if is empty or contains a comment
     */
    bool isValidString(std::string str);

}

#endif /* PARSER_H */