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
TEST_CASE("No declaration declared") {
    std::vector<TokenObject> test
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

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

TEST_CASE("Declarations with the same name and same design entity") {
    std::vector<TokenObject> test
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::COMMA, std::string(",")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

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

TEST_CASE("Declarations with the same name but different design entity") {
    std::vector<TokenObject> test
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::ASSIGN, std::string("assign")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v"))
    };

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

TEST_CASE("Return type not declared") {
    std::vector<TokenObject> test
        TokenObject(TokenType::VARIABLE, std::string("variable")),
        TokenObject(TokenType::NAME, std::string("v")),
        TokenObject(TokenType::SEMI_COLON, std::string(";")),
        TokenObject(TokenType::SELECT, std::string("Select")),
        TokenObject(TokenType::NAME, std::string("v1"))
    };

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

TEST_CASE("Such that with no declaration") {
    std::vector<TokenObject> test
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

TEST_CASE("Such that with param not declaration") {
    std::vector<TokenObject> test
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

TEST_CASE("Uses with wildcard as first parameter") {
    std::vector<TokenObject> test
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

TEST_CASE("Modifies where second param is not variable") {
    std::vector<TokenObject> test
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

TEST_CASE("Pattern with non-assign synonym") {
    std::vector<TokenObject> test
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

TEST_CASE("Pattern with no assign declaration") {
    std::vector<TokenObject> test
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

TEST_CASE("Pattern with param not declared") {
    std::vector<TokenObject> test
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

TEST_CASE("First param of pattern not variable") {
    std::vector<TokenObject> test
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
