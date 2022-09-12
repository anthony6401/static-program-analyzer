#include "ParentTRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

ParentTRelationship::ParentTRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}
