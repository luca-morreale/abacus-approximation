#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "graph.h"

namespace parser {

	const std::regex regex("(_?\\w+)( (\\+|-|\\*|\\/|<|<=|>|>=|==|\\!=|&&|\\|\\||<<a|<<c)( )+(\\w+)( )+(\\w+))? *\n*");


	graph::GraphPtr extractGraph(std::ifstream &cin, std::string type);
	graph::NodePtr parse(std::string str);
	graph::NodePtr nodeFromList(std::vector<std::string> list);

}

#endif /* PARSER_H */