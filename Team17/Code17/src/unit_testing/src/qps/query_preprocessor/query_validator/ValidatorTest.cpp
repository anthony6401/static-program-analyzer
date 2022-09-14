#include "components/qps/query_preprocessor/query_validator/Validator.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"

#include <catch.hpp>
#include <unordered_map>
#include <iostream>

// SemanticError
TEST_CASE("No declaration declared - Select v") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat;
    std::vector<Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms;
    int numOfDeclaredSynonyms = 0;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Declarations with the same name and same design entity - variable v, v; Select v") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat;
    std::vector<Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Declarations with the same name but different design entity - variable v; assign v; Select v") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat;
    std::vector<Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Return type not declared - variable v; Select v1") {
    Select select = Select("v1");
    std::vector<SuchThat> suchThat;
    std::vector<Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();
    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Such that with no declaration - Select v such that Uses(6, v)") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms;
    int numOfDeclaredSynonyms = 0;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Such that with param not declaration - variable v; Select v such that Uses(6, v1)") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v1")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Uses with wildcard as first parameter - variable v; Select v such that Uses(_, v)") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "v")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Modifies where second param is not variable - assign a; Select a such that Uses(6, a)") {
    Select select = Select("a");
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Pattern with non-assign synonym - variable v; assign a; Select v pattern v(\"_\", \"x\")") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat{};
    std::vector<Pattern> pattern{ Pattern("v", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Pattern with no assign declaration variable v; Select v pattern v(\"_\", \"x\")") {
    Select select = Select("v");
    std::vector<SuchThat> suchThat{};
    std::vector<Pattern> pattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("Pattern with param not declared - variable v; assign a; Select v pattern v(s, \"x\")") {
Select select = Select("v");
    std::vector<SuchThat> suchThat{};
    std::vector<Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "s"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};

TEST_CASE("First param of pattern not variable - variable v; assign a; Select v pattern v(a, \"x\")") {
 Select select = Select("v");
    std::vector<SuchThat> suchThat{};
    std::vector<Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);
    QueryObject expectedResult = testParsedQuery.setSemanticallyInvalid();

    Validator validator = Validator(testParsedQuery);
    QueryObject actualResult = validator.validate();

    REQUIRE(expectedResult == actualResult);
};
