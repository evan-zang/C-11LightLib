// timer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Timer
{
public:
	Timer():m_begin(high_resolution_clock::now()){}
	void reset() { m_begin = high_resolution_clock::now(); }

	// 默认输出毫秒
	template<typename Duration=microseconds>
	int64_t elapsed() const
	{
		return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
	}
	// 微秒
	int64_t elapsed_micro() const
	{
		return elapsed<microseconds>();
	}
	// 纳秒
	int64_t elapsed_nano()const
	{
		return elapsed<nanoseconds>();
	}

	// 秒
	int64_t elapsed_seconds()const
	{
		return elapsed<seconds>();
	}

	int64_t elapsed_minutes()const
	{
		return elapsed<minutes>();
	}

	int64_t elasped_hours()const
	{
		return elapsed<hours>();
	}

private:
	time_point<high_resolution_clock> m_begin;
};
void fun()
{
	cout << "hello word" << endl;
}
int main()
{
	Timer t;
	fun();
	
	cout << t.elapsed() <<endl;
	cout << t.elapsed_micro() << endl;
	cout << t.elapsed_nano() << endl;
	cout << t.elapsed_seconds() << endl;
	cout << t.elapsed_minutes() << endl;
	cout << t.elasped_hours() << endl;

}
