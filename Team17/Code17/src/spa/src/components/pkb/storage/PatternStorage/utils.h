#pragma once
#include <string>
#include <utility>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class PatternUtils {
public:
    static bool isSubExpression(const std::string& sub_expression, const std::string& full_expression) {
        size_t idx = full_expression.find_first_of(" *+/-()");
        size_t prev = 0;

        if (idx == std::string::npos) {
            return sub_expression == full_expression;
        }

        while (idx != std::string::npos) {
            std::string str;
            if (prev == 0) {
                str = full_expression.substr(prev, idx - prev);
            }
            else {
                str = full_expression.substr(prev + 1, idx - prev - 1);
            }

            if (str.size() > 0 && str.find_first_of(" *+/-()") == std::string::npos && str == sub_expression) {
                return true;
                
            }

            prev = idx;
            idx = full_expression.find_first_of(" *+/-()", idx + 1);
        }
        std::string lastString = full_expression.substr(prev + 1, full_expression.size() - prev);
        if (lastString.size() > 0 && lastString.find_first_of(" *+/-()") == std::string::npos && lastString == sub_expression) {
            return true;
        }

        return false;
    }
};
