#include "CounterAtomic.h"

CounterAtomic::CounterAtomic()
{
	value.store(0);
}

void CounterAtomic::IncAndReturn(int& result)
{
	result = value.fetch_add(1);
}
