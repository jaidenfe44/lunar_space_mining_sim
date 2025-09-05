#ifndef TEST_CASE_HPP
#define TEST_CASE_HPP

#include <stdexcept>
#include <cstdio>

class TestCase
{
	public:
		virtual void run(unsigned int &pass, unsigned int &fail) = 0;

		virtual void cleanup() = 0;

		constexpr void tcAssert(bool expr, const char* func, const char* msg = "Assertion Failed!")
		{
		    if(!expr)
		    {   
		        printf("        [%s] %s\n", func, msg);
				tcPass = false;
		    }
		}

		bool tcPass = true;
};

#endif // TEST_CASE_HPP
