#include "FixedSizeQueue.h"

#include <iostream>
#include <chrono>

using std::literals::operator ""ms;

FixedSizeQueue::FixedSizeQueue(int _size)
{
	queue = new uint8_t[_size];
	size = _size;
	head = 0;
	tail = 0;
}

void FixedSizeQueue::Push(uint8_t value)
{
	std::unique_lock<std::mutex> locker(mtx);

	while (IsFull())
		write_cv.wait(locker);

	if (!IsFull())
		queue[tail++ % size] = value;
	
	read_cv.notify_all();
}

bool FixedSizeQueue::Pop(uint8_t& value)
{
	std::unique_lock<std::mutex> locker(mtx);

	read_cv.wait_for(locker, 100ms);

	if (IsEmpty())
		return false;
	
	value = queue[head++ % size];
	write_cv.notify_all();
	
	return true;
}

bool FixedSizeQueue::IsFull()
{
	return tail - head >= size;
}

bool FixedSizeQueue::IsEmpty()
{
	return head == tail;
}
