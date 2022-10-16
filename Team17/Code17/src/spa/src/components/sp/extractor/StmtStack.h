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
    std::vector<SimpleToken> varMod;
    std::vector<SimpleToken> varUse;
    std::vector<SimpleToken> stmts;
    std::vector<SimpleToken> stmtsNested;
    std::vector<SimpleToken> callStmts;
    std::multimap<std::string, SimpleToken> whileIfCallMap;
    virtual void extractNext(SimpleToken stmtToken) = 0;

protected:
    StmtStack(SimpleToken parent, Extractor* context) : parent(parent) {};
};
