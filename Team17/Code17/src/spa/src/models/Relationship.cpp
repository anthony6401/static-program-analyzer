#include "Relationship.h"
#include <string>

Relationship::Relationship(std::string leftValue, std::string rightValue) {
	this->leftValue = leftValue;
	this->rightValue = rightValue;
}

std::string Relationship::getLeftValue() {
	return this->leftValue;
}

std::string Relationship::getRightValue() {
	return this->rightValue;
}