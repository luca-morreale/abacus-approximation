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
        this->ending.insert(strpair("_do", "_while"));

        this->loops.insert(strpair("_do", "_while"));
        this->loops.insert(strpair("_for", "_for"));
    }
        
    bool Syntax::endsBlock(std::string start, std::string end)
    {
        return is(this->ending[start], end);
    }

    bool Syntax::closesBlock(std::string start, std::string close)
    {
        return endsBlock(start, close) || is(this->closing[start], close);
    }

    bool Syntax::isLoop(std::string start, std::string end)
    {
        return is(this->loops[start], end);
    }

    bool Syntax::allowsComplementaryBlock(std::string control)
    {
        return this->closing.find(control) != this->closing.end();
    }

    bool Syntax::isControlOp(std::string op)
    {
        if (op[0] == '_') {
            return true;
        }
        return false;
    }

    bool Syntax::is(std::string a, std::string b)
    {
        return a.compare(b) == 0;
    }


} // namespace syntax