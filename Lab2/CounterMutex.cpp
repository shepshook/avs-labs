#include "CounterMutex.h"

CounterMutex::CounterMutex()
{
	value = 0;
}

void CounterMutex::IncAndReturn(int& result)
{
	mtx.lock();
	
	result = value++;
	
	mtx.unlock();
}
