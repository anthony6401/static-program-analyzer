#include "models/Entity/Entity.h"
#include "EntityStorage.h"
#include <unordered_set>

EntityStorage::EntityStorage() : set(new std::unordered_set<std::string>()) {}

int EntityStorage::getSize() {
	return this->set->size();
}
