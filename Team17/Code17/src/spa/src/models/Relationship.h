#pragma once

#include <string>

class Relationship {
private:
	std::string leftValue;
	std::string rightValue;

public:
	Relationship(std::string leftValue, std::string rightValue);
	std::string getLeftValue();
	std::string getRightValue();
};