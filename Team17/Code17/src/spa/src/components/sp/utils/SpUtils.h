#pragma once
#include <vector>
#include <string>
#include <regex>

class SpUtils {
    public:
        static std::vector<std::string> split(std::string code, std::string delimiters);
};