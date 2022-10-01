#include "CallsRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

CallsRelationship::CallsRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}