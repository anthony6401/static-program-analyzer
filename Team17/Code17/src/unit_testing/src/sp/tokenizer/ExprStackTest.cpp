#include <vector>
#include <iostream>
#include "components/sp/SimpleToken.h"
#include "components/sp/utils/SpUtils.h"
#include "components/sp/tokenizer/ExprStack.h"
#include "components/sp/tokenizer/FactorState.h"

#include <catch.hpp>

bool equalChild(std::vector<SimpleToken> test, std::vector<SimpleToken> result) {
    if (test.size() == result.size()) {
        for (int i = 0; i < test.size(); i++) {
            SimpleToken a = test.at(i);
            SimpleToken b = result.at(i);
            if (a.type != b.type || a.statementNumber != b.statementNumber || a.value != b.value) {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

TEST_CASE("FactorState") {
    ExprStack stack = ExprStack();
    stack.setState(new FactorState(&stack));
    try {
        stack.put("-");
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    std::vector<SimpleToken> result;
    result.push_back(SimpleToken(SpTokenType::TOPR, "-", 0, NULL));
    REQUIRE(equalChild(stack.get(),result));

}