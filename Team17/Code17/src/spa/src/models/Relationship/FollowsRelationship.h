#include "Relationship.h"
#include "models/Entity/Entity.h"

class FollowsRelationship : public Relationship {
public:
	FollowsRelationship(Entity* leftEntity, Entity* rightEntity);
};