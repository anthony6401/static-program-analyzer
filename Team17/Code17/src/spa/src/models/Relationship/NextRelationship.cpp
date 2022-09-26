#include "NextRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

NextRelationship::NextRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}
