#include "include/abacus.h"


namespace abacus {

    ABACUSExecuter::ABACUSExecuter(int N, int M, double threshold) : Executer()
    {
        this->N = N;
        this->M = M;
        this->threshold = threshold;
    }

    ABACUSExecuter::~ABACUSExecuter() { }

    void ABACUSExecuter::runAbacusOnGraph(graph::GraphPtr graph)
    {
        AppGraphPtr original = new AppGraph(*graph);
        runGraph(graph);
        for(int i = 0; i < this->N; i++) {

            std::vector<PairGraph> approximatedGraphs;

            for(int j = 0; j < this->M; j++) {
                approximation::Approximation approximation = selectApproximation();
                AppGraphPtr appGraph = approximate(original, approximation);
                double accuracy = evalAccuracy(appGraph, graph);
                if(accuracy < this->threshold) {
                    double fitness = evaluateFitness(appGraph, accuracy);
                    approximatedGraphs.push_back(std::make_pair(fitness, appGraph));
                }
            }

            if(approximatedGraphs.size() > 0) {
                std::sort(approximatedGraphs.begin(), approximatedGraphs.end(), cmpPairs);
                original = approximatedGraphs[0].second;
            }
        }

    }

    approximation::Approximation ABACUSExecuter::selectApproximation()
    {   
        
        return 0;
    }
    AppGraphPtr ABACUSExecuter::approximate(AppGraphPtr graph, approximation::Approximation approximation) {return NULL;}
    double ABACUSExecuter::evalAccuracy(AppGraphPtr graph, graph::GraphPtr original) {return 0.0;}
    double ABACUSExecuter::evaluateFitness(AppGraphPtr graph, double accuracy) {return 0.0;}




    bool ABACUSExecuter::cmpPairs(PairGraph a, PairGraph b)
    {
        return a.first < b.first;
    }

    /**
     * scan the entire graph using next while collect the node with the right operations
     * then randomly choose one and approximate it substituting with different operations -> implement substitute in graph
     * 
     */


}