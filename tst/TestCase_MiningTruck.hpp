#ifndef TEST_CASE_MINING_TRUCK_HPP
#define TEST_CASE_MINING_TRUCK_HPP


#include "MiningTruck.hpp"
#include "TestCase.hpp"


class TestCase_MiningTruck: public TestCase, private MiningTruck
{

	public:
		TestCase_MiningTruck(){};

		void cleanup() override;

		// Test Case execution function
		void run(unsigned int &pass, unsigned int &fail) override
		{
			TC_computeMineTime() ? pass++ : fail++;
			TC_reportStats()     ? pass++ : fail++;
		};

		// Test Cases
		bool TC_computeMineTime();
		bool TC_reportStats();


	private:
};

#endif // TEST_CASE_MINING_TRUCK_HPP
