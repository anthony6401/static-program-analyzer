#include "SuchThatClauseSyntaxChecker.h"
#include <iostream>

using namespace qps;

SuchThatClauseSyntaxChecker::SuchThatClauseSyntaxChecker() {
	this->suchThatSyntax.push(TokenType::RELREF);
	this->suchThatSyntax.push(TokenType::THAT);
	this->suchThatSyntax.push(TokenType::SUCH);
};

SuchThatClauseSyntaxChecker::~SuchThatClauseSyntaxChecker() {};