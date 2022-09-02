#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <list>
#include <vector>

class Evaluator {
public:
    // And also takes in Parsed QueryObject
    static void evaluateQuery(std::list<std::string> &results);
};

#endif //SPA_EVALUATOR_H
