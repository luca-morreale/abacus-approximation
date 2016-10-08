#ifndef ABACUS_H
#define ABACUS_H

#include <algorithm>
#include <omp.h>

#include "graph.h"
#include "executer.h"
#include "approximated_graph.h"
#include "approximation.h"

namespace abacus {

    typedef approximation::ApproximatedGraph AppGraph;
    typedef approximation::ApproximatedGraphPtr AppGraphPtr;
    
    class ABACUSExecuter : public executer::Executer {
    public:
        ABACUSExecuter(int N, int M, double threshold);
        ~ABACUSExecuter();

        virtual void runAbacusOnGraph(graph::GraphPtr graph);

        int getN() { return N; }
        int getM() { return M; }
        double getThreshold() { return threshold; }

    protected:
        typedef std::pair<approximation::Approximation, AppGraphPtr> PairAppr;
        typedef std::pair<double, PairAppr> PairFitness;

        static bool cmpPairs(PairFitness a, PairFitness b);

        virtual approximation::Approximation selectApproximation();
        virtual AppGraphPtr approximate(AppGraphPtr graph, approximation::Approximation approximation);
        virtual double evalAccuracy(AppGraphPtr graph, graph::GraphPtr original);
        virtual double evaluateFitness(approximation::Approximation approximation, double accuracy);

    private:
        int N;
        int M;
        double threshold;

        const double a1 = 0.8;
        const double a2 = 0.12;
        //const double a3 = 0.08;

        ABACUSExecuter() :Executer() { }

        graph::NodePtr selectRandomNode(graph::Nodes suitableNodes, approximation::Approximation approximation);
        PairFitness make_pair(double fitness, approximation::Approximation approximation, AppGraphPtr graph);


    };

    typedef ABACUSExecuter * ABACUSPtr;

} // namespace abacus


#endif /* ABACUS_H */