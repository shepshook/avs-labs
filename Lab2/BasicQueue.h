#pragma once
#include <mutex>
#include <vector>

#include "Queue.h"

class BasicQueue : public Queue
{
private:
	std::vector<uint8_t>* vec;
	std::mutex mtx;
	int head;
	int tail;
	
public:
	BasicQueue();
	
	void Push(uint8_t value) override;
	bool Pop(uint8_t& value) override;
};
