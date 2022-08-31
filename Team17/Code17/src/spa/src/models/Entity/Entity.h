#pragma once

#include <string>


class Entity {
	public:
		Entity(std::string n);
		std::string getValue();
		bool operator==(const Entity& other) const {
			return value == other.value;
		}
	private:
		std::string value;

};

