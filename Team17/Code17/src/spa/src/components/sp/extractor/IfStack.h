#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class IfStack : public StmtStack {
public:
    IfStack(SimpleToken parent, Extractor* context);
    void close(int statemetNumber);
    void mergeStack();
    std::vector<SimpleToken> ifStmts; // statementNumber
    void extractFollows(std::vector<SimpleToken> stmts);
    void extractFollowsT(std::vector<SimpleToken> stmts);
    void extractParent(std::vector<SimpleToken> stmts);
    void extractParentT(std::unordered_set<SimpleToken, SimpleHash> stmtsNested);
    void extractUses(std::unordered_set<SimpleToken, SimpleHash> varUse);
    void extractModify(std::unordered_set<SimpleToken, SimpleHash> varMod);
    Entity* generateEntity(SimpleToken token);
    void extractNext(SimpleToken stmtToken);
    std::vector<SimpleToken> endPoints;

private:
    bool expectElse;
    SimpleToken parent;
    Extractor* context;
};
