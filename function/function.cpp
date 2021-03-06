// function.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <functional>


using namespace std;

void func(void)
{
	cout << __FUNCTION__ << endl;
}

class Foo
{
public:
	static int foo_func(int a)
	{
		cout << __FUNCTION__ << "(" << a << ") ->: ";
		return a;
	}
};

class Bar
{
public:
	int operator()(int a)
	{
		cout << __FUNCTION__ << "(" << a << ") ->: ";
		return a;
	}
};

class A {
	function<void()> callback_;

public:
	A(const function<void()>& f):callback_(f){}
	void notify(void) {
		callback_();
	}
};

class FooA {
public:
	void operator()(void)
	{
		cout << __FUNCTION__ << endl;
	}
};

void call_when_even(int x, const function<void(int)>&f)
{
	if (!(x&1))
	{
		f(x);
	}
}
void output(int x)
{
	cout << x << " ";
}
int main()
{
	function<void(void)> fr1 = func;	//bind a common function
	fr1();

	// bind a static function
	function<int(int)> fr2 = Foo::foo_func;
	cout << fr2(123) << endl;

	// bind a functor
	Bar bar;
	fr2 = bar;
	cout << fr2(123) << endl;


	//1.function as callback
	FooA fooA;
	A aa(fooA);
	aa.notify();
	//2. function as function parameters
	for (int i = 0;i<10;++i)
	{
		call_when_even(i, output);
	}
	cout << endl;

}
