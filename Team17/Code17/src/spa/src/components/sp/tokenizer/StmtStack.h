#pragma once
//change to stack of parents

#include <stack>
#include "../SimpleToken.h"

class StmtStack {

public:
    virtual void put(SimpleToken value) = 0;
    virtual SimpleToken dump() = 0;
    virtual bool isIf() = 0;
};
