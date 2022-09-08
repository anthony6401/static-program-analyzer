#pragma once

#include <string>
#include <vector>
#include <regex>
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"
#include "../../pkb/clients/SPClient.h"

class SimpleTokenizer {
    public:
        SimpleTokenizer(SPClient* client, Extractor extractor);
        void tokenizeCode(std::string code);

    private:
        SPClient* client;
        Extractor extractor;

};
