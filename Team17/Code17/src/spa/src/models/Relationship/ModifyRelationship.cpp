#include "ModifyRelationship.h"
#include <string>
#include "../Entity/Entity.h"

ModifyRelationship::ModifyRelationship(Entity leftEntity, Entity rightEntity) : Relationship(leftEntity, rightEntity) {}
