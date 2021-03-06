
#include "pch.h"
#include <iostream>
#include <utility>
#include <future>
#include <thread>
#include <vector>
using namespace  std;
int func(int x) { return x + 2; }
int main()
{
	packaged_task<int(int)> tsk(func);
	future<int> fut = tsk.get_future(); // 获取future

	thread(move(tsk), 2).detach();		// task作为线程函数
	int value = fut.get();				// 等待task完成并获取结果
	cout << "The result is " << value << ".\n";

	//future是不能复制的，不能放到容器中，需要用shared_future
	vector<shared_future<int>> v;
	shared_future<int> f = async(launch::async, [](int a, int b) {return a + b; }, 2, 3);
	v.push_back(f);
	cout << "The shared_futureresult is " << v[0].get() << endl;
}

