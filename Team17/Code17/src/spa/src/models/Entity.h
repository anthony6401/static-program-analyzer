#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

class Entity {
	public:
		Entity(std::string n);
		std::string getName();
	private:
		std::string name;

};

