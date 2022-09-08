#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>

class Utils {
public:
	static bool insertEntity(std::unordered_map<std::string, std::unordered_set<std::string>>& map, std::string& leftValueTest, std::string& rightValueTest) {
		if (map.find(leftValueTest) == map.end()) {
			map.insert({ leftValueTest, std::unordered_set<std::string>() });
		}

		return map.find(leftValueTest)->second.insert(rightValueTest).second;
	}
};
