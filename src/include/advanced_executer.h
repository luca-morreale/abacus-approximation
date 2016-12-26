#ifndef ADVANCED_EXECUTER_H 
#define ADVANCED_EXECUTER_H

#include <chrono>

#include "graph.h"
#include "executer_compilation.h"
#include "fast_writer.h"


namespace executer {

    class AdvancedExecuter : public ExecuterByCompilation {
    public:
        AdvancedExecuter();
        ~AdvancedExecuter();

        virtual void runGraph(graph::GraphPtr graph, int N, int M, double accuracy, double a1, double a2, int repetitions);

    protected:
        virtual std::string writeExternalApproximationProgram(graph::GraphPtr graph);
        virtual void compile(std::string filename);
        virtual void execute(std::string filename , int N, int M, double accuracy, double a1, double a2, int repetitions);

    protected:
        virtual void executeSystemCommand(std::string command);


    };

} // namespace executer


#endif /* ADVANCED_EXECUTER_H */
