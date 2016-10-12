#ifndef SYNTAX_H
#define SYNTAX_H

#include <map>

#include "graph.h"
#include "utility.h"

namespace syntax {

    class Syntax {
    public:
        Syntax();
        ~Syntax() { }

        virtual bool startsNewBlock(graph::NodePtr start);

        /**
         * Checks if the current node close definetly the control block.
         * To clarify an 'endif' ends an 'if' and a 'else', but 'else' do not ends an 'if'.
         */
        virtual bool endsBlock(std::string start, graph::NodePtr end);
        virtual bool endsBlock(std::string start, std::string end);

        /**
         * Checks if the current node close the current control block.
         * To clarify an 'if' can be closed by an 'else'.
         */
        virtual bool closesBlock(std::string start, graph::NodePtr close);

        virtual bool allowsComplementaryBlock(std::string control);

        virtual bool isLoop(std::string str);
        virtual bool isLoopBlock(std::string start, std::string end);
        
        static bool isControlOp(std::string op);
        static bool isArray(std::string &var);
        static std::string getIdentifier(std::string name, graph::GraphPtr graph);
        static std::string extractArray(std::string name, graph::GraphPtr graph);
        static std::string getIndex(std::vector<std::string> raw_index, graph::GraphPtr graph);

    protected:
        typedef std::pair<std::string, std::string> strpair;
        typedef std::map<std::string, std::string> strmap;
        typedef std::multimap<std::string, std::string> multistrmap;

        multistrmap closing;
        strmap ending;
        strmap loops;

        bool checkContainement(strmap map, std::string key, std::string value);
        bool checkMultiContainement(multistrmap map, std::string key, std::string value);


    };

    typedef Syntax * SyntaxPtr;

    

    

    


} //namespace syntax

#endif /* SYNTAX_H */