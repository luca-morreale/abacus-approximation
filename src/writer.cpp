#include "include/writer.h"


namespace writer {

    void Writer::writeGraph(graph::GraphPtr graph, std::string filename)
    {
        ParsingState state;
        state.graph = graph;
        state.instructionIndex = 0;
        graph::NodePtr *current = &(state.node);
        
        std::ofstream cout(filename + ".cpp");

        prepareFile(cout, state);

        while ((*current = graph->next()) != NULL) {
            writeNode(state, cout);
        }

        closeFile(cout, state, filename);
    }

    void Writer::prepareFile(std::ofstream &cout, ParsingState &state)
    {
        cout << "#include <fstream>" << std::endl;
        cout << generator::generateIncludes() << std::endl;
        cout << generateMasksForDataType(state.graph->getType()) << std::endl;

        cout << generator::generateFunctions(state.graph->getType()) << std::endl;
        cout << "int main(void) {" << std::endl << std::endl;

        declareAllOutputVariables(cout, state);
    }

    std::string Writer::generateMasksForDataType(std::string defaultType)
    {
        std::string masks;
        if (is(defaultType, "double")) {
            masks = "long int mask = 9007199254740991;\n";
            masks += "typedef union { double f; long int i;} my_type;\n";
        } else if (is(defaultType, "float")) {
            masks = "long int mask = 16777215;\n";
            masks += "typedef union { float f; int i;} my_type;\n";
        } else {
            masks = "typedef union { int f; int i;} my_type;\n";
            masks += "long int mask = 8589934591;\n";
        }
        return masks;
    }

    void Writer::declareAllOutputVariables(std::ofstream &cout, ParsingState &state)
    {
        declareEdgesVariables(cout, state, state.graph->getEdges(), state.graph->getType());
        declareNodesVariables(cout, state, state.graph->getNodes(), state.graph->getType());
    }

    void Writer::declareEdgesVariables(std::ofstream &cout, ParsingState &state, graph::Edges edges, std::string defaultType)
    {
        for (auto it = edges.begin(); it != edges.end(); it++) {
            std::string variable = it->first;
            std::string value = it->second;
            if (!isAlreadyDeclared(state, variable)) {
                cout << builDeclaration(variable, defaultType) << ";" << std::endl;
                addDeclaration(state, variable);
            }
            cout << variable << " = " << value << ";" << std::endl;
        }
    }

    void Writer::declareNodesVariables(std::ofstream &cout, ParsingState &state, graph::Nodes nodes, std::string defaultType)
    {
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
            std::string variable = (*it)->out;
            if (!isAlreadyDeclared(state, variable) && !syntax::Syntax::isControlOp(variable)) {
                cout << builDeclaration(variable, defaultType) << ";" << std::endl;
                addDeclaration(state, variable);
            }
        }
    }

    bool Writer::isAlreadyDeclared(ParsingState &state, std::string variable)
    {
        std::string name = syntax::Syntax::getVariableName(variable);
        return isIn(state.declaredVariables, name);
    }

    std::string Writer::builDeclaration(std::string variable, std::string defaultType)
    {
        std::string name = syntax::Syntax::getVariableName(variable);
        std::string type = getTypeFor(variable, defaultType);

        if (syntax::Syntax::isArray(variable)) {
            std::string dimension;
            for (int i=0; i < syntax::Syntax::getArrayDimension(variable); i++) {
                dimension += "[(int)" + name + "Length]";
            }
            name += dimension;
        }
        return type + " " + name;
    }

    std::string Writer::getTypeFor(std::string variable, std::string defaultType) 
    {
        if (approximation::isLoopIterator(variable)) {
            return "int";
        }
        return defaultType;
    }

    void Writer::addDeclaration(ParsingState &state, std::string variable)
    {
        std::string name = syntax::Syntax::getVariableName(variable);
        state.declaredVariables.insert(name);
    }

    void Writer::closeFile(std::ofstream &cout, ParsingState &state, std::string id)
    {
        addOuputPrints(cout, id);

        cout << "return 0;" << std::endl;
        cout << "}" << std::endl;
        cout.close();
    }

    void Writer::addOuputPrints(std::ofstream &cout, std::string id)
    {
        cout << "std::ofstream output_file(\"" << id <<".txt\");" << std::endl;
        cout << "for (i=0; i<outputLength; i++){" << std::endl;
        cout << "output_file << output[i] << std::endl;" << std::endl;
        cout << "}" << std::endl;
        cout << "output_file.close();" << std::endl;
    }

    void Writer::writeNode(ParsingState &state, std::ofstream &cout)
    {
        if (syntax::Syntax::isControlOp(state.node->out)) {
            writeControlOperation(state, cout);
        } else {
            writeBasicOperation(state, cout);
        }
    }

    void Writer::writeBasicOperation(ParsingState &state, std::ofstream &cout)
    {   
        std::string statement = generator::generateStatement(state.node);
        cout << statement << std::endl;
    }

    void Writer::writeControlOperation(ParsingState &state, std::ofstream &cout)
    {
        std::string line;
        if(isOpEmpty(state.node)) {
            line = generateUnconditionedExpression(state.node->out);
        } else {
            // generate the control operation, in case of else close automatically curly braches!
            line = generateConditionedExpression(state.node);
        }
        cout << line << std::endl;
    }

    std::string Writer::generateUnconditionedExpression(std::string out)
    {
        std::string line = "}";
        if (is(out, "_else")) {
            line += syntax::Syntax::convertControlOperation(out);
        }
        return line;
    }

    std::string Writer::generateConditionedExpression(graph::NodePtr node)
    {
            std::string controlOperation = syntax::Syntax::convertControlOperation(node->out);
            std::string expression = generator::generateExpression(node);
            return controlOperation + "(" + expression + ") {"; 
    }


} // namespace executer