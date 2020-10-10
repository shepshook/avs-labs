#pragma once
#include "Queue.h"

#include <condition_variable>
#include <mutex>

class FixedSizeQueue : public Queue
{
private:
	std::mutex mtx;
	std::condition_variable read_cv, write_cv;

	uint8_t* queue;
	long head, tail;
	int size;

	bool IsFull();
	bool IsEmpty();
	
public:
	FixedSizeQueue(int size);
	void Push(uint8_t value) override;
	bool Pop(uint8_t& value) override;
};
