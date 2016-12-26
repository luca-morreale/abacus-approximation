#include "include/compiled_abacus.h"


namespace abacus {

    CompiledABACUS::CompiledABACUS(int N, int M, double threshold) : ABACUS(N, M, threshold)
    {
        this->executer = new executer::ExecuterByCompilation();
    }

    CompiledABACUS::~CompiledABACUS()
    { /*    */ }

    void CompiledABACUS::runAbacusOnGraph(graph::GraphPtr graph)
    {
        approximation::ExecutedGraphPtr original = this->executeGraph(graph, "original");

        double relativeAccuracy = 1 - this->getThreshold();

        for (int i = 0; i < this->getN(); i++) {
            ListExecutedApproximation list;

            #pragma omp parallel for default(shared) shared(list) num_threads(8)
            for (int j = 0; j < this->getM(); j++) {
                generateValidApproximation(list, original, relativeAccuracy, generateUniqueID(i, j));
            }

            if(list.size() > 0) {
                replaceOriginal(&original, relativeAccuracy, list);
            }
        }

        delete(original);
    }

    void CompiledABACUS::generateValidApproximation(ListExecutedApproximation &list, approximation::ExecutedGraphPtr original, double relativeAccuracy, std::string id)
    {
        report::DataPtr graphReport = new report::Data;
        graphReport->approx = selectAppliableApproximation(original);
        approximation::ExecutedGraphPtr executedGraph = applyApproximation(original, graphReport, id);

        graphReport->accuracy = evalAccuracy(executedGraph, original);
        
        if(graphReport->accuracy < relativeAccuracy) {
            graphReport->fitness = evaluateFitness(graphReport);
            #pragma omp critical
            appendToList(list, graphReport, executedGraph);
        }
    }

    double CompiledABACUS::evalAccuracy(approximation::ExecutedGraphPtr graph, approximation::ExecutedGraphPtr original)
    {
        double sum_real = original->getOutputSum();
        double sum_approx = graph->getOutputSum();

        return std::fabs((sum_real - sum_approx) / sum_real);
    }  

    approximation::ExecutedGraphPtr CompiledABACUS::applyApproximation(approximation::ExecutedGraphPtr original, report::DataPtr graphReport, std::string id)
    {
        AppGraphPtr approximatedGraph = approximate(original, graphReport);
        approximation::ExecutedGraphPtr executedGraph = this->executeGraph(approximatedGraph, id);
        delete(approximatedGraph);

        return executedGraph;
    }

    void CompiledABACUS::replaceOriginal(approximation::ExecutedGraphPtr* original, double &relativeAccuracy, ListExecutedApproximation &list)
    {
        list.sort(compareResults);
        relativeAccuracy -= list.front().first->accuracy;
        auto pair = popFront(list);

        report::Report::appendApproximation(pair.first);
         replaceReferences(original, pair.second);

        deleteGraphs(list, &ABACUS::generalDeleter);
    }

    approximation::ExecutedGraphPtr CompiledABACUS::executeGraph(graph::GraphPtr graph, std::string id)
    {
        approximation::ExecutedGraphPtr executed = new approximation::ExecutedGraph(*graph);
        this->executer->runGraph(graph, id);
        std::vector<double> graphOutput;
        this->executer->getOutput(id, graphOutput);
        executed->setOutput(graphOutput);
        this->executer->deleteDependencies(id);

        return executed;
    }

    std::string CompiledABACUS::generateUniqueID(int i, int j)
    {
        return "execution/" + std::to_string(i) + "_" + std::to_string(j);
    }

    void CompiledABACUS::appendToList(ListExecutedApproximation &list, report::DataPtr graphReport, approximation::ExecutedGraphPtr executedGraph)
    {
        auto pair = std::make_pair(graphReport, executedGraph);
        list.push_back(pair);
    }

    void CompiledABACUS::replaceReferences(approximation::ExecutedGraphPtr* original, approximation::ExecutedGraphPtr executed)
    {
        delete(*original);
        *original = executed;
    }

    bool CompiledABACUS::compareResults(ReportGraphPair a, ReportGraphPair b)
    {
        return a.first->fitness < b.first->fitness;
    }
    
} // namespace abacus
