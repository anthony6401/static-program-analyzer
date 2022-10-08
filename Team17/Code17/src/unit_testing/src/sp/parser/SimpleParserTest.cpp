#include "components/sp/parser/SimpleParser.h"
#include <iostream>
#include <catch.hpp>

//Temporary solution. Will clean up in the future
bool equalToken(SimpleToken test, SimpleToken result) {
    return test.type == result.type && test.statementNumber == result.statementNumber && test.value == result.value;
}

bool equalChildren(std::vector<SimpleToken> test, std::vector<SimpleToken> result) {
    if (test.size() != result.size()) {
        return false;
    }
    for (int i = 0; i < test.size(); i++) {
        SimpleToken a = test.at(i);
        SimpleToken b = result.at(i);
        if (!(equalToken(a, b))) {
            return false;
        }
        if (test.empty() == result.empty() && !(test.empty())) {
            if(!(equalChildren(a.getChildren(), b.getChildren()))) {
                return false;
            }
        }
    }
    return true;
}

PKB* stub = new PKB();
auto client = new SPClient(stub);
Extractor xtractor = Extractor(client);
SimpleParser sparser = SimpleParser(&xtractor);

TEST_CASE("parse Read") {
    SECTION("Invalid read missing ;") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens { "test"};
        try {
            sparser.parseRead(test_tokens);
        } catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Read:Line 1"));
        }
    }

    SECTION("Invalid read extra operands") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";"};
        try {
            sparser.parseRead(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Read:Line 1"));
        }
    }
}

TEST_CASE("parse print") {
    SECTION("Invalid Print missing ;") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test" };
        try {
            sparser.parsePrint(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Print:Line 1"));
        }
    }

    SECTION("Invalid Print extra operands") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";" };
        try {
            sparser.parsePrint(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Print:Line 1"));
        }
    }
}

TEST_CASE("parse call") {
    SECTION("Invalid Call missing ;") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test" };
        try {
            sparser.parseCall(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Call:Line 1"));
        }
    }

    SECTION("Invalid Call extra operands") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";" };
        try {
            sparser.parseCall(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Call:Line 1"));
        }
    }
}

TEST_CASE("parse procedure") {
    SECTION("Invalid Procedure missing {") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test" };
        try {
            sparser.parseProcedure(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Procedure:Line 1"));
        }
    }

    SECTION("Invalid Procedure extra operands") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", "{", "{" };
        try {
            sparser.parseProcedure(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Procedure:Line 1"));
        }
    }
}

TEST_CASE("parse while") {
    SECTION("Invalid while missing {") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{"(","test", " == ","abc","+","c",")"};
        try {
            sparser.parseWhile(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid While:Line 1"));
        }
    }

    SECTION("Invalid while not enough tokens") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test",")","{"};
        try {
            sparser.parseWhile(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid While:Line 1"));
        }
    }
}

TEST_CASE("parse If") {
    SECTION("Invalid if missing {") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test", " == ","abc","+","c",")","then"};
        try {
            sparser.parseIf(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid If:Line 1"));
        }
    }

    SECTION("Invalid while not enough tokens") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test",")","then","{"};
        try {
            sparser.parseIf(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid If:Line 1"));
        }
    }

    SECTION("Invalid if missing then") {
        sparser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test", " == ","abc","+","c",")","{" };
        try {
            sparser.parseIf(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid If:Line 1"));
        }
    }
}

TEST_CASE("parse condition") {
    SECTION("valid condition") {
        std::vector<std::string> test_tokens{ "(","(", "(","!","(", "1", "<", "ab1", ")",")", "&&", "(", "abc", "==","123",")"
    , ")", "||", "(", "1", "<=", "abc", ")", ")" };
        std::vector<SimpleToken> test_result = sparser.parseCondition(test_tokens);

        std::vector<SimpleToken> resultTokens;
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "ab1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "123", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
        REQUIRE(equalChildren(test_result, resultTokens));
    }

    SECTION("invalid condition missing (") {
        std::vector<std::string> test_tokens{ "abc","<","123", ")" };
        try {
            sparser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition missing )") {
        std::vector<std::string> test_tokens{"(", "abc","<","123" };
        try {
            sparser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition missing !(") {
        std::vector<std::string> test_tokens{ "(","!", "abc","<","123",")",")"};
        try {
            sparser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition missing !)") {
        std::vector<std::string> test_tokens{ "(","!","(", "abc","<","123",")" };
        try {
            sparser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition invalid &&)") {
        std::vector<std::string> test_tokens{ "(", "abc","<","123", "&&","(","abc","<","123",")",")"};
        try {
            sparser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. invalid && or ||"));
        }
    }

    SECTION("invalid condition invalid ||)") {
        std::vector<std::string> test_tokens{ "(", "abc","<","123", "||","(","abc","<","123",")",")" };
        try {
            sparser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. invalid && or ||"));
        }
    }
}

TEST_CASE("parse relexpr") {
    SECTION("valid relexpr") {
        std::vector<std::string> test_tokens{ "(","a1234","+","1",")","!=","abc" };
        std::vector<SimpleToken> test_result = sparser.parseRelExpr(test_tokens);

        std::vector<SimpleToken> resultTokens;
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "a1234", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
        REQUIRE(equalChildren(test_result, resultTokens));
    }

    SECTION("invalid relexpr missing comparator") {
        std::vector<std::string> test_tokens{ "abc", "23"};
        try {
            sparser.parseRelExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid RelExpr missing comparator"));
        }
    }
}


TEST_CASE("parse expr") {
    SECTION("valid expr") {
        std::vector<std::string> test_tokens{ "(","1","+","(","1",")",")" };
        SimpleToken test_result = sparser.parseExpr(test_tokens);

        SimpleToken result = SimpleToken(SpTokenType::TEXPR, "", 0);

        std::vector<SimpleToken> resultTokens;
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        result.setChildren(resultTokens);
        REQUIRE(equalChildren(test_result.getChildren(), result.getChildren()));
    }

    SECTION("invalid expr missing )") {
        std::vector<std::string> test_tokens{ "(","1","+","(","1",")"};
        try {
            sparser.parseExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid expression. Wrong tokens. "));
        }
    }

    SECTION("invalid expr missing (") {
        std::vector<std::string> test_tokens{ "(","1","+","1",")",")"};
        try {
            sparser.parseExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Unexpected )"));
        }
    }

    SECTION("invalid expr ends at operand") {
        std::vector<std::string> test_tokens{ "(","1",")","+" };
        try {
            sparser.parseExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid expression. Wrong tokens. "));
        }
    }
}

TEST_CASE("parse variable") {
    SECTION("valid variable") {
        std::string test_token = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        REQUIRE(sparser.parseVariable(test_token)==
            std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"));
    }

    SECTION("invalid variable") {
        std::string test_token = "abc!";
        try {
            sparser.parseVariable(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid variable abc!"));
        }
    }
}

TEST_CASE("parse constant") {
    SECTION("valid variable") {
        std::string test_token = "1234567890";
        REQUIRE(sparser.parseConstant(test_token) ==
            std::string("1234567890"));
        test_token = "0";
        REQUIRE(sparser.parseConstant(test_token) ==
            std::string("0"));
    }

    SECTION("invalid constant") {
        std::string test_token = "0123";
        try {
            sparser.parseConstant(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid constant 0123"));
        }
        test_token = "abc";
        try {
            sparser.parseConstant(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid constant abc"));
        }
    }
}