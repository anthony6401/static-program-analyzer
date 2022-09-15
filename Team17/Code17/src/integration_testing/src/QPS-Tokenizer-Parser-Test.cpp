#include <string>
#include <list>
#include <vector>
#include "components/qps/query_evaluator/Evaluator.h"
#include "components/qps/QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"

#include "catch.hpp"
#include <iostream>

// Valid queries
//TEST_CASE("Query with single declaration and no such that or pattern clause") {
//    std::string testQuery = "variable v; Select v";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Query with multiple declarations") {
//    std::string testQuery = "stmt s, s1; variable v, v1; procedure p, q; assign a, a1; while w; if ifs; constant c; read re; print pn; call cl; Select re";
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ 
//        {"s", DesignEntity::STMT}, {"s1", DesignEntity::STMT}, {"v", DesignEntity::VARIABLE}, 
//        {"v1", DesignEntity::VARIABLE}, {"p", DesignEntity::PROCEDURE}, {"q", DesignEntity::PROCEDURE}, 
//        {"a", DesignEntity::ASSIGN}, {"a1", DesignEntity::ASSIGN}, {"w", DesignEntity::WHILE}, 
//        {"ifs", DesignEntity::IF}, {"c", DesignEntity::CONSTANT}, {"re", DesignEntity::READ}, 
//        {"pn", DesignEntity::PRINT}, {"cl", DesignEntity::CALL}
//    };
//    int expectedNumOfDeclaredSynonyms = 14;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Query with synonyms in declaration clause with same name as design entity") {
//    std::string testQuery = "variable variable; Select variable";
//    Select expectedSelect = Select("variable");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"variable", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Modifies Relationship with integer") {
//    std::string testQuery = "variable v;\n"
//        "Select v such that Modifies (6, v)";
// 
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Uses Relationship with integer") {
//    std::string testQuery = "variable v;\n"
//        "Select v such that Uses (14, v)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Follows Relationship") {
//    std::string testQuery = "stmt s;\n"
//        "Select s such that Follows (6, s)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Follows* Relationship") {
//    std::string testQuery = "stmt s;\n"
//        "Select s such that Follows* (6, s)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Parent Relationship") {
//    std::string testQuery = "stmt s;\n"
//        "Select s such that Parent (s, 6)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Parent* Relationship") {
//    std::string testQuery = "assign a; while w;\n"
//        "Select a such that Parent* (w, a)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Pattern Clause with expressions and subexpressions") {
//    std::string testQuery = "assign newa;\n"
//        "Select newa pattern newa ( \"normSq\" , _\"cenX\"_)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Queries with synonyms as design entities") {
//    std::string testQuery = "assign variable;\n"
//        "Select variable pattern variable ( \"normSq\" , _\"cenX\"_)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Pattern Clause with constant expressions") {
//    std::string testQuery = "assign newa;\n"
//        "Select newa pattern newa ( \"normSq\" , \"1\")";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Pattern Clause with constant subexpressions") {
//    std::string testQuery = "assign a1;\n"
//        "Select a1 pattern a1 ( \"x\" , _\"11\"_)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Capital letter synonyms") {
//    std::string testQuery = "stmt Statement;\n"
//        "Select Statement such that Parent (s, 6)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Capital letter design entity synonyms ") {
//    std::string testQuery = "variable Variable;\n"
//        "Select Variable such that Modifies (6, Variable)";
//
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//
//    REQUIRE(testResult == expectedResult);
//}
//
//
//
//// Invalid tokens
//TEST_CASE("Invalid name token") {
//    std::string testQuery = "assign 0x1;\n";
//
//    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
//}
//
//TEST_CASE("Invalid integer token") {
//    std::string testQuery = "stmt s;\n"
//        "Select s such that Parent (s, 01)";
//    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
//}
//
//TEST_CASE("Invalid expression token") {
//    std::string testQuery = "assign a1;\n"
//        "Select s such that Uses (s, \"x\") pattern a (\"x\", \"y)";
//    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
//}
//
//TEST_CASE("Invalid subexpression token") {
//    std::string testQuery = "assign a1;\n"
//        "Select s such that Uses (s, \"x\") pattern a (_\"x\", _\"y\"_)";
//    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
//}
//
//TEST_CASE("Invalid symbols token") {
//    std::string testQuery = "assign *;\n"
//        "Select * such that Uses (*, \"x\")";
//    REQUIRE_THROWS_WITH(QPS::tokenizeAndParseQuery(testQuery), "Token Exception Caught");
//}
//
//
//// Edge cases
//TEST_CASE("Presence of white spaces") {
//    std::string testQuery = "stmt       s;    \n"
//        "Select s    such   that Follows*    (6,   s)";
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Presence of white spaces in Name with Quotes and Subexpressions") {
//    std::string testQuery = "assign newa;\n"
//        "Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Single line queries with space") {
//    std::string testQuery = "assign newa; Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//    REQUIRE(testResult == expectedResult);
//}
//
//TEST_CASE("Single line queries without space") {
//    std::string testQuery = "assign newa;Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";
//    Select expectedSelect = Select("v");
//    std::vector<SuchThat> expectedSuchThat{};
//    std::vector<Pattern> expectedPattern{};
//    std::unordered_map<std::string, DesignEntity> expectedMappedSynonyms{ {"v", DesignEntity::VARIABLE} };
//    int expectedNumOfDeclaredSynonyms = 1;
//
//    QueryObject expectedResult = QueryObject(expectedSelect, expectedSuchThat, expectedPattern, expectedMappedSynonyms, expectedNumOfDeclaredSynonyms);
//    QueryObject testResult = QPS::tokenizeAndParseQuery(testQuery);
//
//    REQUIRE(testResult == expectedResult);
//}
//
//
