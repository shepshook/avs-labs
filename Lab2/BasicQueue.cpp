#include "BasicQueue.h"

#include <iostream>

BasicQueue::BasicQueue()
{
	head = 0;
	tail = 0;
	vec = new std::vector<uint8_t>();
}


void BasicQueue::Push(uint8_t value)
{
	mtx.lock();
	
	vec->push_back(value);
	tail++;
	
	mtx.unlock();
	//std::cout << "Pushed" << std::endl;
}

bool BasicQueue::Pop(uint8_t& value)
{
	mtx.lock();

	if (head >= tail)
	{
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		mtx.lock();
	}
		
	if (head >= tail) 
	{
		mtx.unlock();
		//std::cout << "Empty" << std::endl;
		return false;
	}
	
	value = (*vec)[head++];
	mtx.unlock();

	//std::cout << "Popped" << std::endl;
	return true;
}
