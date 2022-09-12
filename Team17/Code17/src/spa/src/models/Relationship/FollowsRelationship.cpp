#include "FollowsRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

FollowsRelationship::FollowsRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}