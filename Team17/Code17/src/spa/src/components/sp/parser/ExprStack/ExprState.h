#pragma once

#include <vector>
#include "../../SimpleToken.h"

class ExprState {
    public:
        virtual void put(std::vector<SimpleToken>& children, std::string value) {}
        virtual bool valid() { return false; }
};
