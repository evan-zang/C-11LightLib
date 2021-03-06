// for.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

void do_count(int n)
{
	cout << n << endl;
}

vector<int> g_arr{ 1,2,3,4,5 };
vector<int>& get_range(void)
{
	cout << "get_range ->: " << endl;
	return g_arr;
}
int main()
{
	//
	vector<int> arr{};
	// 1.for 
	for (auto it = arr.begin();it != arr.end();++it)
	{
		cout << *it << endl;
	}
	// 2.for_each
	for_each(arr.begin(), arr.end(), do_count);

	// 3.for:base on range,read only
	for (auto n:arr)
	{
		cout << n << endl;
	}

	// 4.for:base on range,if you want to change the element value
	for (auto& n:arr)
	{
		cout << n++ << endl;
	}

	// 5.details
	map<string, int> mm = { {"1",1}, {"2",2},{"3",3} };
	for (auto& val:mm)
	{		
		cout <<val.first<<" -> "<< val.second << endl;
	}
	// 6.samples get_range() will just be invoke once in the first time
	for (auto val:get_range())
	{
		cout << val << endl;
	}
	return 0;
}

