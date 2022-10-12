#include <string>
#include <list>
#include <vector>
#include "components/qps/query_evaluator/Evaluator.h"
#include "components/qps/QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"

#include "catch.hpp"
#include <iostream>

// Valid queries
TEST_CASE("Query with single declaration and no such that or pattern clause") {
    std::string testQuery = "variable v; Select v";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Query with multiple declarations") {
    std::string testQuery = "stmt s, s1; variable v, v1; procedure p, q; assign a, a1; while w; if ifs; constant c; read re; print pn; call cl; Select re";
    
    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("re")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{
        {"s", DesignEntity::STMT}, {"s1", DesignEntity::STMT}, {"v", DesignEntity::VARIABLE},
        {"v1", DesignEntity::VARIABLE}, {"p", DesignEntity::PROCEDURE}, {"q", DesignEntity::PROCEDURE},
        {"a", DesignEntity::ASSIGN}, {"a1", DesignEntity::ASSIGN}, {"w", DesignEntity::WHILE},
        {"ifs", DesignEntity::IF}, {"c", DesignEntity::CONSTANT}, {"re", DesignEntity::READ},
        {"pn", DesignEntity::PRINT}, {"cl", DesignEntity::CALL}
    };
    int expectedNumOfDeclaredSynonyms = 14;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Query with synonyms in declaration clause with same name as design entity") {
    std::string testQuery = "variable variable; Select variable";
    
    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("variable")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Modifies Relationship with integer") {
    std::string testQuery = "variable v;\n"
        "Select v such that Modifies (6, v)";


    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("v")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::MODIFIES, TokenObject(TokenType::INTEGER, "6"),
                                                    TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Uses Relationship with integer") {
    std::string testQuery = "assign a;\n"
        "Select a such that Uses (2, \"x\")";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "2"),
                                                    TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern used as name") {
    std::string testQuery = "variable v; assign pattern; Select pattern pattern pattern(v, \"expr\")";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("pattern")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "pattern", TokenObject(TokenType::NAME, "v"), TokenObject(TokenType::NAME_WITH_QUOTATION, "expr"))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE},  {"pattern", DesignEntity::ASSIGN}};
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}
TEST_CASE("SemanticError - if ifs; Select if") {
    std::string testQuery = "if ifs; Select if";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("if")) });
    std::vector<SuchThat> expectedSuchThat;
    std::vector<Pattern> expectedPattern;
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"ifs", DesignEntity::IF} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);

    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
    
    REQUIRE(testResult == expectedResult);
};

TEST_CASE("Follows Relationship") {
    std::string testQuery = "stmt s1;\n"
        "Select s1 such that Follows (6, s1)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("s1")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::FOLLOWS, TokenObject(TokenType::INTEGER, "6"),
                                                    TokenObject(TokenType::NAME, "s1"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"s1", DesignEntity::STMT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Follows* Relationship") {
    std::string testQuery = "stmt s;\n"
        "Select s such that Follows* (6, s)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("s")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "s"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"s", DesignEntity::STMT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Parent Relationship") {
    std::string testQuery = "stmt s;\n"
        "Select s such that Parent (s, 6)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("s")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::PARENT, TokenObject(TokenType::NAME, "s"), TokenObject(TokenType::INTEGER, "6")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"s", DesignEntity::STMT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Parent* Relationship") {
    std::string testQuery = "assign a; while w;\n"
        "Select a such that Parent* (w, a)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::PARENT_T, TokenObject(TokenType::NAME, "w"), TokenObject(TokenType::NAME, "a")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a", DesignEntity::ASSIGN}, {"w", DesignEntity::WHILE}, };
    int expectedNumOfDeclaredSynonyms = 2;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with expressions and subexpressions") {
    std::string testQuery = "assign newa;\n"
        "Select newa pattern newa ( \"normSq\" , _\"cenX\"_)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("newa")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{Pattern(TokenType::ASSIGN, "newa", TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq"), TokenObject(TokenType::SUBEXPRESSION, "cenX"))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"newa", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Queries with synonyms as design entities") {
    std::string testQuery = "assign variable;\n"
        "Select variable pattern variable ( \"normSq\" , _\"cenX\"_)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("variable")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "variable", TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq"), TokenObject(TokenType::SUBEXPRESSION, "cenX")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with constant expressions") {
    std::string testQuery = "assign newa;\n"
        "Select newa pattern newa ( \"normSq\" , \"1\")";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("newa")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "newa", TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq"), TokenObject(TokenType::EXPRESSION, "1")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"newa", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with constant subexpressions") {
    std::string testQuery = "assign a1;\n"
        "Select a1 pattern a1 ( \"x\" , _\"11\"_)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("a1")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "a1", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::SUBEXPRESSION, "11")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"a1", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Capital letter synonyms") {
    std::string testQuery = "stmt Statement;\n"
        "Select Statement such that Parent (s, 6)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("Statement")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::PARENT, TokenObject(TokenType::NAME, "s"), TokenObject(TokenType::INTEGER, "6"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"Statement", DesignEntity::STMT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Capital letter design entity synonyms ") {
    std::string testQuery = "variable Variable;\n"
        "Select Variable such that Modifies (6, Variable)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("Variable")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::MODIFIES, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "Variable"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"Variable", DesignEntity::VARIABLE} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}



//// Invalid tokens
TEST_CASE("Invalid name token") {
    std::string testQuery = "assign 0x1;\n";

    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid integer token") {
    std::string testQuery = "stmt s;\n"
        "Select s such that Parent (s, 01)";
    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid expression token") {
    std::string testQuery = "assign a1;\n"
        "Select s such that Uses (s, \"x\") pattern a (\"x\", \"y)";
    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid subexpression token") {
    std::string testQuery = "assign a1;\n"
        "Select s such that Uses (s, \"x\") pattern a (_\"x\", _\"y\"_)";
    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid symbols token") {
    std::string testQuery = "assign *;\n"
        "Select * such that Uses (*, \"x\")";
    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid name token - start w digit") {
    std::string testQuery = "assign 1assign;\n"
        "Select * such that Uses (1assign, \"x\")";
    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid subexpression token - start with non-alphanumerical") {
    std::string testQuery = "assign a; Select a pattern a (_, _\" +temp\"_)";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid expression token - start with non-alphanumerical") {
    std::string testQuery = "assign a; Select a pattern a (_, \" +temp\")";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid name token - start with non-alphanumerical") {
    std::string testQuery = "assign +temp; Select +temp";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid attribute token - undefined attribute name") {
    std::string testQuery = "assign a; Select a.stmt";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid attribute token - invalid attribute name") {
    std::string testQuery = "assign a; Select a.1";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid tuple token - invalid attribute") {
    std::string testQuery = "assign a1; Select <a1.assignName>";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid tuple token - missing attribute name") {
    std::string testQuery = "assign a1; Select <a1., a1>";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid tuple token - missing attribute synonym") {
    std::string testQuery = "assign a1; Select <.stmt#>";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid tuple token - empty tuple") {
    std::string testQuery = "assign a1; Select < >";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid tuple token - missing commas") {
    std::string testQuery = "assign a1; Select <a1.stmt# a1.stmt# >";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}


//// Edge cases
TEST_CASE("Presence of white spaces") {
    std::string testQuery = "stmt       s;    \n"
        "Select s    such   that Follows*    (6,   s)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("s")) });
    std::vector<SuchThat> expectedSuchThat{SuchThat(TokenType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "s"))};
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"s", DesignEntity::STMT} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Presence of white spaces in Name with Quotes and Subexpressions") {
    std::string testQuery = "assign newa;\n"
        "Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("newa")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "newa", TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq"), TokenObject(TokenType::SUBEXPRESSION, "cenX")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"newa", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Single line queries with space") {
    std::string testQuery = "assign newa; Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("newa")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{ Pattern(TokenType::ASSIGN, "newa", TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq"), TokenObject(TokenType::SUBEXPRESSION, "cenX")) };
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"newa", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Single line queries without space") {
    std::string testQuery = "assign newa;Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";

    Select expectedSelect = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, std::string("newa")) });
    std::vector<SuchThat> expectedSuchThat{};
    std::vector<Pattern> expectedPattern{Pattern(TokenType::ASSIGN, "newa", TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq"), TokenObject(TokenType::SUBEXPRESSION, "cenX"))};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"newa", DesignEntity::ASSIGN} };
    int expectedNumOfDeclaredSynonyms = 1;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Presence of white spaces in tuple") {
    std::string testQuery = "call       c;   stmt s ; print  pn; "
        "Select <s    ,c\n.    procName,       c.stmt#   ,pn, pn        .varName          >   such   that Follows*    (6,   s)";

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::NAME, std::string("s")), 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("procName")), 
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("stmt#")), 
        TokenObject(TokenType::NAME, std::string("pn")),
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("pn")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "s")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"c", DesignEntity::CALL}, {"s", DesignEntity::STMT}, {"pn", DesignEntity::PRINT}};
    int expectedNumOfDeclaredSynonyms = 3;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("No comma in tuple") {
    std::string testQuery = "call       c;   stmt s ; print  pn; "
        "Select <s    c\n.    procName,       c.stmt#   ,pnpn        .varName          >   such   that Follows*    (6,   s)";

    Select expectedSelect = Select(TokenType::TUPLE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("sc")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("procName")),
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("c")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("stmt#")),
        TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("pnpn")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "s")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"c", DesignEntity::CALL}, {"s", DesignEntity::STMT}, {"pn", DesignEntity::PRINT} };
    int expectedNumOfDeclaredSynonyms = 3;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Presence of white spaces in attribute") {
    std::string testQuery = "call       c;   stmt s ; print pn; "
        "Select  pn     \n   .varName            such   that Follows*    (6,   s)";

    Select expectedSelect = Select(TokenType::ATTRIBUTE, { TokenObject(TokenType::ATTRIBUTE_SYNONYM, std::string("pn")), TokenObject(TokenType::ATTRIBUTE_NAME,  std::string("varName")) });
    std::vector<SuchThat> expectedSuchThat{ SuchThat(TokenType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "6"), TokenObject(TokenType::NAME, "s")) };
    std::vector<Pattern> expectedPattern{};
    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"c", DesignEntity::CALL}, {"s", DesignEntity::STMT}, {"pn", DesignEntity::PRINT} };
    int expectedNumOfDeclaredSynonyms = 3;

    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);

    REQUIRE(testResult == expectedResult);
}


// SyntaxError
TEST_CASE("SyntaxError - missing attribute synonym that passes tokenizer checks ") {
    std::string testQuery = "variable v; Select          .varName";

    QueryObject expectedResult = QueryObject();
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("SyntaxError - extra result clause") {
    std::string testQuery = "variable v;Select     v AND   v .varName";

    QueryObject expectedResult = QueryObject();
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("SyntaxError - extra result clause without AND") {
    std::string testQuery = "variable v;Select     v   v .varName";

    QueryObject expectedResult = QueryObject();
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("SyntaxError - attributes used in such that clause") {
    std::string testQuery = "stmt s;Select  s  such   that Follows*    (6,   s  .stmt#)";

    QueryObject expectedResult = QueryObject();
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

TEST_CASE("SyntaxError - missing brackets in tuple") {
    std::string testQuery = "assign a1; Select a1, a1.stmt# ";

    QueryObject expectedResult = QueryObject();
    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);


    REQUIRE(testResult == expectedResult);
}

