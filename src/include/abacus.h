#ifndef ABACUS_H
#define ABACUS_H

#include <algorithm>

#include "graph.h"
#include "executer.h"
#include "approximated_graph.h"
#include "approximation.h"

namespace abacus {

    typedef approximation::ApproximatedGraph AppGraph;
    typedef approximation::ApproximatedGraphPtr AppGraphPtr;
    
    class ABACUSExecuter : executer::Executer {
    public:
        ABACUSExecuter(int N, int M, double threshold);
        ~ABACUSExecuter();

        void runAbacusOnGraph(graph::GraphPtr graph);

        int getN() { return N; }
        int getM() { return M; }
        double getThreshold() { return threshold; }

    protected:
        typedef std::pair<double, approximation::ApproximatedGraphPtr> PairGraph;
        static bool cmpPairs(PairGraph a, PairGraph b);

        virtual approximation::Approximation selectApproximation();
        virtual AppGraphPtr approximate(AppGraphPtr graph, approximation::Approximation approximation);
        virtual double evalAccuracy(AppGraphPtr graph, graph::GraphPtr original);
        virtual double evaluateFitness(AppGraphPtr graph, double accuracy);

    private:
        int N;
        int M;
        double threshold;

        ABACUSExecuter() :Executer() { }


    };

    typedef ABACUSExecuter * ABACUSPtr;
}

/*
for(int j = 0; j < this->M; j++) {
    approximation = selectApproximation();
    appGraph = approximate(graph, approximation);
    accuracy = evalAccuracy(appGraph);
    if(accuracy < this->threshold) {
        fitness = evaluateFitness(appGraph, accuracy);
        approximatedGraphs.push_back(std::make_pair(fitness, appGraph));
    }
}

*/


#endif /* ABACUS_H */