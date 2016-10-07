#include "include/abacus.h"
#include <list>


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
            std::list<PairFitness> approximatedGraphs;
            
            #pragma omp parallel for default(shared) shared(approximatedGraphs) num_threads(8)
            for(int j = 0; j < this->M; j++) {
                approximation::Approximation approximation = selectApproximation();
                AppGraphPtr appGraph = approximate(original, approximation);
                double accuracy = evalAccuracy(appGraph, graph);
                if(accuracy < this->threshold) {
                    double fitness = evaluateFitness(approximation, accuracy);
                    #pragma omp critical
                    {
                        approximatedGraphs.push_back(make_pair(fitness, approximation, appGraph));
                    }
                }
            }

            if(approximatedGraphs.size() > 0) {
                approximatedGraphs.sort(cmpPairs);
                original = approximatedGraphs.front().second.second;
            }
        }

    }

    approximation::Approximation ABACUSExecuter::selectApproximation()
    {   
        srand(time(NULL));
        int index = rand() % approximation::approximations.size();
        return approximation::approximations[index];
    }

    AppGraphPtr ABACUSExecuter::approximate(AppGraphPtr graph, approximation::Approximation approximation)
    {
        AppGraphPtr copy = new AppGraph(*graph);
        graph::Nodes suitableNodes = approximation::selectSuitableNodes(copy, approximation);

        graph::NodePtr node = selectRandomNode(suitableNodes, approximation);
        copy->substitute(approximation(node), node);

        return copy;
    }

    graph::NodePtr ABACUSExecuter::selectRandomNode(graph::Nodes suitableNodes, approximation::Approximation approximation)
    {
        srand(time(NULL));
        int index = rand() % suitableNodes.size();
        return suitableNodes[index];
    }
    
    double ABACUSExecuter::evalAccuracy(AppGraphPtr graph, graph::GraphPtr original)
    {
        AppGraphPtr copy = new AppGraph(*graph);
        this->runGraph(copy);

        double accuracy = 0;
        auto outputList = original->getOutputList();
        for(auto it = outputList.begin(); it != outputList.end(); it++) {
            double app, real;
            original->get(*it, real);
            copy->get(*it, app);
            accuracy += real - app;
        }


        return accuracy;
    }
    
    double ABACUSExecuter::evaluateFitness(approximation::Approximation approximation, double accuracy)
    {
        double precisionErr = (approximation == approximation::approximateValue)? 0.1 : 0;
        return this->a1 * accuracy + this->a2 * precisionErr;
    }

    ABACUSExecuter::PairFitness ABACUSExecuter::make_pair(double fitness, approximation::Approximation approximation, AppGraphPtr graph)
    {
        return std::make_pair(fitness, std::make_pair(approximation, graph));
    }


    bool ABACUSExecuter::cmpPairs(PairFitness a, PairFitness b)
    {
        return a.first < b.first;
    }

    /**
     * scan the entire graph using next while collect the node with the right operations
     * then randomly choose one and approximate it substituting with different operations -> implement substitute in graph
     * 
     */


}