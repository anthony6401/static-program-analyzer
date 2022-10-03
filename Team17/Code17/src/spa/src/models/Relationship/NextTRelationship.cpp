#include "NextTRelationship.h"
#include "Relationship.h"

#include "models/Entity/Entity.h"

NextTRelationship::NextTRelationship(Entity* leftEntity, Entity* rightEntity) : Relationship(leftEntity, rightEntity) {}
