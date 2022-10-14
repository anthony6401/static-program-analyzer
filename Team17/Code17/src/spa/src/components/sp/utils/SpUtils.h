#pragma once
#include <vector>
#include <string>
#include <regex>

class SpUtils {
    public:
        static std::vector<std::string> split(std::string code, std::regex delimiters);
        static std::string join(std::vector<std::string>, std::string connector);
        static int findOpenBracket(std::vector<std::string>& tokens, int end);
        static int findCloseBracket(std::vector<std::string>& tokens, int start);
};
