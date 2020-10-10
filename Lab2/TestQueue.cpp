#include "TestQueue.h"

#include <iostream>

void TestQueue::RunTests()
{
	for (auto testCase : cases)
	{
		Test(testCase);
	}
}

bool TestQueue::Test(QueueTestCase testCase)
{
	auto* producersDone = new bool[testCase.producersNumber];
	for (auto i = 0; i < testCase.producersNumber; i++)
		producersDone[i] = false;

	auto* results = new int[testCase.consumersNumber];
	
	auto* consumers = RunConsumers(testCase, producersDone, results);

	auto* producers = RunProducers(testCase, producersDone);

	for (auto i = 0; i < testCase.producersNumber; i++)
	{
		producers[i]->join();
	}

	auto sum = 0;
	for (auto i = 0; i < testCase.consumersNumber; i++)
	{
		consumers[i]->join();
		sum += results[i];
		std::cout << results[i] << std::endl;
	}
	std::cout << "Sum: " << sum << std::endl;

	return true;
}

bool TestQueue::AllTrue(bool* values, int size)
{
	for (auto i = 0; i < size; i++)
		if (!values[i])
			return false;

	return true;
}

std::thread** TestQueue::RunConsumers(QueueTestCase testCase, bool* producersDone, int* results)
{
	auto* consumers = new std::thread * [testCase.consumersNumber];
	
	for (auto i = 0; i < testCase.consumersNumber; i++)
	{
		auto* result = results + i;
		consumers[i] = new std::thread([testCase, producersDone, this](int* result)
			{
				*result = 0;
				uint8_t value;
				while (!AllTrue(producersDone, testCase.producersNumber))
					while (testCase.queue->Pop(value))
						*result += value;
			}, result);
	}
	
	return consumers;
}

std::thread** TestQueue::RunProducers(QueueTestCase testCase, bool* producersDone)
{
	auto* producers = new std::thread * [testCase.producersNumber];
	
	for (auto i = 0; i < testCase.producersNumber; i++)
	{
		auto* done = &producersDone[i];
		producers[i] = new std::thread([testCase](bool* done)
			{
				auto counter = testCase.tasksNumber;
				while (counter > 0)
				{
					testCase.queue->Push(1);
					counter--;
				}
				*done = true;
			}, done);
	}

	return producers;
}