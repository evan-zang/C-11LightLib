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

int& func_int_r(void);		
int&& func_int_rr(void);	
int func_int(void);

const int& func_cint_r(void);
const int&& func_cint_rr(void);
const int func_cint(void);

const Foo func_cfoo(void); 

template <class ContainerT>
class Sample
{
	decltype(ContainerT().begin()) it_;
public:
	void func(ContainerT& container)
	{
		it_ = container.begin();
	}
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
	

	int n = 0;
	volatile const int & xx = n;
	decltype(n) a = n;			// a==>int
	decltype(xx) b = n;			// b==>const volatile int &
	decltype(Foo::Number) c = 0;// c==>const int

	Foo foo;
	decltype(foo.x) d = 0;		// d==>int, class access expresion

	//2.exp is a function invoke,decltype(exp) type is same as return type
	int xxx = 0;
	decltype(func_int_r()) a1 = xxx;	// a1==>int&
	decltype(func_int_rr()) b1 = 0;		// b1==>int&&
	decltype(func_int())	c1 = 0;		// c1==>int

	decltype(func_cint_r()) a2 = x;		// a2==>const int &
	decltype(func_cint_rr()) b2 = 0;	// b2==>const int&&
	decltype(func_cint())	 c2 = 0;	// c2==>int 

	decltype(func_cfoo())	ff = Foo();
	//3.other situation if exp is a left value,the decltype(exp) is exp type left reference,otherwise,same as exp type
	struct Test
	{
		int x;
	};
	const Test test = Test();
	decltype(test.x) mm = 0;		// m==>int
	decltype((test.x)) nn = mm;     // n==>const int &

	{
		int n = 0, m = 0;
		decltype(n + m) c = 0;		// c==>int
		decltype(n += m)  d = c;	// d==>int&
	}
}

/*
int& func_int_r(void) {
	
}
int&& func_int_rr(void) {
	
}
int func_int(void) {}

const int& func_cint_r(void) {}
const int&& func_cint_rr(void) {}
const int func_cint(void) {}

const Foo func_cfoo(void) {}

*/