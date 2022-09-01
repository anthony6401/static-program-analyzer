#pragma once

#include <string>


class Entity {
public:
	Entity(std::string entityValue);
	std::string getValue();
	virtual bool operator==(const Entity& other) const {
		return value == other.value;
	}
protected:
	std::string value;

};
