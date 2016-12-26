
#include "include/advanced_executer.h"
#include <iostream>


namespace executer {

    AdvancedExecuter::AdvancedExecuter() : ExecuterByCompilation() { /*    */ }

    AdvancedExecuter::~AdvancedExecuter() { /*    */ }


    void AdvancedExecuter::runGraph(graph::GraphPtr graph, int N, int M, double accuracy, double a1, double a2, int repetitions)
    {
        std::string filename = this->writeExternalApproximationProgram(graph);
        this->compile(filename);
        this->execute(filename, N, M, accuracy, a1, a2, repetitions);
        //this->deleteDependencies(filename);
    }

    std::string AdvancedExecuter::writeExternalApproximationProgram(graph::GraphPtr graph)
    {
        std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        std::string filename = std::to_string(millis.count());
        
        writer::FastWriter writer;
        writer.writeGraph(graph, filename);
        return filename;
    }

    void AdvancedExecuter::compile(std::string filename)
    {
        this->executeSystemCommand("g++ -o " + filename + " " + filename + ".cpp -fopenmp");
    }

    void AdvancedExecuter::execute(std::string filename , int N, int M, double accuracy, double a1, double a2, int repetitions)
    {
        std::cout << "./" + filename << " -N " << N << " -M " << M << " -a " << accuracy << " -r " << repetitions << " -a1 " << a1 << " -a2 " << a2 << std::endl;

        this->executeSystemCommand("./" + filename + " -N " + std::to_string(N) + " -M " + std::to_string(M) + 
                                    " -a " + std::to_string(accuracy) + " -r " + std::to_string(repetitions) + 
                                    " -a1 " + std::to_string(a1) + " -a2 " + std::to_string(a2));
    }

    void AdvancedExecuter::executeSystemCommand(std::string command)
    {
        int i;
        i = std::system(command.c_str());
        if (i) {
            std::cout << "Error executing command " + command << std::endl;
        }
    }


} // namespace executer
