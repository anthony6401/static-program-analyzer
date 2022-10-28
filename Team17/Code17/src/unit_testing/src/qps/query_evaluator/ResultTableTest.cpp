#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

TEST_CASE("Instantiate empty constructor") {
    ResultTable emptyRawResult;
    REQUIRE(emptyRawResult.isEmptyResult() == true);
    REQUIRE(emptyRawResult.synonymsList.empty() == true);
    REQUIRE(emptyRawResult.getIsFalseResult() == false);
}

TEST_CASE("Instantiate constructor with 0 synonym") {
    ResultTable zeroSynonymResult = ResultTable();
    REQUIRE(zeroSynonymResult.isEmptyResult() == true);
    REQUIRE(zeroSynonymResult.synonymsList.empty() == true);
    REQUIRE(zeroSynonymResult.getIsFalseResult() == false);
}

TEST_CASE("Instantiate constructor with one synonym") {
    ResultTable singleSynonymResult = ResultTable("a", {"1", "2", "3", "4"});
    std::vector<std::string> expectedSynonymsList = {"a"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"4"}, {"3"}, {"2"}, {"1"}};

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(singleSynonymResult.resultsList.begin(), singleSynonymResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(singleSynonymResult.synonymsList == expectedSynonymsList);
    REQUIRE(singleSynonymResult.resultsList == expectedResultsList);
    REQUIRE(singleSynonymResult.isEmptyResult() == false);
    REQUIRE(singleSynonymResult.synonymsList.empty() == false);
    REQUIRE(singleSynonymResult.getIsFalseResult() == false);
}

TEST_CASE("Instantiate constructor with two synonyms") {
    std::pair<std::string, std::string> p1("1","x");
    std::pair<std::string, std::string> p2("3","x");
    std::vector<std::pair<std::string, std::string>> results = {p1, p2};
    ResultTable doubleSynonymResult = ResultTable("a", "v", results);
    std::vector<std::string> expectedSynonymsList = {"a", "v"};
    std::vector<std::vector<std::string>> expectedResultsList = {{p1.first, p1.second}, {p2.first, p2.second}};

    std::sort(expectedSynonymsList.begin(), expectedSynonymsList.end());
    std::sort(doubleSynonymResult.synonymsList.begin(), doubleSynonymResult.synonymsList.end());

    for (auto & row : expectedResultsList) {
        sort(row.begin(), row.end());
    }

    for (auto & row : doubleSynonymResult.resultsList) {
        sort(row.begin(), row.end());
    }

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(doubleSynonymResult.resultsList.begin(), doubleSynonymResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(doubleSynonymResult.synonymsList == expectedSynonymsList);
    REQUIRE(doubleSynonymResult.resultsList == expectedResultsList);
    REQUIRE(doubleSynonymResult.isEmptyResult() == false);
    REQUIRE(doubleSynonymResult.synonymsList.empty() == false);
    REQUIRE(doubleSynonymResult.getIsFalseResult() == false);
}

TEST_CASE("Merge empty result with non-empty result") {
    ResultTable emptyRawResult;
    ResultTable singleSynonymResult = ResultTable("a", {"1", "2", "3", "4"});
    emptyRawResult.combineResult(singleSynonymResult);
    ResultTable expectedResult = ResultTable();
    std::vector<std::string> expectedSynonymsList = {"a"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"4"}, {"3"}, {"2"}, {"1"}};

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(emptyRawResult.resultsList.begin(), emptyRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(emptyRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(emptyRawResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge non-empty result with empty result") {
    ResultTable emptyRawResult = ResultTable();
    ResultTable singleSynonymResult = ResultTable("a", {"1", "2", "3", "4"});
    singleSynonymResult.combineResult(emptyRawResult);
    std::vector<std::string> expectedSynonymsList = {"a"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"4"}, {"3"}, {"2"}, {"1"}};

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(singleSynonymResult.resultsList.begin(), singleSynonymResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(singleSynonymResult.synonymsList == expectedSynonymsList);
    REQUIRE(singleSynonymResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge results with common synonyms - single common synonyms in single synonym clauses") {
    // Common synonym a
    ResultTable firstRawResult = ResultTable("a", {"1", "2", "3", "4"});
    ResultTable secondRawResult = ResultTable("a", {"1", "3", "5"});
    std::vector<std::string> expectedSynonymsList = {"a"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"3"}, {"1"}};
    firstRawResult.combineResult(secondRawResult);

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(firstRawResult.resultsList.begin(), firstRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(firstRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(firstRawResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge results with common synonyms - single common synonyms in single/multiple synonym clauses") {
    ResultTable firstRawResult = ResultTable("a", {"1", "2", "3", "4"});
    std::vector<std::pair<std::string, std::string>> results = {{"1", "x"}, {"3", "y"}, {"5", "z"}};
    ResultTable secondRawResult = ResultTable("a", "v", results);
    std::vector<std::string> expectedSynonymsList = {"a", "v"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"3", "y"}, {"1", "x"}};
    firstRawResult.combineResult(secondRawResult);

    std::sort(expectedSynonymsList.begin(), expectedSynonymsList.end());
    std::sort(firstRawResult.synonymsList.begin(), firstRawResult.synonymsList.end());

    for (auto & row : expectedResultsList) {
        sort(row.begin(), row.end());
    }

    for (auto & row : firstRawResult.resultsList) {
        sort(row.begin(), row.end());
    }

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(firstRawResult.resultsList.begin(), firstRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(firstRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(firstRawResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge results with common synonyms - single common synonym in multiple synonyms clauses") {
    std::vector<std::pair<std::string, std::string>> firstResults = {{"1", "x"}, {"1", "y"}, {"3", "z"}};
    std::vector<std::pair<std::string, std::string>> secondResults = {{"1", "x"}, {"2", "z"}};
    ResultTable firstRawResult = ResultTable("s", "v", firstResults);
    ResultTable secondRawResult = ResultTable("a", "v", secondResults);
    std::vector<std::string> expectedSynonymsList = {"s", "v", "a"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"1", "x", "1"}, {"3", "z", "2"}};
    firstRawResult.combineResult(secondRawResult);

    std::sort(expectedSynonymsList.begin(), expectedSynonymsList.end());
    std::sort(firstRawResult.synonymsList.begin(), firstRawResult.synonymsList.end());

    for (auto & row : expectedResultsList) {
        sort(row.begin(), row.end());
    }

    for (auto & row : firstRawResult.resultsList) {
        sort(row.begin(), row.end());
    }

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(firstRawResult.resultsList.begin(), firstRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(firstRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(firstRawResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge results with common synonyms - multiple common synonyms in multiple synonyms clauses") {
    std::vector<std::pair<std::string, std::string>> firstResults = {{"1", "x"}, {"1", "y"}, {"3", "z"}};
    std::vector<std::pair<std::string, std::string>> secondResults = {{"1", "x"}, {"2", "z"}};
    ResultTable firstRawResult = ResultTable("a", "v", firstResults);
    ResultTable secondRawResult = ResultTable("a", "v", secondResults);
    std::vector<std::string> expectedSynonymsList = {"a", "v"};
    std::vector<std::vector<std::string>> expectedResultsList = {{"1", "x"}};
    firstRawResult.combineResult(secondRawResult);

    std::sort(expectedSynonymsList.begin(), expectedSynonymsList.end());
    std::sort(firstRawResult.synonymsList.begin(), firstRawResult.synonymsList.end());

    for (auto & row : expectedResultsList) {
        sort(row.begin(), row.end());
    }

    for (auto & row : firstRawResult.resultsList) {
        sort(row.begin(), row.end());
    }

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(firstRawResult.resultsList.begin(), firstRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(firstRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(firstRawResult.resultsList == expectedResultsList);
}

// Cross join
TEST_CASE("Merge results with no common synonyms - single synonym clauses") {
    ResultTable firstRawResult = ResultTable("a", {"1", "2", "3", "4"});
    ResultTable secondRawResult = ResultTable("v", {"x", "y", "z", "k"});
    std::vector<std::string> expectedSynonymsList = {"a", "v"};
    std::vector<std::vector<std::string>> expectedResultsList = { { "4", "k" },
                                                                  { "4", "z" },
                                                                  { "4", "y" },
                                                                  { "4", "x" },
                                                                  { "3", "k" },
                                                                  { "3", "z" },
                                                                  { "3", "y" },
                                                                  { "3", "x" },
                                                                  { "2", "k" },
                                                                  { "2", "z" },
                                                                  { "2", "y" },
                                                                  { "2", "x" },
                                                                  { "1", "k" },
                                                                  { "1", "z" },
                                                                  { "1", "y" },
                                                                  { "1", "x" } };
    firstRawResult.combineResult(secondRawResult);

    std::sort(expectedSynonymsList.begin(), expectedSynonymsList.end());
    std::sort(firstRawResult.synonymsList.begin(), firstRawResult.synonymsList.end());

    for (auto & row : expectedResultsList) {
        sort(row.begin(), row.end());
    }

    for (auto & row : firstRawResult.resultsList) {
        sort(row.begin(), row.end());
    }

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(firstRawResult.resultsList.begin(), firstRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(firstRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(firstRawResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge results with no common synonyms - multiple synonym clauses") {
    std::vector<std::pair<std::string, std::string>> firstResults = {{"1", "x"}, {"3", "y"}, {"5", "z"}};
    std::vector<std::pair<std::string, std::string>> secondResults ={{"2", "i"}, {"4", "j"}, {"6", "k"}};
    ResultTable firstRawResult = ResultTable("a", "v", firstResults);
    ResultTable secondRawResult = ResultTable("a1", "v1", secondResults);
    std::vector<std::string> expectedSynonymsList = {"a", "v", "a1", "v1"};
    std::vector<std::vector<std::string>> expectedResultsList = { { "1", "x", "2", "i" },
                                                                  { "1", "x", "4", "j" },
                                                                  { "1", "x", "6", "k" },
                                                                  { "3", "y", "2", "i" },
                                                                  { "3", "y", "4", "j" },
                                                                  { "3", "y", "6", "k" },
                                                                  { "5", "z", "2", "i" },
                                                                  { "5", "z", "4", "j" },
                                                                  { "5", "z", "6", "k" }};
    firstRawResult.combineResult(secondRawResult);

    std::sort(expectedSynonymsList.begin(), expectedSynonymsList.end());
    std::sort(firstRawResult.synonymsList.begin(), firstRawResult.synonymsList.end());

    for (auto & row : expectedResultsList) {
        sort(row.begin(), row.end());
    }

    for (auto & row : firstRawResult.resultsList) {
        sort(row.begin(), row.end());
    }

    std::sort(expectedResultsList.begin(), expectedResultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::sort(firstRawResult.resultsList.begin(), firstRawResult.resultsList.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    REQUIRE(firstRawResult.synonymsList == expectedSynonymsList);
    REQUIRE(firstRawResult.resultsList == expectedResultsList);
}

TEST_CASE("Merge with alternative attribute Select clause") {
    ResultTable firstTable;
    ResultTable secondTable;
    secondTable.setHasAlternativeAttributeNameToTrue();
    firstTable.combineResult(secondTable);
    REQUIRE(firstTable.getHasAlternativeAttributeName() == true);
    REQUIRE(secondTable.getHasAlternativeAttributeName() == true);
}
