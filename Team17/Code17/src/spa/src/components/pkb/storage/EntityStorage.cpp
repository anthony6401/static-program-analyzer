#include "models/Entity/Entity.h"
#include "EntityStorage.h"
#include <unordered_set>

EntityStorage::EntityStorage() : set(std::unordered_set<std::string>()) {}

int EntityStorage::getSize() {
	return set.size();
}
