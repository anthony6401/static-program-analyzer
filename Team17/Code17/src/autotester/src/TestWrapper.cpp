#include "TestWrapper.h"
#include "components/pkb/pkb.h"
#include "components/qps/QPS.h"
#include <fstream>

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
	this->simpleTokenizer = new SimpleTokenizer();
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	std::ifstream testFile;
	testFile.open(filename);

	if (!(testFile.is_open())) {
		std::cout << "Cannot open file";
		exit(EXIT_FAILURE);
	}
	std::string code((std::istreambuf_iterator<char>(testFile)),
		std::istreambuf_iterator<char>());

	this->simpleTokenizer->tokenizeCode(code);

}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
    QPS::processQueryResult(query, results);
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
