#pragma once
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace  std;
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
		/*
			1.先创建一个unique_lock获取mutex
			2.通过条件变量m_notEmpty来等待判断式（一个是停止的标志，另一个是不为空的条件）
			当不满足任何一个条件时，条件变量会释放mutex并将线程置于waiting状态，等待其它线程调用
			notify_one/notify_all将其唤醒；
			当满足任一条件时，则继续往下执行后面的逻辑，即将队列中的任务取出，并唤醒一个正处于等待状态的添加
			任务的线程去添加任务。
			3.当处于waiting状态的线程被notify_one或notify_all唤醒时，条件变量会先重新获取mutex,然后再检查条件是否
			满足，如果满足，则往下执行，如果不满足，则释放mutex继续等待
		*/
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