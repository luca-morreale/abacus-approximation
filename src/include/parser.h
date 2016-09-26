#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "node.h"

namespace parser {

	const std::regex regex("(_?\\w+)( (\\+|-|\\*|\\/|<|<=|>|>=|==|\\!=|&&|\\|\\||<<a|<<c)( )+(\\w+)( )+(\\w+))? *\n*");


	graph::Node *parse(std::string str);
	graph::Node *nodeFromList(std::vector<std::string> list);

}

#endif /* PARSER_H */