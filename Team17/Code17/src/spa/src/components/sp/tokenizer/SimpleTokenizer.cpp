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
    
    std::stack<StmtStack*> stmtStack;
    StmtStack* currentStack = new ProgramStack(SimpleToken(SpTokenType::TPROGRAM, "", 0, NULL));
    if (codeLines.size() < 3) {//temporary solution
        throw std::invalid_argument("Received invalid SIMPLE code. Empty procedure");
    }
    for (std::string line : codeLines) {
        line = std::regex_replace(line, tokenDelimiters, " $& ");
        std::vector<std::string> lineTokens = SpUtils::split(line, whiteSpace);
        SimpleToken lineToken = SimpleParser::parseLine(lineTokens, line);
        (lineToken.parseFunction)(lineToken, lineTokens, extractor);
        if (lineToken.type == SpTokenType::TPROCEDURE) {
            stmtStack.push(currentStack);
            currentStack = new NestedStack(lineToken);
        } else if (lineToken.type == SpTokenType::TWHILE) {
            stmtStack.push(currentStack);
            currentStack = new NestedStack(lineToken);
        } else if (lineToken.type == SpTokenType::TIF) {
            stmtStack.push(currentStack);
            currentStack = new IfStack(lineToken);
        } else if (lineToken.type == SpTokenType::TCLOSE) {
            if (stmtStack.size() == 0) {
                throw std::invalid_argument("Received invalid SIMPLE code. Extra }");
            }
            currentStack->put(lineToken);
            if (!(currentStack->isIf())) {
                StmtStack* parentStack = stmtStack.top();
                parentStack->put(currentStack->dump());
                delete currentStack;
                currentStack = parentStack;
                stmtStack.pop();
            }
        } else {
            currentStack->put(lineToken);
        }
    }
    if (stmtStack.size() == 0) {
        SimpleToken procedure = currentStack->dump().getChildren().at(0);
        procedure.setChildren(procedure.getChildren().at(1).getChildren());
        extractor->extractAll(procedure);
    } else {
        throw std::invalid_argument("Received incomplete SIMPLE code");
    }
}
