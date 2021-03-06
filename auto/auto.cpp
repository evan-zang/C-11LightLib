// auto.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;
class Foo
{
public :
	static int get(void)
	{
		return 0;
	}
};

class Bar 
{
public:
	static const char* get(void)
	{
		return "0";
	}
};

template <class A>
void func(void)
{
	auto val = A::get();

}
int main()
{
	auto  x = 5;					// OK: x==> int 
	auto pi = new auto(1);			// OK: pi==>int*
	const auto *v = &x, u = 6;		//OK: v ==>const int* ,u==>const int 
	static auto y = 0.0;			//OK: y ==>double
	// auto int r ; error
	// auto s; error

	int xx = 0;
	auto* a = &xx;	//a==>int*,auto==>int
	auto b = &xx;	//b==>int*,auto==>int*
	auto &c = xx;	//c==>int&,auto==>int
	auto d = c;		//d==>int,auto==>int

	const auto e = xx;	//e==>const int 
	auto f = e;			//f==>int

	const auto& g = xx;		//g==>const int&
	auto& h = g;			//f==>const int&
	//auto limits
	//1.can't be a parameter of a function
	//2.can't be used in a non-static variable member
	//3.can't define an array
	//4.can't infer the template's parameter

	// stl container example
	/*
	map<double, double> resMap;
	map<double, double>::iterator it = resMap.begin();
	for (;it != resMap.end();++it)
	{
	}
	*/
	map<double, double>resMap;
	for (auto it=resMap.begin();it != resMap.end();++it)
	{
	}
	/*
	unordered_multimap<int, int>resultMap;
	unordered_multimap<int, int>::iterator range = resultMap.equal_range(key);
	*/
	unordered_multimap<int, int>map;
	//auto range = map.equal_range(key);
	// a new sample auto simple the function
	func<Foo>();
	func<Bar>();
	return 0;
}
