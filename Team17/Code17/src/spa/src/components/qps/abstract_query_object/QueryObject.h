#include "Pattern.h"
#include "Select.h"
#include "SuchThat.h"
#include "With.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "models/Entity/DesignEntity.h"
#include <unordered_map>
#include <vector>

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence for
// now
class QueryObject {
private:
  std::vector<SuchThat> relationships;
  std::vector<qps::Pattern> patterns;
  std::vector<With> withs;
  Select select;
  bool hasNoSyntaxError = false;
  bool hasNoSemanticError =
      true; // Assumed true till QueryObject is passed into the Validator
  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
  int numOfDeclaredSynonyms = 0;

public:
  QueryObject();
  QueryObject(
      Select &select, std::vector<SuchThat> &relationship,
      std::vector<qps::Pattern> &pattern,
      std::unordered_map<std::string, DesignEntity> &synonymToDesignEntity,
      int numOfDeclaredSynonyms);
  QueryObject(
      Select &select, std::vector<SuchThat> &relationship,
      std::vector<qps::Pattern> &pattern, std::vector<With> &with,
      std::unordered_map<std::string, DesignEntity> &synonymToDesignEntity,
      int numOfDeclaredSynonyms);
  bool isSyntacticallyCorrect();
  bool isSemanticallyValid();
  std::vector<SuchThat> getRelationships();
  std::vector<qps::Pattern> getPattern();
  std::vector<With> getWith();
  Select getSelect();
  std::unordered_map<std::string, DesignEntity> getSynonymToDesignEntityMap();
  int getNumOfDeclaredSynonyms();
  void setSemanticallyInvalid();
  void setReturnTypeToSynonym();
  void setPatternTypeToAssign(int index);
  bool operator==(const QueryObject &other) const {
    return relationships == other.relationships && patterns == other.patterns &&
           select == other.select && withs == other.withs &&
           hasNoSyntaxError == other.hasNoSyntaxError &&
           hasNoSemanticError == other.hasNoSemanticError &&
           synonymToDesignEntityMap == other.synonymToDesignEntityMap &&
           numOfDeclaredSynonyms == other.numOfDeclaredSynonyms;
  }
};

#endif // SPA_QUERY_H