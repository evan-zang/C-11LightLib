
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
	cout << boolalpha;
	cout << "is_const:" << endl;
	cout << "int:" << is_const<int>::value << endl;
	cout << "const int:" << is_const<const int>::value << endl;
	cout << "const int&:" << is_const<const int&>::value << endl;
	cout << "const int*:" << is_const<const int*>::value << endl;
	{
		// is_same用法
		cout << "is_same:" << endl;
		cout << is_same<int, int>::value << endl;
		cout << is_same<int, unsigned int>::value << endl;
		cout << is_same<int, signed int>::value << endl;
	}

	{
		// is_base_of 是否为继承关系
		class A {};
		class B :A {};
		class C{};

		cout << "is_base_of:" << endl;
		cout << is_base_of<A, B>::value << endl;
		cout << is_base_of<B, A>::value << endl;
		cout << is_base_of<C, B>::value << endl;
	}
}
