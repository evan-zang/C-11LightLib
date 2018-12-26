
#include "pch.h"
#include <iostream>
#include <type_traits>

using namespace std;
int main()
{
	/*
		判断类型的traits通过字面意思就能知道其含义,都是派生于integral_constant,
		因此可以通过is_xxx::value是否为true来判断模板类型是否为目标类型
	*/
	cout << "is_const:" << endl;
	cout << "int:" << is_const<int>::value << endl;
	cout << "const int:" << is_const<const int>::value << endl;
	cout << "const int&:" << is_const<const int&>::value << endl;
	cout << "const int*:" << is_const<const int*>::value << endl;

}
