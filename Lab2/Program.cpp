#include "TestCounter.h"
#include "TestQueue.h"

int main()
{
	TestCounter testCounter;
	testCounter.RunTests();
	
	TestQueue testQueue;
	testQueue.RunTests();
}
