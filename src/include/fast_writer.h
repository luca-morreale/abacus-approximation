#ifndef FAST_WRITER_H
#define FAST_WRITER_H


#include "advanced_operation_generator.h"
#include "writer.h"


namespace writer {

    #define APPROXIMATIONS 5

    class FastWriter : public Writer {
    public:
        FastWriter();
        ~FastWriter() { /*    */ }

    private:
        std::vector<int> approximableOperations[APPROXIMATIONS];
        std::map<int, std::string> mapping;
        std::map<std::string, int> inverseMapping;

    protected:

        virtual void resetOperationsList();
        virtual void updateInstructionMapping(std::string op, int instructionIndex);

        virtual void prepareFile(std::ofstream &cout, ParsingState &state);
        virtual void closeFile(std::ofstream &cout, ParsingState &state, std::string id);
        
        virtual void writeBasicOperation(ParsingState &state, std::ofstream &cout);
        virtual void updateInstructionIndex(std::string op, int &instructionIndex);

        virtual std::string mainVariablesInitialization();
        virtual std::string getArgsVariablesExtraction();

        virtual std::string declareApproximationVariables(std::string defaultType, std::initializer_list<double> vals);
        virtual std::string initializationApproximationVariables();

        virtual std::string getDeclarationOuterLoop(std::string defaultType, int instructionCount);
        virtual std::string getDeclarationInnerLoop(std::string defaultType, int instructionCount);

        virtual std::string approximationInstruction(int instructionCount);
        virtual std::string accuracyEstimationInstructions();

        virtual std::string getAdditionToListInstructions(std::string defaultType, int instructionCount);
        virtual std::string substutionInstructions();

        virtual std::string getReportPrintingInstructions();


        virtual std::string includes();
        virtual std::string defines();
        virtual std::string staticDefinition(std::string defaultType);
        virtual std::string functionProtopypes(std::string defaultType);

        virtual std::string utilityFunctions();
        virtual std::string flagExtractionFunction();
        virtual std::string fitnessComparisionFunction();
        virtual std::string approximationFunctions();
        virtual std::string maskGenerationFunctions();
        virtual std::string accuracyEvaluationFunctions(std::string defaultType);
        virtual std::string fitnessEvaluationFunctions();
        virtual std::string substitutionOfOriginalFunctions(std::string defaultType);
        // missing to add all instructions index
        virtual std::string reportFunctions();
        virtual std::string openApproximatedFunction(std::string defaultType);


        template <typename T, typename... Args>
        std::string unpackParams(T t, Args... args) {
            return ", " + t + unpackParams(args...);
        }

        template <typename T> 
        std::string unpackParams(T x) {
            return ", " + x;
        }

        template <typename... Args>
        std::string callApproximatedFunction(std::string param, Args &&... args) {
            return "benchmark(" + param + unpackParams(args...) + ");";
        }

        

    };

    

} // namespace writer


#endif /* FAST_WRITER_H */
