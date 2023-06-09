#include "Validator.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/With.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>

using namespace qps;

Validator::Validator(QueryObject parsedQuery) {
  this->parsedQuery = parsedQuery;
};

QueryObject Validator::validate() {
  if (!isSemanticallyValid()) {
    this->parsedQuery.setSemanticallyInvalid();
  }

  return this->parsedQuery;
}

bool Validator::isSemanticallyValid() {
  // If query has SyntaxError, do not proceed with checking for SemanticError
  if (!this->parsedQuery.isSyntacticallyCorrect()) {
    return true;
  }

  int numOfDeclaredSynonyms = this->parsedQuery.getNumOfDeclaredSynonyms();

  std::unordered_map<std::string, DesignEntity> declaredSynonyms =
      this->parsedQuery.getSynonymToDesignEntityMap();

  // Declaration contains multiple synonyms with the same name
  if (numOfDeclaredSynonyms > declaredSynonyms.size()) {
    return false;
  }

  if (!selectClauseIsSemanticallyCorrect()) {
    return false;
  }

  if (!suchThatClauseIsSemanticallyCorrect()) {
    return false;
  }

  if (!patternClauseIsSemanticallyCorrect()) {
    return false;
  }

  if (!withClauseIsSemanticallyCorrect()) {
    return false;
  }

  return true;
};

bool Validator::selectClauseIsSemanticallyCorrect() {
  Select selectClause = this->parsedQuery.getSelect();
  TokenType returnType = selectClause.getReturnType();
  std::vector<TokenObject> const &returnValues = selectClause.getReturnValues();

  std::vector<TokenObject> attributeTokens{};

  std::unordered_map<std::string, DesignEntity> mappedSynonyms =
      this->parsedQuery.getSynonymToDesignEntityMap();

  for (TokenObject token : returnValues) {
    TokenType currTokenType = token.getTokenType();
    std::string tokenValue = token.getValue();

    if ((currTokenType == TokenType::ATTRIBUTE_SYNONYM) ||
        currTokenType == TokenType::ATTRIBUTE_NAME) {
      attributeTokens.push_back(token);
      continue;
    }

    // Synonym is not declared, do nothing if return type is BOOLEAN
    if (mappedSynonyms.find(tokenValue) == mappedSynonyms.end()) {
      if (tokenValue == "BOOLEAN" && returnType == TokenType::BOOLEAN) {
        continue;
      }
      return false;
    }

    // BOOLEAN used as a synonym in declaration, convert return type to SYNONYM
    if (tokenValue == "BOOLEAN" && returnType == TokenType::BOOLEAN) {
      this->parsedQuery.setReturnTypeToSynonym();
    }
  }

  if (!isValidAttrRef(attributeTokens)) {
    return false;
  }

  return true;
};

bool Validator::suchThatClauseIsSemanticallyCorrect() {
  std::vector<SuchThat> const &suchThatClause =
      this->parsedQuery.getRelationships();
  bool isSemanticallyCorrect = true;

  for (SuchThat relationship : suchThatClause) {
    TokenType relationshipType = relationship.getRelationshipType();

    if (relationshipType == TokenType::USES ||
        relationshipType == TokenType::MODIFIES) {
      isSemanticallyCorrect =
          isSemanticallyCorrect && isValidUsesAndModifies(relationship);
    }

    if (relationshipType == TokenType::CALLS ||
        relationshipType == TokenType::CALLS_T) {
      isSemanticallyCorrect =
          isSemanticallyCorrect && isValidCalls(relationship);
    }

    if (relationshipType == TokenType::FOLLOWS ||
        relationshipType == TokenType::FOLLOWS_T ||
        relationshipType == TokenType::PARENT ||
        relationshipType == TokenType::PARENT_T ||
        relationshipType == TokenType::NEXT ||
        relationshipType == TokenType::NEXT_T) {
      isSemanticallyCorrect =
          isSemanticallyCorrect && isValidFollowsParentNext(relationship);
    }

    if (!isSemanticallyCorrect) {
      return false;
    }
  }

  return true;
};

bool Validator::patternClauseIsSemanticallyCorrect() {
  std::vector<Pattern> const &patternClause = this->parsedQuery.getPattern();
  int index = 0;

  while (index < patternClause.size()) {
    Pattern pattern = patternClause.at(index);
    TokenType patternType = pattern.getPatternType();
    std::string patternSynonym = pattern.getSynonym();
    TokenObject leftParam = pattern.getLeft();

    // Check that synonym is declared and declared appropriate design entity
    if (!isDeclaredSynonym(patternSynonym)) {
      return false;
    }

    if (patternType == TokenType::ASSIGN &&
        !isValidDesignEntity(patternSynonym, DesignEntity::ASSIGN)) {
      return false;
    }

    if (patternType == TokenType::IF &&
        !isValidDesignEntity(patternSynonym, DesignEntity::IF)) {
      return false;
    }

    if (patternType == TokenType::WHILE &&
        !isValidDesignEntity(patternSynonym, DesignEntity::WHILE)) {
      // Check if synonym is declared as assign design entity
      if (!isValidDesignEntity(patternSynonym, DesignEntity::ASSIGN)) {
        return false;
      }

      this->parsedQuery.setPatternTypeToAssign(index);
    }

    // Check first parameter is valid
    if (leftParam.getTokenType() == TokenType::NAME) {
      std::string synonymName = leftParam.getValue();

      if (!isValidParameter(synonymName, DesignEntity::VARIABLE)) {
        return false;
      }
    }

    index++;
  }

  return true;
};

bool Validator::withClauseIsSemanticallyCorrect() {
  std::vector<With> const &withClause = this->parsedQuery.getWith();

  for (With with : withClause) {
    TokenType leftType = with.getLeftType();
    TokenType rightType = with.getRightType();

    // Incompatible attribute types
    if (leftType != rightType) {
      return false;
    }

    // If ref is IDENT or INTEGER, no need to validate. Hence, we only check if
    // attribute is valid
    std::vector<TokenObject> left = with.getLeft();

    if (left.size() > 1) {
      if (!isValidAttrRef(left)) {
        return false;
      }
    }

    std::vector<TokenObject> right = with.getRight();

    if (right.size() > 1) {
      if (!isValidAttrRef(right)) {
        return false;
      }
    }
  }

  return true;
};

bool Validator::isValidUsesAndModifies(SuchThat &relationship) {
  TokenObject leftParam = relationship.getLeft();
  TokenObject rightParam = relationship.getRight();
  bool isValid = true;

  // First parameter of Uses and Modifies cannot be WILDCARD due to ambiguity
  if (leftParam.getTokenType() == TokenType::WILDCARD) {
    return false;
  }

  // Check first parameter is valid
  if (leftParam.getTokenType() == TokenType::NAME) {
    std::string synonymName = leftParam.getValue();

    // Synonym name is not declared or does not have the appropriate design
    // entity
    if (!isDeclaredSynonym(synonymName)) {
      return false;
    }

    if (!isValidUsesAndModifiesLeftParameter(synonymName)) {
      return false;
    }
  }

  // Check second parameter if valid
  if (rightParam.getTokenType() == TokenType::NAME) {
    std::string synonymName = rightParam.getValue();
    isValid = isValid && isValidParameter(synonymName, DesignEntity::VARIABLE);
  }

  return isValid;
}

bool Validator::isValidFollowsParentNext(SuchThat &relationship) {
  TokenObject leftParam = relationship.getLeft();
  TokenObject rightParam = relationship.getRight();
  bool isValid = true;

  // Check first parameter is valid
  if (leftParam.getTokenType() == TokenType::NAME) {
    std::string synonymName = leftParam.getValue();
    isValid = isValid && isValidParameter(synonymName, DesignEntity::STMT);
  }

  // Check second parameter if valid
  if (rightParam.getTokenType() == TokenType::NAME) {
    std::string synonymName = rightParam.getValue();
    isValid = isValid && isValidParameter(synonymName, DesignEntity::STMT);
  }

  return isValid;
}

bool Validator::isValidCalls(SuchThat &relationship) {
  TokenObject leftParam = relationship.getLeft();
  TokenObject rightParam = relationship.getRight();
  bool isValid = true;

  // Check first parameter is valid
  if (leftParam.getTokenType() == TokenType::NAME) {
    std::string synonymName = leftParam.getValue();
    isValid = isValid && isValidParameter(synonymName, DesignEntity::PROCEDURE);
  }

  // Check second parameter if valid
  if (rightParam.getTokenType() == TokenType::NAME) {
    std::string synonymName = rightParam.getValue();
    isValid = isValid && isValidParameter(synonymName, DesignEntity::PROCEDURE);
  }

  return isValid;
}

bool Validator::isValidParameter(std::string synonymName,
                                 DesignEntity validDesignEntity) {
  // Synonym name is not declared or does not have the appropriate design entity
  if (!isDeclaredSynonym(synonymName)) {
    return false;
  }

  if (validDesignEntity == DesignEntity::STMT) {
    return isStatement(synonymName);
  }

  return isValidDesignEntity(synonymName, validDesignEntity);
}

bool Validator::isDeclaredSynonym(std::string synonym) {
  std::unordered_map<std::string, DesignEntity> const &mappedSynonyms =
      this->parsedQuery.getSynonymToDesignEntityMap();
  if (mappedSynonyms.find(synonym) == mappedSynonyms.end()) {
    return false;
  }

  return true;
}

bool Validator::isStatement(std::string synonym) {
  std::vector<DesignEntity> &validDesignEntities =
      this->statementDesignEntities;
  DesignEntity designEntityOfSynonym =
      this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

  if (!std::binary_search(validDesignEntities.begin(),
                          validDesignEntities.end(), designEntityOfSynonym)) {
    return false;
  }

  return true;
};

bool Validator::isValidDesignEntity(std::string synonym,
                                    DesignEntity designEntityToMatch) {
  DesignEntity designEntityOfSynonym =
      this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

  if (designEntityOfSynonym != designEntityToMatch) {
    return false;
  }

  return true;
};

bool Validator::isValidUsesAndModifiesLeftParameter(std::string synonym) {
  // Removed READ since according to the slides, READ is not a valid parameter
  // for Uses and Modifies
  std::vector<DesignEntity> &validDesignEntities =
      this->validDesignEntitiesForUsesAndModifies;
  DesignEntity designEntityOfSynonym =
      this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

  if (!std::binary_search(validDesignEntities.begin(),
                          validDesignEntities.end(), designEntityOfSynonym)) {
    return false;
  }

  return true;
};

bool Validator::isValidAttrNameToAttrSynonym(
    std::string attrName, DesignEntity attrSynonymDesignEntity) {
  std::vector<DesignEntity> validDesignEntities =
      this->attrNameToValidDesignEntity.at(attrName);

  if (!std::binary_search(validDesignEntities.begin(),
                          validDesignEntities.end(), attrSynonymDesignEntity)) {
    return false;
  }

  return true;
};

bool Validator::isValidAttrRef(std::vector<TokenObject> &ref) {
  DesignEntity currAttributeSynonymDesignEntity{};
  std::unordered_map<std::string, DesignEntity> const &mappedSynonyms =
      this->parsedQuery.getSynonymToDesignEntityMap();

  for (TokenObject &token : ref) {
    TokenType currTokenType = token.getTokenType();
    std::string tokenValue = token.getValue();

    if (currTokenType == TokenType::ATTRIBUTE_SYNONYM) {
      // Synonym is not declared
      if (mappedSynonyms.find(tokenValue) == mappedSynonyms.end()) {
        return false;
      }

      currAttributeSynonymDesignEntity = mappedSynonyms.at(tokenValue);
      continue;
    }

    if (currTokenType == TokenType::ATTRIBUTE_NAME) {
      bool isValidAttrName = isValidAttrNameToAttrSynonym(
          tokenValue, currAttributeSynonymDesignEntity);

      if (!isValidAttrName) {
        return false;
      }
      continue;
    }

    // token is neither attribute synonym nor attribute name, thus not valid
    // attribute should never reach here!!
    throw std::runtime_error("Error validating attribute");
  }

  return true;
}
