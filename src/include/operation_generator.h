#ifndef OPEARTION_GENERATOR_H
#define OPERATION_GENERATOR_H

#include "graph.h"
#include "syntax.h"

namespace generator {

    extern std::map<std::string, std::string> functionMap;

    std::string generateStatement(graph::NodePtr node);
    std::string generateExpression(graph::NodePtr node);

    std::string generateIncludes();
    std::string generateFunctions(std::string defaultType);
    

    std::string binaryLogicOperator(std::string nameOp1, std::string nameOp2, std::string op);
    std::string negBit(std::string nameOp1, std::string nameOp2);
    std::string cast(std::string nameOp1, std::string nameOp2);
    std::string abs(std::string nameOp1, std::string nameOp2);

    bool isBitOperation(std::string op);
    bool isBinaryBitOperation(std::string op);
    bool isShiftOperation(std::string op);
    void getOperands(std::string nameOp1, std::string &operand1, std::string nameOp2, std::string &operand2);
    void extractOperand(std::string name, std::string &operand);


} // namespace generator


#endif /* OPERATION_GENERATOR_H */