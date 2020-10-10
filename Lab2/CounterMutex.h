#pragma once
#include <mutex>

#include "Counter.h"

class CounterMutex : public Counter
{
private:
	int value;
	std::mutex mtx;

public:
	CounterMutex();

	void IncAndReturn(int& result) override;
};

