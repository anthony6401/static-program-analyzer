#pragma once

#include <string>
#include <vector>
#include <regex>
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"
#include "../../pkb/clients/SPClient.h"

class SimpleTokenizer {
    public:
        SimpleTokenizer(Extractor* client);
        void tokenizeCode(std::string code);

    private:
        Extractor* extractor;

};
