#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

TEST_CASE("Instantiate empty constructor") {
    RawResult emptyRawResult;
    REQUIRE(emptyRawResult.isEmptyResult() == true);
    REQUIRE(emptyRawResult.synonymsList.empty() == true);
    REQUIRE(emptyRawResult.getIsBooleanResult() == true);
    REQUIRE(emptyRawResult.getIsFalseResult() == false);
}

TEST_CASE("Instantiate constructor with 0 synonym") {
    RawResult zeroSynonymResult = RawResult();
    REQUIRE(zeroSynonymResult.getIsBooleanResult() == true);
    REQUIRE(zeroSynonymResult.isEmptyResult() == true);
    REQUIRE(zeroSynonymResult.synonymsList.empty() == true);
    REQUIRE(zeroSynonymResult.getIsFalseResult() == false);
}

TEST_CASE("Instantiate constructor with one synonym") {
    RawResult singleSynonymResult = RawResult("a", {"1", "2", "3", "4"});
    std::vector<std::string> expectedSynonymsList = {"a"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"4"}, {"3"}, {"2"}, {"1"}};
    REQUIRE(singleSynonymResult.synonymsList == expectedSynonymsList);
    REQUIRE(singleSynonymResult.resultsList == expectedResultsList);
    REQUIRE(singleSynonymResult.isEmptyResult() == false);
    REQUIRE(singleSynonymResult.getIsBooleanResult() == false);
    REQUIRE(singleSynonymResult.synonymsList.empty() == false);
    REQUIRE(singleSynonymResult.getIsFalseResult() == false);
}

TEST_CASE("Instantiate constructor with two synonyms") {
    std::pair<std::string, std::string> p1("1","x");
    std::pair<std::string, std::string> p2("3","x");
    RawResult doubleSynonymResult = RawResult("a", "v", {p1, p2});
    std::vector<std::string> expectedSynonymsList = {"a", "v"};
    std::vector<std::vector<std::string>> expectedResultsList = {{p2.first, p2.second}, {p1.first, p1.second}};
    REQUIRE(doubleSynonymResult.synonymsList == expectedSynonymsList);
    REQUIRE(doubleSynonymResult.isEmptyResult() == false);
    REQUIRE(doubleSynonymResult.synonymsList.empty() == false);
    REQUIRE(doubleSynonymResult.getIsBooleanResult() == false);
    REQUIRE(doubleSynonymResult.getIsFalseResult() == false);
}

TEST_CASE("Merge results with common synonyms") {
    RawResult rawResult;

}

TEST_CASE("Merge results with no common synonyms") {
    RawResult rawResult;

}