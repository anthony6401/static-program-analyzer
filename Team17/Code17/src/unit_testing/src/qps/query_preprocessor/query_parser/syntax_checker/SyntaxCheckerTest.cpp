#include "components/qps/query_preprocessor/query_parser/syntax_checker/SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/DeclarationClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/SelectClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/SuchThatClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/PatternClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/WithClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <tuple>

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

TEST_CASE("Syntactically correct Select with and synonym") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::AND, "and")
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

TEST_CASE("Syntactically correct Select with synonym name as SELECT") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::SELECT, "Select"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSelectTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct Select with synonym name as pattern") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::PATTERN, "pattern"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSelectTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct Select with attribute as return type") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::ATTRIBUTE, "proc.procName"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSelectTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct Select with boolean as return type") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::BOOLEAN, "BOOLEAN"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSelectTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct Select with tuple as return type") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> validSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::TUPLE, "<a, a1, v, v1>"),
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

TEST_CASE("Syntactically incorrect Select with multiple return types") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> invalidSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::BOOLEAN, "BOOLEAN"),
        TokenObject(TokenType::TUPLE, "<v>")
    };
    bool actualResult = checker.isSyntacticallyCorrect(invalidSelectTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect Select with invalid return type") {
    SelectClauseSyntaxChecker checker = SelectClauseSyntaxChecker();
    std::vector<TokenObject> invalidSelectTokens{
        TokenObject(TokenType::SELECT, "Select"),
        TokenObject(TokenType::INTEGER, "1")
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

TEST_CASE("Calls relationship - ENTREF_ENTREF") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Calls* relationship - with synonym name Calls") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS_T, "Calls*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Next relationship") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME, "s"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Next* relationship - WILDCARD") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT_T, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Synonyms with same name as such or that types") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::MODIFIES, "Modifies"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Synonyms with same name as relationship types") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::MODIFIES, "Modifies"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::MODIFIES, "Modifies"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - no and clause") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
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

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - and clause") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::PARENT, "Parent"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PARENT, "Parent"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - multiple and clause") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::PARENT, "Parent"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PARENT, "Parent"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PARENT, "Parent"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - such that - and - such that") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::FOLLOWS, "Follows"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PARENT, "Parent*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - such that - such that - and") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CALLS_T, "Calls*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - pattern clause with relref synonym name taken with relref syntax") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CALLS_T, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Multiple such that clauses - and as synonym name") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CALLS_T, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
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

TEST_CASE("Syntactically incorrect - Calls with STMTREF parameter as first parameter") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Calls* with STMTREF parameter as second parameter") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS_T, "Calls*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Next with ENTREF as one of the parameters") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - Next* with ENTREF-ENTREF parameters") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "y"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
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

TEST_CASE("Syntactically incorrect - such that start with and") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CALLS_T, "Calls*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - and immediately after such that") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CALLS_T, "Calls*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - and clause and such that missing") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - token after and is such that") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - such that - and - pattern") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUBEXPRESSION, "_\"y\"_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - such that - and - pattern clause") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUBEXPRESSION, "_\"y\"_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - such that - and - pattern clause with relref as synonym name") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::SUBEXPRESSION, "_\"y\"_"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - multiple and in a row") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - multiple instances but does not end in closed bracket") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::CALLS_T, "Calls*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v")

    };

    bool actualResult = checker.isSyntacticallyCorrect(validSuchThatTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - and clause with no relref") {
    SuchThatClauseSyntaxChecker checker = SuchThatClauseSyntaxChecker();
    std::vector<TokenObject> validSuchThatTokens{
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::CALLS, "Calls"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::SUCH, "such"),
        TokenObject(TokenType::THAT, "that"),
        TokenObject(TokenType::NEXT, "Next*"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::INTEGER, "6"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and")
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

TEST_CASE("Valid pattern clause - synonym name is pattern") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Valid pattern clause - assign synonym name is pattern") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Valid pattern clause - more than one pattern") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);

};

TEST_CASE("Valid pattern clause - more than one pattern using and clause") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);

};

TEST_CASE("Valid pattern clause - pattern - and - pattern") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);

};

TEST_CASE("Valid pattern clause - pattern - pattern - and") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);

};

TEST_CASE("Valid pattern clause - and is used as synonym") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == true);

};

TEST_CASE("Valid pattern clause - relref as synonym name with valid pattern and such that syntax") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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

TEST_CASE("Syntactically incorrect - pattern start with and") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - relref as synonym name with valid such that syntax only") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
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

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - multiple and clauses in a row") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::USES, "Uses"),
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
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - multiple and clause is incomplete") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
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
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - ends in and clause") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::AND, "and")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - multiple clauses with no and clause") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::WILDCARD, "_"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")"),
        TokenObject(TokenType::USES, "Uses"),
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
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - multiple clauses with no pattern clause") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
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
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

TEST_CASE("Syntactically incorrect - pattern token after and") {
    PatternClauseSyntaxChecker checker = PatternClauseSyntaxChecker();
    std::vector<TokenObject> validPatternTokens{
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
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
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::OPEN_BRACKET, "("),
        TokenObject(TokenType::PATTERN, "pattern"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::EXPRESSION, "x"),
        TokenObject(TokenType::CLOSED_BRACKET, ")")
    };

    bool actualResult = checker.isSyntacticallyCorrect(validPatternTokens);
    REQUIRE(actualResult == false);

};

// Tests for WithClauseSyntaxChecker
TEST_CASE("Instantiate WithClauseSyntaxChecker") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> emptyDeclaration{};
    bool withSyntaxIsEmpty = checker.isSyntacticallyCorrect(emptyDeclaration);
    REQUIRE(withSyntaxIsEmpty == false);
};

TEST_CASE("Syntactically correct - attribute = attribute") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "v.varName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "c.procName")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct - ident = integer") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct with and clause") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct with multiple and clause") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct with multiple with clause") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically correct with both and and with clause") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == true);
};

TEST_CASE("Syntactically incorrect - missing with") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - name as ref") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - missing first ref") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - missing second ref") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - missing equals") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::INTEGER, "1"),

    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - missing and") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "v"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - missing with in multi-clause") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - extra with") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - extra with in multi-clause") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - extra and") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Syntactically incorrect - extra ref") {
    WithClauseSyntaxChecker checker = WithClauseSyntaxChecker();
    std::vector<TokenObject> validWithTokens{
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::INTEGER, "1"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::ATTRIBUTE, "p.procName"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::AND, "and"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "IDENT"),
        TokenObject(TokenType::WITH, "with"),
        TokenObject(TokenType::NAME_WITH_QUOTATION, "p"),
        TokenObject(TokenType::EQUALS, "="),
        TokenObject(TokenType::ATTRIBUTE, "calls.stmt#"),
    };
    bool actualResult = checker.isSyntacticallyCorrect(validWithTokens);
    REQUIRE(actualResult == false);
};
