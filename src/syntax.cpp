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
        return endsBlock(start, close) || checkContainement(this->closing, start, close->out);
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

    bool Syntax::checkContainement(strmap map, std::string key, std::string value)
    {
        try {
            return is(map.at(key), value);
        } catch (std::out_of_range e) {
            return false;
        }
    }


    bool Syntax::isControlOp(std::string op)
    {
        if (op[0] == '_') {
            return true;
        }
        return false;
    }

    bool Syntax::isArray(std::string &var)
    {
        return var.find("_") != std::string::npos;
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


} // namespace syntax