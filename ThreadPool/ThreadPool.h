#pragma once
#include <list>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include "SyncQueue.h"

using namespace std;

const int MaxTaskCount = 100;
class ThreadPool
{
public:
	using Task = function<void()>;
	ThreadPool(int numThreads = thread::hardware_concurrency()) :m_queue(MaxTaskCount)
	{
		Start(numThreads);
	}
	~ThreadPool()
	{
		// ���û��ֹͣʱ������ֹͣ�̳߳�
		Stop();
	}

	void Stop()
	{
		// ��֤���߳������ֻ����һ��StopThreadGroup
		call_once(m_flag, [this] {StopThreadGroup(); });
	}

	void AddTask(Task&& task)
	{
		m_queue.Put(forward<Task>(task));
	}

	void AddTask(const Task& task)
	{
		m_queue.Put(task);
	}
private:
	void Start(int numThreads)
	{
		m_running = true;
		// �����߳���
		for (int i =0;i<numThreads;++i)
		{
			m_threadgroup.push_back(make_shared<thread>(&ThreadPool::RunInThread, this));
		}
	}

	void RunInThread()
	{
		while (m_running)
		{
			// ȡ����ֱ�ִ��
			list<Task> list;
			m_queue.Take(list);
			for (auto& task:list)
			{
				if (!m_running)
					return;
				task();
			}
		}
	}
	void StopThreadGroup()
	{
		m_queue.Stop();		//��ͬ�������е��߳�ֹͣ 
		m_running = false;	//��Ϊfalse,���ڲ��߳�����ѭ�����˳�
		for (auto thread:m_threadgroup)		//�ȴ��߳̽���
		{
			if (thread)
			{
				thread->join();
			}			
		}
		m_threadgroup.clear();
	}

private:
	list<shared_ptr<thread>> m_threadgroup; //����������߳���
	SyncQueue<Task> m_queue;				//ͬ������
	atomic_bool m_running;					// �Ƿ�ֹͣ�ı�־
	once_flag m_flag;
};