#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

class Entity {
	public:
		Entity(std::string n);
		std::string getValue();
	private:
		std::string value;

};

