#pragma once

#include "ExprState.h"
#include "ExprStack.h"

class FactorState : public ExprState {
    public:
        FactorState(ExprStack* context);
        void put(std::vector<SimpleToken>& children, std::string value);
        bool valid();

    private:
        ExprStack* context;

};
