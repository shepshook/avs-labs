#include "TestCounter.h"


#include <iostream>

bool TestCounter::Test(CounterTestCase testCase)
{
	auto* data = new uint8_t[testCase.tasksNumber];
	for (auto i = 0; i < testCase.tasksNumber; i++)
	{
		data[i] = 0;
	}

	auto* pool = new std::thread * [testCase.threadsNumber];

	auto startTime = std::chrono::steady_clock::now();

	for (auto i = 0; i < testCase.threadsNumber; i++)
	{
		pool[i] = new std::thread([&]()
			{
				int index;
				auto delay = std::chrono::nanoseconds(testCase.delayNs);
				testCase.counter->IncAndReturn(index);
				while (index < testCase.tasksNumber)
				{
					data[index]++;
					testCase.counter->IncAndReturn(index);
					std::this_thread::sleep_for(delay);
				}
			}
		);
	}

	for (auto i = 0; i < testCase.threadsNumber; i++)
		pool[i]->join();

	auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime);

	auto ok = true;
	for (auto i = 0; i < testCase.tasksNumber; i++)
	{
		if (int(data[i]) != 1)
		{
			ok = false;
			break;
		}
	}

	std::cout << (ok ? "OK" : "Fail") << std::endl;
	std::cout << "Elapsed " << elapsedMs.count() << " ms" << std::endl << std::endl;
	return ok;
}

void TestCounter::RunTests()
{
	std::cout << "=============== COUNTER TESTS ===============" << std::endl;
	for (auto testCase : cases)
	{
		std::cout << "Tasks: " << testCase.tasksNumber << ", Threads: " << testCase.threadsNumber << ", Delay: " << testCase.delayNs << ", " << typeid(*testCase.counter).name() << std::endl;
		Test(testCase);
	}
}
