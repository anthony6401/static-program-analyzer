#pragma once
#include "Relationship.h"
#include <string>

class ModifyRelationship : public Relationship {

public:
	ModifyRelationship(std::string leftValue, std::string rightValue);
};