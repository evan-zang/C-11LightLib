// Command.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <functional>
#include <type_traits>

using namespace std;
template<typename R=void>
struct CommCommand
{
private:
	function<R()> m_f;

public:
	// 接受可调用对象的函数包装器
	template<class F,class...Args,class=typename enable_if<!is_member_function_pointer<F>::value>::type>
	void Wrap(F&& f, Args&& ... args)
	{
		m_f = [&] {return f(args...); };
	}

	// 接受常量成员函数的函数包装器
	template<class R,class C,class...DArgs,class P,class... Args>
	void Wrap(R(C::*f)(DArgs...)const,P&& p,Args&&...args)
	{
		m_f = [&, f] {return (*p.*f)(args...); };
	}
	// 接受非常量成员函数的函数包装器
	template<class R,class C,class... DArgs,class P,class...Args>
	void Wrap(R(C::*f)(DArgs...), P && p,Args && ...args)
	{
		m_f = [&, f] {return (*p.*f)(args...); };
	}

	R Execute()
	{
		return m_f();
	}
};

struct STA
{
	int m_a;
	int operator()() { return m_a; }
	int operator()(int n) { return m_a + n; }
	int triple0() { return m_a * 3; }
	int triple(int a) { return m_a * 3 + a; }
	int triple1()const { return m_a * 3; }
	const int triple2(int a)const { return m_a * 3 + a; }
	void triple3() { cout << "" << endl; }
};

int add_one(int n)
{
	return n + 1;
}

int main()
{
	CommCommand<int> cmd;
	// 接受普通函数
	cmd.Wrap(add_one, 0);
	auto r =  cmd.Execute();
	cout << r << endl;
	// 接受lambda表达式
	cmd.Wrap([](int n) {return n + 1; }, 1);
	auto r1 = cmd.Execute();
	cout << r1 << endl;

	STA t{ 10 };
	int x{ 3 };

	// 接受成员函数
	cmd.Wrap(&STA::triple0, &t);
	auto r2 = cmd.Execute();
	cout << r2 << endl;

	cmd.Wrap(&STA::triple, &t,x);
	auto r3 = cmd.Execute();
	cout << r3 << endl;

	cmd.Wrap(&STA::triple, &t, 3);
	auto r4 = cmd.Execute();
	cout << r4 << endl;


	cmd.Wrap(&STA::triple2, &t, 3);
	auto r5 = cmd.Execute();
	cout << r5 << endl;
}

