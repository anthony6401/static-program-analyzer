#pragma once
#include <vector>
#include <string>
#include <regex>
#include "../SimpleToken.h"

struct SimpleHash {
    std::size_t operator()(const SimpleToken& _token) const {
        std::size_t h1 = std::hash<SpTokenType>()(_token.type);
        std::size_t h2 = std::hash<int>()(_token.statementNumber);
        std::size_t h3 = std::hash<std::string>()(_token.value);
        return ((h1 ^ (h2 << 1)) << 1) ^ h3;
    }
};

class SpUtils {
    public:
        static std::vector<std::string> split(std::string code, std::regex delimiters);
        static std::string join(std::vector<std::string>, std::string connector);
        static int findOpenBracket(std::vector<std::string>& tokens, int end);
        static int findCloseBracket(std::vector<std::string>& tokens, int start);
};
