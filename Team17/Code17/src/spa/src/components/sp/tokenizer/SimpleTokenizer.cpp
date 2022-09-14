#include "SimpleTokenizer.h"
#include "./ProgramStack.h"
#include "./IfStack.h"
#include "./NestedStack.h"
#include "../parser/SimpleParser.h"
#include "../utils/SpUtils.h"

SimpleTokenizer::SimpleTokenizer(Extractor* extractor) {
    this->extractor = extractor;
}

/// <summary>
/// Main method to tokenize SIMPLE code for design extractor
/// </summary>
/// <param name="code">SIMPLE code to be processed</param>
void SimpleTokenizer::tokenizeCode(std::string code) {
    std::regex lineDelimiters = std::regex("[^{};]*[{};]");
    std::regex tokenDelimiters = std::regex("(==)|(!=)|(&&)|(\\|\\|)|(>=)|(<=)|[!%+\\-/*=(){};<>]");
    std::regex whiteSpace = std::regex("\\S+");

    std::vector<std::string> codeLines = SpUtils::split(code, lineDelimiters);
    if (codeLines.empty()) {
        throw std::invalid_argument("Received invalid SIMPLE code");
    }
    /*
    std::stack<StmtStack> stmtStack;
    StmtStack currentStack = ProgramStack(SimpleToken(SpTokenType::TPROGRAM, "", 0, NULL));
    bool isIf = false;

    for (std::string line : codeLines) {
        line = std::regex_replace(line, tokenDelimiters, " $& ");
        std::vector<std::string> lineTokens = SpUtils::split(line, whiteSpace);
        SimpleToken lineToken = SimpleParser::parseLine(lineTokens, line);
        (lineToken.parseFunction)(lineToken, lineTokens, extractor);
        currentStack->put(lineToken);
        if (lineToken.type == SpTokenType::TPROCEDURE) {
            stmtStack.push(currentStack);
            currentStack = &NestedStack(&lineToken);
        } else if (lineToken.type == SpTokenType::TWHILE) {
            stmtStack.push(currentStack);
            currentStack = &NestedStack(&lineToken);
        } else if (lineToken.type == SpTokenType::TIF) {
            isIf = true;
            stmtStack.push(currentStack);
            currentStack = &IfStack(&lineToken);
        } else if (lineToken.type == SpTokenType::TCLOSE) {
            if (isIf) {
                isIf = false;
            } else {
                currentStack = stmtStack.top();
                stmtStack.pop();
            }
        }
    }*/
}
