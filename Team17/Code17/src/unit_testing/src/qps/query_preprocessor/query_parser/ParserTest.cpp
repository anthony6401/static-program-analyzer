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
#include <iostream>

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
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Variable name same as variable design entity") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::VARIABLE, std::string("variable"))
    };

    Select expectedSelect = Select("variable");
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE} };

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - such that") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };

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

TEST_CASE("SyntaxError - Such that clause ends in semi-colon") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
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

TEST_CASE("SyntaxError - SyntaxError in such that clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

// Semantic Error tests - tests should pass as they are syntactically correct
TEST_CASE("No declaration") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Select expectedSelect = Select();
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - such that with no declaration") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select();
    std::vector<SuchThat> expectedSuchThat{ SuchThat() };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};
