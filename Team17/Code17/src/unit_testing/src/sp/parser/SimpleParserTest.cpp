#include "components/sp/parser/SimpleParser.h"
#include <iostream>
#include <catch.hpp>

bool equalToken(SimpleToken& test, SimpleToken& result) {
    return test.type == result.type && test.statementNumber == result.statementNumber && test.value == result.value;
}

bool equalChildren(std::vector<SimpleToken> test, std::vector<SimpleToken> result) {
    if (test.size() != result.size()) {
        std::cout << 1;
        return false;
    }
    for (int i = 0; i < test.size(); i++) {
        SimpleToken a = test.at(i);
        SimpleToken b = result.at(i);
        if (!(equalToken(a, b))) {
            std::cout << 2;
            return false;
        }
        if (test.empty() == result.empty() && !(test.empty())) {
            if(!(equalChildren(a.getChildren(), b.getChildren()))) {
                return false;
            }
        }
    }
    return true;
}

TEST_CASE("parseLine print") {
    SimpleParser::statementNumber = 1;
    std::string code = "print test;";
    std::vector<std::string> test_tokens;
    test_tokens.push_back("print");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = SimpleParser::parseLine(test_tokens, code);
    SimpleToken expected_result = SimpleToken(SpTokenType::TPRINT, code,
        1, SimpleParser::parsePrint);
    REQUIRE(equalToken(test_result, expected_result));
}

TEST_CASE("parseLine read") {
    SimpleParser::statementNumber = 1;
    std::string code = "read test;";
    std::vector<std::string> test_tokens;
    test_tokens.push_back("read");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = SimpleParser::parseLine(test_tokens, code);
    SimpleToken expected_result = SimpleToken(SpTokenType::TREAD, code,
        1, SimpleParser::parseRead);
    REQUIRE(equalToken(test_result, expected_result));
}

TEST_CASE("parse expr") {
    SimpleParser::statementNumber = 1;
    std::vector<std::string> test_tokens;
    test_tokens.push_back("(");
    test_tokens.push_back("1");
    test_tokens.push_back("+");
    test_tokens.push_back("1");
    test_tokens.push_back(")");
    SimpleToken test_result = SimpleParser::parseExpr(test_tokens);
    SimpleToken result = SimpleToken(SpTokenType::TEXPR, "",
        0, NULL);
    std::vector<SimpleToken> resultTokens;
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0, NULL));
    resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0, NULL));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0, NULL));
    result.setChildren(resultTokens);
    REQUIRE(equalChildren(test_result.getChildren(), result.getChildren()));
}

TEST_CASE("parse assign") {
    SimpleParser::statementNumber = 1;
    std::vector<std::string> test_tokens;
    test_tokens.push_back("a");
    test_tokens.push_back("(");
    test_tokens.push_back("1");
    test_tokens.push_back("+");
    test_tokens.push_back("1");
    test_tokens.push_back(")");
    test_tokens.push_back(";");
    SimpleToken test = SimpleToken(SpTokenType::TASSIGN, "", 1, SimpleParser::parseAssign);
    SimpleParser::parseAssign(test, test_tokens, NULL);
    SimpleToken result = SimpleToken(SpTokenType::TASSIGN, "",
        1, NULL);
    std::vector<SimpleToken> children;
    std::vector<SimpleToken> resultTokens;
    children.push_back(SimpleToken(SpTokenType::TVARIABLE, "a", 0, NULL));
    SimpleToken expr = SimpleToken(SpTokenType::TEXPR, "", 0, NULL);
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0, NULL));
    resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0, NULL));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0, NULL));
    expr.setChildren(resultTokens);
    children.push_back(expr);
    result.setChildren(children);
    REQUIRE(equalToken(test, result));
    REQUIRE(equalChildren(test.getChildren(), result.getChildren()));
}

/*
TEST_CASE("parse read") {
    SimpleParser::statementNumber = 1;
    std::string code = "read test;";
    std::vector<std::string> tokens;
    tokens.push_back("test");
    tokens.push_back(";");
    SimpleToken test_token = SimpleToken(SpTokenType::TREAD, code,
        1, SimpleParser::parseRead);
    (test_token.parseFunction)(test_token, tokens, NULL, NULL);
    SimpleToken expected_children = SimpleToken(SpTokenType::TVARIABLE, "test", 
        0, NULL);
    std::vector<SimpleToken> expected_result;
    expected_result.push_back(expected_children);
    REQUIRE(equalChildren(test_token.getChildren(), expected_result));
}

TEST_CASE("parse print") {
    SimpleParser::statementNumber = 1;
    std::string code = "print test;";
    std::vector<std::string> tokens;
    tokens.push_back("print");
    tokens.push_back(";");
    SimpleToken test_token = SimpleToken(SpTokenType::TPRINT, code,
        1, SimpleParser::parsePrint);
    (test_token.parseFunction)(test_token, tokens, NULL, NULL);
    SimpleToken expected_children = SimpleToken(SpTokenType::TVARIABLE, "test",
        0, NULL);
    std::vector<SimpleToken> expected_result;
    expected_result.push_back(expected_children);
    REQUIRE(equalChildren(test_token.getChildren(), expected_result));
}
*/
