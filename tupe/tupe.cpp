
#include "pch.h"
#include <iostream>
#include <tuple>
#include <string>
using namespace  std;


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
}
