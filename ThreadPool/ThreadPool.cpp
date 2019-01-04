// ThreadPool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

template<typename T>
class SyncQueue
{
public:
	SyncQueue(int maxSize) :m_maxSize(maxSize), m_needStop(false)
	{

	}
	void Put(const T&x)
	{
		Add(x);
	}
	void Put(T&& x)
	{
		Add(forward<T>(x));
	}

	void Take(list<T>& list)
	{
		unique_lock<mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this] {return m_needStop || NotEmpty(); });

		if (m_needStop)
			return;
		list = move(m_queue);
		m_notFull.notify_one();
	}

	void Take(T& t)
	{
		unique_lock<mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this] {return m_needStop || NotEmpty(); });
		if (m_needStop)
			return;
		t = m_queue.front();
		m_queue.pop_front();
		m_notFull.notify_one();
	}

	void Stop()
	{
		{
			lock_guard<mutex> locker(m_mutex);
			m_needStop = true;
		}
		m_notFull.notify_all();
		m_notEmpty.notify_all();
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
	bool NotFull()const
	{
		bool full = m_queue.size() >= m_maxSize;
		if (full)
			cout << "缓冲区满了，需要等待..." << endl;
		return !full;
	}

	bool NotEmpty()const
	{
		bool empty = m_queue.empty();
		if (empty)
			cout << "缓冲区空了，需要等待...，异步层的线程ID：" << this_thread::get_id() << endl;
		return !empty;
	}

	template<typename F>
	void Add(F&& x)
	{
		unique_lock<mutex> locker(m_mutex);
		m_notFull.wait(locker, [this] {return m_needStop || NotFull(); });
		if (m_needStop)
			return;
		m_queue.push_back(forward<F>(x));
		m_notEmpty.notify_one();
	}
private:
	list<T> m_queue;				//缓冲区
	mutex m_mutex;					//互斥量和条件变量结合超来使用
	condition_variable m_notEmpty;	//不为空的条件变量
	condition_variable m_notFull;	//没有满的条件变量
	int m_maxSize;					//同步队列最大的size
	bool m_needStop;				// 停止的标志
};
int main()
{
    
}


