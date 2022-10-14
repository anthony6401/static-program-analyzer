#include "SpUtils.h"

std::vector<std::string> SpUtils::split(std::string code, std::regex delimiters) {
    std::vector<std::string> tokens;
    std::regex_iterator<std::string::iterator> start(code.begin(), code.end(), delimiters);
    std::regex_iterator<std::string::iterator> end;

    while (start != end) {
        std::string token = start->str();
        tokens.push_back(token);
        ++start;
    }
    return tokens;
}

std::string SpUtils::join(std::vector<std::string> tokens, std::string connector) {
    std::string output = "";
    for (std::vector<std::string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i) {
        output += *i;
        output += connector;
    }
    if (!(output.empty()) && !(connector.empty())) {
        output.pop_back();
    }
    return output;
}

//Return indice of ( that pairs with last )
int SpUtils::findOpenBracket(std::vector<std::string>& tokens, int end) {
    if (tokens.at(end) != ")") {
        return -1;
    }
    int bracketStack = 1;
    for (int i = end - 1; i >= 0; i--) {
        std::string token = tokens.at(i);
        if (token == ")") {
            bracketStack++;
        } else if (token == "(") {
            bracketStack--;
            if (bracketStack == 0) {
                return i;
            }
        } 
    }
    return -1;
}

//Return indice of ) that pairs with first (
int SpUtils::findCloseBracket(std::vector<std::string>& tokens, int start) {
    if (tokens.at(start) != "(") {
        return -1;
    }
    int bracketStack = 1;
    int endIndice = tokens.size();
    for (int i = start + 1; i < endIndice; i++) {
        std::string token = tokens.at(i);
        if (token == "(") {
            bracketStack++;
        }
        else if (token == ")") {
            bracketStack--;
            if (bracketStack == 0) {
                return i;
            }
        }
    }
    return -1;
}

