#ifndef ABACUS_H
#define ABACUS_H

#include <algorithm>
#include <omp.h>

#include "approximated_graph.h"
#include "approximation.h"
#include "executer.h"
#include "graph.h"
#include "report.h"
#include "utility.h"


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
        /**
         * Selects randomly an approximation.
         */
        virtual approximation::Approximation selectRandomApproximation();
        /**
         * Replaces an operation with an approximated version of it.
         */
        virtual AppGraphPtr approximate(AppGraphPtr graph, approximation::Approximation approximation);
        /**
         * Runs the graph and evaluate its accuracy wrt the original one.
         */
        virtual double evalAccuracy(AppGraphPtr graph, graph::GraphPtr original);
        /**
         * Evaluates the fitness given the approximation applied and the accuracy obtained.
         */
        virtual double evaluateFitness(approximation::Approximation approximation, double accuracy);

        typedef std::pair<approximation::Approximation, AppGraphPtr> PairAppr;
        typedef std::pair<double, PairAppr> PairFitness;

        static bool cmpPairs(PairFitness a, PairFitness b);

    private:
        int N;
        int M;
        double threshold;

        /**
         * Constants used in the fitness formula
         */
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