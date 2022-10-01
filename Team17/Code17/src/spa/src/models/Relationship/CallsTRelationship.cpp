#include "CallsTRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

CallsTRelationship::CallsTRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}
