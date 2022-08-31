#include "components/qps/query_preprocessor/query_parser/syntax_checker/SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_parser/syntax_checker/DeclarationClauseSyntaxChecker.h"
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

TEST_CASE("Missing design entity") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Missing synonym") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Missing semi-colon") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == false);
};

TEST_CASE("Multiple single declaration with missing comma") {
    DeclarationClauseSyntaxChecker checker = DeclarationClauseSyntaxChecker();
    std::vector<TokenObject> validDeclarationTokens{
        TokenObject(TokenType::VARIABLE, "variable"),
        TokenObject(TokenType::NAME, "v"),
        TokenObject(TokenType::NAME, "a"),
        TokenObject(TokenType::COMMA, ","),
        TokenObject(TokenType::NAME, "vh"),
        TokenObject(TokenType::SEMI_COLON, ";")
    };
    bool actualResult = checker.isSyntacticallyCorrect(validDeclarationTokens);
    REQUIRE(actualResult == false);
};
