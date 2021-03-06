// ThreadPool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "ThreadPool.h"
#include <thread>

using namespace std;
int main()
{
	ThreadPool pool{2};
	thread thd1([&pool] {
		for (int i = 0;i<10;i++)
		{
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId]
			{
				cout << "同步线程1的线程ID： " << thdId << endl;
			});
		}
	});

	thread thd2([&pool] {
		for (int i = 0;i<10;i++)
		{
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId] {
				cout << "同步线程2的线程ID：" << thdId << endl;
			});
		}
	});

	this_thread::sleep_for(chrono::seconds(2));
	getchar();
	pool.Stop();
	thd1.join();
	thd2.join();
}


