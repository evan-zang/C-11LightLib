// AOP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "AOP.h"
#include <functional>


using namespace std;

struct AA
{
	void Before(int i)
	{
		cout << "Before from AA " << i << endl;
	}
	void After(int i)
	{
		cout << "After from AA " << i << endl;
	}
};

struct BB
{
	void Before(int i)
	{
		cout << "Before from BB " << i << endl;
	}
	void After(int i)
	{
		cout << "After from BB " << i << endl;
	}
};

struct CC
{
	void Before()
	{
		cout << "Before from CC "  << endl;
	}
	void After()
	{
		cout << "After from CC "  << endl;
	}
};

struct DD
{
	void Before()
	{
		cout << "Before from DD "<< endl;
	}
	void After()
	{
		cout << "After from DD " << endl;
	}
};

void GT()
{
	cout << "real GT function" << endl;
}

void HT(int a)
{
	cout << "real HT function: " << a<<endl;
}
int main()
{
   //织入普通函数 
	function<void(int)> f = bind(&HT, placeholders::_1);
	Invoke<AA, BB>(function<void(int)>(bind(&HT,placeholders::_1)),1);
	// 组合了两个切面AA,BB
	Invoke<AA, BB>(f, 1);

	// 织入普通函数
	Invoke<CC, DD>(&GT);
	Invoke<AA, BB>(&HT, 1);
	// 织入lambda表达式
	Invoke<AA, BB>([](int i) {},1);
	Invoke<CC, DD>([] {});
}

