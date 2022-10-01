#pragma once

#include "../SimpleToken.h"


class SimpleTokenizer {
    public:
        static std::vector<std::string> tokenizeCode(std::string code);
        static std::vector<std::string> tokenizeLine(std::string code);
};
