#include <iostream>

#include "TestCounter.h"
#include "TestQueue.h"

int main()
{
	TestCounter testCounter;
	testCounter.RunTests();
	
	//TestCounterRun();
	TestQueue testQueue;
	testQueue.RunTests();
}
