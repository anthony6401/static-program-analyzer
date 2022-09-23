#pragma once

#include <vector>
#include <string>

enum class SpTokenType {
    TPROCEDURE,
    TELSE,
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
    TOPR,
    TEXPR,
    TSTMTLIST,
    TPROGRAM
};

class Extractor;

class SimpleToken {
public:
    SimpleToken(SpTokenType type, std::string value, int statementNumber);
    SpTokenType type;
    int statementNumber;
    std::string value;
    void setChildren(std::vector<SimpleToken> tokens);
    std::vector<SimpleToken> getChildren();

private:
    std::vector<SimpleToken> children;

};
