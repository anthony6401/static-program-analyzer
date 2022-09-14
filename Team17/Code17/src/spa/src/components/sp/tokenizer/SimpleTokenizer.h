#pragma once

#include <string>
#include <vector>
#include <stack>
#include <regex>
#include "./StmtStack.h"
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"

class SimpleTokenizer {
    public:
        SimpleTokenizer(Extractor* client);
        void tokenizeCode(std::string code);
        StmtStack newStack(SimpleToken& token);

    private:
        Extractor* extractor;

};
