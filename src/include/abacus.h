#ifndef ABACUS_H
#define ABACUS_H

#include <algorithm>
#include <list>
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
    
    class ABACUS {
    public:
        ABACUS(int N, int M, double threshold);
        ~ABACUS();

        virtual void runAbacusOnGraph(graph::GraphPtr graph);

        int getN() { return N; }
        int getM() { return M; }
        double getThreshold() { return threshold; }

    protected:
        /**
         * Selects randomly an approximation.
         */
        virtual approximation::Approximation selectAppliableApproximation(AppGraphPtr graph);
        virtual approximation::Approximation selectRandomApproximation();
        /**
         * Replaces an operation with an approximated version of it.
         */
        virtual AppGraphPtr approximate(AppGraphPtr graph, report::DataPtr rep);
        /**
         * Runs the graph and evaluate its accuracy wrt the original one.
         */
        virtual double evalAccuracy(AppGraphPtr graph, AppGraphPtr original);
        /**
         * Evaluates the fitness given the approximation applied and the accuracy obtained.
         */
        virtual double evaluateFitness(report::DataPtr rep);
        virtual double evaluateBitReset(int mask);

        typedef std::pair<report::DataPtr, AppGraphPtr> PairAppr;
        typedef std::list<PairAppr> ListPair;

        static bool cmpPairs(PairAppr a, PairAppr b);

    private:
        int N;
        int M;
        double threshold;
        executer::ExecuterPtr exec;

        /**
         * Constants used in the fitness formula
         */
        const double a1 = 0.8;
        const double a2 = 0.12;
        //const double a3 = 0.08;

        ABACUS() { }

        std::vector<int> getReportCounts();
        double calculateOutputSum(AppGraphPtr graph);
        double get(std::string variable, graph::GraphPtr graph);
        PairAppr make_pair(report::DataPtr data, AppGraphPtr graph);
        AppGraphPtr popFront(ListPair &list);
        void deleteGraphs(ListPair trashedGraphs);


    };

    typedef ABACUS * ABACUSPtr;

} // namespace abacus


#endif /* ABACUS_H */