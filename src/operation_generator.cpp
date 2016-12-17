#include "include/operation_generator.h"

namespace generator {

    std::map<std::string, std::string> functionMap = {{"<<", "leftshift"}, {">>", "rightshift"}, {"&", "andbit"}, {"|", "orbit"}};


    std::string generateStatement(graph::NodePtr node)
    {
        std::string outputVariable = syntax::Syntax::getCompleteIdentifier(node->out);
        std::string expression = generateExpression(node);

        return outputVariable + " = " + expression + ";";
    }

    std::string generateExpression(graph::NodePtr node)
    {
        std::string expression;
        
        if(is(node->op, "cast")) {
            expression = cast(node->incoming[0], node->incoming[1]);
        } else if(is(node->op, "abs")) {
            expression = abs(node->incoming[0], node->incoming[1]);
        } else if(is(node->op, "~")) {
            expression = negBit(node->incoming[0], node->incoming[1]);
        } else if(isBinaryBitOperation(node->op) || isShiftOperation(node->op)) {
            expression = binaryLogicOperator(node->incoming[0], node->incoming[1], node->op);
        } else {
            std::string operand1, operand2;
            getOperands(node->incoming[0], operand1, node->incoming[1], operand2);
            expression = operand1 + " " + node->op + " " + operand2;
        }
        return expression;
    }

    bool isBitOperation(std::string op)
    {
        return isBinaryBitOperation(op) || is(op, "~");
    }

    bool isBinaryBitOperation(std::string op)
    {
        return is(op, "&") || is(op, "|");
    }

    bool isShiftOperation(std::string op)
    {
        return is(op, "<<") || is(op, ">>");
    }


    std::string binaryLogicOperator(std::string nameOp1, std::string nameOp2, std::string op)
    {
        std::string operand1, operand2;
        getOperands(nameOp1, operand1, nameOp2, operand2);

        return functionMap[op] + "(" + operand1 + ", " + operand2 + ")";
    }

    std::string negBit(std::string nameOp1, std::string nameOp2)
    {
        std::string operand;
        extractOperand(nameOp1, operand);

        return "negbit(" + operand + ")";
    }

    std::string cast(std::string nameOp1, std::string nameOp2)
    {
        std::string operand;
        extractOperand(nameOp2, operand);
        return "(" + nameOp1 + ")" + operand;
    }

    std::string abs(std::string nameOp1, std::string nameOp2)
    {
        std::string operand;
        extractOperand(nameOp1, operand);
        return "std::abs(" + operand + ")";
    }


    void getOperands(std::string nameOp1, std::string &operand1, std::string nameOp2, std::string &operand2) 
    {
        extractOperand(nameOp1, operand1);
        extractOperand(nameOp2, operand2);
    }
    
    void extractOperand(std::string name, std::string &operand)
    {
        if (isNumber(name)){
            operand = name;
        } else if (is(name, "randomFloat")) {
            operand = "" + std::to_string(randDouble());
        }else {
            operand = syntax::Syntax::getCompleteIdentifier(name, true);
        }
    }

    std::string generateIncludes()
    {
        return "#include <cstring>\n#include <cmath>\n";
    }


    std::string generateFunctions(std::string defaultType)
    {
        std::string functions = "";
        functions += defaultType + " leftshift(" + defaultType + " a," + defaultType + " b) { "
                "long int first, second; "
                 + defaultType + " result; "
                "std::memcpy(&first, &a, sizeof a);"
                "std::memcpy(&second, &b, sizeof b);"
                "first = (first & ~mask) | (((first & mask) << second) & mask);"
                "std::memcpy(&result, &first, sizeof first);"
                "return result;"
           " }\n";

        functions += defaultType + " rightshift(" + defaultType + " a," + defaultType + " b) { "
                "long int first, second;"
                + defaultType + " result;"
                "std::memcpy(&first, &a, sizeof a);"
                "std::memcpy(&second, &b, sizeof b);"
                "first = (first & ~mask) | (((first & mask) >> second) & mask);"
                "std::memcpy(&result, &first, sizeof first);"
                "return result;"
            "}\n";

        functions += defaultType + " andbit(" + defaultType + " a," + defaultType + " b) { "
                "long int first, second;"
                + defaultType + " result;"
                "std::memcpy(&first, &a, sizeof a);"
                "std::memcpy(&second, &b, sizeof b);"
                "first = first & second;"
                "std::memcpy(&result, &first, sizeof first);"
                "return result;"
            "}\n";

        functions += defaultType + " orbit(" + defaultType + " a," + defaultType + " b) { "
                "long int first, second;"
                + defaultType + " result;"
                "std::memcpy(&first, &a, sizeof a);"
                "std::memcpy(&second, &b, sizeof b);"
                "first = first | second;"
                "std::memcpy(&result, &first, sizeof first);"
                "return result;"
            "}\n";

        functions += defaultType + " negbit(" + defaultType + " a) { "
                "long int first;"
                + defaultType + " result;"
                "std::memcpy(&first, &a, sizeof a);"
                "first = ~first;"
                "std::memcpy(&result, &first, sizeof first);"
                "return result;"
            "}\n";

        return functions;
    }


}