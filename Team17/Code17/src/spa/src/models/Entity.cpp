#include <string>

#include "Entity.h"


Entity::Entity(std::string n) {
	this->value = n;
}

std::string Entity::getValue() {
	return this->value;
}