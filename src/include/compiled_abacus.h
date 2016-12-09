#ifndef COMPILED_ABACUS_H
#define COMPILED_ABACUS_H

#include <algorithm>
#include <list>
#include <omp.h>

#include "abacus.h"
#include "executer_compilation.h"
#include "executed_graph.h"


namespace abacus {


    class CompiledABACUS : public ABACUS {
    public:
        CompiledABACUS(int N, int M, double threshold);
        ~CompiledABACUS();

        virtual void runAbacusOnGraph(graph::GraphPtr graph);

    protected:

        typedef std::pair<report::DataPtr, approximation::ExecutedGraphPtr> ReportGraphPair;
        typedef std::list<ReportGraphPair> ListExecutedApproximation;

        virtual void generateValidApproximation(ListExecutedApproximation &list, approximation::ExecutedGraphPtr original, double relativeAccuracy, std::string id);

        virtual double evalAccuracy(approximation::ExecutedGraphPtr graph, approximation::ExecutedGraphPtr original);

        virtual void replaceReferences(approximation::ExecutedGraphPtr* original, approximation::ExecutedGraphPtr executed);

        static bool compareResults(ReportGraphPair a, ReportGraphPair b);

    private:
        executer::ExecuterByCompilationPtr executer;
        
        typedef approximation::ExecutedGraphPtr ExecutedGraphPtr;

        void replaceOriginal(ExecutedGraphPtr* original, double &relativeAccuracy, ListExecutedApproximation &list);

        void appendToList(ListExecutedApproximation &list, report::DataPtr graphReport, approximation::ExecutedGraphPtr executedGraph);

        ExecutedGraphPtr applyApproximation(ExecutedGraphPtr original, report::DataPtr graphReport, std::string id);
        ExecutedGraphPtr executeGraph(graph::GraphPtr graph, std::string id);
        std::string generateUniqueID(int i, int j);

    };

    typedef CompiledABACUS * CompiledABACUSPtr;

} // namespace abacus


#endif /* COMPILED_ABACUS_H */
