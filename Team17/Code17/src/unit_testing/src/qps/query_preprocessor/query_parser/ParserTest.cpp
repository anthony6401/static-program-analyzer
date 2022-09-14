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

TEST_CASE("Parse queries with no such that or pattern clause") {
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
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

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
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

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
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - such that with variable name such") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SUCH, std::string("such")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select("such");
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "such")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"such", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}};
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - pattern with synonym name pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select("pattern");
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"pattern", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
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
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Muti-clause query - synonym name is same as design entity") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select("variable");
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "variable")) };
    std::vector<Pattern> expectedPattern{ Pattern("assign", TokenObject(TokenType::NAME, std::string("variable")), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"assign", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << (actualResult.getRelationships().at(0).getRight().getTokenType() == TokenType::VARIABLE);

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Muti-clause query - synonym name is same as other clause tokens") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SUCH, std::string("such")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::FOLLOWS, std::string("Follows")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUCH, std::string("such")),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::FOLLOWS, std::string("Follows")),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select("Select");
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "such")) };
    std::vector<Pattern> expectedPattern{ Pattern("assign", TokenObject(TokenType::NAME, std::string("Follows")), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"such", DesignEntity::VARIABLE}, {"Follows", DesignEntity::VARIABLE}, {"Select", DesignEntity::VARIABLE},{"assign", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 4;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << (actualResult.getRelationships().at(0).getRight().getTokenType() == TokenType::VARIABLE);

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

TEST_CASE("SyntaxError - SyntaxError in pattern clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - more than one such that") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
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
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - more than one pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
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
    int expectedNumOfDeclaredSynonyms = 0;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multiple declarations with the same name and same design entity") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multiple declarations with the same name but different design entity") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - such that with no declaration") {
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
    int expectedNumOfDeclaredSynonyms = 0;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- such that with param not declaration") {
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
        TokenObject(TokenType::NAME, "v1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{ SuchThat() };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - pattern with non-assign synonym") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern{} };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}};
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - no assign declaration") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{Pattern()};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}};
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - pattern with param not declared") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "s"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    Select expectedSelect = Select("v");
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern{} };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};
