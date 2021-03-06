
#include "pch.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;

int main()
{
	/*
		move 是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存拷贝。
		move 实际上并不能移动任何东西，它唯一的功能是将一个左值强制转换成一个右值引用，使我们可以
		通过右值引用使用该值，以用于移动语义。	 
	 */
	{
		// 存在拷贝,拷贝的代价很大，性能较低
		list<string> tokens;	
		list<string> t = tokens; 
	}
	{
		// 使用move几乎没有任何代价，只是转换了资源的所有权
		// 实际上是将左值变成右值引用，然后应用move语义调用构造函数，就避免了拷贝，提高了程序性能。
		// 将一个对象内部有较大的堆内存或者动态数组时，很有必要写move语义的拷贝构造函数和赋值函数，避免无谓的深拷贝
		list<string> tokens;
		list<string> t = move(tokens);
	}


}