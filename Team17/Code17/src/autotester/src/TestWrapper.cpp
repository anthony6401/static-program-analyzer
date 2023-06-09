#include "TestWrapper.h"
#include "components/pkb/pkb.h"
#include "components/qps/QPS.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "components/sp/parser/SimpleParser.h"
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
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
  // auto pkb = std::make_shared<PKB>();
  pkb = new PKB();
  //this->simpleTokenizer = new SimpleTokenizer();
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	SPClient* client = new SPClient(pkb);
	Extractor extractor = Extractor(client);
	SimpleParser simpleParser = SimpleParser(&extractor);
	std::ifstream testFile;
	testFile.open(filename);

	if (!(testFile.is_open())) {
		std::cout << "Cannot open file";
		exit(EXIT_FAILURE);
	}
	std::string code((std::istreambuf_iterator<char>(testFile)),
		std::istreambuf_iterator<char>());
	try {
		simpleParser.parseCode(code);
	} catch(std::invalid_argument e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}


}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
    auto qpsClient = QPSClient(pkb);
    QPS::processQueryResult(query, results, qpsClient);
	qpsClient.clearCache();
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
