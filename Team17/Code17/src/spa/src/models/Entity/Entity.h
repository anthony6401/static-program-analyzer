#pragma once

#include <string>
#include <functional>


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

namespace std {
	template <> struct std::hash<Entity> {
		std::size_t operator()(Entity& e) const {
			return std::hash<std::string>()(e.getValue());
		}
	};
}