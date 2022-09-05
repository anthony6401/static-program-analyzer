#include "components/sp/parser/SimpleParser.h"
#include <catch.hpp>

bool equalToken(SimpleToken& test, SimpleToken& result) {
    return test.type == result.type && test.statementNumber == result.statementNumber && test.value == result.value;
}

bool equalChildren(std::vector<SimpleToken> test, std::vector<SimpleToken> result) {
    if (test.size() == result.size()) {
        for (int i = 0; i < test.size(); i++) {
            SimpleToken a = test.at(i);
            SimpleToken b = result.at(i);
            if (a.type != b.type && a.statementNumber != b.statementNumber && a.value != b.value) {
                return false;
            } 
        }
        return true;
    }
    else {
        return false;
    }
}

TEST_CASE("parseLine print") {
    SimpleParser::statementNumber = 1;
    std::string code = "print test;";
    std::vector<std::string> test_tokens;
    test_tokens.push_back("print");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = SimpleParser::parseLine(test_tokens, code);
    SimpleToken expected_result = SimpleToken(TokenType::TPRINT, code,
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
    SimpleToken expected_result = SimpleToken(TokenType::TREAD, code,
        1, SimpleParser::parseRead);
    REQUIRE(equalToken(test_result, expected_result));
}

TEST_CASE("parse read") {
    SimpleParser::statementNumber = 1;
    std::string code = "read test;";
    std::vector<std::string> tokens;
    tokens.push_back("test");
    tokens.push_back(";");
    SimpleToken test_token = SimpleToken(TokenType::TREAD, code,
        1, SimpleParser::parseRead);
    (test_token.parseFunction)(test_token, tokens);
    SimpleToken expected_children = SimpleToken(TokenType::TVARIABLE, "test", 
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
    SimpleToken test_token = SimpleToken(TokenType::TPRINT, code,
        1, SimpleParser::parsePrint);
    (test_token.parseFunction)(test_token, tokens);
    SimpleToken expected_children = SimpleToken(TokenType::TVARIABLE, "test",
        0, NULL);
    std::vector<SimpleToken> expected_result;
    expected_result.push_back(expected_children);
    REQUIRE(equalChildren(test_token.getChildren(), expected_result));
}

