#include <iostream>
#include "Test.h"

int main()
{
	std::cout << "Test 1: " << (test1() ? "OK" : "Fail") << std::endl;
	std::cout << "Test 2: " << (test2() ? "OK" : "Fail") << std::endl;

	return 0;
}
