#include "include/fast_writer.h"


namespace writer {

    FastWriter::FastWriter() : Writer()
    {
        mapping[0] = "+";
        inverseMapping["+"] = 0;
        mapping[1] = "-";
        inverseMapping["-"] = 1;
        mapping[2] = "*";
        inverseMapping["*"] = 2;
        mapping[3] = "/";
        inverseMapping["/"] = 3;
        mapping[4] = "values";
        inverseMapping["values"] = 4;
    }

    void FastWriter::prepareFile(std::ofstream &cout, ParsingState &state)
    {
        cout << includes() << std::endl;
        cout << defines() << std::endl;
        cout << "using namespace std;" << std::endl;
        cout << staticDefinition(state.graph->getType()) << std::endl;
        cout << functionProtopypes(state.graph->getType()) << std::endl;

        cout << generator::generateFunctions(state.graph->getType()) << std::endl;
        cout << utilityFunctions() << std::endl;
        cout << approximationFunctions() << std::endl;
        cout << accuracyEvaluationFunctions(state.graph->getType()) << std::endl;
        cout << fitnessEvaluationFunctions() << std::endl;
        cout << substitutionOfOriginalFunctions(state.graph->getType()) << std::endl;
        

        cout << openApproximatedFunction(state.graph->getType()) << std::endl;

        state.declaredVariables.insert("output");   // avoid declare output inside the function, must be a parameter.
        declareAllOutputVariables(cout, state);
    }

    void FastWriter::closeFile(std::ofstream &cout, ParsingState &state, std::string id)
    {
        std::string defaultType = state.graph->getType();
        double outputLength;
        state.graph->get("outputLength", outputLength);

        cout << "}" << std::endl << std::endl;      // close approximated function


        cout << "int main(int argc, char *argv[]) {" << std::endl;

        cout << mainVariablesInitialization() << std::endl;

        // repetition loop
        cout << "for (int r=0; r < R; r++) {" << std::endl;

        cout << declareApproximationVariables(defaultType, {outputLength, (double)state.instructionIndex}) << std::endl;
        cout << initializationApproximationVariables() << std::endl;


        cout << callApproximatedFunction(std::string("output"), std::string("approximations"), std::string("masks")) << std::endl;

        cout << "for (int i=0; i < N; i++) {" << std::endl;

        cout << getDeclarationOuterLoop(defaultType, state.instructionIndex) << std::endl;

        cout << "#pragma omp parallel for default(shared) shared(approximationList) num_threads(8)" << std::endl;
        cout << "for (int j=0; j < M; j++) {" << std::endl;

        cout << getDeclarationInnerLoop(defaultType, state.instructionIndex) << std::endl;

        cout << approximationInstruction(state.instructionIndex) << std::endl;
        cout << callApproximatedFunction(std::string("test_output"), std::string("new_approximations"), std::string("new_masks")) << std::endl;
        
        cout << accuracyEstimationInstructions() << std::endl;
        cout << getAdditionToListInstructions(defaultType, state.instructionIndex) << std::endl;

        cout << "}" << std::endl;   // close j loop
        
        cout << substutionInstructions() << std::endl;
        
        cout << "cout << \"End Iteration \" << i << std::endl;" << std::endl;
        cout << "}" << std::endl;   // close i loop
        
        cout << getReportPrintingInstructions();

        cout << "cout << \"End Repetition \" << r << std::endl;" << std::endl;
        cout << "}" << std::endl;   // close r loop
        
        cout << "return 0;" << std::endl;
        cout << "}" << std::endl;
        cout.close();

        resetOperationsList();
    }

    void FastWriter::resetOperationsList()
    {
        for (int i = 0; i < APPROXIMATIONS; i++) {
            approximableOperations[i].clear();
        }
    }


    void FastWriter::writeBasicOperation(ParsingState &state, std::ofstream &cout)
    {
        if (approximation::isLoopIterator(state.node->out)) {
            Writer::writeBasicOperation(state, cout);
            return;
        }

        updateInstructionMapping(state.node->op, state.instructionIndex);
        
        std::string statement = generator::generateStatement(state.node, state.instructionIndex);
        std::string approximatedStatement = generator::generateApproximatedStatement(state.node, state.instructionIndex);

        cout << "if (!approximations[" << state.instructionIndex << "]) {" << std::endl;
        cout << "   " << statement << std::endl;
        cout << "} else {" << std::endl;
        cout << "   " << approximatedStatement << std::endl;
        cout << "}" << std::endl;

        updateInstructionIndex(state.node->op, state.instructionIndex);
    }

    void FastWriter::updateInstructionMapping(std::string op, int instructionIndex)
    {
        int index = inverseMapping["values"];
        approximableOperations[index].push_back(instructionIndex);

        if (isIn(inverseMapping, op)) {
            index = inverseMapping[op];
            approximableOperations[index].push_back(instructionIndex);
        }
    }

    void FastWriter::updateInstructionIndex(std::string op, int &instructionIndex)
    {
        instructionIndex++;
        if(is(op, "*") || is(op, "/")) {
            instructionIndex += 2;
        }
    }


    std::string FastWriter::mainVariablesInitialization()
    {
        return "srand(time(NULL));\n"        
                + getArgsVariablesExtraction()
                + "ofstream out(\"execution/report.txt\", fstream::app);\n";
    }

    std::string FastWriter::getArgsVariablesExtraction()
    {
        return "double acc;\n"
                "int N, M, R;\n"
                "extractFlags(argc, argv, acc, N, M, R, a1, a2);\n";
    }

    std::string FastWriter::declareApproximationVariables(std::string defaultType, std::initializer_list<double> vals)
    {
        return builDeclaration("outputLength", defaultType) + ";\n"
                "outputLength = " + std::to_string(at(vals, 0)) + ";\n"
                + builDeclaration("output_0", defaultType) + ";\n"     // added _0 to make it an array
                + builDeclaration("relativeAccuracy", defaultType) + ";\n"
                "relativeAccuracy = 1 - acc;\n"
                + builDeclaration("approximationsLength", defaultType) + ";\n"
                "approximationsLength = " + std::to_string(at(vals, 1)) + ";\n"
                + builDeclaration("approximations_0", "int") + ";\n"  // added _0 to make it an array
                + builDeclaration("masksLength", defaultType) + ";\n"
                "masksLength = " + std::to_string(at(vals, 1)) + ";\n"
                + builDeclaration("masks_0", "int") + ";\n"  // added _0 to make it an array
                "double relAccuracy = acc;\n";
    }

    std::string FastWriter::initializationApproximationVariables()
    {
        return "for (int i = 0; i<70; i++) {\n"
                "   approximations[i] = 0;\n"
                "   masks[i] = mask_int;\n"
                "}\n";
    }

    std::string FastWriter::getDeclarationOuterLoop(std::string defaultType, int instructionCount)
    {
        return "std::list<ApproximationElement> approximationList;\n";
    }

    std::string FastWriter::getDeclarationInnerLoop(std::string defaultType, int instructionCount)
    {
        return defaultType + " test_output[(int)outputLength];\n"
                "int new_approximations[" + std::to_string(instructionCount) + "];\n"
                "int new_masks[" + std::to_string(instructionCount) + "];\n";
    }

    std::string FastWriter::approximationInstruction(int instructionCount)
    {
        return "copy(approximations, approximations+" + std::to_string(instructionCount) + ", new_approximations);\n"
                "copy(masks, masks+" + std::to_string(instructionCount) + ", new_masks);\n"
                "pair<int, string> app = approximate(new_approximations, new_masks);\n";
    }

    std::string FastWriter::accuracyEstimationInstructions()
    {
        return "double app_acc = compareOutputs(output, test_output, outputLength);\n";
    }

    std::string FastWriter::getAdditionToListInstructions(std::string defaultType, int instructionCount)
    {
        return "if (app_acc < relAccuracy) {\n"
                "double fitness = computeFitness(app_acc, app, new_masks);\n"
                "#pragma omp critical\n"
                "approximationList.push_back(ApproximationElement(vector<" + defaultType + ">"
                        "(test_output, test_output+(int)outputLength), vector<int>(new_approximations, new_approximations+"
                            + std::to_string(instructionCount) + "), vector<int>(new_masks, new_masks+"
                            + std::to_string(instructionCount) + "), app_acc, fitness, app));\n"
                "}\n";
    }

    std::string FastWriter::substutionInstructions()
    {
        return "if (approximationList.size() > 0) {\n"
                "   replaceOriginal(relativeAccuracy, output, approximations, masks, approximationList);\n"
                "}\n";
    }

    std::string FastWriter::getReportPrintingInstructions()
    {
        return "printReport(cout, relAccuracy);\n"
                "printInCSVFormat(out, relAccuracy);\n"
                "reset();\n";
    }


    std::string FastWriter::includes()
    {
        return "#include <cstring>\n"
                "#include <cstdlib>\n"
                "#include <omp.h>\n"
                "#include <fstream>\n"
                "#include <iostream>\n"
                "#include <list>\n"
                "#include <map>\n"
                "#include <set>\n"
                "#include <vector>\n"
                + generator::generateIncludes();
    }

    std::string FastWriter::defines()
    {
        return "#define PARAMETERS 6\n"
                "#define FLAG_ACCURACY \"-a\"\n"
                "#define FLAG_N \"-N\"\n"
                "#define FLAG_M \"-M\"\n"
                "#define FLAG_A1 \"-a1\"\n"
                "#define FLAG_A2 \"-a2\"\n"
                "#define FLAG_REPETITION \"-r\"\n";
    }

    // missing a1 and a2
    std::string FastWriter::staticDefinition(std::string defaultType)
    {
        return "struct ApproximationElement{\n"
                "   vector<"+ defaultType +"> output;\n"
                "   vector<int> approximations;\n"
                "   vector<int> masks;\n"
                "   double accuracy;\n"
                "   double fitness;\n"
                "   pair<int, string> app;\n"
                "   ApproximationElement(vector<"+ defaultType +"> output, vector<int> approximations, vector<int> masks, double accuracy, double fitness, pair<int, string> app) {\n"
                "       this->output = output;\n"
                "       this->approximations = approximations;\n"
                "       this->masks = masks;\n"
                "       this->accuracy = accuracy;\n"
                "       this->fitness = fitness;\n"
                "       this->app = app;\n"
                "   }\n"
                "} ;\n"
                "set<int> availabilites[5];\n"
                "set<int> dones[5];\n"
                "map<int, int> shiftsInfo;\n"
                "map<int, string> correspondance;\n"    // index to operation
                "map<string, int> inverse_correspondance;\n"    // operation to index
                "double a1, a2;\n"
                + generateMasksForDataType(defaultType);
    }

    std::string FastWriter::functionProtopypes(std::string defaultType)
    {
        return "void assign(string &str, char source[]);\n"
                "bool cmpPairs(ApproximationElement a, ApproximationElement b);\n"
                "void replaceOriginal(double &relativeAccuracy, "+ defaultType +" *originalOut, int *approximations, int *masks, list<ApproximationElement> approximationList);\n"
                "double compareOutputs("+ defaultType +" *originalOut, "+ defaultType +" *approximatedOut, int length);\n"
                "void extractFlags(int argc, char *argv[], double &acc, int &N, int &M, int &r);\n"
                "bool is(std::string a, std::string b);\n"
                "double randDouble();\n"
                "vector<double> normalizeProbabilities(vector<int> &prob);\n"
                "int sampleIndex(vector<double> &probabilities);\n"
                "int selectUniformlyRandom(std::vector<int> array);\n"
                "vector<int> getReportCounts();\n"
                "int selectRandomFrom(set<int> values);\n"
                "pair<int, string> selectRandomApproximation();\n"
                "vector<int> values(map<int, int> m);\n"
                "vector<int> keys(map<int, int> m);\n"
                "vector<int> getPowTwo();\n"
                "void fillBaseShiftValue(map<int, int> &shifts);\n"
                "map<int, int> getShiftList();\n"
                "int evolveShift(int old_shift);\n"
                "int selectMask();\n"
                "pair<int, string> approximate(int *approximations, int *masks);\n"
                "double evaluateBitReset(int mask);\n"
                "double computeFitness(double app_acc, pair<int, string> app, int *masks);\n"
                "void reset();\n"
                "void saveApproximation(pair<int, string> app, int *masks);\n"
                "void printReport(ostream &cout, double finalAccuracy);\n"
                "void printInCSVFormat(ostream &cout, double finalAccuracy);\n";
    }

    std::string FastWriter::utilityFunctions()
    {
        return "vector<int> values(map<int, int> m) {\n"
                "    vector<int> v;\n"
                "    for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {\n"
                "        v.push_back(it->second);\n"
                "    }\n"
                "    return v;\n"
                "}\n"
                "vector<int> keys(map<int, int> m) {\n"
                "    vector<int> v;\n"
                "    for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {\n"
                "        v.push_back(it->first);\n"
                "    }\n"
                "    return v;\n"
                "}\n"
                "vector<int> getPowTwo() {\n"
                "    vector<int> v;\n"
                "    v.push_back(0);\n"
                "    for(int i = 0; i < 30; i++) {\n"
                "        v.push_back(1 << i);\n"
                "    }\n"
                "    return v;\n"
                "}\n"
                "void fillBaseShiftValue(map<int, int> &shifts) {\n"
                "    vector<int> powtwo = getPowTwo();\n"
                "    for(map<int, int>::iterator it = shifts.begin(); it != shifts.end(); it++) {\n"
                "        shifts[it->first]++;\n"
                "    }\n"
                "    for(vector<int>::iterator it = powtwo.begin(); it != powtwo.end(); it++) {\n"
                "        shifts[*it]++;\n"
                "    }\n"
                "}\n"
                "map<int, int> getShiftList() {\n"
                "    map<int, int> shifts = shiftsInfo;\n"
                "    if(shifts.size() < 30) {\n"
                "        fillBaseShiftValue(shifts);\n"
                "    }\n"
                "    return shifts;\n"
                "}\n"
                "int sampleIndex(vector<double> &probabilities) {\n"
                "    double rnd = randDouble();\n"
                "    unsigned int i;\n"
                "    for(i = 0; i < probabilities.size(); i++) {\n"
                "        if(rnd < probabilities[i]) {\n"
                "            return i;\n"
                "        }\n"
                "        rnd -= probabilities[i];\n"
                "    }\n"
                "    return i;\n"
                "}\n"
                "int selectUniformlyRandom(std::vector<int> array) {\n"
                "    int index = rand() % array.size();\n"
                "    return array[index];\n"
                "}\n"
                "vector<int> getReportCounts() {\n"
                "    vector<int> counts;\n"
                "    for (int i=0; i<5; i++) {\n"
                "        counts.push_back((int)dones[i].size()+1);\n"
                "    }\n"
                "    return counts;\n"
                "}\n"
                "int selectRandomFrom(set<int> values) {\n"
                "    vector<int> v(values.size(), 1);\n"
                "    vector<double> probs = normalizeProbabilities(v);\n"
                "    int index = sampleIndex(probs);\n"
                "    set<int>::iterator it = values.begin();\n"
                "    advance(it, index);\n"
                "    return *it;\n"
                "}\n"
                "bool is(std::string a, std::string b) {\n"
                "    return a.compare(b) == 0;\n"
                "}\n"
                "double randDouble() {\n"
                "    return ((double) rand() / (RAND_MAX));\n"
                "}\n"
                "vector<double> normalizeProbabilities(vector<int> &prob) {\n"
                "    vector<double> arr(prob.begin(), prob.end());\n"
                "    double sum = 0;\n"
                "    for(vector<int>::iterator it = prob.begin(); it != prob.end(); it++) {\n"
                "        sum += *it;\n"
                "    }\n"
                "    for(vector<double>::iterator it = arr.begin(); it != arr.end(); it++) {\n"
                "        *it = *it / sum;\n"
                "    }\n"
                "    return arr;\n"
                "}\n"
                + flagExtractionFunction()
                + fitnessComparisionFunction();
    }

    std::string FastWriter::flagExtractionFunction()
    {
        return "void extractFlags(int argc, char *argv[], double &acc, int &N, int &M, int &r, double &a1, double &a2) {\n"
                "    for(int i = 1; i < argc; i++) {\n"
                "        if(strcmp(FLAG_ACCURACY, argv[i]) == 0) {\n"
                "            acc = strtod(argv[++i], NULL);\n"
                "        } else if(strcmp(FLAG_N, argv[i]) == 0) {\n"
                "            N = atoi(argv[++i]);\n"
                "        } else if(strcmp(FLAG_M, argv[i]) == 0) {\n"
                "            M = atoi(argv[++i]);\n"
                "        } else if(strcmp(FLAG_REPETITION, argv[i]) == 0) { \n"
                "           r = atoi(argv[++i]);\n"
                "        } else if(strcmp(FLAG_A2, argv[i]) == 0) { \n"
                "           a2 = strtod(argv[++i], NULL);\n"
                "        }  else if(strcmp(FLAG_A1, argv[i]) == 0) { \n"
                "           a1 = strtod(argv[++i], NULL);\n"
                "        }\n"
                "    }\n"
                "}\n";
    }

    std::string FastWriter::fitnessComparisionFunction()
    {
        return "bool cmpPairs(ApproximationElement a, ApproximationElement b) { \n"
                "   return a.fitness >= b.fitness;\n"
                "}\n";
    }

    std::string FastWriter::approximationFunctions()
    {
        return "pair<int, string> approximate(int *approximations, int *masks) {\n"
                "    pair<int, string> app = selectRandomApproximation();\n"
                "    if (is(app.second, \"values\")) {\n"
                "        masks[app.first] = selectMask();\n"
                "    } else {\n"
                "        approximations[app.first] = 1;\n"
                "    }\n"
                "    return app;\n"
                "}\n"
                "pair<int, string> selectRandomApproximation() {\n"
                "    pair<int, string> app;\n"
                "    vector<int> vals = getReportCounts();\n"
                "    vector<double> probs = normalizeProbabilities(vals);\n"
                "    int index = sampleIndex(probs);\n"
                "    int operation = selectRandomFrom(availabilites[index]);\n"
                "    return make_pair(operation, correspondance[index]);\n"
                "}\n"
                + maskGenerationFunctions();
    }

    std::string FastWriter::maskGenerationFunctions()
    {
        return "int evolveShift(int old_shift) {\n"
                "    int evolution = old_shift;\n"
                "    vector<int> powtwo = getPowTwo();\n"
                "    while(old_shift == evolution) {\n"
                "        evolution += selectUniformlyRandom(powtwo);\n"
                "    }\n"
                "    return evolution;\n"
                "}\n"
                "int selectMask() {\n"
                "    map<int, int> shiftsMap = getShiftList();\n"
                "    vector<int> shifts = keys(shiftsMap);\n"
                "    vector<int> counts = values(shiftsMap);\n"
                "    vector<double> prob = normalizeProbabilities(counts);\n"
                "    int shift = shifts[sampleIndex(prob)];\n"
                "    if(randDouble() > 0.5) {\n"
                "        shift = evolveShift(shift);\n"
                "    }\n"
                "    return shift;\n"
                "}\n";
    }
    
    std::string FastWriter::accuracyEvaluationFunctions(std::string defaultType)
    {
        return "double compareOutputs("+ defaultType +" *originalOut, "+ defaultType +"*approximatedOut, int length) {\n"
                "    double sum = 0;\n"
                "    for (int i=0; i<length; i++) {\n"
                "        sum += originalOut[i] - approximatedOut[i];\n"
                "    }\n"
                "    return sum;\n"
                "}\n";
    }

    std::string FastWriter::fitnessEvaluationFunctions()
    {
        return "double evaluateBitReset(int mask) {\n"
                "    return ((double)mask) / 32.0;\n" 
                "}\n" 
                "double computeFitness(double app_acc, pair<int, string> app, int *masks) {\n" 
                "    double precisionErr = (is(app.second, \"value\"))? evaluateBitReset(masks[app.first]) : 0;\n" 
                "    return a1 * app_acc + a2 * precisionErr;\n" 
                "}\n";
    }

    std::string FastWriter::substitutionOfOriginalFunctions(std::string defaultType)
    {
        return "void replaceOriginal(double &relativeAccuracy, "+ defaultType +" *originalOut, int *approximations, int *masks, list<ApproximationElement> approximationList) {\n"
                "    approximationList.sort(cmpPairs);\n"
                "    ApproximationElement *element = &(approximationList.front());\n"
                "    relativeAccuracy -= element->accuracy;\n"
                "    copy(element->output.begin(), element->output.end(), originalOut);\n"
                "    copy(element->approximations.begin(), element->approximations.end(), approximations);\n"
                "    copy(element->masks.begin(), element->masks.end(), masks);\n"
                "    saveApproximation(element->app, masks);\n"
                "}\n";
    }

    // missing to add all instructions index
    std::string FastWriter::reportFunctions()
    {
        return "void reset() {\n"
                // missing to add all instructions index
                "   for (int i=0; i<5; i++) {\n"
                "       dones[i].clear();\n"
                "   }\n"
                "   shiftsInfo.clear();\n"
                "}\n"
                "void saveApproximation(pair<int, string> app, int *masks) {\n"
                "   int index = inverse_correspondance[app.second];\n"
                "   availabilites[index].erase(app.first);\n"
                "   dones[index].erase(app.first);\n"
                "   if(is(app.second, \"value\")) {\n"
                "       shiftsInfo[masks[app.first]]++;\n"
                "   }\n"
                "}\n"
                "void printReport(ostream &cout, double finalAccuracy) {\n"
                "   cout << \"Report:\" << std::endl;\n"
                "    for (int i =0; i<5; i++) {\n"
                "        cout << correspondance[i] << \" \" << dones[i].size() << std::endl;\n"
                "    }\n"
                "    if(shiftsInfo.size() != 0) {\n"
                "        cout << \"Shifts:\" << std::endl;\n"
                "        for(map<int, int>::iterator it = shiftsInfo.begin(); it != shiftsInfo.end(); it++) {\n"
                "            cout << \"\t\" << it->first << \": \" << it->second << std::endl;\n"
                "        }\n"
                "    }\n"
                "    cout << \"Final accuracy: \" << (1 - finalAccuracy) << std::endl;\n"
                "}\n"
                "void printInCSVFormat(ostream &cout, double finalAccuracy) {\n"
                "    cout << (1 - finalAccuracy) << \";\";\n"
                "    for (int i =0; i<5; i++) {\n"
                "        cout << dones[i].size() << \";\";\n"
                "    }\n"
                "    cout << std::endl;\n"
                "    if(shiftsInfo.size() != 0) {\n"
                "        for(map<int, int>::iterator it = shiftsInfo.begin(); it != shiftsInfo.end(); it++) {\n"
                "            cout << it->first << \";\" << it->second << \";\";\n"
                "        }\n"
                "    } else {\n"
                "        cout << \";\";\n"
                "    }\n"
                "    cout << std::endl;\n"
                "}\n";
    }

    std::string FastWriter::openApproximatedFunction(std::string defaultType)
    {
        return "void benchmark("+ defaultType +" *output, int *approximations, int *masks) {\n";
    }

    
    

} // namespace writer
