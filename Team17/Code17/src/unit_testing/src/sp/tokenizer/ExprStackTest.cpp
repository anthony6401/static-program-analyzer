#include <vector>
#include <iostream>
#include "components/sp/SimpleToken.h"
#include "components/sp/utils/SpUtils.h"
#include "components/sp/tokenizer/ExprStack.h"
#include "components/sp/tokenizer/FactorState.h"
#include "components/sp/tokenizer/OperandState.h"
#include "components/sp/tokenizer/ExprCloseState.h"

#include <catch.hpp>

//Temporary solution. Will clean up in the future
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

TEST_CASE("Correct FactorState") {
    ExprStack stack = ExprStack();
    stack.setState(new FactorState(&stack));
    try {
        stack.put("-");
        stack.setState(new FactorState(&stack));
        std::vector<SimpleToken> result;
        result.push_back(SimpleToken(SpTokenType::TOPR, "-", 0, NULL));
        REQUIRE(equalChild(stack.get(), result));
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
        FAIL();
    }
}

TEST_CASE("Incorrect FactorState") {
    ExprStack stack = ExprStack();
    stack.setState(new FactorState(&stack));
    std::vector<std::string> test_tokens{ "a","1","(" };
    for (std::string test_token : test_tokens) {
        try {
            stack.put(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == ("Invalid character " + test_token));
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
}

TEST_CASE("Correct OperandState") {
    ExprStack stack = ExprStack();
    stack.setState(new OperandState(&stack));
    try {
        stack.put("1");
        stack.setState(new OperandState(&stack));
        stack.put("a");
        std::vector<SimpleToken> result;
        result.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0, NULL));
        result.push_back(SimpleToken(SpTokenType::TVARIABLE, "a", 0, NULL));
        REQUIRE(equalChild(stack.get(), result));
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
        FAIL();
    }
}

TEST_CASE("Incorrect OperandState") {
    ExprStack stack = ExprStack();
    stack.setState(new OperandState(&stack));
    std::vector<std::string> test_tokens{ ")", "^"};
    for (std::string test_token : test_tokens) {
        try {
            stack.put(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == ("Invalid character " + test_token));
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
}

TEST_CASE("Correct ExprCloseState") {
    ExprStack stack = ExprStack();
    stack.setState(new ExprCloseState(&stack));
    try {
        stack.put("1");
        stack.setState(new ExprCloseState(&stack));
        stack.put("a");
        stack.setState(new ExprCloseState(&stack));
        stack.put("+");
        std::vector<SimpleToken> result;
        result.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0, NULL));
        result.push_back(SimpleToken(SpTokenType::TVARIABLE, "a", 0, NULL));
        result.push_back(SimpleToken(SpTokenType::TOPR, "+", 0, NULL));
        REQUIRE(equalChild(stack.get(), result));
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
        FAIL();
    }
}

TEST_CASE("Incorrect ExprCloseState") {
    ExprStack stack = ExprStack();
    stack.setState(new ExprCloseState(&stack));
    std::vector<std::string> test_tokens{ ")", "(" };
    for (std::string test_token : test_tokens) {
        try {
            stack.put(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == ("Invalid character " + test_token));
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
}

TEST_CASE("ExprStack close") {
    ExprStack stack = ExprStack();
    try {
        stack.put("1");
        stack.put(")");
    }
    catch (std::invalid_argument e) {
        REQUIRE(e.what() == std::string("Unexpected )"));
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
