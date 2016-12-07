#ifndef EXECUTER_BY_COMPILATION_H
#define EXECUTER_BY_COMPILATION_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "executer.h"
#include "writer.h"

namespace executer {

    class ExecuterByCompilation : public Executer {

    public:
        ExecuterByCompilation();
        ~ExecuterByCompilation();

        virtual void runGraph(graph::GraphPtr graph, std::string filename);
        virtual void getOutput(std::string filename, std::vector<double> &output);
        virtual void deleteDependencies(std::string filename);

    protected:
        virtual void compile(std::string filename);
        virtual void execute(std::string filename);
        virtual void executeSystemCommand(std::string command);
        virtual void collectOutputFrom(std::ifstream &cin, std::vector<double> &output);

    };

    typedef ExecuterByCompilation * ExecuterByCompilationPtr;


}  // namespace executer


#endif /* EXECUTER_BY_COMPILATION_H */    
