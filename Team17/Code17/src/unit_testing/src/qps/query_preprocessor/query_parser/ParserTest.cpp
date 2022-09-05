#include "components/qps/query_preprocessor/query_parser/Parser.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"

#include <catch.hpp>
#include <components/qps/query_preprocessor/query_parser/Parser.cpp>
#include <unordered_map>

// Tests for Parser
TEST_CASE("Initialize Parser") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Parser parser = Parser(testTokenObject);
    REQUIRE(parser.getTokenizedQuery() == testTokenObject);
};

TEST_CASE("Parse queries") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat {};
    std::vector<Pattern> expectedPattern {};
    std::unordered_map<std::string, TokenType> expectedMappedSynonyms{ {"v", TokenType::VARIABLE} };

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("No declaration") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Select expectedSelect = Select();
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, TokenType> expectedMappedSynonyms;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - No return value") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select"))
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - Select clause ends in semi-colon") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";"))
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - No Select token") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::NAME, std::string("v")),
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - SyntaxError in declarations") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};