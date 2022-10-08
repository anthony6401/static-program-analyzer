#pragma once
#include <string>
#include <utility>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class PatternUtils {
public:
    // Helper function
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

    static bool isSubArray(std::vector<std::string> A, std::vector<std::string> B) {
        //Get the length of the two array
        int n = A.size();
        int m = B.size();

        //Initialize Pointer
        int i = 0;
        int j = 0;

        while (i < n && j < m) {

            // If element matches
            // increment both pointers
            if (A[i] == B[j]) {

                i++;
                j++;

                // If array B is completely
                // traversed
                if (j == m)
                    return true;
            }
            // If not,
            // increment i and reset j
            else {
                i = i - j + 1;
                j = 0;
            }
        }

        return false;
    }
    // End of helper function


    // full_expression in postfix format
    static bool isSubExpression(const std::string sub_expression, const std::string full_expression) {
        std::string subExprPostfix = convertInfixToPostfix(sub_expression);
        
        //Convert sub expression to vector<string>
        std::stringstream subExpStream(subExprPostfix);
        std::istream_iterator<std::string> subExpBegin(subExpStream);
        std::istream_iterator<std::string> subExpEnd;
        std::vector<std::string> subExpressionArr(subExpBegin, subExpEnd);

        //Convert full_expression to vector<string>
        std::stringstream fullExpStream(full_expression);
        std::istream_iterator<std::string> fullExpBegin(fullExpStream);
        std::istream_iterator<std::string> fullExpEnd;
        std::vector<std::string> fullExpressionArr(fullExpBegin, fullExpEnd);

        return isSubArray(fullExpressionArr, subExpressionArr);
    }

    static std::string convertInfixToPostfix(std::string pattern) {
        // Using stack
        std::stack<char> st;
        
        std::string result;

        //bool hasAddedSpace = false;

        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];


            // If the scanned character is
            // an operand, add it to output string.
            if (isAlphanumeric(c)) {
                std::string temp;
                while (isAlphanumeric(pattern[i])) {
                    temp +=pattern[i];
                    i++;
                }
                temp += " ";
                result += temp;
                i--;
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
                    result += " ";
                    st.pop();
                }
                st.pop();
            }

            // If an operator is scanned
            else {
              /*  if (!hasAddedSpace) {
                    result += " ";
                    hasAddedSpace = true;
                }*/
                while (!st.empty()
                    && prec(pattern[i]) <= prec(st.top())) {
                    result += st.top();
                    result += " ";
                    st.pop();
                }
                st.push(c);
            }
        }

        // Pop all the remaining elements from the stack
        while (!st.empty()) {
            result += st.top();
            result += " ";
            st.pop();
        }

        return result;
    }

    static void populatePairFromSet(std::unordered_set<std::string>* set, std::string key, std::vector<std::pair<std::string, std::string>>* result) {
        for (const auto& elem : *set) {
            result->push_back({ elem, key });
        }
    }
};
