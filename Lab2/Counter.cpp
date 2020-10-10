#include <mutex>

class Counter
{
public:
	virtual void Inc() = 0;
	virtual int GetValue() = 0;
};

class CounterMutex : Counter
{
private:
	int value;
	std::mutex mtx;
	
public:
	CounterMutex()
	{
		value = 0;
	}
	
	void Inc() override
	{
		mtx.lock();
		value++;
		mtx.unlock();
	}

	int GetValue() override
	{
		return value;
	}
};

