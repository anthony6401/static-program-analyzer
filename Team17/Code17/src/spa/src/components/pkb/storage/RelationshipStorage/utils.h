#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "models/Entity/Entity.h"

bool insertEntity(std::unordered_map<std::string, std::unordered_set<std::string>*>* map, std::string leftValue, std::string rightValue) {
	if (map->find(leftValue) == map->end()) {
		map->insert({ leftValue, new std::unordered_set<std::string> });
	}
	return map->find(leftValue)->second->insert(rightValue).second;
}