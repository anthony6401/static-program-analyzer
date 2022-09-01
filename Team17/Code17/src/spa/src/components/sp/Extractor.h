#pragma once

#include "SimpleToken.h"
#include "../../models/Relationship/Relationship.h"

class Extractor {
public:
	Extractor::Extractor();
	Relationship extractRelationship(SimpleToken parentToken);

private:
	SimpleToken current;

};
