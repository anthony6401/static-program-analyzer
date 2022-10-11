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
    void extractParentT(std::vector<SimpleToken> stmtsNested);
    void extractUses(std::vector<SimpleToken> varUse);
    void extractModify(std::vector<SimpleToken> varMod);
    Entity* generateEntity(SimpleToken token);

private:
    bool expectElse;
    SimpleToken parent;
    Extractor* context;
};
