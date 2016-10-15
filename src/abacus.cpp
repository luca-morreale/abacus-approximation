#include "include/abacus.h"
#include <cmath>


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

        for(int i = 0; i < this->N; i++) {
            AppGraph executedOriginal(*original);
            this->exec->runGraph(&executedOriginal);

            ListPair approximatedGraphs;
            
            #pragma omp parallel for default(shared) shared(approximatedGraphs) num_threads(8)
            for(int j = 0; j < this->M; j++) {
                report::DataPtr rep = new report::Data;

                rep->approx = selectAppliableApproximation(original);
                AppGraphPtr appGraph = approximate(original, rep);
                rep->accuracy = evalAccuracy(appGraph, &executedOriginal);

                if(rep->accuracy < 1 - this->threshold) {
                    rep->fitness = evaluateFitness(rep);
                    #pragma omp critical
                    approximatedGraphs.push_back(make_pair(rep, appGraph));
                }
            }

            if(approximatedGraphs.size() > 0) {
                approximatedGraphs.sort(cmpPairs);
                original = popFront(approximatedGraphs);
                deleteGraphs(approximatedGraphs);
            }
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
    
    double ABACUS::evalAccuracy(AppGraphPtr graph, AppGraphPtr original)
    {
        AppGraph copy(*graph);
        this->exec->runGraph(&copy);

        double sum_real = calculateOutputSum(original);
        double sum_approx = calculateOutputSum(&copy);

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

    AppGraphPtr ABACUS::popFront(ListPair &list)
    {
        auto first = list.front().second;
        report::Report::appendApproximation(list.front().first);
        list.pop_front();
        return first;
    }

    void ABACUS::deleteGraphs(ListPair trashedGraphs)
    {
        for(auto it = trashedGraphs.begin(); it != trashedGraphs.end(); it++) {
            delete it->second;
            free(it->first);
        }
    }

    ABACUS::PairAppr ABACUS::make_pair(report::DataPtr data, AppGraphPtr graph)
    {
        return std::make_pair(data, graph);
    }


    bool ABACUS::cmpPairs(PairAppr a, PairAppr b)
    {
        return a.first->fitness < b.first->fitness;
    }

    /**
     * scan the entire graph using next while collect the node with the right operations
     * then randomly choose one and approximate it substituting with different operations -> implement substitute in graph
     * 
     */


}