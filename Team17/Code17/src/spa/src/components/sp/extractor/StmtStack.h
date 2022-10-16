#pragma once

#include <unordered_set>
#include <vector>
#include <map>
#include "../SimpleToken.h"
#include "../utils/SpUtils.h"

class StmtStack {

public:
    SimpleToken parent;
    virtual void close(int statementNumber) = 0;
    virtual void mergeStack() = 0;
    std::unordered_set<SimpleToken, SimpleHash> varMod;
    std::unordered_set<SimpleToken, SimpleHash> varUse;
    std::unordered_set<SimpleToken, SimpleHash> stmtsNested;
    std::vector<SimpleToken> stmts;
    std::vector<SimpleToken> callStmts;
    std::multimap<std::string, SimpleToken> whileIfCallMap;
    virtual void extractNext(SimpleToken stmtToken) = 0;

protected:
    StmtStack(SimpleToken parent, Extractor* context) : parent(parent) {};
};
