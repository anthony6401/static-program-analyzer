#include "components/qps/query_preprocessor/query_parser/syntax_checker/SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/DeclarationClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/SelectClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/SuchThatClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/PatternClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <catch.hpp>

// Tests for DeclarationClauseSyntaxChecker
TEST_CASE("Instantiate DeclarationClauseSyntaxChecker") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> emptyDeclaration{};
    bool declarationSyntaxIsEmpty = checker.isSyntacticallyCorrect(emptyDeclaration);
    REQUIRE(declarationSyntaxIsEmpty == false);
};

TEST_CASE("Syntactically correct declaration") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple single declaration") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "vh"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple declarations with single synonym value") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";"),
        TokenObject(TokenType::STMT, "stmt"),
        TokenObject(TokenType::NAME, "s"),
        TokenObject(TokenType::SEMI_COLON, ";"),
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";"),
        TokenObject(TokenType::READ, "read"),
        TokenObject(TokenType::NAME, "re"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Synonym has same name as design entity") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Missing design entity") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Missing synonym") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Missing semi-colon") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Multiple single declaration with missing comma") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "vh"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Multiple single declaration with extra comma") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "vh"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Multiple declarations with missing semi-colon") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::STMT, "stmt"),
        TokenObject(TokenType::NAME, "s"),
        TokenObject(TokenType::SEMI_COLON, ";"),
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";"),
        TokenObject(TokenType::READ, "read"),
        TokenObject(TokenType::NAME, "re"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Multiple declarations separated by comma instead of semi-colon") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> invalidDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::STMT, "stmt"),
        TokenObject(TokenType::NAME, "s"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::READ, "read"),
        TokenObject(TokenType::NAME, "re"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidDeclarationTokens);
    REQUIRE(actualResult == false);
};

// Tests for SelectClauseSyntaxChecker
TEST_CASE("Instantiate SelectClauseSyntaxChecker") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> emptyDeclaration{};
    bool selectSyntaxIsEmpty = checker.isSyntacticallyCorrect(emptyDeclaration);
    REQUIRE(selectSyntaxIsEmpty == false);
};

TEST_CASE("Syntactically correct Select with synonym") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::NAME, "v"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSelectTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct Select with synonym with same name as a design entity") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::VARIABLE, "variable"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSelectTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically incorrect Select with synonym") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> invalidSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidSelectTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect Select with multiple synonyms") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> invalidSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "y")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidSelectTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Missing select") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> invalidSelectTokens{
        TokenObject(TokenType::NAME, "v")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidSelectTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Missing return value") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> invalidSelectTokens{
        TokenObject(TokenType::SELECT, "Select")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidSelectTokens);
    REQUIRE(actualResult == false);
};

// Tests for SuchThatClauseSyntaxChecker
TEST_CASE("Instantiate SuchThatClauseSyntaxChecker") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> emptyDeclaration{};
    bool suchThatSyntaxIsEmpty = checker.isSyntacticallyCorrect(emptyDeclaration);
    REQUIRE(suchThatSyntaxIsEmpty == false);
};

TEST_CASE("Follows relationship") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::FOLLOWS, "Follows"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "s"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Parent* relationship - WILDCARD") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::PARENT_T, "Parent*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Uses relationship - STMTREF_ENTREF") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Modifies relationship - ENTREF_ENTREF") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::MODIFIES, "Modifies"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically incorrect - Follows with wrong parameters") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::FOLLOWS, "Follows"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Uses with STMTREF as 2nd parameter") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Missing such token") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Missing that token") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Missing RELREF token") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Missing bracket tokens") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Missing relationship tokens") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Missing parameters") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

// Tests for PatternClauseSyntaxChecker
TEST_CASE("Instantiate PatternClauseSyntaxChecker") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> emptyDeclaration{};
    bool patternSyntaxIsEmpty = checker.isSyntacticallyCorrect(emptyDeclaration);
    REQUIRE(patternSyntaxIsEmpty == false);
};

TEST_CASE("Valid pattern clause - single declaration") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUBEXPRESSION, "_\"y\"_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Valid pattern clause - multiple declaration") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically incorrect - Invalid parameters") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "3"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - missing pattern token") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - extra tokens") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);
 };