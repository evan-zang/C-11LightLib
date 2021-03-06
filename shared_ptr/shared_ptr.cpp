
#include "pch.h"
#include <iostream>

using namespace  std;

void DeleteIntPtr(int* p)
{
	delete p;
}
int main()
{
	/*
		shared_ptr 共享智能指针,使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。
		在最后一个shared_ptr析构的时候，内存才会被释放。			
	*/
	//1.初始化
	shared_ptr<int> p(new int(1));
	shared_ptr<int> p2 = p;
	shared_ptr<int> ptr;
	ptr.reset(new int(1));

	if (ptr)
	{
		cout << "ptr is not null";
	}
	// 不能将一个原始指针直接赋值给一个智能指针，尽量用make_shared来构造智能指针，因为它更加高效
	// shared_ptr<int> p = new int(1); // error
	//2.获取原始指针
	{
		shared_ptr<int> ptr(new int(1));
		int* p = ptr.get();
	}
	//3.指定删除器
	{
		shared_ptr<int> p(new int(1), DeleteIntPtr);
		// lambda表达式写法
		shared_ptr<int> pt(new int, [](int* p) {delete p; });
	}
	//4.注意问题
	{
		//1)不要用一个原始指针初始化多个shared_ptr
		{
			int* ptr = new int;
			shared_ptr<int> p1(ptr);
			shared_ptr<int> p2(ptr); // logic error
		}
		//2) 不要在函数实参中创建share_ptr
		// function (shared_ptr<int>(new int),g()); //有缺陷
		// 正确写法
		// shared_ptr<int> p(new int());
		// f(p, g());
		//3)通过shared_from_this() 返回this指针。不要将this指针作为shared_ptr 返回出来，因为this指针本质上是一个裸指针，因此，这样可能会导致重复析构
		{
			struct A {
				shared_ptr<A>GetSelf()
				{
					// return shared_ptr<S>(this); //don't do this!
				}
			};

		}

		//4)避免循环引用。智能指针最大的一个陷阱就是循环引用，循环引用会导致内存泄露
		{
			struct A;
			struct B;

			struct A {
				shared_ptr<B> bptr;
				~A()
				{
					cout << "A is deleted!" << endl;
				}
			};

			struct B
			{
				 shared_ptr<A> aptr;
				 ~B() { cout << "B is deleted!" << endl; }
			};

			shared_ptr<A> ap(new A);
			shared_ptr<B> bp(new B);
			ap->bptr = bp;
			bp->aptr = ap;		// objects should be destroyed.

		}
	
	}
}

