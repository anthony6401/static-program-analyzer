#include "ModifyRelationship.h"
#include <string>
#include "../Entity/Entity.h"

ModifyRelationship::ModifyRelationship(Entity leftEntity, Entity rightEntity) : SuchThat(leftEntity, rightEntity) {}
