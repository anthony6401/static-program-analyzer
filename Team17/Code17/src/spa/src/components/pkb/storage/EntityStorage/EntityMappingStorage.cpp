#include "EntityMappingStorage.h"
#include <unordered_set>
#include <unordered_map>
#include <string>

EntityMappingStorage::EntityMappingStorage() : EntityStorage(), map(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}
