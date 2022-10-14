#include "components/sp/tokenizer/SimpleTokenizer.h"

#include <catch.hpp>

TEST_CASE("tokenize SIMPLE code") {
    SECTION("tokenize code single liner") {
        std::string test_string = "procedure computeAverage {read num1;sum = num1 + num2 + num3;print ave;}";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeCode(test_string);
        std::vector<std::string> expected_result;
        expected_result.push_back("procedure computeAverage {");
        expected_result.push_back("read num1;");
        expected_result.push_back("sum = num1 + num2 + num3;");
        expected_result.push_back("print ave;");
        expected_result.push_back("}");
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize code procedure") {
        std::string test_string = "procedure computeAverage {"
            "read num1;"
            "sum = num1 + num2 + num3;"
            "print ave;"
            "}";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeCode(test_string);
        std::vector<std::string> expected_result;
        expected_result.push_back("procedure computeAverage {");
        expected_result.push_back("read num1;");
        expected_result.push_back("sum = num1 + num2 + num3;");
        expected_result.push_back("print ave;");
        expected_result.push_back("}");
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize code no procedure") {
        std::string test_string = "qwerty";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeCode(test_string);
        REQUIRE(test_result.empty());
    }
}


TEST_CASE("tokenize SIMPLE line") {
    SECTION("tokenize assign line") {
        std::string test_string = " a  = b + c * d - f / g % e;";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result { "a", "=","b","+","c","*","d","-","f","/","g","%","e",";"};
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize read line") {
        std::string test_string = "read print;";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "read", "print", ";"};
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize print line") {
        std::string test_string = "print read;";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "print", "read", ";" };
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize procedure line") {
        std::string test_string = "procedure newprocedure{";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "procedure", "newprocedure", "{" };
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize call line") {
        std::string test_string = "call newprocedure;";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "call", "newprocedure", ";" };
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize if line") {
        std::string test_string = "if ((a == b) && (b!=C)) then {";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "if", "(","(", "a","==","b",")","&&","(","b","!=","C",")",")","then","{"};
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize else line") {
        std::string test_string = "else {";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "else", "{" };
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize } line") {
        std::string test_string = "}";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ "}" };
        REQUIRE(test_result == expected_result);
    }

    SECTION("tokenize while line") {
        std::string test_string = "while (((a <= b) && (b >=C)) || ((a < b) && (b >C))) {";
        std::vector<std::string> test_result = SimpleTokenizer::tokenizeLine(test_string);
        std::vector<std::string> expected_result{ { "while","(", "(","(", "a","<=","b",")","&&","(","b",">=","C",")",
            ")","||","(","(", "a","<","b",")","&&","(","b",">","C",")",")",")","{"}};
        REQUIRE(test_result == expected_result);
    }
}