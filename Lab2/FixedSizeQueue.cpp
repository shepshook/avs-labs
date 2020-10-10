#include "FixedSizeQueue.h"

#include <iostream>

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
	std::cout << "Push" << std::endl;
	read_cv.notify_all();
}

bool FixedSizeQueue::Pop(uint8_t& value)
{
	std::unique_lock<std::mutex> locker(mtx);

	while (IsEmpty())
		read_cv.wait(locker);

	if (!IsEmpty())
		value = queue[head++ % size];
	std::cout << "Pop" << std::endl;
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
