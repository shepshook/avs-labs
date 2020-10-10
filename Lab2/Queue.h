#pragma once
#include <cstdint>

class Queue
{
public:
	virtual void Push(uint8_t value) = 0;
	virtual bool Pop(uint8_t& value) = 0;
};
