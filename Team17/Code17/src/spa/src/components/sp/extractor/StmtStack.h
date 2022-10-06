#pragma once

#include <stack>
#include <map>
#include <set>
#include "../SimpleToken.h"
#include "../validator/SimpleValidator.h"

class StmtStack {

public:
    SimpleToken parent;
    virtual void close(int statementNumber) = 0;
    virtual void mergeStack() = 0;
    std::vector<SimpleToken> modifies;
    std::vector<SimpleToken> uses;
    std::vector<SimpleToken> follows;
    std::vector<SimpleToken> parentT;

protected:
    StmtStack(SimpleToken parent, Extractor* context) : parent(parent) {};

};
