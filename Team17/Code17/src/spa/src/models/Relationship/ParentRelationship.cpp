#include "ParentRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

ParentRelationship::ParentRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}