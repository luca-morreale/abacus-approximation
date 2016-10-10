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
            ListPair approximatedGraphs;
            
            #pragma omp parallel for default(shared) shared(approximatedGraphs) private(original) num_threads(8)
            for(int j = 0; j < this->M; j++) {
                approximation::Approximation approximation = selectRandomApproximation();
                AppGraphPtr appGraph = approximate(original, approximation);
                double accuracy = evalAccuracy(appGraph, graph);

                if(accuracy < this->threshold) {
                    double fitness = evaluateFitness(approximation, accuracy);
                    #pragma omp critical
                    {
                        // Missing mask!!!!
                        approximatedGraphs.push_back(make_pair(report::newData(approximation, fitness, accuracy, -1), appGraph));
                    }
                }
            }

            if(approximatedGraphs.size() > 0) {
                approximatedGraphs.sort(cmpPairs);
                original = popFront(approximatedGraphs);
                deleteGraphs(approximatedGraphs);
            }
        }
    }

    approximation::Approximation ABACUSExecuter::selectRandomApproximation()
    {
        int index = rand() % approximation::approximations.size();
        return approximation::approximations[index];
    }

    AppGraphPtr ABACUSExecuter::approximate(AppGraphPtr graph, approximation::Approximation approximation)
    {
        graph::Nodes suitableNodes = approximation::selectSuitableNodes(graph, approximation);

        graph::NodePtr node = selectUniformlyRandom(suitableNodes);
        return graph->substitute(approximation(node), node);
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

        // difference on all elements of the array
        // sum up all differences??

        return accuracy;
    }
    
    double ABACUSExecuter::evaluateFitness(approximation::Approximation approximation, double accuracy)
    {
        double precisionErr = (approximation == approximation::approximateValue)? 0.1 : 0;
        return this->a1 * accuracy + this->a2 * precisionErr;
    }

    AppGraphPtr ABACUSExecuter::popFront(ListPair list)
    {
        auto first = list.front().second;
        list.pop_front();
        return first;
    }

    void ABACUSExecuter::deleteGraphs(ListPair trashedGraphs)
    {
        for(auto it = trashedGraphs.begin(); it != trashedGraphs.end(); it++) {
            delete it->second;
        }
    }

    ABACUSExecuter::PairAppr ABACUSExecuter::make_pair(report::DataPtr data, AppGraphPtr graph)
    {
        return std::make_pair(data, graph);
    }


    bool ABACUSExecuter::cmpPairs(PairAppr a, PairAppr b)
    {
        return a.first->fitness < b.first->fitness;
    }

    /**
     * scan the entire graph using next while collect the node with the right operations
     * then randomly choose one and approximate it substituting with different operations -> implement substitute in graph
     * 
     */


}