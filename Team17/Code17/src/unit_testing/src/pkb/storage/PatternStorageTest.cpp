#include <catch.hpp>

#include "components/pkb/storage/PatternStorage/PatternStorage.h"
#include "components/pkb/storage/PatternStorage/AssignPatternStorage.h"
#include "components/pkb/storage/PatternStorage/IfPatternStorage.h"
#include "components/pkb/storage/PatternStorage/WhilePatternStorage.h"
#include "../PatternObject.h"
#include "../ReuseableTokenObject.h"

TEST_CASE("Assign Pattern Storage Test") {
	PatternStorage* assignPatternStorage = new AssignPatternStorage();

	REQUIRE(assignPatternStorage->storePattern(assignPatternOne));
	REQUIRE(assignPatternStorage->storePattern(assignPatternTwo));
	REQUIRE(assignPatternStorage->storePattern(assignPatternThree));
	REQUIRE(assignPatternStorage->storePattern(assignPatternFour));
	REQUIRE(assignPatternStorage->storePattern(assignPatternFive));
	REQUIRE(assignPatternStorage->storePattern(assignPatternSix));
	REQUIRE(assignPatternStorage->storePattern(assignPatternSeven));
	REQUIRE(assignPatternStorage->storePattern(assignPatternEight));

	std::unordered_set<std::string> assignGetPatternNameNameOne = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildcardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = assignPatternStorage->getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildcardTokenObject);

	std::unordered_set<std::string> expectedGetPatternNameNameOne({ assignLineNumOne, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameNameTwo({ assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprOne({ assignLineNumFive });
	std::unordered_set<std::string> expectedGetPatternNameSubexprTwo({ assignLineNumTwo, assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprThree({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWildcardOne({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWilcardTwo({ assignLineNumTwo, assignLineNumSix });

	REQUIRE(assignGetPatternNameNameOne == expectedGetPatternNameNameOne);
	REQUIRE(assignGetPatternNameNameTwo == expectedGetPatternNameNameTwo);
	REQUIRE(assignGetPatternNameSubexprOne == expectedGetPatternNameSubexprOne);
	REQUIRE(assignGetPatternNameSubexprTwo == expectedGetPatternNameSubexprTwo);
	REQUIRE(assignGetPatternNameSubexprThree == expectedGetPatternNameSubexprThree);
	REQUIRE(assignGetPatternNameWildcardOne == expectedGetPatternNameWildcardOne);
	REQUIRE(assignGetPatternNameWildcardTwo == expectedGetPatternNameWilcardTwo);

	std::unordered_set<std::string> assignGetPatternWildcardNameNameOne = assignPatternStorage->getPatternWildcard(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternWildcardNameNameTwo = assignPatternStorage->getPatternWildcard(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternWildcardNameSubexprOne = assignPatternStorage->getPatternWildcard(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternWildcardNameSubexprTwo = assignPatternStorage->getPatternWildcard(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternWildcardNameSubexprThree = assignPatternStorage->getPatternWildcard(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternWildcardNameWildcard = assignPatternStorage->getPatternWildcard(DesignEntity::ASSIGN, wildcardTokenObject);

	std::unordered_set<std::string> expectedGetPatternWildcardNameNameOne = { assignLineNumOne, assignLineNumEight };
	std::unordered_set<std::string> expectedGetPatternWildcardNameNameTwo = { assignLineNumSix, assignLineNumSeven };
	std::unordered_set<std::string> expectedGetPatternWildcardNameSubexprOne = { assignLineNumTwo, assignLineNumThree, assignLineNumFive };
	std::unordered_set<std::string> expectedGetPatternWildcardNameSubexprTwo = { assignLineNumOne, assignLineNumTwo, assignLineNumThree, assignLineNumSix, assignLineNumSeven, assignLineNumEight };
	std::unordered_set<std::string> expectedGetPatternWildcardNameSubexprThree = { assignLineNumOne, assignLineNumFour, assignLineNumFive, assignLineNumEight };
	std::unordered_set<std::string> expectedGetPatternWildcardNameWilcard = { assignLineNumOne, assignLineNumTwo, assignLineNumThree, assignLineNumFour, assignLineNumFive, assignLineNumSix, assignLineNumSeven, assignLineNumEight };

	REQUIRE(assignGetPatternWildcardNameNameOne == expectedGetPatternWildcardNameNameOne);
	REQUIRE(assignGetPatternWildcardNameNameTwo == expectedGetPatternWildcardNameNameTwo);
	REQUIRE(assignGetPatternWildcardNameSubexprOne == expectedGetPatternWildcardNameSubexprOne);
	REQUIRE(assignGetPatternWildcardNameSubexprTwo == expectedGetPatternWildcardNameSubexprTwo);
	REQUIRE(assignGetPatternWildcardNameSubexprThree == expectedGetPatternWildcardNameSubexprThree);
	REQUIRE(assignGetPatternWildcardNameWildcard == expectedGetPatternWildcardNameWilcard);

	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = assignPatternStorage->getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = assignPatternStorage->getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = assignPatternStorage->getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = assignPatternStorage->getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = assignPatternStorage->getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = assignPatternStorage->getPatternPair(DesignEntity::ASSIGN, wildcardTokenObject);

	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameOne{ {assignLineNumOne, assignFirstValueOne}, 
																						{assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameTwo{ {assignLineNumSix, assignFirstValueSix}, 
																					{assignLineNumSeven, assignFirstValueSeven} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameSubexprOne{ {assignLineNumTwo, assignFirstValueTwo}, 
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumFive, assignFirstValueFive} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameSubexprTwo{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumTwo, assignFirstValueTwo}, 
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumSix, assignFirstValueSix},
																						{assignLineNumSeven, assignFirstValueSeven},
																						{assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameSubexprThree{ {assignLineNumOne, assignFirstValueOne},
																						 {assignLineNumFour, assignFirstValueFour},
																						 {assignLineNumFive, assignFirstValueFive},
																						 {assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameWilcard{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumFour, assignFirstValueFour},
																						{assignLineNumFive, assignFirstValueFive},
																						{assignLineNumSix, assignFirstValueSix},
																						{assignLineNumSeven, assignFirstValueSeven},
																						{assignLineNumEight, assignFirstValueEight} };

	sort(assignGetPatternPairNameNameOne.begin(), assignGetPatternPairNameNameOne.end());
	sort(assignGetPatternPairNameNameTwo.begin(), assignGetPatternPairNameNameTwo.end());
	sort(assignGetPatternPairNameSubexprOne.begin(), assignGetPatternPairNameSubexprOne.end());
	sort(assignGetPatternPairNameSubexprTwo.begin(), assignGetPatternPairNameSubexprTwo.end());
	sort(assignGetPatternPairNameSubexprThree.begin(), assignGetPatternPairNameSubexprThree.end());
	sort(assignGetPatternPairNameWildcard.begin(), assignGetPatternPairNameWildcard.end());

	REQUIRE(assignGetPatternPairNameNameOne == expectedGetPatternPairNameNameOne);
	REQUIRE(assignGetPatternPairNameNameTwo == expectedGetPatternPairNameNameTwo);
	REQUIRE(assignGetPatternPairNameSubexprOne == expectedGetPatternPairNameSubexprOne);
	REQUIRE(assignGetPatternPairNameSubexprTwo == expectedGetPatternPairNameSubexprTwo);
	REQUIRE(assignGetPatternPairNameSubexprThree == expectedGetPatternPairNameSubexprThree);
	REQUIRE(assignGetPatternPairNameWildcard == expectedGetPatternPairNameWilcard);
}

TEST_CASE("If Pattern Storage Test") {
	PatternStorage* ifPatternStorage = new IfPatternStorage();


	REQUIRE(ifPatternStorage->storePattern(ifPatternOne));
	REQUIRE(ifPatternStorage->storePattern(ifPatternTwo));
	REQUIRE(ifPatternStorage->storePattern(ifPatternOneDup));


	std::unordered_set<std::string> ifGetPatternNameNameOne = ifPatternStorage->getPattern(DesignEntity::IF, ifPatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> ifGetPatternNameNameTwo = ifPatternStorage->getPattern(DesignEntity::IF, ifPatternTokenObjectFirstTwo, TokenObject());

	std::unordered_set<std::string> expectedResultIfGetPatternOne({ ifLineNumOne });
	std::unordered_set<std::string> expectedResultIfGetPatternTwo({ ifLineNumOne, ifLineNumTwo });

	REQUIRE(ifGetPatternNameNameOne == expectedResultIfGetPatternOne);
	REQUIRE(ifGetPatternNameNameTwo == expectedResultIfGetPatternTwo);

	std::unordered_set<std::string> ifGetPatternWildcardOne = ifPatternStorage->getPatternWildcard(DesignEntity::IF, ifPatternTokenObjectFirstOne);

	std::unordered_set<std::string> expectedGetPatternWildcard = { ifLineNumOne, ifLineNumTwo };

	REQUIRE(ifGetPatternWildcardOne == expectedGetPatternWildcard);

	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameOne = ifPatternStorage->getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameTwo = ifPatternStorage->getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstTwo);
	
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameOne{ { ifLineNumOne, ifFirstValueOne },
																						{ ifLineNumTwo, ifFirstValueTwo},
																						{ ifLineNumOne, ifFirstValueTwo} };
	
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameTwo{ { ifLineNumOne, ifFirstValueOne },
																						{ ifLineNumTwo, ifFirstValueTwo},
																						{ ifLineNumOne, ifFirstValueTwo} };
	
	sort(ifGetPatternPairNameNameOne.begin(), ifGetPatternPairNameNameOne.end());
	sort(ifGetPatternPairNameNameTwo.begin(), ifGetPatternPairNameNameTwo.end());
	sort(expectedGetPatternPairNameNameTwo.begin(), expectedGetPatternPairNameNameTwo.end());
	sort(expectedGetPatternPairNameNameOne.begin(), expectedGetPatternPairNameNameOne.end());

	REQUIRE(ifGetPatternPairNameNameOne == expectedGetPatternPairNameNameOne);
	REQUIRE(ifGetPatternPairNameNameTwo == expectedGetPatternPairNameNameTwo);
}

TEST_CASE("While Pattern Storage Test") {
	PatternStorage* whilePatternStorage = new WhilePatternStorage();


	REQUIRE(whilePatternStorage->storePattern(whilePatternOne));
	REQUIRE(whilePatternStorage->storePattern(whilePatternTwo));
	REQUIRE(whilePatternStorage->storePattern(whilePatternOneDup));

  
	std::unordered_set<std::string> whileGetPatternNameNameOne = whilePatternStorage->getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> whileGetPatternNameNameTwo = whilePatternStorage->getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo, TokenObject());

	std::unordered_set<std::string> expectedResultWhileGetPatternOne({ whileLineNumOne });
	std::unordered_set<std::string> expectedResultWhileGetPatternTwo({ whileLineNumOne, whileLineNumTwo });

	REQUIRE(whileGetPatternNameNameOne == expectedResultWhileGetPatternOne);
	REQUIRE(whileGetPatternNameNameTwo == expectedResultWhileGetPatternTwo);

	std::unordered_set<std::string> whileGetPatternWildcardOne = whilePatternStorage->getPatternWildcard(DesignEntity::WHILE, whilePatternTokenObjectFirstOne);

	std::unordered_set<std::string> expectedGetPatternWildcard = { whileLineNumOne, whileLineNumTwo };

	REQUIRE(whileGetPatternWildcardOne == expectedGetPatternWildcard);

	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameOne = whilePatternStorage->getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstOne);
	
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameTwo = whilePatternStorage->getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo);
	

	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameOne{ { whileLineNumOne, whileFirstValueOne },
																						{ whileLineNumTwo, whileFirstValueTwo},
																						{ whileLineNumOne, whileFirstValueTwo} };
	

	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameTwo{ { whileLineNumOne, whileFirstValueOne },
																						{ whileLineNumTwo, whileFirstValueTwo},
																						{ whileLineNumOne, whileFirstValueTwo} };
	sort(whileGetPatternPairNameNameOne.begin(), whileGetPatternPairNameNameOne.end());
	sort(whileGetPatternPairNameNameTwo.begin(), whileGetPatternPairNameNameTwo.end());
	sort(expectedGetPatternPairNameNameOne.begin(), expectedGetPatternPairNameNameOne.end());
	sort(expectedGetPatternPairNameNameTwo.begin(), expectedGetPatternPairNameNameTwo.end());

	REQUIRE(whileGetPatternPairNameNameOne == expectedGetPatternPairNameNameOne);
	REQUIRE(whileGetPatternPairNameNameTwo == expectedGetPatternPairNameNameTwo);
}
