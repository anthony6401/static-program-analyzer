#include "models/Entity/Entity.h"
#include "EntityStorage.h"
#include <unordered_set>

EntityStorage::EntityStorage() : set(new std::unordered_set<Entity*>()) {}
