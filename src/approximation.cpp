#include "include/approximation.h"
//#include "include/report.h"
#include <iostream>


namespace approximation {

    std::vector<Approximation> approximations(approx_values, approx_values + map_start_values_size);

    std::map<Approximation, std::string> approximationsOp(op_start_values, op_start_values + op_map_values_size);


    graph::Nodes selectSuitableNodes(Approximation approximation, graph::GraphPtr graph)
    {
        graph::Graph copy(*graph);
        if(approximation == approximateValue) {
            return selectAll(&copy);
        } else {
            return selectOperation(&copy, approximationsOp[approximation]);
        }
    }

    graph::Nodes selectOperation(graph::GraphPtr graph, std::string op)
    {
        graph::Nodes suitableNodes;
        graph::NodePtr current;
        while ((current=graph->next()) != NULL) {
            if (is(current->op, op) && isOperationalNode(current)) {
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
            if (isOperationalNode(current) && !is(current->op, "cast") && !is(current->op, "abs")) {
                suitableNodes.push_back(current);
            }
        }
        return suitableNodes;
    }

    bool isOperationalNode(graph::NodePtr node)
    {
        return !syntax::Syntax::isControlOp(node->out) && !isLoopIterator(node->out) && !is(node->op, "&");
    }

    bool isLoopIterator(std::string it)
    {
        return is("i", it) || is("it", it) || is("j", it) || is("k", it) || is("n", it);
    }

    bool canBeApplied(Approximation approximation, graph::GraphPtr graph)
    {
        return (selectSuitableNodes(approximation, graph)).size() > 0;
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

        invertedReplaceOperations(replacement, "~", "&", node->incoming[1]);

        mask = -1;

        return replacement;
    }

    graph::Nodes approximateMult(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));
        
        mask = calculateShift();
        replaceOperations(replacement, "<<", "+", std::to_string(mask));
        
        return replacement;
    }
    
    graph::Nodes approximateDiv(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));
        
        mask = calculateShift();
        replaceOperations(replacement, ">>", "-", std::to_string(mask));
        return replacement;
    }

    graph::Nodes approximateValue(graph::NodePtr node, int &mask)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        mask = calculateShift();
        replaceOperations(replacement, "&", node->op, std::to_string(mask));
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

    void invertedReplaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand)
    {
        replacement[0]->op = op1;
        replacement[0]->out = "tmp";
        replacement[0]->incoming[0] = operand;

        replacement[1]->op = op2;
        replacement[1]->incoming[1] = "tmp";
    }

    report::ShiftInformations getShiftList()
    {
        report::ShiftInformations shifts = report::Report::getShiftReport();
        if(shifts.size() < 16) {
            fillBaseShiftValue(shifts);
        }
        return shifts;
    }

    int calculateShift()
    {
        report::ShiftInformations shiftMap = getShiftList();
        std::vector<int> shifts = keys(shiftMap);
        std::vector<int> counts = values(shiftMap);

        std::vector<double> prob = normalizeProbabilities(counts);
        int shift = shifts[sampleIndex(prob)];

        if(randDouble() > 0.5) {
            shift = evolveShift(shift);
        }

        return shift;
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
