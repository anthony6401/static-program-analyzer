#include "ClauseUtils.h"
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::pair<std::string, std::string>> ClauseUtils::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::vector<std::pair<std::string, std::string>> processedResult;
    for (const auto& entry : results) {
        std::string firstSynonym = entry.first;
        std::unordered_set<std::string> secondSynonymList = entry.second;
        for (const auto& secondSynonym : secondSynonymList) {
            std::pair<std::string, std::string> newPair = {firstSynonym, secondSynonym};
            processedResult.emplace_back(newPair);
        }
    }
    return processedResult;
}

std::unordered_set<std::string> ClauseUtils::processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (const auto& entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

std::unordered_set<std::string> ClauseUtils::processMapToSetFromSecond(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (const auto& entry : results) {
        std::unordered_set<std::string> valuesInRow = entry.second;
        processedResult.insert(valuesInRow.begin(), valuesInRow.end());
    }
    return processedResult;
}

std::unordered_set<std::string> ClauseUtils::processMapToSetByMapIntersection(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> intersection;
    std::unordered_map<std::string, std::unordered_set<std::string>>::iterator it;
    for (it = results.begin(); it != results.end(); it++) {
        std::unordered_set<std::string> keys;
        std::unordered_set<std::string> values;
        keys.insert(it -> first);
        std::unordered_set<std::string> valuesInEntry = it -> second;
        values.insert(valuesInEntry.begin(), valuesInEntry.end());

        for (const auto& k : keys) {
            if (values.count(k) != 0) {
                intersection.insert(k);
            }
        }
    }

    return intersection;
}