
#include "pch.h"
#include <iostream>
#include <tuple>
#include <string>
using namespace  std;

typedef std::tuple<int, double, int, double> Mytuple;
int main()
{
	{
		// tupe:是一个固定大小的不同类型值的集合，泛化的std::pair
		// tuple<const char*,int> tp = make_tuple(sendPack,nSendSize); 
		// 等价于 struct A{ char* p;int len;};

	}
	{
		tuple<int, string, float> t1(10, "Test", 3.14);
		int n = 7;
		auto t2 = tuple_cat(t1, make_pair("Foo", "bar"), t1, tie(n));
	}

	{
		Mytuple c0(0, 1, 2, 3);

		// display contents " 0 1 2 3" 
		std::cout << " " << std::get<0>(c0);
		std::cout << " " << std::get<1>(c0);
		std::cout << " " << std::get<2>(c0);
		std::cout << " " << std::get<3>(c0);
		std::cout << std::endl;

		int v4 = 4;
		double v5 = 5;
		int v6 = 6;
		double v7 = 7;
		std::tie(v4, v5, v6, v7) = c0;

		// display contents " 0 1 2 3" 
		std::cout << " " << v4;
		std::cout << " " << v5;
		std::cout << " " << v6;
		std::cout << " " << v7;
		std::cout << std::endl;

		return (0);
	}
}
