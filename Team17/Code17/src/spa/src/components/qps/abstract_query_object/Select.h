#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

using namespace qps;

class Select {
private:
    std::string synonym;

public:
    Select();
    Select(std::string synonym);
    std::string getSynonym();
    bool operator==(const Select& other) const {
        return synonym == other.synonym;
    }
};

#endif //SPA_SELECT_H
