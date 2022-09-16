#pragma once
//change to stack of parents

#include <iostream>
#include <stack>
#include "../SimpleToken.h"

class StmtStack {

public:
    virtual void put(SimpleToken value) = 0;
    virtual SimpleToken dump() = 0;
};
