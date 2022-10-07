#include "CallEntity.h"
#include "Entity.h"

#include <string>

CallEntity::CallEntity(std::string entityValue, std::string valueName) : StatementEntity(entityValue), valueName(valueName) {};

std::string CallEntity::getValueName() {
	return this->valueName;
}
