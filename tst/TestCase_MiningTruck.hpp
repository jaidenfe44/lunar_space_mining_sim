#ifndef TEST_CASE_MINING_TRUCK_HPP
#define TEST_CASE_MINING_TRUCK_HPP


#include "MiningTruck.hpp"
#include "TestCase.hpp"


class TestCase_MiningTruck: public TestCase, MiningTruck
{

	public:
		TestCase_MiningTruck(){};

		void cleanup() override;

		// Test Case execution function
		void run(unsigned int &pass, unsigned int &fail) override
		{
			TC_computeMineTime() ? pass++ : fail++;
		};

		// Test Cases
		bool TC_computeMineTime();
};

#endif // TEST_CASE_MINING_TRUCK_HPP
