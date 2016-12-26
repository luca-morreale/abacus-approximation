#ifndef ADVANCED_OPERATION_GENERATOR_H
#define ADVANCED_OPERATION_GENERATOR_H

#include "operation_generator.h"

namespace generator {
    
    std::string generateApproximatedStatement(graph::NodePtr node, int nodeIndex);
    std::string generateStatement(graph::NodePtr node, int nodeIndex);

    std::string generateExpression(graph::NodePtr node, int nodeIndex);

    std::string binaryLogicOperator(std::string nameOp1, std::string nameOp2, std::string op, int nodeIndex);

    std::string negBit(std::string nameOp1, std::string nameOp2, int nodeIndex);
    std::string cast(std::string nameOp1, std::string nameOp2, int nodeIndex);
    std::string abs(std::string nameOp1, std::string nameOp2, int nodeIndex);


} // namespace generator

#endif /* ADVANCED_OPERATION_GENERATOR_H */
