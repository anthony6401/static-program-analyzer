#pragma once

#include <string>
#include <vector>

class SimpleValidator {
    public:
        static bool validateVariable(std::string& token);
        static bool validateConstant(std::string& token);
        static bool validateExprOpr(std::string& token);
        static bool validateFactorState(std::string& token);
        static bool validateOperandState(std::string& token);
};
