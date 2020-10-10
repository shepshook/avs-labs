#pragma once
#include <atomic>
#include <chrono>


#include "Counter.h"

class CounterAtomic : public Counter
{
private:
	std::atomic<int> value;

public:
	CounterAtomic();

	void IncAndReturn(int& result) override;
};

