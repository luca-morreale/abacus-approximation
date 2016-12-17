#include "include/executer_compilation.h"

namespace executer {

    ExecuterByCompilation::ExecuterByCompilation() : Executer() 
    { /*    */ }

    ExecuterByCompilation::~ExecuterByCompilation()
    { /*    */ }

    void ExecuterByCompilation::runGraph(graph::GraphPtr graph, std::string filename)
    {
        writer::Writer::writeGraph(graph, filename);
        this->compile(filename);
        this->execute(filename);
    }

    void ExecuterByCompilation::compile(std::string filename)
    {
        this->executeSystemCommand("g++ -O1 -o " + filename + " " + filename + ".cpp");
    }

    void ExecuterByCompilation::execute(std::string filename)
    {
        this->executeSystemCommand("./" + filename);
    }

    void ExecuterByCompilation::executeSystemCommand(std::string command)
    {
        int i;
        i = std::system(command.c_str());
        if (i) {
            std::cout << "Error executing command " + command << std::endl;
        }
    }

    void ExecuterByCompilation::getOutput(std::string filename, std::vector<double> &output)
    {
        std::ifstream cin(filename + ".txt");
        this->collectOutputFrom(cin, output);
    }

    void ExecuterByCompilation::collectOutputFrom(std::ifstream &cin, std::vector<double> &output)
    {
        double tmp;
        while (cin >> tmp) {
            output.push_back(tmp);
        }
    }

    void ExecuterByCompilation::deleteDependencies(std::string filename)
    {
        std::remove((filename + ".cpp").c_str());
        std::remove((filename + ".cpp.txt").c_str());
        std::remove((filename + ".txt").c_str());
        std::remove((filename + ".o").c_str());
        std::remove((filename + ".cpp.o").c_str());
        std::remove(filename.c_str());
    }


} // namespace executer
