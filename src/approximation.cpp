#include "include/approximation.h"
#include "report.h"


namespace approximation {

    std::vector<Approximation> approximations(approx_values, approx_values + map_start_values_size);

    std::map<Approximation, std::string> approximationsOp(op_start_values, op_start_values + op_map_values_size);


    graph::Nodes selectSuitableNodes(graph::GraphPtr graph, Approximation approximation)
    {
        if(approximation == approximateValue) {
            return selectAll(graph);
        } else {
            return selectOperation(graph, approximationsOp[approximation]);
        }
    }

    graph::Nodes selectOperation(graph::GraphPtr graph, std::string op)
    {
        graph::Nodes suitableNodes;
        graph::NodePtr current;
        while ((current=graph->next()) != NULL) {
            if (is(current->op, op) && !syntax::Syntax::isControlOp(current->out)) {
                suitableNodes.push_back(current);
            }
        }
        return suitableNodes;
    }

    graph::Nodes selectAll(graph::GraphPtr graph)
    {
        graph::Nodes suitableNodes;
        graph::NodePtr current;
        while ((current=graph->next()) != NULL) {
            if (!syntax::Syntax::isControlOp(current->out)) {
                suitableNodes.push_back(current);
            }
        }
        return suitableNodes;
    }
    
    
    graph::Nodes approximateSum(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement[0]->op = "|";
        mask = -1;
        return replacement;
    }

    graph::Nodes approximateMinus(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        replaceOperations(replacement, "~", "&", replacement[0]->incoming[1]);
        mask = -1;

        return replacement;
    }

    graph::Nodes approximateMult(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        mask = calculateShift();
        replaceOperations(replacement, "<<", "+", mask+"");

        return replacement;
    }
    
    graph::Nodes approximateDiv(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        mask = calculateShift();
        replaceOperations(replacement, ">>", "-", mask+"");

        return replacement;
    }

    graph::Nodes approximateValue(graph::NodePtr node, int &mask)  // to complete
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        mask = calculateShift();
        replaceOperations(replacement, "&", node->op, mask+"");
        return replacement;
    }

    void replaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand)
    {
        replacement[0]->op = op1;
        replacement[0]->out = "tmp";
        replacement[0]->incoming[1] = operand;

        replacement[1]->op = op2;
        replacement[1]->incoming[0] = "tmp";
    }

    int calculateShift()    // to complete
    {
        std::vector<int> shiftsCount = getShiftList();
        std::vector<double> prob = normalizeProbabilities(shiftsCount);
        int shift = shiftsCount[sampleIndex(prob)];

        if(randDouble() > 0.5) {
            shift = evolveShift(shift);
        }

        return shift;
    }

    std::vector<int> getShiftList()
    {
        auto shifts = report::Report::getShiftReport();
        if(shifts.size() < 32) {
            fillBaseShiftValue(shifts);
        }
        return values(shifts);
    }

    void fillBaseShiftValue(report::ShiftInformations &shifts)
    {
        auto powtwo = getPowTwo();
        for(auto it = shifts.begin(); it != shifts.end(); it++) {
            shifts[it->first]++;
        }
        for(auto it = powtwo.begin(); it != powtwo.end(); it++) {
            shifts[*it]++;
        }
    }

    int evolveShift(int old_shift)
    {
        int evolution = old_shift;
        auto powtwo = getPowTwo();
        while(old_shift == evolution) {
            evolution += selectUniformlyRandom(powtwo);
        }
        return evolution;
    }


} // namespace approximation