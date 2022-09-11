#include <locale>
#include <regex>
#include <stack>
#include "SimpleValidator.h"
#include "../utils/SpUtils.h"

bool SimpleValidator::validateVariable(std::string& token) {
    std::regex constant = std::regex("[a-zA-Z][a-zA-Z0-9]*");
    return std::regex_match(token, std::regex(constant));
}

bool SimpleValidator::validateConstant(std::string& token) {
    std::regex numeric = std::regex("(0|[1-9][0-9]*)");
    return std::regex_match(token, numeric);
}

bool SimpleValidator::validateExprOpr(std::string& token) {
    std::regex operand = std::regex("([+-/*%])");
    return std::regex_match(token, operand);
}
