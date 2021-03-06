// chrono.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <typeinfo>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;
void fun()
{
	cout << "hello word" << endl;
}
int main()
{
	chrono::microseconds ms{ 3 };
	chrono::microseconds us = 2 * ms;
	chrono::duration<double, ratio<1, 30>> hz30{ 3.5 };

	cout << "2 ms duration has " << ms.count() << " ticks\n" << "6000 us duration has " << us.count() << " ticks\n";
	{
		chrono::duration<double, ratio<9, 7>>d1(3);
		chrono::duration<double, ratio<6, 5>> d2(1);
		auto d3 = d1 - d2;
		cout << typeid(d3).name() << endl;
		cout << d3.count() << endl;
	}
	{
		typedef chrono::duration<int, ratio<60 * 60 * 24>> days_type;
		chrono::time_point<chrono::system_clock, days_type> today = chrono::time_point_cast<days_type>(chrono::system_clock::now());
		cout << today.time_since_epoch().count() << " days since epoch" << endl;
	}
	{
		chrono::system_clock::time_point t1 = chrono::system_clock::now();
		cout << "Hello world\n";
		chrono::system_clock::time_point t2 = chrono::system_clock::now();
		cout << (t2 - t2).count() << " tick count" << endl;
	}
	{
		auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
		cout << put_time(localtime(&t), "%Y-%m-%d %X") << endl;
		cout << put_time(localtime(&t), "%Y-%m-%d %H.%M.%S") << endl;
	}
	{
		
	}
}


