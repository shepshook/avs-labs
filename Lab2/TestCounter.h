#pragma once
#include <vector>

#include "Counter.h"
#include "CounterAtomic.h"
#include "CounterMutex.h"

struct CounterTestCase
{
	int tasksNumber;
	int threadsNumber;
	Counter* counter;
	int delayNs;
};

class TestCounter
{
private:
	std::vector<CounterTestCase> cases = {
		{100, 2, new CounterMutex(), 0},
		{100, 2, new CounterAtomic(), 0},
		{100, 4, new CounterMutex(), 0},
		{100, 4, new CounterAtomic(), 0},
		{1024, 4, new CounterMutex(), 0},
		{1024, 4, new CounterAtomic(), 0},
		{1024 * 1024, 4, new CounterMutex(), 0},
		{1024 * 1024, 4, new CounterAtomic(), 0},
		{1024 * 1024, 8, new CounterMutex(), 0},
		{1024 * 1024, 8, new CounterAtomic(), 0},
		{1024 * 1024, 16, new CounterMutex(), 0},
		{1024 * 1024, 16, new CounterAtomic(), 0},
		{1024 * 1024, 32, new CounterMutex(), 0},
		{1024 * 1024, 32, new CounterAtomic(), 0},
		{1024 * 1024, 8, new CounterMutex(), 10},
		{1024 * 1024, 8, new CounterAtomic(), 10},
		{1024 * 1024, 32, new CounterMutex(), 10},
		{1024 * 1024, 32, new CounterAtomic(), 10},
	};
	bool Test(CounterTestCase testCase);
public:
	void RunTests();
};

