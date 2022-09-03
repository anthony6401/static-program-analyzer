#include "components/sp/parser/SimpleParser.h"

#include <catch.hpp>
#include <iostream>

bool equalToken(SimpleToken& test, SimpleToken& result) {
    return test.type == result.type && test.statementNumber == result.statementNumber && test.value == result.value;
}

TEST_CASE("parseLine print") {
    SimpleParser::statementNumber = 1;
    std::string code = "print test;";
    std::vector<std::string> test_tokens;
    test_tokens.push_back("print");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = SimpleParser::parseLine(test_tokens, code);
    std::vector<std::string> result_tokens;
    result_tokens.push_back("test");
    result_tokens.push_back(";");
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
    std::vector<std::string> result_tokens;
    result_tokens.push_back("test");
    result_tokens.push_back(";");
    SimpleToken expected_result = SimpleToken(TokenType::TREAD, code,
        1, SimpleParser::parseRead);
    REQUIRE(equalToken(test_result, expected_result));
}
