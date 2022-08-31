#pragma once

#include <string>


class Entity {
	public:
		Entity(std::string n);
		std::string getValue();
	private:
		std::string value;

};

