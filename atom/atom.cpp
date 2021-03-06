
#include "pch.h"
#include <iostream>
#include <mutex>
#include <atomic>
using namespace std;

struct Counter
{
	int value;
	mutex m_mutex;

	void increment()
	{
		lock_guard<mutex>lock(m_mutex);
		++value;
	}

	void decrement()
	{
		lock_guard<mutex> lock(mutex);
		--value;
	}
	int get()
	{
		return value;
	}
};

struct AtomicCounter {
	atomic<int> value;
	void increment() {
		++value;
	}

	void decrement() {
		--value;
	}
	int get() {
		return value.load();
	}
};

int main()
{
    
}
