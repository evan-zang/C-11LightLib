
#include "pch.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <list>

using namespace std;
template<typename T>
class SyncQueue
{
	bool IsFull() const
	{
		return m_queue.size() == m_maxSize;
	}

	bool IsEmpty() const
	{
		return m_queue.empty();
	}
public:
	SyncQueue(int maxSize):m_maxSize(maxSize){}

	void Put(const T& x)
	{
		lock_guard<mutex> locker(m_mutex);
		while (IsFull())
		{
			cout << "缓冲区满了，需要等待..." << endl;
			m_notFull.wait(m_mutex);
		}
		m_queue.push_back(x);
		m_notEmpty.notify_one();
	}

	void Take(T& x)
	{
		lock_guard<mutex> locker(m_mutex);
		while (IsEmpty())
		{
			cout << "缓冲区空了，需要等待..." << endl;
			m_notEmpty.wait(m_mutex);
		}
		x = m_queue.front();
		m_queue.pop_front();
		m_notFull.notify_one();
	}
	bool Empty()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.empty();
	}
	bool Full()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.size() == m_maxSize;
	}

	size_t Size()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.size();
	}

	int Count()
	{
		return m_queue.size();
	}
private:
	list<T> m_queue;	//缓冲区
	mutex m_mutex;		//互斥量和条件变量结合起来使用
	condition_variable_any m_notEmpty;	//不为空的条件变量
	condition_variable_any m_notFull;	//没有满的条件变量
	int m_maxSize;
};
int main()
{
	/*
		使用过程
		1.拥有条件变量线程获取互斥量
		2.循环检查某个条件，如果条件不满足，则阻塞直到条件满足；如果条件满足，则向下执行
		3.某个线程满足条件执行完成之后调用notify_one或notify_all唤醒一个或者所有的等待线程
	*/

}

