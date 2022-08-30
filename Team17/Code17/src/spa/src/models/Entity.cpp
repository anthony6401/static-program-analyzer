#include <string>

#include "Entity.h"


Entity::Entity(std::string n) {
	this->name = n;
}

std::string Entity::getName() {
	return this->name;
}