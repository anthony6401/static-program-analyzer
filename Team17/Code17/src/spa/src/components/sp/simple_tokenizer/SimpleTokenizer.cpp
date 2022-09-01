#include "SimpleTokenizer.h"
#include "../utils/SpUtils.h"

SimpleTokenizer::SimpleTokenizer(std::string code) {
    std::vector<std::string> codeLines = SpUtils::split(code, "[^{};]*[{};]");
    SpUtils::split(code, "^[^=(\s]+");
}
