#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

class SimpleValidator {
    public:
        static bool validateVariable(std::string& token);
        static bool validateConstant(std::string& token);
        static bool validateExprOpr(std::string& token);
        static bool validateFactorState(std::string& token);
        static bool validateOperandState(std::string& token);
        static bool isAndOrCenter(std::vector<std::string> tokens, int connectorPosition);
        static bool isValidCalls(std::multimap<std::string, std::string> &callProcedures,
            std::set<std::string>& procedures);
        static bool SimpleValidator::isCyclic(std::multimap<std::string, std::string>& callProcedures,
            std::map<std::string, bool> visited, std::string procedure);

};
