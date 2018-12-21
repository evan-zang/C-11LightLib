// decltype.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

class Foo 
{
public:
	static const int Number = 0;
	int x;
};
int main()
{
   // grammar
   // decltype(exp),it deduce the type in compiling time
	int x = 0;
	decltype(x) y = 1;			// y==>int
	decltype(x + y) z = 0;		// z==>int

	const int& i = x;
	decltype(i) j = y;			// j==>const int&

	const decltype(z)* p = &z;	// *p==>const int,p==>const int*
	decltype(z)*pi = &z;		// *pi==>int	,pi==>int*
	decltype(pi)*pp = &pi;		// *pp==>int*   ,pp==>int**

	//rules
	//1.exp is identify、class access expression,the decltype(exp) is same as exp type
	//2.exp is a function invoke,decltype(exp) type is same as return type
	//3.other situation if exp is a left value,the decltype(exp) is exp type left reference,otherwise,same sa exp type

	int n = 0;
	volatile const int & x = n;
	decltype(n) a = n;			// a==>int
	decltype(x) b = n;			// b==>const volatile int &
	decltype(Foo::Number) c = 0;// c==>const int

	Foo foo;
	decltype(foo.x) d = 0;		// d==>int, class access expresion
}
