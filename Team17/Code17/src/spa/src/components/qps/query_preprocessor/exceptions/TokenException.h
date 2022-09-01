#ifndef SPA_TOKENEXCEPTION_H
#define SPA_TOKENEXCEPTION_H

#include <exception>
#include "string"


class TokenException : public std::exception {
    std::string _msg;
public:
    TokenException() : _msg("Token Exception Caught"){}
    virtual const char* what() const noexcept override
    {
        return _msg.c_str();
    }
};

#endif //SPA_TOKENEXCEPTION_H
