// Bind.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <functional>

using namespace std;

void call_when_even(int x, const function<void(int)>& f)
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

void output_add_2(int x)
{
	cout << x + 2 << " ";
}
int main()
{
	{
		auto fr = bind(output, placeholders::_1);
		for (int i=0;i<10;++i)
		{
			call_when_even(i, fr);
		}
		cout << endl;
	}
	{
		auto fr = bind(output_add_2, placeholders::_1);
		for (int i= 0;i<10;++i)
		{
			call_when_even(i, fr);
		}
		cout << endl;
	}
}

