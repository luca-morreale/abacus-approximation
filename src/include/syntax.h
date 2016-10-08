#ifndef SYNTAX_H
#define SYNTAX_H

#include <map>

#include "utility.h"
#include "graph.h"

namespace syntax {

    class Syntax {
    public:
        Syntax();
        ~Syntax() { }

        /**
         * Checks if the current node close definetly the control block.
         * To clarify an 'endif' ends an 'if' and a 'else', but 'else' do not ends an 'if'.
         */
        bool endsBlock(std::string start, std::string end);
        /**
         * Checks if the current node close the current control block.
         * To clarify an 'if' can be closed by an 'else'.
         */
        bool closesBlock(std::string start, std::string close);

        bool allowsComplementaryBlock(std::string control);

        bool isLoopBlock(std::string start, std::string end);
        
        static bool isControlOp(std::string op);

    private:
        typedef std::pair<std::string, std::string> strpair;
        typedef std::map<std::string, std::string> strmap;

        strmap closing;
        strmap ending;
        strmap loops;

        bool checkContainement(strmap map, std::string key, std::string value);


    };

    typedef Syntax * SyntaxPtr;

    std::string getIdentifier(std::string name, graph::GraphPtr graph);
    std::string extractArray(std::string name, graph::GraphPtr graph);
    std::string getIndex(std::string raw_index, graph::GraphPtr graph);

    bool isArray(std::string &var);

    


} //namespace syntax

#endif /* SYNTAX_H */