#pragma once
#ifndef SPA_PATTERN_PKB_H
#define SPA_PATTERN_PKB_H
#include <string>

namespace kb {

	class Pattern {
	private:
		std::string lineNum;
		std::string firstValue;

	public:
		Pattern(std::string lineNum, std::string firstValue);
		virtual ~Pattern() = default;
		std::string getLineNum();
		std::string getFirstValue();
	};
}
#endif //SPA_PATTERN_PKB_H
