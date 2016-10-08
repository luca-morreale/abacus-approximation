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
        
    bool Syntax::endsBlock(std::string start, std::string end)
    {
        return checkContainement(this->ending, start, end);
    }

    bool Syntax::closesBlock(std::string start, std::string close)
    {
        return endsBlock(start, close) || checkContainement(this->closing, start, close);
    }

    bool Syntax::isLoop(std::string start, std::string end)
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

    bool isArray(std::string &var)
    {
        return var.find("_") != std::string::npos;
    }

    std::string getIdentifier(std::string name, graph::GraphPtr graph)
    {
        std::string var = name;
        if (isArray(name)) {
            var = extractArray(name, graph);
        }

        return var;
    }

    std::string extractArray(std::string name, graph::GraphPtr graph)
    {
        int pos = name.find("_");
        std::string vec = name.substr(0, pos);
        std::string index = getIndex(name.substr(pos, name.size()), graph);
        return vec + "[" + index + "]";
    }

    std::string getIndex(std::string raw_index, graph::GraphPtr graph)
    {
        std::string index;
        if(!isNumber(raw_index)) {
            int i;
            graph->get(raw_index, i);
            index = "" + i;
        } else {
            index = raw_index;
        }
        return index;
    }


} // namespace syntax