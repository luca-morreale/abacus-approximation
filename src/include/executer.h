#ifndef EXECUTER_H
#define EXECUTER_H

#include <string>

#include "graph.h"
#include "operations.h"
#include "syntax.h"
#include "utility.h"


namespace executer {

    class Executer {

    public:
        Executer();
        ~Executer();

        void runGraph(graph::GraphPtr graph);

        void runNode(graph::NodePtr node, graph::GraphPtr graph);
        void runBasicOperation(graph::NodePtr node, graph::GraphPtr graph);

        /**
         * Runs the control structure; after the execution the next instruction 
         * will be the one following the entire control block.
         */
        void runControlOperation(graph::NodePtr node, graph::GraphPtr graph);

        /**
         * Skips to the complementary structure if exists and then executes it.
         */
        void runComplementaryBlock(std::string opening, graph::GraphPtr graph);

        void runLoop(graph::NodePtr start, graph::GraphPtr graph);

        /**
         * Runs a control block, at the end do not skip to the end of the structure.
         */
        void runBlock(std::string opening, graph::GraphPtr graph);

        /**
         * Skips to the end of the control structure.
         */
        void skipToEndBlock(std::string control, graph::GraphPtr graph);


        void rollbackToStart(graph::NodePtr start, graph::NodePtr current, graph::GraphPtr graph);
        void rollbackToStart(graph::NodePtr end, graph::GraphPtr graph);

    private:
        syntax::SyntaxPtr checker;

        int evaluateCondition(graph::NodePtr condition, graph::GraphPtr graph);

    };

    typedef Executer * ExecuterPtr;


}  // namespace executer


#endif /* EXECUTER_H */