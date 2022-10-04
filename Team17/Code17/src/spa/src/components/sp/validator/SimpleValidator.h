#pragma once

#include <string>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include "./states/ValidatorState.h"

class SimpleValidator {
    public:
        SimpleValidator();
        ValidatorState* state;
        std::stack<ValidatorState*> parentStates;
        std::set<std::string> procedureNames;
        bool validCode();
        void close();
        void setState(ValidatorState* newState);
        void validLine(SpTokenType type, int statementNumber);
        bool validateProcedure(std::string& token);
        static bool validateVariable(std::string& token);
        static bool validateConstant(std::string& token);
        static bool validateExprOpr(std::string& token);
        static bool isAndOrCenter(std::vector<std::string> tokens, int connectorPosition);
        static bool isValidCalls(std::multimap<std::string, std::string> &callProcedures,
            std::set<std::string>& procedures);
        static bool isCyclic(std::multimap<std::string, std::string>& callProcedures,
            std::map<std::string, bool> visited, std::string procedure);

};
