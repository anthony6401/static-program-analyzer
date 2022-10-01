#include "CallsTRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

CallsTRelationship::CallsRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}
