#include "../PatternObject.h"
#include "../ReuseableTokenObject.h"

#include "components/pkb/manager/PatternManager.h"

#include <catch.hpp>

TEST_CASE("Pattern Manager test") {
	PatternManager patternManager = PatternManager();

	//ASSIGN
	REQUIRE(patternManager.storePattern(assignPatternOne));
	REQUIRE(patternManager.storePattern(assignPatternTwo));
	REQUIRE(patternManager.storePattern(assignPatternThree));
	REQUIRE(patternManager.storePattern(assignPatternFour));
	REQUIRE(patternManager.storePattern(assignPatternFive));
	REQUIRE(patternManager.storePattern(assignPatternSix));
	REQUIRE(patternManager.storePattern(assignPatternSeven));
	REQUIRE(patternManager.storePattern(assignPatternEight));

	//IF
	REQUIRE(patternManager.storePattern(ifPatternOne));
	REQUIRE(patternManager.storePattern(ifPatternOneDup));
	REQUIRE(patternManager.storePattern(ifPatternTwo));

	//WHILE
	REQUIRE(patternManager.storePattern(whilePatternOne));
	REQUIRE(patternManager.storePattern(whilePatternOneDup));
	REQUIRE(patternManager.storePattern(whilePatternTwo));

	//ASSIGN
	std::unordered_set<std::string> assignGetPatternNameNameOne = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = patternManager.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

	//IF
	std::unordered_set<std::string> ifGetPatternNameNameOne = patternManager.getPattern(DesignEntity::IF, ifPatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> ifGetPatternNameNameTwo = patternManager.getPattern(DesignEntity::IF, ifPatternTokenObjectFirstTwo, TokenObject());
	
	//WHILE
	std::unordered_set<std::string> whileGetPatternNameNameOne = patternManager.getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> whileGetPatternNameNameTwo = patternManager.getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo, TokenObject());

	//ASSIGN
	std::unordered_set<std::string> expectedGetPatternNameNameOne({ assignLineNumOne, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameNameTwo({ assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprOne({ assignLineNumFive });
	std::unordered_set<std::string> expectedGetPatternNameSubexprTwo({ assignLineNumTwo, assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprThree({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWildcardOne({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWilcardTwo({ assignLineNumTwo, assignLineNumSix });

	//IF
	std::unordered_set<std::string> expectedResultIfGetPatternOne({ ifLineNumOne });
	std::unordered_set<std::string> expectedResultIfGetPatternTwo({ ifLineNumOne, ifLineNumTwo });

	//WHILE
	std::unordered_set<std::string> expectedResultWhileGetPatternOne({ whileLineNumOne });
	std::unordered_set<std::string> expectedResultWhileGetPatternTwo({ whileLineNumOne, whileLineNumTwo });

	//ASSIGN 
	REQUIRE(assignGetPatternNameNameOne == expectedGetPatternNameNameOne);
	REQUIRE(assignGetPatternNameNameTwo == expectedGetPatternNameNameTwo);
	REQUIRE(assignGetPatternNameSubexprOne == expectedGetPatternNameSubexprOne);
	REQUIRE(assignGetPatternNameSubexprTwo == expectedGetPatternNameSubexprTwo);
	REQUIRE(assignGetPatternNameSubexprThree == expectedGetPatternNameSubexprThree);
	REQUIRE(assignGetPatternNameWildcardOne == expectedGetPatternNameWildcardOne);
	REQUIRE(assignGetPatternNameWildcardTwo == expectedGetPatternNameWilcardTwo);

	//IF
	REQUIRE(ifGetPatternNameNameOne == expectedResultIfGetPatternOne);
	REQUIRE(ifGetPatternNameNameTwo == expectedResultIfGetPatternTwo);

	//WHILE
	REQUIRE(whileGetPatternNameNameOne == expectedResultWhileGetPatternOne);
	REQUIRE(whileGetPatternNameNameTwo == expectedResultWhileGetPatternTwo);

	//ASSIGN
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = patternManager.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = patternManager.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = patternManager.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = patternManager.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = patternManager.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = patternManager.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

	//IF
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameOne = patternManager.getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameTwo = patternManager.getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstTwo);

	//WHILE
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameOne = patternManager.getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameTwo = patternManager.getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo);

	//ASSIGN
	std::vector<std::pair<std::string, std::string>> assignExpectedGetPatternPairNameNameOne{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> assignExpectedGetPatternPairNameNameTwo{ {assignLineNumSix, assignFirstValueSix},
																					{assignLineNumSeven, assignFirstValueSeven} };
	std::vector<std::pair<std::string, std::string>> assignExpectedGetPatternPairNameSubexprOne{ {assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumFive, assignFirstValueFive} };
	std::vector<std::pair<std::string, std::string>> assignExpectedGetPatternPairNameSubexprTwo{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumSix, assignFirstValueSix},
																						{assignLineNumSeven, assignFirstValueSeven},
																						{assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> assignExpectedGetPatternPairNameSubexprThree{ {assignLineNumOne, assignFirstValueOne},
																						 {assignLineNumFour, assignFirstValueFour},
																						 {assignLineNumFive, assignFirstValueFive},
																						 {assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> assignExpectedGetPatternPairNameWilcard{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumFour, assignFirstValueFour},
																						{assignLineNumFive, assignFirstValueFive},
																						{assignLineNumSix, assignFirstValueSix},
																						{assignLineNumSeven, assignFirstValueSeven},
																						{assignLineNumEight, assignFirstValueEight} };

	//IF
	std::vector<std::pair<std::string, std::string>> ifExpectedGetPatternPairNameNameOne{	{ ifLineNumOne, ifFirstValueOne },
																							{ ifLineNumTwo, ifFirstValueTwo},
																							{ ifLineNumOne, ifFirstValueTwo} };

	std::vector<std::pair<std::string, std::string>> ifExpectedGetPatternPairNameNameTwo{	{ ifLineNumOne, ifFirstValueOne },
																							{ ifLineNumTwo, ifFirstValueTwo},
																							{ ifLineNumOne, ifFirstValueTwo} };

	//WHILE
	std::vector<std::pair<std::string, std::string>> whileExpectedGetPatternPairNameNameOne{ { whileLineNumOne, whileFirstValueOne },
																							{ whileLineNumTwo, whileFirstValueTwo},
																							{ whileLineNumOne, whileFirstValueTwo} };

	std::vector<std::pair<std::string, std::string>> whileExpectedGetPatternPairNameNameTwo{ { whileLineNumOne, whileFirstValueOne },
																							{ whileLineNumTwo, whileFirstValueTwo},
																							{ whileLineNumOne, whileFirstValueTwo} };

	sort(assignGetPatternPairNameNameOne.begin(), assignGetPatternPairNameNameOne.end());
	sort(assignGetPatternPairNameNameTwo.begin(), assignGetPatternPairNameNameTwo.end());
	sort(assignGetPatternPairNameSubexprOne.begin(), assignGetPatternPairNameSubexprOne.end());
	sort(assignGetPatternPairNameSubexprTwo.begin(), assignGetPatternPairNameSubexprTwo.end());
	sort(assignGetPatternPairNameSubexprThree.begin(), assignGetPatternPairNameSubexprThree.end());
	sort(assignGetPatternPairNameWildcard.begin(), assignGetPatternPairNameWildcard.end());

	sort(ifGetPatternPairNameNameOne.begin(), ifGetPatternPairNameNameOne.end());
	sort(ifGetPatternPairNameNameTwo.begin(), ifGetPatternPairNameNameTwo.end());
	sort(ifExpectedGetPatternPairNameNameOne.begin(), ifExpectedGetPatternPairNameNameOne.end());
	sort(ifExpectedGetPatternPairNameNameTwo.begin(), ifExpectedGetPatternPairNameNameTwo.end());

	sort(whileGetPatternPairNameNameOne.begin(), whileGetPatternPairNameNameOne.end());
	sort(whileGetPatternPairNameNameTwo.begin(), whileGetPatternPairNameNameTwo.end());
	sort(whileExpectedGetPatternPairNameNameOne.begin(), whileExpectedGetPatternPairNameNameOne.end());
	sort(whileExpectedGetPatternPairNameNameTwo.begin(), whileExpectedGetPatternPairNameNameTwo.end());

	REQUIRE(assignGetPatternPairNameNameOne == assignExpectedGetPatternPairNameNameOne);
	REQUIRE(assignGetPatternPairNameNameTwo == assignExpectedGetPatternPairNameNameTwo);
	REQUIRE(assignGetPatternPairNameSubexprOne == assignExpectedGetPatternPairNameSubexprOne);
	REQUIRE(assignGetPatternPairNameSubexprTwo == assignExpectedGetPatternPairNameSubexprTwo);
	REQUIRE(assignGetPatternPairNameSubexprThree == assignExpectedGetPatternPairNameSubexprThree);
	REQUIRE(assignGetPatternPairNameWildcard == assignExpectedGetPatternPairNameWilcard);

	REQUIRE(ifGetPatternPairNameNameOne == ifExpectedGetPatternPairNameNameOne);
	REQUIRE(ifGetPatternPairNameNameTwo == ifExpectedGetPatternPairNameNameTwo);

	REQUIRE(whileGetPatternPairNameNameOne == whileExpectedGetPatternPairNameNameOne);
	REQUIRE(whileGetPatternPairNameNameTwo == whileExpectedGetPatternPairNameNameTwo);
}
