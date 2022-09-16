#include <vector>
#include <iostream>
#include "components/sp/SimpleToken.h"
#include "components/sp/utils/SpUtils.h"
#include "components/sp/tokenizer/StmtStack.h"
#include "components/sp/tokenizer/NestedStack.h"
#include "components/sp/tokenizer/IfStack.h"
#include "components/sp/tokenizer/ProgramStack.h"

#include <catch.hpp>

TEST_CASE("incorrect Programstack") {
    SimpleToken programToken = SimpleToken(SpTokenType::TPROGRAM, "", 0, NULL);
    SimpleToken procedureToken = SimpleToken(SpTokenType::TPROCEDURE, "", 1, NULL);
    SimpleToken ifToken = SimpleToken(SpTokenType::TIF, "", 2, NULL);
    SimpleToken elseToken = SimpleToken(SpTokenType::TELSE, "", 3, NULL);
    SimpleToken whileToken = SimpleToken(SpTokenType::TWHILE, "", 4, NULL);
    SimpleToken assignToken = SimpleToken(SpTokenType::TASSIGN, "", 5, NULL);
    SimpleToken printToken = SimpleToken(SpTokenType::TPRINT, "", 6, NULL);
    SimpleToken readToken = SimpleToken(SpTokenType::TREAD, "", 7, NULL);
    SimpleToken callToken = SimpleToken(SpTokenType::TCALL, "", 8, NULL);
    StmtStack* stack = new ProgramStack(programToken);
    std::vector<SimpleToken> tokens{ ifToken, elseToken, whileToken, assignToken, printToken, readToken, callToken };
    for (SimpleToken token : tokens) {
        try {
            stack->put(token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == "Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
    delete stack;
}