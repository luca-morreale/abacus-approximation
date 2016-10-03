
#include <iostream>
#include <fstream>
#include <cstring>

#include "include/parser.h"
#include "include/graph.h"
#include "include/executer.h"

#define PARAMETERS 4
#define FLAG_FILE "-f"
#define FLAG_TYPE "-t"

using namespace std;


void extractFlags(int argc, char *argv[], string &benchmark, string &type)
{
    for(int i = 1; i < argc; i++) {
        if(strcmp(FLAG_TYPE, argv[i]) == 0) {
            type.assign(argv[i], strlen(argv[++i]));
        } else if(strcmp(FLAG_FILE, argv[i]) == 0) {
            benchmark.assign(argv[i], strlen(argv[++i]));
        }
    }
}


int main(int argc, char *argv[])
{
    if(argc < PARAMETERS + 1) {
        cout << "Usage: -f benchmark_filename -t data_type" << endl;
        return 0;
    }

    string benchmark;
    string type;
    extractFlags(argc, argv, benchmark, type);

    ifstream cin(benchmark);
    if(!cin.is_open()) {
        cout << "Couldn't open " << benchmark << ", path or file invalid" << std::endl;
        return 1;
    }

    graph::GraphPtr graph = parser::extractGraph(cin, type);

    #ifdef DEBUG
        graph->debug();
    #endif

    executer::ExecuterPtr exec = new executer::Executer();

    exec->runGraph(graph);


    cin.close();


    return 0;
}
