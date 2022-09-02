#include "components/sp/simple_parser/SimpleParser.h"

#include <catch.hpp>
#include <iostream>

bool equalToken(SimpleToken& test, SimpleToken& result) {
    return test.type == result.type && test.statementNumber == result.statementNumber && test.value == result.value;
}

TEST_CASE("parse print") {
    SimpleParser::initializeParser();
    std::vector<std::string> test_tokens;
    test_tokens.push_back("print");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = SimpleParser::parseLine(test_tokens);
    std::vector<std::string> result_tokens;
    result_tokens.push_back("test");
    result_tokens.push_back(";");
    SimpleToken expected_result = SimpleToken(TokenType::TPRINT, result_tokens, 1);
    REQUIRE(equalToken(test_result, expected_result));
}

TEST_CASE("parse read") {
    SimpleParser::initializeParser();
    std::vector<std::string> test_tokens;
    test_tokens.push_back("read");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = SimpleParser::parseLine(test_tokens);
    std::vector<std::string> result_tokens;
    result_tokens.push_back("test");
    result_tokens.push_back(";");
    SimpleToken expected_result = SimpleToken(TokenType::TREAD, result_tokens, 1);
    REQUIRE(equalToken(test_result, expected_result));
}