#include <vector>
#include <iostream>
#include "components/sp/SimpleToken.h"
#include "components/sp/Parser/SimpleParser.h"
#include "components/sp/tokenizer/StmtStack.h"
#include "components/sp/tokenizer/ProgramStack.h"
#include "components/sp/tokenizer/NestedStack.h"
#include "components/sp/tokenizer/IfStack.h"

#include <catch.hpp>
/*
//will implement proper tests in later iteration
TEST_CASE("Procedure stack") {
    std::stack<StmtStack*> stmtStack;
    SimpleToken program = SimpleToken(SpTokenType::TPROGRAM, "test", 1, NULL);
    SimpleToken procedure = SimpleToken(SpTokenType::TPROCEDURE, "test2", 1, NULL);
    SimpleToken assign = SimpleToken(SpTokenType::TASSIGN, "", 4, NULL);
    SimpleToken close = SimpleToken(SpTokenType::TCLOSE, "", 5, NULL);
    ProgramStack progStack = ProgramStack(&program);
    NestedStack nestedStack = NestedStack(&procedure);
    StmtStack* currentStack = &progStack;
    currentStack->put(procedure);
    stmtStack.push(&progStack);
    currentStack = &nestedStack;
    currentStack->put(assign);
    currentStack->put(assign);
    currentStack->put(close);
    currentStack = stmtStack.top();
    stmtStack.pop();
    REQUIRE(procedure.getChildren().at(0).getChildren().size() == 2);
    REQUIRE(procedure.getChildren().at(0).getChildren().at(0).type == SpTokenType::TASSIGN);
}

TEST_CASE("if else stack") {
    std::stack<StmtStack*> stmtStack;
    bool isIf = false;
    StmtStack* currentStack = &ProgramStack(SimpleToken(SpTokenType::TPROGRAM, "", 0, NULL));
    SimpleToken procedure = SimpleToken(SpTokenType::TPROCEDURE, "test2", 1, NULL);
    SimpleToken assign = SimpleToken(SpTokenType::TASSIGN, "", 4, NULL);
    SimpleToken whileToken = SimpleToken(SpTokenType::TWHILE, "", 4, NULL);
    SimpleToken ifToken = SimpleToken(SpTokenType::TIF, "", 1, NULL);
    SimpleToken elseToken = SimpleToken(SpTokenType::TELSE, "else", 5, NULL);
    SimpleToken close = SimpleToken(SpTokenType::TCLOSE, "}", 5, NULL);
    std::vector<SimpleToken> tokenStack;
    tokenStack.push_back(procedure);
    tokenStack.push_back(assign);
    tokenStack.push_back(ifToken);
    tokenStack.push_back(assign);
    tokenStack.push_back(close);
    tokenStack.push_back(elseToken);
    tokenStack.push_back(close);
    tokenStack.push_back(close);
    for (SimpleToken lineToken : tokenStack) {
        if (lineToken.type == SpTokenType::TPROCEDURE) {
            stmtStack.push(currentStack);
            currentStack = &NestedStack(lineToken);
        }
        else if (lineToken.type == SpTokenType::TWHILE) {
            stmtStack.push(currentStack);
            currentStack = &NestedStack(lineToken);
        }
        else if (lineToken.type == SpTokenType::TIF) {
            isIf = true;
            stmtStack.push(currentStack);
            currentStack = &IfStack(lineToken);
        }
        else if (lineToken.type == SpTokenType::TCLOSE) {
            currentStack->put(lineToken);
            if (isIf) {
                isIf = false;
            }
            else {
                StmtStack* parentStack = stmtStack.top();
                parentStack->put(currentStack->dump());
                currentStack = parentStack;
                stmtStack.pop();
            }
        } else {
            currentStack->put(lineToken);
        }
    }
    REQUIRE(currentStack->dump().getChildren().at(0).getChildren().at(0).getChildren().at(1).type == SpTokenType::TIF);
    REQUIRE(currentStack->dump().getChildren().at(0).type == SpTokenType::TPROCEDURE);
}*/

