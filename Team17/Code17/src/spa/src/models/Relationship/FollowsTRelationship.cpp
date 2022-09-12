#include "FollowsTRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

FollowsTRelationship::FollowsTRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}