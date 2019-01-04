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
			1.�ȴ���һ��unique_lock��ȡmutex
			2.ͨ����������m_notEmpty���ȴ��ж�ʽ��һ����ֹͣ�ı�־����һ���ǲ�Ϊ�յ�������
			���������κ�һ������ʱ�������������ͷ�mutex�����߳�����waiting״̬���ȴ������̵߳���
			notify_one/notify_all���份�ѣ�
			��������һ����ʱ�����������ִ�к�����߼������������е�����ȡ����������һ�������ڵȴ�״̬�����
			������߳�ȥ�������
			3.������waiting״̬���̱߳�notify_one��notify_all����ʱ�����������������»�ȡmutex,Ȼ���ټ�������Ƿ�
			���㣬������㣬������ִ�У���������㣬���ͷ�mutex�����ȴ�
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
			cout << "���������ˣ���Ҫ�ȴ�..." << endl;
		return !full;
	}

	bool NotEmpty()const
	{
		bool empty = m_queue.empty();
		if (empty)
			cout << "���������ˣ���Ҫ�ȴ�...���첽����߳�ID��" << this_thread::get_id() << endl;
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
	list<T> m_queue;				//������
	mutex m_mutex;					//������������������ϳ���ʹ��
	condition_variable m_notEmpty;	//��Ϊ�յ���������
	condition_variable m_notFull;	//û��������������
	int m_maxSize;					//ͬ����������size
	bool m_needStop;				// ֹͣ�ı�־
};