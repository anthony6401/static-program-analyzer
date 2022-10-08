#pragma once

#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"
#include "models/Pattern/IfPattern.h"

static std::string assignLineNumOne = "1";
static std::string assignFirstValueOne = "a";
static std::string assignSecondValueOne = "a/x%y-1";
static std::string assignLineNumTwo = "2";
static std::string assignFirstValueTwo = "b";
static std::string assignSecondValueTwo = "a*b-abc+100";
static std::string assignLineNumThree = "3";
static std::string assignFirstValueThree = "c";
static std::string assignSecondValueThree = "a/(b*(d*(100/c)))";
static std::string assignLineNumFour = "4";
static std::string assignFirstValueFour = "d";
static std::string assignSecondValueFour = "x-y+z*10";
static std::string assignLineNumFive = "5";
static std::string assignFirstValueFive = "a";
static std::string assignSecondValueFive = "x+100";
static std::string assignLineNumSix = "6";
static std::string assignFirstValueSix = "b";
static std::string assignSecondValueSix = "a";
static std::string assignLineNumSeven = "7";
static std::string assignFirstValueSeven = "c";
static std::string assignSecondValueSeven = "a";
static std::string assignLineNumEight = "8";
static std::string assignFirstValueEight = "a";
static std::string assignSecondValueEight = "a/x%y-1";

static std::string assignSecondValueForTokenOne = "a/x%y-1";
static std::string assignSecondValueForTokenTwo = "a";
static std::string assignSecondValueForTokenThree = "x";

static std::string assignSubexprOne = "100";
static std::string assignSubexprTwo = "a";
static std::string assignSubexprThree = "x";

static kb::Pattern* assignPatternOne = new AssignPattern(assignLineNumOne, assignFirstValueOne, assignSecondValueOne);
static kb::Pattern* assignPatternTwo = new AssignPattern(assignLineNumTwo, assignFirstValueTwo, assignSecondValueTwo);
static kb::Pattern* assignPatternThree = new AssignPattern(assignLineNumThree, assignFirstValueThree, assignSecondValueThree);
static kb::Pattern* assignPatternFour = new AssignPattern(assignLineNumFour, assignFirstValueFour, assignSecondValueFour);
static kb::Pattern* assignPatternFive = new AssignPattern(assignLineNumFive, assignFirstValueFive, assignSecondValueFive);
static kb::Pattern* assignPatternSix = new AssignPattern(assignLineNumSix, assignFirstValueSix, assignSecondValueSix);
static kb::Pattern* assignPatternSeven = new AssignPattern(assignLineNumSeven, assignFirstValueSeven, assignSecondValueSeven);
static kb::Pattern* assignPatternEight = new AssignPattern(assignLineNumEight, assignFirstValueEight, assignSecondValueEight);


static std::string ifLineNumOne = "100";
static std::string ifFirstValueOne = "x";
static std::string ifLineNumTwo = "200";
static std::string ifFirstValueTwo = "abc";

static kb::Pattern* ifPatternOne = new IfPattern(ifLineNumOne, ifFirstValueOne);
static kb::Pattern* ifPatternOneDup = new IfPattern(ifLineNumOne, ifFirstValueTwo);
static kb::Pattern* ifPatternTwo = new IfPattern(ifLineNumTwo, ifFirstValueTwo);