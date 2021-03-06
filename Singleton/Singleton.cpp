// Singleton.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Singleton 
{
public:
	template<typename... Args>
	static T* Instance(Args&&... args)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T(forward<Args>(args)...);
		return m_pInstance;
	}

	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			throw::logic_error("the instance is not init,please initialize the instance first");
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	Singleton(void);
	virtual ~Singleton(void);
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
private:
	static T* m_pInstance;
};
template<class T> T* Singleton<T>::m_pInstance = nullptr;

struct A
{
	A(const string&) { cout << "lvalue" << endl; }
	A(string&& x) { cout << "rvalue" << endl; }
};

struct B
{
	B(const string&) { cout << "lvalue" << endl; }
	B(string&& x) { cout << "rvalue" << endl; }
};

struct C
{
	C(int x, double y) {}
	void Fun() { cout << "test" << endl; }
};
int main()
{
	string str = "bb";
	// 创建A类型的单例
	Singleton<A>::Instance(str);
	// 创建B类型的单例，临时变量str被move之后变成右值，然后可以根据移动语义来避免复制
	Singleton<B>::Instance(move(str));
	// 创建C类型的单例，含两个参数
	Singleton<C>::Instance(1, 3.14);
	// 获取单例并调用单例对象的方法
	Singleton<C>::GetInstance()->Fun();
	// 释放单例
	Singleton<A>::DestroyInstance();
	Singleton<B>::DestroyInstance();
	Singleton<C>::DestroyInstance();
}
