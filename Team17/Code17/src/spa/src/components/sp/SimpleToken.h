#pragma once

#include <vector>
#include <string>
#include "../pkb/clients/SPClient.h"

enum class SpTokenType {
    TPROCEDURE,
    TELSE,
    TSTMT,
    TREAD,
    TPRINT,
    TCALL,
    TWHILE,
    TIF,
    TASSIGN,
    TCONDEXPR,
    TVARIABLE,
    TCONSTANT,
    TCLOSE,
    TOPR
};

class Extractor;

class SimpleToken {
public:
    SimpleToken(SpTokenType type, std::string value,
        int statementNumber, void (*parseFunction)(SimpleToken&, std::vector<std::string>&,
            Extractor* extractor, SPClient* client));
    SpTokenType type;
    int statementNumber;
    void (*parseFunction)(SimpleToken&, std::vector<std::string>&, Extractor* extractor, SPClient* client);
    std::string value;
    void setChildren(std::vector<SimpleToken> tokens);
    std::vector<SimpleToken> getChildren();

private:
    std::vector<SimpleToken> children;

};
