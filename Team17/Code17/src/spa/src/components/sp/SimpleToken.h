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
    TVARIABLE,
    TCONSTANT,
    TCLOSE,
    TOPR,
    TEXPR
};

class Extractor;

class SimpleToken {
public:
    SimpleToken();
    SimpleToken(SpTokenType type, std::string value, int statementNumber);
    SpTokenType type;
    int statementNumber;
    std::string value;
    void setChildren(std::vector<SimpleToken> tokens);
    std::vector<SimpleToken> getChildren();
    bool operator==(const SimpleToken& other) const {
        return value == other.value && 
            statementNumber == other.statementNumber && 
            value == value && 
            children == children;
    }
    std::size_t operator()(const SimpleToken& _token) const {
        std::size_t h1 = std::hash<SpTokenType>()(_token.type);
        std::size_t h2 = std::hash<int>()(_token.statementNumber);
        std::size_t h3 = std::hash<std::string>()(_token.value);
        return ((h1 ^ (h2 << 1)) << 1) ^ h3;
    }

private:
    std::vector<SimpleToken> children;

};
