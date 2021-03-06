// any_of.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace  std;

int main()
{	
	vector<int> v{ 1,3,5,7,9 };
	auto isEven = [](int i) {return i % 2 != 0; };
	bool isallOdd = all_of(v.begin(), v.end(), isEven);
	if (isallOdd)
		cout << "all is odd" << endl;
	bool isNoneEven = none_of(v.begin(), v.end(), isEven);
	if (isNoneEven)
		cout << "none is even" << endl;

	vector<int> v1{ 1,3,5,7,8,9 };
	bool anyof = any_of(v1.begin(), v1.end(), isEven);
	if (anyof)
		cout << "at least one is Even" << endl;
}

