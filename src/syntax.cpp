#include "include/syntax.h"


namespace syntax {

    Syntax::Syntax()
    {
        this->closing.insert(strpair("_if", "_elseif"));
        this->closing.insert(strpair("_if", "_else"));
        this->closing.insert(strpair("_elseif", "_else"));

        this->ending.insert(strpair("_if", "_if"));
        this->ending.insert(strpair("_elseif", "_if"));
        this->ending.insert(strpair("_else", "_if"));
        this->ending.insert(strpair("_for", "_for"));
        
        this->loops.insert(strpair("_for", "_for"));
    }

    bool Syntax::startsNewBlock(graph::NodePtr start)
    {
        return isControlOp(start->out) && !isOpEmpty(start);
    }
        
    bool Syntax::endsBlock(std::string start, graph::NodePtr end)
    {
        return endsBlock(start, end->out) && isOpEmpty(end);
    }

    bool Syntax::endsBlock(std::string start, std::string end)
    {
        return checkContainement(this->ending, start, end);
    }

    bool Syntax::closesBlock(std::string start, graph::NodePtr close) 
    {
        return endsBlock(start, close) || checkMultiContainement(this->closing, start, close->out);
    }

    bool Syntax::isLoop(std::string str)
    {
        return this->loops.find(str) != this->loops.end();
    }

    bool Syntax::isLoopBlock(std::string start, std::string end)
    {
        return checkContainement(this->loops, start, end);
    }

    bool Syntax::allowsComplementaryBlock(std::string control)
    {
        return this->closing.find(control) != this->closing.end();
    }

    bool Syntax::checkMultiContainement(multistrmap map, std::string key, std::string value)
    {
        for(auto it = map.find(key); it != map.end(); it++) {
            if (is(it->second, value)) {
                return true;
            }
        }
        return false;
    }

    bool Syntax::checkContainement(strmap map, std::string key, std::string value)
    {
        try {
            return is(map.at(key), value);
        } catch (std::out_of_range e) {
            return false;
        }
    }

    bool Syntax::isArray(std::string &var)
    {
        return (var.find("_") != std::string::npos || var.find("[") != std::string::npos) && !isControlOp(var);
    }

    int Syntax::getArrayDimension(std::string variable)
    {
        auto group = split(variable, '_');
        if (group.size() < 2) {
            group = split(variable, '[');
        }
        
        return group.size() - 1;
    }

    bool Syntax::isControlOp(std::string op)
    {
        if (op[0] == '_') {
            return true;
        }
        return false;
    }

    std::string Syntax::convertControlOperation(std::string controlOperation)
    {
        if(is(controlOperation, "_if")) {
            return "if ";
        } else if(is(controlOperation, "_else")) {
            return " else {";
        } else if(is(controlOperation, "_elseif")) {
            return "} else if ";
        } else if(is(controlOperation, "_for")) {
            return "while ";
        }
    }

    std::string Syntax::getVariableName(std::string name)
    {
        std::string var = name;
        if (isArray(name)) {
            auto group = split(name, '_');
            if (group.size() < 2) {
                group = split(name, '[');
            }
            var = group[0];
        }

        return var;
    }

    std::string Syntax::getCompleteIdentifier(std::string name, bool indexCast)
    {
        std::string var = name;
        if (isArray(name)) {
            var = extractArray(name, indexCast);
        }
        return var;
    }

    std::string Syntax::getIdentifier(std::string name, graph::GraphPtr graph)
    {
        std::string var = name;
        if (isArray(name)) {
            var = extractArray(name, graph);
        }

        return var;
    }

    std::string Syntax::extractArray(std::string name, graph::GraphPtr graph)
    {
        std::vector<std::string> list = split(name, '_');
        return list[0] + getIndex(list, graph);
    }

    std::string Syntax::extractArray(std::string name, bool indexCast)
    {
        std::vector<std::string> list = split(name, '_');
        return list[0] + getIndex(list, indexCast);
    }

    std::string Syntax::getIndex(std::vector<std::string> raw_index, graph::GraphPtr graph)
    {
        std::string index = "";
        for(auto it = raw_index.begin() + 1; it != raw_index.end(); it++) {
            if(!isNumber(*it)) {
                int i;
                graph->get(*it, i);
                index += "[" +  std::to_string(i) + "]";
            } else {
                index += "[" + *it + "]";
            }
        }

        return index;
    }

    std::string Syntax::getIndex(std::vector<std::string> raw_index, bool indexCast)
    {
        std::string index = "";
        for(auto it = raw_index.begin() + 1; it != raw_index.end(); it++) {
            index += (indexCast) ? "[(int)" + *it + "]" : "[" + *it + "]";
        }
        return index;
    }


} // namespace syntax