#pragma once

#include <string>
#include <vector>
#include "SimpleToken.h"

class SimpleTokenizer {
    public:
        SimpleTokenizer();
        void processCode(std::string code);
        std::vector<std::string> splitBracket(std::string code);
};