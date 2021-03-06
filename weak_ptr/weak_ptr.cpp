
#include "pch.h"
#include <iostream>

using namespace std;

weak_ptr<int> gw;
void f()
{
	if (gw.expired())
	{
		cout << "gw is expired\n";
	}
	else
	{
		auto spt = gw.lock();
		cout << *spt << endl;
	}
}
int main()
{
   /*
	弱引用指针weak_ptr是用来监视shared_ptr的，不会使引用计数加1，,它不管理shared_ptr内部的指针，
	主要是为了监视shared_ptr的生命周期，更像是shared_ptr的一个助手。
	纯粹只是作为一个旁观者来监视shared_ptr中管理的资源是否存在。	
   */
	//1.基本用法
	//1)通过use_count()方法来获得当前观测资源的引用计数
	{
		shared_ptr<int> sp(new int(10));
		weak_ptr<int> sw(sp);
		cout << sw.use_count() << endl;
	}
	//2)通过expired()方法来判断所观测的资源是否已经释放
	{
		shared_ptr<int> sp(new int(10));
		weak_ptr<int> wp(sp);
		if (wp.expired())
		{
			cout << "weak_ptr无效\n";
		}
		else
		{
			cout << "weak_ptr有效\n";
		}
				
	}
	//3)通过lock方法来获取所监视的shared_ptr
	{
		auto sp = make_shared<int>(42);
		gw = sp;
		f();
	}
	f();

	//2.weak_ptr返回this指针
	{
		struct A :public enable_shared_from_this<A>
		{
			shared_ptr<A> GetSelf()
			{
				return shared_from_this();
			}
			~A()
			{
				cout << "A is deleted" << endl;
			}
		};

		shared_ptr<A> spy(new A);
		shared_ptr<A> p = spy->GetSelf(); // OK
	}
	//3.weak_ptr解决循环引用问题
	{
		cout << "--------------------" << endl;
		struct A;
		struct B;
		struct A {
			shared_ptr<B> bptr;
			~A() {
				cout << "A is deleted!" << endl;
			}
		};

		struct B {
			weak_ptr<A> aptr;
			~B() {
				cout << "B is deleted!" << endl;
			}
		};

		{

			shared_ptr<A> ap(new A);
			shared_ptr<B> bp(new B);
			ap->bptr = bp;
			bp->aptr = ap;
		}
	}
}
