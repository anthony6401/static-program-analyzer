#pragma once

#include "SimpleToken.h"
#include "../../models/Relationship/Relationship.h"

#include <vector>

using namespace std;

class Extractor {
public:
	Extractor::Extractor();
	vector<Relationship*> extractRelationships(SimpleToken parentToken);
};
