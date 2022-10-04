#pragma once

#include <stack>
#include <vector>
#include <stdexcept>
#include "../../SimpleToken.h"
#include "ExprState.h"

class FactorState;

class ExprStack {

    public:
        ExprState* state;
        ExprStack();
        ~ExprStack() {
            delete state;
        }
        void setState(ExprState* state);
        void open();
        void close();
        void put(std::string value);
        bool valid();
        std::vector<SimpleToken> get();

    private:
        std::stack<std::string> bracketStack;
        std::vector<SimpleToken> children;

};
