#include "components/qps/query_preprocessor/query_parser/Parser.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/abstract_query_object/QueryObject.h"
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("variable")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Boolean return type") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::BOOLEAN, std::string("BOOLEAN"))
    };

    Select expectedSelect = Select(TokenType::BOOLEAN, { TokenObject(TokenType::NAME, std::string("BOOLEAN")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Attribute return type") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, std::string("variable.varName"))
    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("variable")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Attribute return type - synonym name same as attrName") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::CONSTANT, std::string("constant")),
        TokenObject(TokenType::NAME, std::string("value")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, std::string("value.value"))
    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("value")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("value")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"value", DesignEntity::CONSTANT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
    REQUIRE(actualResult.isSyntacticallyCorrect() == true);
};

TEST_CASE("Tuple return type - only synonyms") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<variable,v>"))
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("variable")), TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

};

TEST_CASE("Tuple return type - only a single synonyms") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<variable>"))
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("variable")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Tuple return type - only attributes") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<variable.varName,v.varName>"))
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("variable")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")), 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Tuple return type - only a single attribute") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<variable.varName>"))
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("variable")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Tuple return type - attributes and synonyms") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::VARIABLE, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<variable.varName,v,variable,v.varName>"))
    };

    Select expectedSelect = Select(TokenType::TUPLE, { 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("variable")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")), 
        TokenObject(TokenType::NAME, std::string("v")), TokenObject(TokenType::NAME, std::string("variable")), 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, "such") });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "such")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"such", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - new Calls relationship") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "proc"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::CALL, "call"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("call")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::NAME_WITH_QUOTATION, "proc"), TokenObject(TokenType::NAME, "call")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"call", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    std::cout << actualResult.isSyntacticallyCorrect();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - new Next relationship") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::STMT, std::string("stmt")),
        TokenObject(TokenType::SUCH, std::string("such")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };
    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, "such") });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::NEXT, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "such")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"such", DesignEntity::STMT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << actualResult.isSyntacticallyCorrect();

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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pattern")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"pattern", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - while pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::WHILE, std::string("while")),
        TokenObject(TokenType::NAME, std::string("w")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "w"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pattern")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::WHILE, "w", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"pattern", DesignEntity::VARIABLE}, {"w", DesignEntity::WHILE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - assign pattern with while syntax") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("w")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "w"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pattern")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::WHILE, "w", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"pattern", DesignEntity::VARIABLE}, {"w", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - if pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::IF, std::string("if")),
        TokenObject(TokenType::NAME, std::string("w")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "w"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pattern")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::IF, "w", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"pattern", DesignEntity::VARIABLE}, {"w", DesignEntity::IF} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - with clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::NAME, std::string("c")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "v.varName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::vector<With> expectedWith{ With(TokenType::NAME, TokenType::NAME, 
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName"))}, 
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"c", DesignEntity::CALL} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Single clause query - with clause and synonym name of return type is with") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::NAME, std::string("c")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("with")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::vector<With> expectedWith{ With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::NAME_WITH_QUOTATION, std::string("v"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"with", DesignEntity::VARIABLE}, {"c", DesignEntity::CALL} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("Single clause query - with clause where with is used in attribute") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CONSTANT, std::string("constant")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "3"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "with.value")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::vector<With> expectedWith{ With(TokenType::INTEGER, TokenType::INTEGER,
        {TokenObject(TokenType::INTEGER, std::string("3"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("value"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"with", DesignEntity::CONSTANT} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

}


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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("variable")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "variable")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "assign", TokenObject(TokenType::NAME, std::string("variable")), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE}, {"assign", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("Select")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "such")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "assign", TokenObject(TokenType::NAME, std::string("Follows")), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"such", DesignEntity::VARIABLE}, {"Follows", DesignEntity::VARIABLE}, {"Select", DesignEntity::VARIABLE},{"assign", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 4;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Muti-clause query - synonym name is same as new Calls and Next tokens") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::CALLS, std::string("Calls")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::NEXT, std::string("Next")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NEXT, std::string("Next")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::CALLS, std::string("Calls")),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NEXT, std::string("Next")),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("Next")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "Calls")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "assign", TokenObject(TokenType::NAME, std::string("Next")), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"Calls", DesignEntity::VARIABLE}, {"Next", DesignEntity::VARIABLE}, {"Select", DesignEntity::VARIABLE},{"assign", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 4;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << (actualResult.getRelationships().at(0).getRight().getTokenType() == TokenType::VARIABLE);

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - return type is not used in other clauses") {
    std::vector<TokenObject> testTokenObject{
    TokenObject(TokenType::VARIABLE, std::string("variable")),
    TokenObject(TokenType::NAME, std::string("v")),
    TokenObject(TokenType::COMMA, std::string(",")),
    TokenObject(TokenType::NAME, std::string("v1")),
    TokenObject(TokenType::SEMI_COLON, std::string(";")),
    TokenObject(TokenType::ASSIGN, std::string("assign")),
    TokenObject(TokenType::NAME, std::string("a")),
    TokenObject(TokenType::SEMI_COLON, std::string(";")),
    TokenObject(TokenType::CALL, std::string("call")),
    TokenObject(TokenType::NAME, std::string("c")),
    TokenObject(TokenType::SEMI_COLON, std::string(";")),
    TokenObject(TokenType::SELECT, std::string("Select")),
    TokenObject(TokenType::NAME, std::string("v")),
    TokenObject(TokenType::SUCH, "such"),
    TokenObject(TokenType::THAT, "that"),
    TokenObject(TokenType::FOLLOWS, "Follows"),
    TokenObject(TokenType::OPEN_BRACKET, "("),
    TokenObject(TokenType::INTEGER, "6"),
    TokenObject(TokenType::COMMA, ","),
    TokenObject(TokenType::WILDCARD, std::string("_")),
    TokenObject(TokenType::CLOSED_BRACKET, ")"),
    TokenObject(TokenType::PATTERN, "pattern"),
    TokenObject(TokenType::NAME, std::string("a")),
    TokenObject(TokenType::OPEN_BRACKET, "("),
    TokenObject(TokenType::NAME, std::string("v1")),
    TokenObject(TokenType::COMMA, ","),
    TokenObject(TokenType::EXPRESSION, "expr"),
    TokenObject(TokenType::CLOSED_BRACKET, ")")
    };


    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::FOLLOWS, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME, "v1"), TokenObject(TokenType::EXPRESSION, "expr")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"v1", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"c", DesignEntity::CALL} };
    int expectedNumOfDeclaredSynonyms = 4;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than one such that") {
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")), 
        SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}};
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than 2 and clauses") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::WHILE, std::string("while")),
        TokenObject(TokenType::NAME, std::string("w")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::MODIFIES, "Modifies"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PARENT_T, "Parent*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "w"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NEXT_T, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        SuchThat(TokenType::PARENT_T, TokenObject(TokenType::NAME, "w"), TokenObject(TokenType::NAME, "a")), 
        SuchThat(TokenType::NEXT_T, TokenObject(TokenType::INTEGER, "1"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"w", DesignEntity::WHILE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();


    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than one such that with and clause") {
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
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")),
        SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - 2 such that with 1 pattern in the middle") {
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")),
        SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - and as select synonym") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::AND, std::string("and")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::PATTERN, std::string("pattern")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::AND, std::string("and")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("and")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "and"))};
    std::vector<Pattern> expectedPattern{Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")), 
        Pattern(TokenType::ASSIGN, "pattern", TokenObject(TokenType::NAME, "pattern"), TokenObject(TokenType::EXPRESSION, "x")),
        Pattern(TokenType::ASSIGN, "and", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::ASSIGN}, {"and", DesignEntity::ASSIGN}, {"pattern", DesignEntity::ASSIGN}, };
    int expectedNumOfDeclaredSynonyms = 3;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
    
};

TEST_CASE("Multi clause query - pattern and such that clause with same pattern and such that clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::USES, std::string("Uses")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
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
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        SuchThat(TokenType::USES, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")), 
        Pattern(TokenType::ASSIGN, "pattern", TokenObject(TokenType::NAME, "pattern"), TokenObject(TokenType::EXPRESSION, "x")),
        Pattern(TokenType::ASSIGN, "Uses", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"Uses", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 3;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - 2 pattern clause 1 such that clause in the middle") {
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")), 
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than one pattern") {
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than one pattern using and clause") {
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
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than 2 and clause for pattern") {
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
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")), 
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than 2 and clause for pattern with new return type") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<v.varName,v,a,a,v,a.value>")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")),
        TokenObject(TokenType::NAME, std::string("v")), TokenObject(TokenType::NAME, std::string("a")), 
        TokenObject(TokenType::NAME, std::string("a")), TokenObject(TokenType::NAME, std::string("v")), 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("a")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("value")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than one pattern clause with different pattern types") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::IF, std::string("if")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::IF, std::string("if")),
        TokenObject(TokenType::WHILE, std::string("while")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::WHILE, std::string("while")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<v.varName,v,a,a,v,a.value>")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::IF, "if"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::ASSIGN, "assign"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::WHILE, "while"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")),
        TokenObject(TokenType::NAME, std::string("v")), TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::NAME, std::string("a")), TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("a")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("value")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "if", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::WHILE, "assign", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::WILDCARD, "_")), 
        Pattern(TokenType::IF, "while", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"if", DesignEntity::ASSIGN}, {"while", DesignEntity::IF}, {"assign", DesignEntity::WHILE}};
    int expectedNumOfDeclaredSynonyms = 4;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Multi clause query - more than one instance of with clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::NAME, std::string("c")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "with.varName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "4"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.stmt#")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("with")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::vector<With> expectedWith{ With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}), 
        With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::NAME_WITH_QUOTATION, std::string("v"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}), 
        With(TokenType::INTEGER, TokenType::INTEGER,
        {TokenObject(TokenType::INTEGER, std::string("4"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("stmt#"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"with", DesignEntity::VARIABLE}, {"c", DesignEntity::CALL} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("Multi clause query - more than one instance of with clause using and") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::NAME, std::string("c")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, "with.varName"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "with.varName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::INTEGER, "4"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.stmt#")

    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::vector<With> expectedWith{ With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}),
        With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::NAME_WITH_QUOTATION, std::string("v"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}),
        With(TokenType::INTEGER, TokenType::INTEGER,
        {TokenObject(TokenType::INTEGER, std::string("4"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("stmt#"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"with", DesignEntity::VARIABLE}, {"c", DesignEntity::CALL} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("Multi clause query - more than one instance of with clause using and and with") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::NAME, std::string("c")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, "<with.varName,with,c.stmt#,c.procName,c>"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "with.varName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "4"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.stmt#")

    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")), 
        TokenObject(TokenType::NAME, std::string("with")), TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("stmt#")), 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName")), TokenObject(TokenType::NAME, std::string("c")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::vector<With> expectedWith{ With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}),
        With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::NAME_WITH_QUOTATION, std::string("v"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}),
        With(TokenType::INTEGER, TokenType::INTEGER,
        {TokenObject(TokenType::INTEGER, std::string("4"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("stmt#"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"with", DesignEntity::VARIABLE}, {"c", DesignEntity::CALL} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("Multi clause query - multiple such that, pattern and with clauses") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::NAME, std::string("c")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "with.varName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::MODIFIES, "Modifies"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PARENT_T, "Parent*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "w"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::INTEGER, "4"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.stmt#"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT_T, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("with")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        SuchThat(TokenType::PARENT_T, TokenObject(TokenType::NAME, "w"), TokenObject(TokenType::NAME, "a")),
        SuchThat(TokenType::NEXT_T, TokenObject(TokenType::INTEGER, "1"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")),
        Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::vector<With> expectedWith{ With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("with")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}),
        With(TokenType::NAME, TokenType::NAME,
        {TokenObject(TokenType::NAME_WITH_QUOTATION, std::string("v"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("procName"))}),
        With(TokenType::INTEGER, TokenType::INTEGER,
        {TokenObject(TokenType::INTEGER, std::string("4"))},
        {TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("stmt#"))}) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"with", DesignEntity::VARIABLE}, {"c", DesignEntity::CALL}, {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 4;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedWith, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);

}

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

TEST_CASE("SyntaxError - Return value is not a synonym") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::INTEGER, std::string("5"))
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

TEST_CASE("SyntaxError - Invalid return clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::INTEGER, std::string("1"))
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

TEST_CASE("SyntaxError - invalid second parameter for if pattern clause") {
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
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - invalid third parameter for if pattern clause") {
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
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - and followed by such that clause instead of pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::USES, std::string("Uses")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
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
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("SyntaxError - and followed by pattern clause instead of such that clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::USES, std::string("Uses")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
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

TEST_CASE("SyntaxError - invalid and clause for such that") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::USES, std::string("Uses")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
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
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
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

TEST_CASE("SyntaxError - invalid and clause for pattern") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::USES, std::string("Uses")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
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
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
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

TEST_CASE("SyntaxError - invalid ref for with clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "with.procName")

    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("SyntaxError - missing with token for with clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "with.procName")

    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("SyntaxError - with clause with missing return clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "with.procName")

    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("SyntaxError - with clause with missing equals") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::ATTRIBUTE, "with.procName")

    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);

}

TEST_CASE("SyntaxError - with clause invalid and clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::CALL, std::string("call")),
        TokenObject(TokenType::WITH, std::string("with")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "with.procName"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "with.procName")

    };

    QueryObject expectedResult = QueryObject();

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);

}

// Semantic Error tests - tests should pass as they are syntactically correct
TEST_CASE("No declaration") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("if ifs; Select if") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::IF, std::string("if")),
        TokenObject(TokenType::NAME, std::string("ifs")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("if"))
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("if")) });
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"ifs", DesignEntity::IF} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Pattern used as name") {
    //std::string testQuery = "variable v; assign pattern; Select pattern pattern pattern(v, \"expr\")";
    std::vector<TokenObject> testTokenObject{
    TokenObject(TokenType::VARIABLE, std::string("variable")),
    TokenObject(TokenType::NAME, std::string("v")),
    TokenObject(TokenType::SEMI_COLON, std::string(";")),
    TokenObject(TokenType::ASSIGN, std::string("assign")),
    TokenObject(TokenType::PATTERN, std::string("pattern")),
    TokenObject(TokenType::SEMI_COLON, std::string(";")),
    TokenObject(TokenType::SELECT, std::string("Select")),
    TokenObject(TokenType::PATTERN, std::string("pattern")),
    TokenObject(TokenType::PATTERN, std::string("pattern")),
    TokenObject(TokenType::PATTERN, std::string("pattern")),
    TokenObject(TokenType::OPEN_BRACKET, std::string("(")),
    TokenObject(TokenType::NAME, std::string("v")),
    TokenObject(TokenType::COMMA, std::string(",")),
    TokenObject(TokenType::NAME_WITH_QUOTATION, std::string("\"expr\"")),
    TokenObject(TokenType::CLOSED_BRACKET, std::string(")")),
    };


    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pattern")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{qps::Pattern(TokenType::ASSIGN, "pattern", TokenObject(TokenType::NAME, "v"),
                                                      TokenObject(TokenType::NAME_WITH_QUOTATION, "\"expr\""))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"pattern", DesignEntity::ASSIGN},
                                                                          {"v", DesignEntity::VARIABLE}};
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
}

TEST_CASE("Semantically incorrect - return type not declared") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v1"))
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v1")) });
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v")) };
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v1")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- Uses with wildcard as first parameter") {
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
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- Modifies where second param is not variable") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- Calls* where first param is not proedure") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS_T, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::CALLS_T,  TokenObject(TokenType::NAME, "v"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << actualResult.isSyntacticallyCorrect();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- Calls where second param is not proedure") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << actualResult.isSyntacticallyCorrect();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- Next where second param is not statement") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::PROCEDURE, std::string("procedure")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::NEXT, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::PROCEDURE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << actualResult.isSyntacticallyCorrect();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorect- Next* where first param is not statement") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::CONSTANT, std::string("constant")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT_T, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::NEXT_T, TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::CONSTANT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();
    std::cout << actualResult.isSyntacticallyCorrect();

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
 
    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "v", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}};
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - pattern with no assign declaration") {
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

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
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
    
    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME, "s"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - first param of pattern not variable") {
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
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - synonym in result clause not declared") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v1")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v1")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - synonym in tuple result clause not declared") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::TUPLE, std::string("<v1>")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("v1")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - synonym in attribute result clause not declared") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, std::string("v1.varName")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v1")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - attribute name does not match attribute synonym") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, std::string("v.stmt#")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("stmt#")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - non-if synonym for if pattern clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, std::string("v.varName")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::IF, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "a"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Semantically incorrect - non-while synonym for while pattern clause") {
    std::vector<TokenObject> testTokenObject{
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::IF, std::string("if")),
        TokenObject(TokenType::NAME, std::string("a")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::ATTRIBUTE, std::string("v.varName")),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("v")), TokenObject(TokenType::ATTRIBUTE_NAME, std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::WHILE, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "a"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::IF} };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    Parser parser = Parser(testTokenObject);
    QueryObject actualResult = parser.parse();

    REQUIRE(expectedResult == actualResult);
};
