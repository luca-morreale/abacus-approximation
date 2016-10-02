#ifndef SYNTAX_H
#define SYNTAX_H

#include <map>

namespace syntax {

    typedef std::pair<std::string, std::string> strpair;
    typedef std::map<std::string, std::string> strmap;

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

        bool isLoop(std::string start, std::string end);
        
        bool isControlOp(std::string op);

    private:
        strmap closing;
        strmap ending;
        strmap loops;

        bool is(std::string a, std::string b);


    };

    typedef Syntax * SyntaxPtr;



    


} //namespace syntax

#endif /* SYNTAX_H */