#pragma once

#include <stack>
#include <map>
#include <set>
#include "../SimpleToken.h"
#include "../validator/SimpleValidator.h"

#include "../../../models/Relationship/Relationship.h"
#include "../../../models/Relationship/FollowsRelationship.h"
#include "../../../models/Relationship/FollowsTRelationship.h"
#include "../../../models/Relationship/ParentRelationship.h"
#include "../../../models/Relationship/ParentTRelationship.h"
#include "../../../models/Relationship/UsesRelationship.h"
#include "../../../models/Relationship/ModifyRelationship.h"
#include "../../../models/Relationship/CallsRelationship.h"

class StmtStack {

public:
    StmtStack();
    //virtual void close(int statementNumber) = 0;
    //virtual bool isIf() = 0;
    //virtual void mergeStack(StmtStack &parentStack, StmtStack &childStack);
    void close(int statementNumber);
    bool isIf();
    void mergeStack(StmtStack& parentStack, StmtStack& childStack);
    std::vector<ModifyRelationship*> modifies;
    std::vector<UsesRelationship*> uses;
    std::vector<SimpleToken> follows;
    std::vector<CallsRelationship*> calls;
    std::multimap<std::string, std::string> callProcedures;

    void addFollows(SimpleToken token);
    void addUses(UsesRelationship* relationship);
    void addModify(ModifyRelationship* relationship);
    void addCall(CallsRelationship* relationship);

};
