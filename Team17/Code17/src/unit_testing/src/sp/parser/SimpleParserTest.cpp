#include "components/sp/parser/SimpleParser.h"
#include <iostream>
#include <catch.hpp>
/*
//Temporary solution. Will clean up in the future
bool equalToken(SimpleToken& test, SimpleToken& result) {
    return test.type == result.type && test.statementNumber == result.statementNumber && test.value == result.value;
}

bool equalChildren(std::vector<SimpleToken> test, std::vector<SimpleToken> result) {
    if (test.size() != result.size()) {
        return false;
    }
    for (int i = 0; i < test.size(); i++) {
        SimpleToken a = test.at(i);
        SimpleToken b = result.at(i);
        if (!(equalToken(a, b))) {
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

PKB* stubSP = new PKB();
auto stubClient = new SPClient(stubSP);
Extractor extractor = Extractor(stubClient);
SimpleParser parser = SimpleParser(&extractor);

TEST_CASE("parseLine print") {
    parser.statementNumber = 1;
    std::string code = "print test;";
    std::vector<std::string> test_tokens;
    test_tokens.push_back("print");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = parser.parseLine(code);
    SimpleToken expected_result = SimpleToken(SpTokenType::TPRINT, code,1);
    REQUIRE(equalToken(test_result, expected_result));
}

TEST_CASE("parseLine read") {
    parser.statementNumber = 1;
    std::string code = "read test;";
    std::vector<std::string> test_tokens;
    test_tokens.push_back("read");
    test_tokens.push_back("test");
    test_tokens.push_back(";");
    SimpleToken test_result = parser.parseLine(code);
    SimpleToken expected_result = SimpleToken(SpTokenType::TREAD, code,1);
    REQUIRE(equalToken(test_result, expected_result));
}

TEST_CASE("parse expr") {
    std::vector<std::string> test_tokens;
    test_tokens.push_back("(");
    test_tokens.push_back("1");
    test_tokens.push_back("+");
    test_tokens.push_back("1");
    test_tokens.push_back(")");
    SimpleToken test_result = parser.parseExpr(test_tokens);

    SimpleToken result = SimpleToken(SpTokenType::TEXPR, "", 0);

    std::vector<SimpleToken> resultTokens;
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
    result.setChildren(resultTokens);
    REQUIRE(equalChildren(test_result.getChildren(), result.getChildren()));
}

TEST_CASE("parse assign") {
    std::vector<std::string> test_tokens{ "a", "(", "1", "+","1", ")",";" };
    SimpleToken test = SimpleToken(SpTokenType::TASSIGN, "", 1);
    parser.parseAssign(test, test_tokens);

    std::vector<SimpleToken> children;
    std::vector<SimpleToken> resultTokens;
    SimpleToken result = SimpleToken(SpTokenType::TASSIGN, "", 1);
    children.push_back(SimpleToken(SpTokenType::TVARIABLE, "a", 0));
    SimpleToken expr = SimpleToken(SpTokenType::TEXPR, "", 0);
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
    expr.setChildren(resultTokens);
    children.push_back(expr);
    result.setChildren(children);

    REQUIRE(equalToken(test, result));
    REQUIRE(equalChildren(test.getChildren(), result.getChildren()));
}

TEST_CASE("parse while") {
    std::vector<std::string> test_tokens{ "(", "(", "(", "15", "<", "20", ")", "&&", "(", "abc", "==","10",")"
        , ")", "||", "(", "5", "<=", "10", ")", ")" , "{"};
    SimpleToken test = SimpleToken(SpTokenType::TWHILE, "", 1);
    parser.parseWhile(test, test_tokens);

    std::vector<SimpleToken> children;
    std::vector<SimpleToken> resultTokens;
    SimpleToken result = SimpleToken(SpTokenType::TWHILE, "", 1);
    SimpleToken expr = SimpleToken(SpTokenType::TCONDEXPR, "", 0);
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "15", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "20", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "10", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "5", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "10", 0));
    expr.setChildren(resultTokens);
    children.push_back(expr);
    result.setChildren(children);

    REQUIRE(equalToken(test, result));
    REQUIRE(equalChildren(test.getChildren(), result.getChildren()));
}

TEST_CASE("parse if") {
    std::vector<std::string> test_tokens{ "(", "(", "(", "15", "<", "20", ")", "&&", "(", "abc", "==","10",")"
        , ")", "||", "(", "5", "<=", "10", ")", ")" , "then", "{" };
    SimpleToken test = SimpleToken(SpTokenType::TIF, "", 1);
    parser.parseIf(test, test_tokens);

    std::vector<SimpleToken> children;
    std::vector<SimpleToken> resultTokens;
    SimpleToken result = SimpleToken(SpTokenType::TIF, "", 1);
    SimpleToken expr = SimpleToken(SpTokenType::TCONDEXPR, "", 0);
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "15", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "20", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "10", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "5", 0));
    resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "10", 0));
    expr.setChildren(resultTokens);
    children.push_back(expr);
    result.setChildren(children);

    REQUIRE(equalToken(test, result));
    REQUIRE(equalChildren(test.getChildren(), result.getChildren()));
}


TEST_CASE("parse read") {
    parser.statementNumber = 1;
    std::string code = "read test;";
    std::vector<std::string> tokens;
    tokens.push_back("test");
    tokens.push_back(";");
    SimpleToken test_token = SimpleToken(SpTokenType::TREAD, code,1);
    parser.parseRead(test_token, tokens);
    SimpleToken expected_children = SimpleToken(SpTokenType::TVARIABLE, "test", 
        0);
    std::vector<SimpleToken> expected_result;
    expected_result.push_back(expected_children);
    REQUIRE(equalChildren(test_token.getChildren(), expected_result));
}

TEST_CASE("parse print") {
    parser.statementNumber = 1;
    std::string code = "print test;";
    std::vector<std::string> tokens;
    tokens.push_back("test");
    tokens.push_back(";");
    SimpleToken test_token = SimpleToken(SpTokenType::TPRINT, code,1);
    parser.parsePrint(test_token, tokens);
    SimpleToken expected_children = SimpleToken(SpTokenType::TVARIABLE, "test",
        0);
    std::vector<SimpleToken> expected_result;
    expected_result.push_back(expected_children);
    REQUIRE(equalChildren(test_token.getChildren(), expected_result));
}
*/
