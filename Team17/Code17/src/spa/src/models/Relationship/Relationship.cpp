#include "Relationship.h"
#include <string>
#include "../Entity/Entity.h"

Relationship::Relationship(Entity* leftEntity, Entity* rightEntity) : leftEntity(leftEntity), rightEntity(rightEntity) {}

Entity* Relationship::getLeftEntity() {
	return this->leftEntity;
}

Entity* Relationship::getRightEntity() {
	return this->rightEntity;
}
