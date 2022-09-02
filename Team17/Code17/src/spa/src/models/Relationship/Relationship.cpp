#include "Relationship.h"
#include <string>
#include "../Entity/Entity.h"

SuchThat::SuchThat(Entity leftEntity, Entity rightEntity) : leftEntity(leftEntity), rightEntity(rightEntity) {}

Entity SuchThat::getLeftEntity() {
	return this->leftEntity;
}

Entity SuchThat::getRightEntity() {
	return this->rightEntity;
}
