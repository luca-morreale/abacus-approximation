#include "include/advanced_operation_generator.h"

namespace generator {

    
    std::string generateApproximatedStatement(graph::NodePtr node, int nodeIndex)
    {
        std::string outputVariable = syntax::Syntax::getCompleteIdentifier(node->out);
        std::string expression;

        std::string operand1, operand2;
        getOperands(node->incoming[0], operand1, node->incoming[1], operand2);
        
        if (is(node->op, "+")) {
            expression = "orbit(" + operand1 + ", andbitMask(masks[" + std::to_string(nodeIndex) + "], " + operand2 + "))";
        } else if (is(node->op, "*")) {
            expression = "leftshiftMask(" + operand1 + ", masks[" + std::to_string(nodeIndex) + "]) + andbit(masks[" + std::to_string(nodeIndex+1) + "], " + operand2 + ")";
        } else if (is(node->op, "-")) {
            expression = "andbit(" + operand1 + ", negbit(" + operand2 + "))";
        } else if (is(node->op, "/")) {
            expression = "rightshiftMask(" + operand1 + ", masks[" + std::to_string(nodeIndex) + "]) - andbit(masks[" + std::to_string(nodeIndex+1) + "], " + operand2 + ")";
        } else {
            expression = generateExpression(node, nodeIndex);
        }
        return outputVariable + " = " + expression + ";";
    }

    std::string generateStatement(graph::NodePtr node, int nodeIndex)
    {
        std::string outputVariable = syntax::Syntax::getCompleteIdentifier(node->out);
        std::string expression = generateExpression(node, nodeIndex);

        return outputVariable + " = " + expression + ";";
    }

    std::string generateExpression(graph::NodePtr node, int nodeIndex)
    {
        std::string expression;
        
        if(is(node->op, "cast")) {
            expression = cast(node->incoming[0], node->incoming[1], nodeIndex);
        } else if(is(node->op, "abs")) {
            expression = abs(node->incoming[0], node->incoming[1], nodeIndex);
        } else if(is(node->op, "~")) {
            expression = negBit(node->incoming[0], node->incoming[1], nodeIndex);
        } else if(isBinaryBitOperation(node->op) || isShiftOperation(node->op)) {
            expression = binaryLogicOperator(node->incoming[0], node->incoming[1], node->op, nodeIndex);
        } else {
            expression = expressionForNormalOperation(node->op, node->incoming[0], node->incoming[1], nodeIndex);
        }
        return expression;
    }

    std::string expressionForNormalOperation(std::string op, std::string nameOp1, std::string nameOp2, int nodeIndex)
    {
        std::string operand1, operand2;
        getOperands(nameOp1, operand1, nameOp2, operand2);
        nodeIndex += (is(op, "*") || is(op, "/")) ? 1 : 0;
        
        return operand1 + " " + op + " andbitMask(masks[" + std::to_string(nodeIndex) + "], " + operand2 + ")";
    }

    std::string binaryLogicOperator(std::string nameOp1, std::string nameOp2, std::string op, int nodeIndex)
    {
        std::string operand1, operand2;
        getOperands(nameOp1, operand1, nameOp2, operand2);
        return functionMap[op] + "(" + operand1 + ", andbitMask(masks[" + std::to_string(nodeIndex) + "], " + operand2 + "))";
    }

    std::string negBit(std::string nameOp1, std::string nameOp2, int nodeIndex)
    {
        std::string operand;
        extractOperand(nameOp1, operand);
        return "negbit(andbitMask(masks[" + std::to_string(nodeIndex) + "], " + operand + "))";
    }

    std::string cast(std::string nameOp1, std::string nameOp2, int nodeIndex)
    {
        std::string operand;
        extractOperand(nameOp2, operand);
        return "(" + nameOp1 + ")andbitMask(masks[" + std::to_string(nodeIndex) + "], " + operand + ")";
    }

    std::string abs(std::string nameOp1, std::string nameOp2, int nodeIndex)
    {
        std::string operand;
        extractOperand(nameOp1, operand);
        return "std::abs(andbitMask(masks[" + std::to_string(nodeIndex) + "], " + operand + "))";
    }


} // namespace generator
