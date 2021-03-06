// IOC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "IOC.h"

using namespace std;

struct IX
{
	virtual void g() {}
	virtual~IX() {}
};

class X :public IX
{
public:
	void g()
	{
		cout << "it is a test in x" << endl;
	}
};

class Y :public IX
{
	public:	
		void g()
		{
			cout << "it is a test in y "  << endl;
		}
	
};

struct MyStructA
{
	MyStructA(IX* x) :m_x(x) {}
	
	~MyStructA()
	{
		if (m_x != nullptr)
		{
			delete m_x;
			m_x = nullptr;
		}
	}
	void Fun() { m_x->g(); }

private:
	IX* m_x;
};

int main()
{
	{
		MyStructA *pa = new MyStructA(new X()); //直接创建依赖对象
		pa->Fun();
		delete pa;
	}
	IocContainer ioc;
	ioc.RegisterType<MyStructA, X>("A"); //配置依赖关系
	// 通过Ioc容器去创建目标对象及其依赖的对象
	shared_ptr<MyStructA> pb = ioc.ResolveShared<MyStructA>("A");
	pb->Fun();

	ioc.RegisterType<MyStructA, Y>("A1");
	auto pc = ioc.ResolveShared<MyStructA>("A1");
	pc->Fun();

}


