#pragma once
#include <vector>

#include "BasicQueue.h"
#include "FixedSizeQueue.h"
#include "Queue.h"

struct QueueTestCase
{
	int tasksNumber;
	int producersNumber;
	int consumersNumber;
	Queue* queue;
};

class TestQueue
{
private:
	std::vector<QueueTestCase> cases = {
		{128, 1, 1, new FixedSizeQueue(1)},
		{1024, 2, 2, new FixedSizeQueue(4)},
		{4 * 1024, 4, 4, new FixedSizeQueue(16)},
		{16 * 1024, 4, 4, new FixedSizeQueue(16)},
		{32 * 1024, 4, 4, new FixedSizeQueue(16)},
		{16, 1, 1, new BasicQueue()},
		{1024, 2, 2, new BasicQueue()},
		{16 * 1024, 4, 4, new BasicQueue()},
	};

	bool Test(QueueTestCase testCase);
	bool AllTrue(bool* values, int size);
	std::thread** RunConsumers(QueueTestCase testCase, bool* producersDone, int* results);
	std::thread** RunProducers(QueueTestCase testCase, bool* producersDone);
	
public:
	void RunTests();
};
