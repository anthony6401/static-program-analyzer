#pragma once
#include <string>
#include <utility>
#include <stack>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class PatternUtils {
public:
    static bool isSubExpression(const std::string& sub_expression, const std::string& full_expression) {
        size_t idx = full_expression.find_first_of(" *+/-%()");
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

            if (str.size() > 0 && str.find_first_of(" *+/-%()") == std::string::npos && str == sub_expression) {
                return true;
                
            }

            prev = idx;
            idx = full_expression.find_first_of(" *+/-%()", idx + 1);
        }
        std::string lastString = full_expression.substr(prev + 1, full_expression.size() - prev);
        if (lastString.size() > 0 && lastString.find_first_of(" *+/-()") == std::string::npos && lastString == sub_expression) {
            return true;
        }

        return false;
    }

    static bool isAlphanumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }

    static int prec(char c)
    {
        if (c == '^') {
            return 3;
        }
        else if (c == '/' || c == '*' || c == '%') {
            return 2;
        }
        else if (c == '+' || c == '-') {
            return 1;
        }
        else
            return -1;
    }

    static std::string convertInfixToPostfix(std::string pattern) {
        // Using stack
        std::stack<char> st;
        
        std::string result;

        bool hasAddedSpace = false;

        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];


            // If the scanned character is
            // an operand, add it to output string.
            if (isAlphanumeric(c)) {
                result += c;
                hasAddedSpace = false;
            }

            // If the scanned character is an
            // ‘(‘, push it to the stack.
            else if (c == '(') {
                st.push('(');
            }

            // If the scanned character is an ‘)’,
            // pop and to output string from the stack
            // until an ‘(‘ is encountered.
            else if (c == ')') {
                while (st.top() != '(') {
                    result += st.top();
                    //result += " ";
                    st.pop();
                }
                st.pop();
            }

            // If an operator is scanned
            else {
                if (!hasAddedSpace) {
                    result += " ";
                    hasAddedSpace = true;
                }
                while (!st.empty()
                    && prec(pattern[i]) <= prec(st.top())) {
                    result += st.top();
                    //result += " ";
                    st.pop();
                }
                st.push(c);
            }
        }

        // Pop all the remaining elements from the stack
        while (!st.empty()) {
            result += st.top();
            //result += " ";
            st.pop();
        }

        return result;
    }
};
