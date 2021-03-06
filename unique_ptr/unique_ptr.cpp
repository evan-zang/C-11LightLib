
#include "pch.h"
#include <iostream>

using namespace std;

struct MyDeleter
{
	void operator()(int* p)
	{
		cout << "delete" << endl;
		delete p;
	}

};
int main()
{
	/*
		unique_ptr 是一个独占型的智能指针，它不允许其他的智能指针共享其内部的指针，不允许通过
		赋值将一个unique_ptr赋值给另外一个unique_ptr
	
	*/
	{
		// unique_ptr<int> myPtr(new int);
		// unique_ptr<int> myOtherPtr = myPtr;	//错误，不能复制

		//unique_ptr不允许复制，但可以通过函数返回给其他的unique_ptr,还可以通过move来转移到其他的
		//unique_ptr,这样本身就不再拥有原来指针的所有权了
		unique_ptr<int> myPtr(new int); //OK
		unique_ptr<int> myOtherPtr = move(myPtr); //OK
		// unique_ptr<int> ptr = myPtr;		//错误，只能移动，不可复制
	}
	unique_ptr<int, MyDeleter> p(new int(1));
	return 0;
}

