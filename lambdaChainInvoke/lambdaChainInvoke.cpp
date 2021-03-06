#include "pch.h"
#include <iostream>
#include <functional>
#include <type_traits>

using namespace std;

template<typename T>
class Task;

template<typename R,typename... Args>
class Task<R(Args...)>
{
public:
	Task(function<R(Args...)>&&f):m_fn(move(f)) {}
	Task(function<R(Args...)>&f):m_fn(f) {}

	R Run(Args&&...args)
	{
		return m_fn(forward<Args>(args)...); //完美转发
	}

	// 连续调用新的函数，将函数不断地串联起来
	template<typename F>
	auto Then(F&& f)->Task<typename result_of<F(R)>::type(Args...)>
	{
		// result_of 获取F的返回类型
		using return_type = typename result_of<F(R)>::type;

		auto func = move(m_fn);
		return Task<return_type(Args...)>([func, &f](Args&&... args) {
			//将前一个函数的输出作为后一个函数的输入
			return f(func(forward<Args>(args)...));
		});
	}
private:
	function<R(Args...)>m_fn;
};
int main()
{
	Task<int(int)> task([](int i) {return i; });
	auto result = task.Then([](int i) {return i + 1; }).Then([](int i) {return i + 2; }).Then([](int i) {return i + 3; }).Run(1);
	cout << result << endl;
}


