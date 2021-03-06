// Observer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	// 禁用复制构造
	NonCopyable(const NonCopyable&) = delete;
	// 禁用赋值构造
	NonCopyable& operator = (const NonCopyable&) = delete;
};

template<typename Func>
class Events :NonCopyable
{
public:
	Events() {}
	~Events() {}
	// 注册观察者，支持右值引用
	int Connect(Func&& f)
	{
		return Assign(f);
	}

	//  注册观察者
	int Connect(const Func&f)
	{
		return Assign(f);
	}
	// 移除观察者
	void Disconnect(int key)
	{
		m_connections.erase(key);
	}

	// 通知所有观察者
	template<typename... Args>
	void Notify(Args&&... args)
	{
		for (auto& it:m_connections)
		{
			it.second(forward<Args>(args)...);
		}
	}
private:
	//保存观察者并分配观察者的编号 
	template<typename F>
	int Assign(F&& f)
	{
		int k = m_observerId++;
		m_connections.emplace(k, forward<F>(f));
		return k;
	}
	// 观察者对应的编号
	int m_observerId = 0;
	// 观察者列表
	map<int, Func> m_connections;
};

struct stA
{
	int a, b;
	void print(int a, int b) { cout << a << ", " << b << endl; }
};

void print(int a, int b) { cout << a << ", " << b << endl; }
int main()
{
	Events<function<void(int, int)>> myevent;
	// 以函数方式注册观察者
	auto key = myevent.Connect(print);

	stA t;
	// lamda注册function注册
	auto lambdakey = myevent.Connect([&t](int a, int b) {t.a = a; t.b = b; });
	function<void(int, int)> f = bind(&stA::print, &t, placeholders::_1, placeholders::_2);
	myevent.Connect(f);
	int a = 1,  b = 2;
	myevent.Notify(a, b);

	myevent.Disconnect(key);
}
