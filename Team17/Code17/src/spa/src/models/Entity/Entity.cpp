#include <string>

#include "Entity.h"


Entity::Entity(std::string entityValue) {
	this->value = entityValue;
}

std::string Entity::getValue() {
	return this->value;
}
