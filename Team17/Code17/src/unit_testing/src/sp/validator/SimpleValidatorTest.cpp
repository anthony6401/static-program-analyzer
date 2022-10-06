#include "components/sp/validator/SimpleValidator.h"

#include <catch.hpp>
#include <regex>

TEST_CASE("valid Variable") {
    std::string test_string = "azAZ09";
    REQUIRE(SimpleValidator::validateVariable(test_string));
}

TEST_CASE("invalid Variable") {
    std::string test_string = "0abcd";
    REQUIRE(!(SimpleValidator::validateVariable(test_string)));
    test_string = "+--/%()&";
    REQUIRE(!(SimpleValidator::validateVariable(test_string)));
}

TEST_CASE("valid constant") {
    std::string test_string = "123456789";
    REQUIRE(SimpleValidator::validateConstant(test_string));
    test_string = "1";
    REQUIRE(SimpleValidator::validateConstant(test_string));
    test_string = "0";
    REQUIRE(SimpleValidator::validateConstant(test_string));
}

TEST_CASE("invalid constant") {
    std::string test_string = "012345";
    REQUIRE(!(SimpleValidator::validateConstant(test_string)));
    test_string = "-123";
    REQUIRE(!(SimpleValidator::validateConstant(test_string)));
    test_string = "000";
    REQUIRE(!(SimpleValidator::validateConstant(test_string)));
}

TEST_CASE("valid center") {
    std::vector<std::string> strings {  "(", "(", "15", "<", "20", ")", " && ", "(", "5", " == ","10",")"
        , ")", "||", "(", "5", "<=", "10", ")"};
    REQUIRE(SimpleValidator::isAndOrCenter(strings, 13));
    REQUIRE(!(SimpleValidator::isAndOrCenter(strings, 7)));
    std::vector<std::string> tstrings{ "(", "15", "<", "20", ")", " && ", "(", "5", " == ","10",")" };
    REQUIRE(SimpleValidator::isAndOrCenter(tstrings, 5));
    REQUIRE(!(SimpleValidator::isAndOrCenter(tstrings, 7)));
}

TEST_CASE("Not cyclic calls") {
    std::multimap<std::string, std::string> callProcedures = {
        {"proc1", "proc2"},
        {"proc1", "proc3"},
        {"proc2", "proc3"}
    };
    std::set<std::string> procedures = {"proc1", "proc2", "proc3"};
    REQUIRE(SimpleValidator::isValidCalls(callProcedures, procedures));
}

TEST_CASE("Is cyclic calls") {
    std::multimap<std::string, std::string> callProcedures = {
        {"proc1", "proc2"},
        {"proc1", "proc3"},
        {"proc2", "proc3"},
        {"proc3", "proc1"}
    };
    std::set<std::string> procedures = { "proc1", "proc2", "proc3" };
    REQUIRE(!(SimpleValidator::isValidCalls(callProcedures, procedures)));
}

TEST_CASE("Multiple cyclic calls") {
    std::multimap<std::string, std::string> callProcedures = {
        {"proc1", "proc2"},
        {"proc1", "proc3"},
        {"proc2", "proc3"},
        {"proc3", "proc1"},
        {"proc2", "proc1"}
    };
    std::set<std::string> procedures = { "proc1", "proc2", "proc3" };
    REQUIRE(!(SimpleValidator::isValidCalls(callProcedures, procedures)));
}

TEST_CASE("Rcursive calls") {
    std::multimap<std::string, std::string> callProcedures = {
        {"proc1", "proc1"}
    };
    std::set<std::string> procedures = { "proc1"};
    REQUIRE(!(SimpleValidator::isValidCalls(callProcedures, procedures)));
}