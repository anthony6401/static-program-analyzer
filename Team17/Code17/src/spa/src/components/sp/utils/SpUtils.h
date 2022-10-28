#pragma once
#include <vector>
#include <string>
#include <regex>
#include "../../../models/Entity/Entity.h"

struct SimpleHash {
    std::size_t operator()(const Entity* _entity) const {
        std::size_t h1 = std::hash<std::string>()(_entity->getValue());
        std::size_t h2 = std::hash<std::string>()(typeid(_entity).name());
        return h1 ^ (h2 << 1);
    }
};

class SpUtils {
    public:
        static std::vector<std::string> split(std::string code, std::regex delimiters);
        static std::string join(std::vector<std::string>, std::string connector);
        static int findOpenBracket(std::vector<std::string>& tokens, int end);
        static int findCloseBracket(std::vector<std::string>& tokens, int start);
};
