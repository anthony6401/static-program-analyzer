#pragma once
#include "Relationship.h"
#include <string>

class UsesRelationship : public Relationship {

public:
	UsesRelationship(std::string leftValue, std::string rightValue);
};