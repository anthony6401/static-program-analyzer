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

// No SemanticError
TEST_CASE("Query with no such that or pattern clause") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Single clause queries - such that") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v")) };
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Single clause queries - such that Next") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::NEXT, TokenObject(TokenType::NAME, "call"),TokenObject(TokenType::NAME, "while")) };
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"call", DesignEntity::CALL}, {"while", DesignEntity::WHILE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Single clause queries - pattern") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}};
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Multi clause queries") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "p"),TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::SUBEXPRESSION, "_\"x\"_")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"p", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Multi clause queries where return type is not used in other clauses -  variable v, v1; call c; assign a; Select v such that Follows(c, _) pattern a(v1, _)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::FOLLOWS, TokenObject(TokenType::NAME, "c"),TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "v1"), TokenObject(TokenType::WILDCARD, "_")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"v1", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"c", DesignEntity::CALL} };
    int numOfDeclaredSynonyms = 4;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Uses with print as first parameter - variable v; print pn; Select v such that Uses(pn, v)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::NAME, "pn"), TokenObject(TokenType::NAME, "v")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"pn", DesignEntity::PRINT} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Modifies where first param is read statement - read r; Select r such that Modifies(r, _)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("r")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "r"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"r", DesignEntity::READ} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Calls where both parameters are procedures") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("r")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::NAME, "p"), TokenObject(TokenType::NAME, "q")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"r", DesignEntity::READ}, {"p", DesignEntity::PROCEDURE}, {"q", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 3;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Query returns boolean") {
    Select select = Select(TokenType::BOOLEAN, { TokenObject(TokenType::NAME, std::string("BOOLEAN")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::NAME, "p"), TokenObject(TokenType::NAME, "q")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"r", DesignEntity::READ}, {"p", DesignEntity::PROCEDURE}, {"q", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 3;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Query returns boolean but BOOLEAN is declared as synonym") {
    Select select = Select(TokenType::BOOLEAN, { TokenObject(TokenType::NAME, std::string("BOOLEAN")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::NAME, "p"), TokenObject(TokenType::NAME, "q")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"BOOLEAN", DesignEntity::READ}, {"p", DesignEntity::PROCEDURE}, {"q", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 3;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
    REQUIRE(validatedQuery.getSelect().getReturnType() == TokenType::SYNONYM);
};

TEST_CASE("Query returns tuple") {
    Select select = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("r")), TokenObject(TokenType::ATTRIBUTE, std::string("r.value")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::NAME, "p"), TokenObject(TokenType::NAME, "q")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"r", DesignEntity::READ}, {"p", DesignEntity::PROCEDURE}, {"q", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 3;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("SyntaxError - query should be deemed as semantically valid") {
    QueryObject testParsedQuery = QueryObject();

    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

// SemanticError
TEST_CASE("No declaration declared - Select v") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms;
    int numOfDeclaredSynonyms = 0;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Declarations with the same name and same design entity - variable v, v; Select v") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Declarations with the same name but different design entity - variable v; assign v; Select v") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Return type not declared - variable v; Select v1") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v1")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Return type not declared - if ifs; Select if") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("if")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"ifs", DesignEntity::IF} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Return type not declared - if ifs; Select <if>") {
    Select select = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("if")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"ifs", DesignEntity::IF} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Return type not declared - if ifs; Select <ifs, if>") {
    Select select = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("ifs")), TokenObject(TokenType::NAME, std::string("if")) });
    std::vector<SuchThat> suchThat;
    std::vector<qps::Pattern> pattern;
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"ifs", DesignEntity::IF} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();
    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Such that with no declaration - Select v such that Uses(6, v)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms;
    int numOfDeclaredSynonyms = 0;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Such that with param not declaration - variable v; Select v such that Uses(6, v1)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "6"),TokenObject(TokenType::NAME, "v1")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Uses with wildcard as first parameter - variable v; Select v such that Uses(_, v)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "v")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Uses with read as first parameter - variable v; read r; Select v such that Uses(r, v)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::NAME, "r"), TokenObject(TokenType::NAME, "v")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"r", DesignEntity::READ}};
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Modifies where second param is not variable - assign a; Select a such that Modifies(6, a)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "a")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Modifies where first param is print statement - print pn; Select pn such that Modifies(pn, _)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pn")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "pn"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"pn", DesignEntity::PRINT} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == true);
};

TEST_CASE("Parent where first param is not statement - procedure p; Select p such that Parent(p, _)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("p")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::PARENT, TokenObject(TokenType::NAME, "p"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"p", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};


TEST_CASE("Follows where second param is not statement - constant c; Select c such that Follows(c, _)") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("c")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::FOLLOWS, TokenObject(TokenType::NAME, "c"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"c", DesignEntity::CONSTANT} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Pattern with non-assign synonym - variable v; assign a; Select v pattern v(\"_\", \"x\")") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{};
    std::vector<qps::Pattern> pattern{ Pattern("v", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Pattern with no assign declaration variable v; Select v pattern a(\"_\", \"x\")") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{};
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Pattern with param not declared - variable v; assign a; Select v pattern a(s, \"x\")") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{};
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "s"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("First param of pattern not variable - variable v; assign a; Select v pattern a(a, \"x\")") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{};
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Parent takes in cosntant as param") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{SuchThat(TokenType::PARENT, TokenObject(TokenType::NAME, "c"), TokenObject(TokenType::WILDCARD, "_"))};
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"c", DesignEntity::CONSTANT}};
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};


TEST_CASE("Uses takes in cosntant as param") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::USES, TokenObject(TokenType::NAME, "c"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"c", DesignEntity::CONSTANT} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Modifies takes in cosntant as param") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "c"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<qps::Pattern> pattern{ Pattern("a", TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x")) };
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE}, {"a", DesignEntity::ASSIGN}, {"c", DesignEntity::CONSTANT} };
    int numOfDeclaredSynonyms = 2;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Calls* where first param is not proedure") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::CALLS_T,  TokenObject(TokenType::NAME, "v"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Calls where second param is not proedure") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::CALLS, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"a", DesignEntity::ASSIGN} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Next where second param is not statement") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::NEXT, TokenObject(TokenType::WILDCARD, "_"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"a", DesignEntity::PROCEDURE} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

TEST_CASE("Next* where first param is not statement") {
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> suchThat{ SuchThat(TokenType::NEXT_T, TokenObject(TokenType::NAME, "a"), TokenObject(TokenType::WILDCARD, "_")) };
    std::vector<Pattern> pattern{};
    std::unordered_map<std::string, DesignEntity> mappedSynonyms{ {"a", DesignEntity::CONSTANT} };
    int numOfDeclaredSynonyms = 1;

    QueryObject testParsedQuery = QueryObject(select, suchThat, pattern, mappedSynonyms, numOfDeclaredSynonyms);


    Validator validator = Validator(testParsedQuery);
    QueryObject validatedQuery = validator.validate();

    REQUIRE(validatedQuery.isSemanticallyValid() == false);
};

