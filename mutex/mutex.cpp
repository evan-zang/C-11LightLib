
#include "pch.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
mutex g_lock;
void func()
{
	//lock_guard<mutex> locker(g_lock); //出作用域之后自动解锁
	g_lock.lock();
	cout << "entered thread " << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "leaving thread " << this_thread::get_id() << endl;
	g_lock.unlock();

}
int main()
{
	/*
		1)mutex:独占的互斥量，不能递归使用
		2)time_mutex:带超时的独占互斥量，不能递归使用
		3)recursive_mutex:递归互斥量，不带超时功能
		4)recursive_timed_mutex:带超时的递归互斥量	
	*/
	{
		thread t1(func);
		thread t2(func);
		thread t3(func);
		thread t4(func);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}

	{
		//recursive_mutext的基本用法
		struct Complex
		{
			recursive_mutex mutex;
			int i;
			Complex() :i(0)
			{}
				void mul(int x) {
					lock_guard<recursive_mutex> lock(mutex);
					i *= x;
				}
				void div(int x) {
					lock_guard<recursive_mutex> lock(mutex);
					i /= x;
				}
				void both(int x, int y) {
					lock_guard<recursive_mutex> lock(mutex);
					mul(x);
					div(y);
				}
			
		};

		Complex complex;
		complex.both(32, 23);	//因为同一线程可以多次获取同一互斥量，不会发生死锁

		//尽量不要使用递归锁
		//1)需要用到递归锁定的多线程互斥处理往往本身就是可以简化的，允许递归互斥很容易放纵复杂逻辑的产生，从面导致一些
		//	多线程同步引起的晦涩问题
		//2)递归锁比非递归锁，效率会低一些
		//3)递归锁虽然允许同一个线程多次获得同一个互斥量，可重复获得的最大次数并未具体说明，一旦超过一定次数，再对lock进行调用
		//	就会抛出system错误
	}
}

