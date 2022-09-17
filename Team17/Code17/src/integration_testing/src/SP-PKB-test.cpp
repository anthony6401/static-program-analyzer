#include "components/sp/tokenizer/SimpleTokenizer.h"

#include <catch.hpp>



TEST_CASE("test SP PKB integration") {
	auto pkb = new PKB();
	SPClient* client = new SPClient(pkb);
	Extractor extractor = Extractor(client);
	SimpleTokenizer simpleTokenizer = SimpleTokenizer(&extractor);
	simpleTokenizer.tokenizeCode("    procedure computeCentroid {\
		      count = 0;\
	      cenX = 0;\
	      cenY = 0;\
	      call readPoint;\
	      while ((x != 0) && (y != 0)) {\
		          count = count + 1;\
		          cenX = cenX + x;\
		          cenY = cenY + y;\
		          call readPoint;\
	}\
	      if (count == 0) then{\
	          flag = 1;\
	}\
	else {\
		          cenX = cenX / count;\
		          cenY = cenY / count;\
	}\
	      normSq = cenX * cenX + cenY * cenY;\
}");
}