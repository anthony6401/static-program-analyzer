#pragma once
#ifndef SPA_PATTERN_PKB_H
#define SPA_PATTERN_PKB_H
#include <string>

namespace kb {

	class Pattern {
	private:
		std::string lineNum;
		std::string firstValue;
		std::string secondValue;

	public:
		Pattern(std::string lineNum, std::string firstValue, std::string secondValue);
		virtual ~Pattern() = default;
		std::string getLineNum();
		std::string getFirstValue();
		std::string getSecondValue();
	};
}
#endif //SPA_PATTERN_PKB_H
