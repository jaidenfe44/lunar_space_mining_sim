

#include "TestSuite.hpp"


int main()
{
	// TODO
	TestSuite &suite = TestSuite::getInstance();

	suite.run();

	suite.report();

	return 0;
}
