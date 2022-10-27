#pragma once
#include <vector>
#include <string>
#include <regex>
#include "../SimpleToken.h"

struct SimpleHash {
    std::size_t operator()(const Entity _entity) const {
        std::size_t h1 = std::hash<std::string>()(_entity.getValue());
        return h1;
    }
};

class SpUtils {
    public:
        static std::vector<std::string> split(std::string code, std::regex delimiters);
        static std::string join(std::vector<std::string>, std::string connector);
        static int findOpenBracket(std::vector<std::string>& tokens, int end);
        static int findCloseBracket(std::vector<std::string>& tokens, int start);
};
