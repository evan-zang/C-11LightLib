
#include "pch.h"
#include <string>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<thread> g_list;
vector<shared_ptr<thread>> g_list2;
void func()
{
	//cout << "test"<<endl;
	//线程休眠
	this_thread::sleep_for(chrono::seconds(3));
	cout << "time out " << "test" << endl;
}

void func1(int i ,double d ,string&& s)
{
	cout << i << ", " << d << ", " << s << endl;
}

void CreateThread()
{
	thread t(func);
	g_list.push_back(move(t));
	g_list2.push_back(make_shared<thread>(func));
}
int main()
{
   /*
	线程的创建
   */
	{
		thread t(func);
		t.join();			//join函数将会阻塞线程，直到线程函数执行结束		
	}

	{
		thread t1(func);
		t1.detach();			//线程和线程对象分离了，让线程作为后台线程去执行，当前线程也不会阻塞了
	}

	{
		//线程还可以接收任意个数的参数
		thread t2(func1, 1, 2.0, "test");
		t2.join();
	}
	{
		// 线程不能被复制，但可以移动
		// 需要保证线程函数的生命周期在线程变量thread生命周期之内
		thread t(func);
		thread t1(move(t));
		//t.join();	//线程被移动之后，线程对象t将不再代表任何线程了
		t1.join();
	}
	{
		CreateThread();
		for (auto& thread:g_list)
		{
			thread.join();
		}
		for (auto& thread:g_list2)
		{
			thread->join();
		}
	}
	{
		// 线程的基本用法
		thread t(func);
		// 获取当前线程的 ID 
		cout << t.get_id() << endl; 
		// 获取CPU核数，如果获取失败则返回0
		cout << thread::hardware_concurrency() << endl;
	}
}

