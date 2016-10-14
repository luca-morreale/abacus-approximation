
#include <iostream>
#include <fstream>
#include <cstring>
#include <omp.h>

#include "include/parser.h"
#include "include/graph.h"
#include "include/executer.h"
#include "include/abacus.h"

#define PARAMETERS 12
#define FLAG_FILE "-f"
#define FLAG_INPUT "-i"
#define FLAG_TYPE "-t"
#define FLAG_ACCURACY "-a"
#define FLAG_N "-N"
#define FLAG_M "-M"

using namespace std;


void assign(string &str, char source[])
{
    str.assign(source, strlen(source));
}

void extractFlags(int argc, char *argv[], string &benchmark, string &type, string &input, double &acc, int &N, int &M)
{
    for(int i = 1; i < argc; i++) {
        if(strcmp(FLAG_TYPE, argv[i]) == 0) {
            assign(type, argv[++i]);
        } else if(strcmp(FLAG_FILE, argv[i]) == 0) {
            assign(benchmark, argv[++i]);
        } else if(strcmp(FLAG_INPUT, argv[i]) == 0) {
            assign(input, argv[++i]);
        } else if(strcmp(FLAG_ACCURACY, argv[i]) == 0) {
            acc = strtod(argv[++i], NULL);
        } else if(strcmp(FLAG_N, argv[i]) == 0) {
            N = atoi(argv[++i]);
        } else if(strcmp(FLAG_M, argv[i]) == 0) {
            M = atoi(argv[++i]);
        }
    }
}


graph::GraphPtr loadFromFiles(string benchFile, string type, string inputFile)
{
    ifstream bench(benchFile);
    if(!bench.is_open()) {
        cout << "Could not open " << benchFile << ", path or file invalid" << std::endl;
        exit(1);
    }

    graph::GraphPtr graph = parser::extractGraph(bench, type);
    bench.close();

    ifstream input(inputFile);
    if(!input.is_open()) {
        cout << "Couldn't open " << inputFile << ", path or file invalid" << std::endl;
        exit(1);
    }
    graph::Edges edges = parser::extractEdges(input);
    graph->loadInputData(edges);
    input.close();



    return graph;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    if(argc < PARAMETERS + 1) {
        cout << "Usage: -f benchmark_filename -t data_type -i input_data_file" << endl;
        return 0;
    }

    string benchmark, input, type;
    double acc;
    int N, M;
    extractFlags(argc, argv, benchmark, type, input, acc, N, M);

    graph::GraphPtr graph = loadFromFiles(benchmark, type, input);

    #ifdef DEBUG
        graph->debug();
    #endif

    executer::Executer exec;

    exec.runGraph(graph);

    delete(graph);

    return 0;
}
