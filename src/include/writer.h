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
        Writer() { /*    */ }
        ~Writer() { /*    */ }

        virtual void writeGraph(graph::GraphPtr graph, std::string filename);        

    protected:
        typedef struct {
            graph::NodePtr node;
            graph::GraphPtr graph;
            std::set<std::string> declaredVariables;
            int instructionIndex;
        } ParsingState;

        virtual void writeNode(ParsingState &state, std::ofstream &cout);
        virtual void writeBasicOperation(ParsingState &state, std::ofstream &cout);
        virtual void writeControlOperation(ParsingState &state, std::ofstream &cout);

        virtual void prepareFile(std::ofstream &cout, ParsingState &state);
        virtual std::string generateMasksForDataType(std::string defaultType);
        virtual void closeFile(std::ofstream &cout, ParsingState &state, std::string id);

        virtual void declareAllOutputVariables(std::ofstream &cout, ParsingState &state);
        virtual void declareEdgesVariables(std::ofstream &cout, ParsingState &state, graph::Edges edges, std::string defaultType);
        virtual void declareNodesVariables(std::ofstream &cout, ParsingState &state, graph::Nodes nodes, std::string defaultType);
        virtual std::string builDeclaration(std::string variable, std::string defaultType);

        virtual void addOuputPrints(std::ofstream &cout, std::string id);
        
    private:
        std::set<std::string> filename_used;

        bool isAlreadyDeclared(ParsingState &state, std::string variable);
        void addDeclaration(ParsingState &state, std::string variable);
        std::string getTypeFor(std::string variable, std::string defaultType);

        std::string generateUnconditionedExpression(std::string out);
        std::string generateConditionedExpression(graph::NodePtr node);

    };

}

#endif /* WRITER_H */