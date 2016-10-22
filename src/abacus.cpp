#include "include/abacus.h"
#include <cmath>
#ifdef ITERATIONS
    #include <iostream>
#endif


namespace abacus {

    ABACUS::ABACUS(int N, int M, double threshold)
    {
        this->N = N;
        this->M = M;
        this->threshold = threshold;
        this->exec = new executer::Executer();
    }

    ABACUS::~ABACUS()
    {
        delete(exec);
    }

    void ABACUS::runAbacusOnGraph(graph::GraphPtr graph)
    {
        AppGraphPtr original = new AppGraph(*graph);
        AppGraphPtr executedOriginal = new AppGraph(*original);
        
        double relAccuracy = 1 - this->threshold;
        this->exec->runGraph(executedOriginal);

        for(int i = 0; i < this->N; i++) {
            
            ListPair approximatedGraphs;
            
            #pragma omp parallel for default(shared) shared(approximatedGraphs) num_threads(8)
            for(int j = 0; j < this->M; j++) {
                try {
                    generateValidApproximation(approximatedGraphs, original, executedOriginal, relAccuracy);
                } catch (std::out_of_range oor) { } // approximation may cause errors reguarding index of arrays, which is not a valid approximation
            }

            if(approximatedGraphs.size() > 0) {
                substituteOriginal(&original, &executedOriginal, relAccuracy, approximatedGraphs);
            }

            #ifdef ITERATIONS
                std::cout <<"Iteration #"<< i << " completed." << std::endl;
            #endif
        }

        delete(executedOriginal);
        delete(original);
    }

    void ABACUS::generateValidApproximation(ListPair &approximatedGraphs, AppGraphPtr original, AppGraphPtr executedOriginal, double &relAccuracy)
    {
        report::DataPtr rep = new report::Data;
        rep->approx = selectAppliableApproximation(original);
        AppGraphPtr appGraph = approximate(original, rep);

        AppGraphPtr executedApproxGraph;
        rep->accuracy = evalAccuracy(appGraph, executedOriginal, &executedApproxGraph);  // estimated relative accuracy wrt previuos approximation
        
        if(rep->accuracy < relAccuracy) {
            rep->fitness = evaluateFitness(rep);
            #pragma omp critical
            approximatedGraphs.push_back(make_pair(rep, appGraph, executedApproxGraph));
        }
    }

    approximation::Approximation ABACUS::selectAppliableApproximation(AppGraphPtr graph)
    {
        approximation::Approximation approx;
        do {
            approx = selectRandomApproximation();
        } while(!approximation::canBeApplied(approx, graph));
        return approx;
    }

    approximation::Approximation ABACUS::selectRandomApproximation()
    {
        std::vector<int> vals = getReportCounts();
        std::vector<double> probs = normalizeProbabilities(vals);
        int index = sampleIndex(probs);
        
        return approximation::approximations[index];
    }

    AppGraphPtr ABACUS::approximate(AppGraphPtr graph, report::DataPtr rep)
    {
        graph::Nodes suitableNodes = approximation::selectSuitableNodes(rep->approx, graph);
        graph::NodePtr node = selectUniformlyRandom(suitableNodes);
        return graph->substitute(rep->approx(node, rep->mask), node);
    }
    
    double ABACUS::evalAccuracy(AppGraphPtr graph, AppGraphPtr original, AppGraphPtr *executed)
    {
        *executed = new AppGraph(*graph);
        this->exec->runGraph(*executed);

        double sum_real = calculateOutputSum(original);
        double sum_approx = calculateOutputSum(*executed);

        return std::abs((sum_real - sum_approx) / sum_real);
    }    
    
    double ABACUS::evaluateFitness(report::DataPtr rep)
    {
        double precisionErr = (rep->approx == approximation::approximateValue)? evaluateBitReset(rep->mask) : 0;
        return this->a1 * rep->accuracy + this->a2 * precisionErr;
    }

    double ABACUS::evaluateBitReset(int mask)
    {
        return ((double)mask) / 32.0;
    }

    double ABACUS::calculateOutputSum(AppGraphPtr graph)
    {
        double sum = 0;
        auto outputList = graph->getOutputList();
        for(auto it = outputList.begin(); it != outputList.end(); it++) {
            sum += get(*it, graph);
        }
        return sum;
    }

    std::vector<int> ABACUS::getReportCounts()
    {
        auto rep = report::Report::getReport();
        for(auto it = rep.begin(); it != rep.end(); it++) {
            rep[it->first]++;
        }

        return values(rep);
    }

    double ABACUS::get(std::string variable, graph::GraphPtr graph)
    {
        double value;
        graph->get(variable, value);
        return value;
    }

    void ABACUS::substituteOriginal(AppGraphPtr *original, AppGraphPtr *executed, double &relAccuracy, ListPair &approximatedGraphs)
    {
        approximatedGraphs.sort(cmpPairs);
        reduceRelativeAccuracy(relAccuracy, approximatedGraphs);
        auto pairGraphs = popFront(approximatedGraphs);
        replaceGraphReferences(original, executed, pairGraphs);
        deleteGraphs(approximatedGraphs);
    }

    void ABACUS::replaceGraphReferences(AppGraphPtr *original, AppGraphPtr *executed, GraphPair pairGraphs)
    {
        delete(*executed);
        *original = pairGraphs.first;
        *executed = pairGraphs.second;
    }

    void ABACUS::reduceRelativeAccuracy(double &relAccuracy, ListPair &approximatedGraphs)
    {
        relAccuracy -= approximatedGraphs.front().first->accuracy;
    }

    ABACUS::GraphPair ABACUS::popFront(ListPair &list)
    {
        auto firstEl = list.front();
        report::Report::appendApproximation(firstEl.first);
        list.pop_front();
        return firstEl.second;
    }

    void ABACUS::deleteGraphs(ListPair trashedGraphs)
    {
        for(auto it = trashedGraphs.begin(); it != trashedGraphs.end(); it++) {
            delete(it->second.first);
            delete(it->second.second);
            free(it->first);
        }
    }

    ABACUS::PairAppr ABACUS::make_pair(report::DataPtr data, AppGraphPtr graph, AppGraphPtr executedGraph)
    {
        return std::make_pair(data, std::make_pair(graph, executedGraph));
    }


    bool ABACUS::cmpPairs(PairAppr a, PairAppr b)
    {
        return a.first->fitness < b.first->fitness;
    }
} // namespace abacus
