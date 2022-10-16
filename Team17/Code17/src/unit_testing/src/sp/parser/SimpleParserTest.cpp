#include "components/sp/parser/SimpleParser.h"
#include <catch.hpp>

PKB* stub = new PKB();
auto client = new SPClient(stub);
Extractor xtractor = Extractor(client);

TEST_CASE("parse code") {
    SECTION("parse invalid empty code") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        try {
            parser.parseCode("    ");
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code"));
        }
    }
}

TEST_CASE("parse line") {
    SECTION("invalid code line") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        try {
            parser.parseLine("not valid code");
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code line 1"));
        }
    }

    SECTION("invalid code line lacking tokens") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        try {
            parser.parseLine("else");
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code line not enough tokens::1"));
        }
    }

}

TEST_CASE("parse Read") {
    SECTION("Invalid read missing ;") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens { "test"};
        try {
            parser.parseRead(test_tokens);
        } catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Read:Line 1"));
        }
    }

    SECTION("Invalid read extra operands") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";"};
        try {
            parser.parseRead(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Read:Line 1"));
        }
    }
}

TEST_CASE("parse print") {
    SECTION("Invalid Print missing ;") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test" };
        try {
            parser.parsePrint(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Print:Line 1"));
        }
    }

    SECTION("Invalid Print extra operands") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";" };
        try {
            parser.parsePrint(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Print:Line 1"));
        }
    }
}

TEST_CASE("parse call") {
    SECTION("Invalid Call missing ;") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test" };
        try {
            parser.parseCall(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Call:Line 1"));
        }
    }

    SECTION("Invalid Call extra operands") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";" };
        try {
            parser.parseCall(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Call:Line 1"));
        }
    }
}

TEST_CASE("parse procedure") {
    SECTION("Invalid Procedure missing {") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test" };
        try {
            parser.parseProcedure(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Procedure:Line 1"));
        }
    }

    SECTION("Invalid Procedure extra operands") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", "{", "{" };
        try {
            parser.parseProcedure(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Procedure:Line 1"));
        }
    }
}

TEST_CASE("parse while") {
    SECTION("Invalid while missing {") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{"(","test", " == ","abc","+","c",")"};
        try {
            parser.parseWhile(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid While:Line 1"));
        }
    }

    SECTION("Invalid while not enough tokens") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test",")","{"};
        try {
            parser.parseWhile(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid While:Line 1"));
        }
    }
}

TEST_CASE("parse If") {
    SECTION("Invalid if missing {") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test", " == ","abc","+","c",")","then"};
        try {
            parser.parseIf(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid If:Line 1"));
        }
    }

    SECTION("Invalid if not enough tokens") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test",")","then","{"};
        try {
            parser.parseIf(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid If:Line 1"));
        }
    }

    SECTION("Invalid if missing then") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "(","test", " == ","abc","+","c",")","{" };
        try {
            parser.parseIf(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid If:Line 1"));
        }
    }
}

TEST_CASE("parse Else") {
    SECTION("Invalid Else wrong token") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "else;" };
        try {
            parser.parseElse(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Else:Line 1"));
        }
    }

    SECTION("Invalid Else extra tokens") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "else { {" };
        try {
            parser.parseElse(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Else:Line 1"));
        }
    }

    SECTION("Invalid read extra operands") {
        SimpleParser parser = SimpleParser(&xtractor);
        parser.statementNumber = 1;
        std::vector<std::string> test_tokens{ "test", ";", ";" };
        try {
            parser.parseRead(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid Read:Line 1"));
        }
    }
}

TEST_CASE("parse condition") {
    SECTION("valid condition") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","(", "(","!","(", "1", "<", "ab1", ")",")", "&&", "(", "abc", "==","123",")"
    , ")", "||", "(", "1", "<=", "abc", ")", ")" };
        std::vector<SimpleToken> test_result = parser.parseCondition(test_tokens);

        std::vector<SimpleToken> resultTokens;
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "ab1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "123", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
        REQUIRE(test_result ==resultTokens);
    }

    SECTION("invalid condition missing (") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "abc","<","123", ")" };
        try {
            parser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition missing )") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{"(", "abc","<","123" };
        try {
            parser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition missing !(") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","!", "abc","<","123",")",")"};
        try {
            parser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition missing !)") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","!","(", "abc","<","123",")" };
        try {
            parser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. Missing brackets"));
        }
    }

    SECTION("invalid condition invalid &&)") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(", "abc","<","123", "&&","(","abc","<","123",")",")"};
        try {
            parser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. invalid && or ||"));
        }
    }

    SECTION("invalid condition invalid ||)") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(", "abc","<","123", "||","(","abc","<","123",")",")" };
        try {
            parser.parseCondition(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid condition. invalid && or ||"));
        }
    }
}

TEST_CASE("parse relexpr") {
    SECTION("valid relexpr") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","a1234","+","1",")","!=","abc" };
        std::vector<SimpleToken> test_result = parser.parseRelExpr(test_tokens);

        std::vector<SimpleToken> resultTokens;
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "a1234", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TVARIABLE, "abc", 0));
        REQUIRE(test_result == resultTokens);
    }

    SECTION("invalid relexpr missing comparator") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "abc", "23"};
        try {
            parser.parseRelExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid RelExpr missing comparator"));
        }
    }
}


TEST_CASE("parse expr") {
    SECTION("valid expr") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","1","+","(","1",")",")" };
        SimpleToken test_result = parser.parseExpr(test_tokens);

        SimpleToken result = SimpleToken(SpTokenType::TEXPR, "", 0);

        std::vector<SimpleToken> resultTokens;
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TOPR, "+", 0));
        resultTokens.push_back(SimpleToken(SpTokenType::TCONSTANT, "1", 0));
        result.setChildren(resultTokens);
        REQUIRE(test_result.getChildren() == result.getChildren());
    }

    SECTION("invalid expr missing )") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","1","+","(","1",")"};
        try {
            parser.parseExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid expression. Wrong tokens. "));
        }
    }

    SECTION("invalid expr missing (") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","1","+","1",")",")"};
        try {
            parser.parseExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Unexpected )"));
        }
    }

    SECTION("invalid expr ends at operand") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::vector<std::string> test_tokens{ "(","1",")","+" };
        try {
            parser.parseExpr(test_tokens);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid expression. Wrong tokens. "));
        }
    }
}

TEST_CASE("parse variable") {
    SECTION("valid variable") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::string test_token = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        REQUIRE(parser.parseVariable(test_token)==
            std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"));
    }

    SECTION("invalid variable") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::string test_token = "abc!";
        try {
            parser.parseVariable(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid variable abc!"));
        }
    }
}

TEST_CASE("parse constant") {
    SECTION("valid variable") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::string test_token = "1234567890";
        REQUIRE(parser.parseConstant(test_token) ==
            std::string("1234567890"));
        test_token = "0";
        REQUIRE(parser.parseConstant(test_token) ==
            std::string("0"));
    }

    SECTION("invalid constant") {
        SimpleParser parser = SimpleParser(&xtractor);
        std::string test_token = "0123";
        try {
            parser.parseConstant(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid constant 0123"));
        }
        test_token = "abc";
        try {
            parser.parseConstant(test_token);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid constant abc"));
        }
    }
}