// Visitor.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

template<typename... Types>
struct Visitor;

template<typename T,typename... Types>
struct Visitor<T, Types...> :Visitor<Types...>
{
	// 通过using 避免隐藏基类的Visit同名方法
	using Visitor<Types...>::Visit;
	virtual void Visit(const T&) = 0;
};

template<typename T>
struct Visitor<T>
{
	virtual void Visit(const T&) = 0;
};

struct stA;
struct stB;

struct Base
{
	// 定义通用的访问者类型，它可以访问stA和stB
	typedef Visitor<stA, stB> MyVisitor;
	virtual void Accept(MyVisitor&) = 0;
};

struct stA :Base
{
	double val;
	void Accept(Base::MyVisitor& v)
	{
		v.Visit(*this);
	}
};

struct stB :Base 
{
	int val;
	void Accept(Base::MyVisitor&v)
	{
		v.Visit(*this);
	}
};

struct PrintVisitor :Base::MyVisitor
{
	void Visit(const stA& a)
	{
		cout << "from stA: " << a.val << endl;
	}
	void Visit(const stB& b)
	{
		cout << "from stB: " << b.val << endl;
	}
};
int main()
{
	PrintVisitor vis;
	stA a;
	a.val = 8.97;
	stB b;
	b.val = 8;
	Base* base = &a;
	base->Accept(vis);
	base = &b;
	base->Accept(vis);
}


