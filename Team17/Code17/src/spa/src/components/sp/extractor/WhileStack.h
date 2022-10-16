#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class WhileStack : public StmtStack {
public:
    WhileStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    void mergeStack();
    void extractFollows(std::vector<SimpleToken> stmts);
    void extractFollowsT(std::vector<SimpleToken> stmts);
    void extractParent(std::vector<SimpleToken> stmts);
    void extractParentT(std::unordered_set<SimpleToken, SimpleHash> stmtsNested);
    void extractUses(std::unordered_set<SimpleToken, SimpleHash> varUse);
    void extractModify(std::unordered_set<SimpleToken, SimpleHash> varMod);
    Entity* generateEntity(SimpleToken token);
    void extractNext(SimpleToken stmtToken);

private:
    SimpleToken parent;
    Extractor* context;
};
