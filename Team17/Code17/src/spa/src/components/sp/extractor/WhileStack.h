#pragma once

#include "StmtStack.h"

class WhileStack : public StmtStack {
public:
    WhileStack(SimpleToken parent);
    void put(SimpleToken token);
    bool isIf();

private:
    SimpleToken parent;

};
