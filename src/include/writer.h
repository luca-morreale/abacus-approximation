#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <set>

#include "approximation.h"
#include "graph.h"
#include "operation_generator.h"
#include "syntax.h"
#include "utility.h"

namespace writer {


    class Writer {
    public:
        static void writeGraph(graph::GraphPtr graph, std::string filename);

    private:
        static std::set<std::string> filename_used;

        typedef struct {
            graph::NodePtr node;
            graph::GraphPtr graph;
            std::set<std::string> declaredVariables;
        } ParsingState;

    protected:
        static void writeNode(ParsingState &state, std::ofstream &cout);
        static void writeBasicOperation(ParsingState &state, std::ofstream &cout);
        static void writeControlOperation(ParsingState &state, std::ofstream &cout);

        static void prepareFile(std::ofstream &cout, ParsingState &state, graph::GraphPtr graph);
        static void closeFile(std::ofstream &cout, graph::GraphPtr graph, std::string id);

        static void declareAllOutputVariables(std::ofstream &cout, ParsingState &state, graph::GraphPtr graph);
        static void declareEdgesVariables(std::ofstream &cout, ParsingState &state, graph::Edges edges, std::string defaultType);
        static void declareNodesVariables(std::ofstream &cout, ParsingState &state, graph::Nodes nodes, std::string defaultType);
        static std::string builDeclaration(std::string variable, std::string defaultType);

        static void addOuputPrints(std::ofstream &cout, std::string id);

        
    private:
        static bool isAlreadyDeclared(ParsingState &state, std::string variable);
        static void addDeclaration(ParsingState &state, std::string variable);
        static std::string getTypeFor(std::string variable, std::string defaultType);

        static std::string generateUnconditionedExpression(std::string out);
        static std::string generateConditionedExpression(graph::NodePtr node);

    };

}

#endif /* WRITER_H */