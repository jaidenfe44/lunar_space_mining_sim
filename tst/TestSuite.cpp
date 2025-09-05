
#include "TestSuite.hpp"

#include <chrono>
#include <cstdio>

void TestSuite::run()
{
	printf("Running Test Suite...\n");

	// get start time
	auto start_t = std::chrono::system_clock::now();

	// Note: Could improve execution time by parallelizing test case execution

	// Execute test cases
	tcMiningTruck.run(passed, failed);
	tcStation.run(passed, failed);
	tcStationHub.run(passed, failed);

	// get end time 
	auto end_t = std::chrono::system_clock::now();

	// Store time duration (in milliseconds)
	execTime = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t);
}


void TestSuite::report()
{
	printf("\nTest Report\n");
	printf("    Passed: %i\n", passed);
	printf("    Failed: %i\n", failed);

	printf("\n    Runtime: %lld ms\n", execTime.count());
}
